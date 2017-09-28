#include "scenetree.hpp"
#include "config.hpp"
#include "scenetreemodel.hpp"
#include "selectionpath.hpp"
#include "selectiontree.hpp"

#include <parser/nodegraph.hpp>
#include <parser/propertywriter.hpp>

#include <2d/CCNode.h>

#include <QDebug>

namespace ee {
using Self = SceneTree;

Self::SceneTree(QWidget* parent)
    : Super(parent) {
    setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
}

Self::~SceneTree() {}

const NodeGraph& Self::getNodeGraph() const {
    Q_ASSERT(nodeGraph_);
    return *nodeGraph_;
}

void Self::setNodeGraph(const NodeGraph& graph) {
    nodeGraph_ = std::make_unique<NodeGraph>(graph);
    treeModel_ = std::make_unique<SceneTreeModel>(this);
    treeModel_->setNodeGraph(*nodeGraph_);
    setModel(treeModel_.get());
}

SelectionTree Self::currentSelection() const {
    auto selection = SelectionTree::emptySelection();
    auto modelIndices = selectedIndexes();
    for (auto&& index : modelIndices) {
        auto path = SelectionPath::fromIndex(index, treeModel_->rootIndex());
        selection.addPath(path);
    }
    return selection;
}

void Self::selectionChanged(const QItemSelection& selected,
                            const QItemSelection& deselected) {
    Super::selectionChanged(selected, deselected);

    auto selectedModelIndices = selected.indexes();
    auto currentModelIndices = selectedIndexes();

    std::sort(selectedModelIndices.begin(), selectedModelIndices.end());
    std::sort(currentModelIndices.begin(), currentModelIndices.end());

    bool shouldEmitSignal = true;
    if (selectedModelIndices == currentModelIndices) {
        // OK.
    } else {
        QItemSelection toBeDeselectedIndices;
        QModelIndex candidateIndex;
        for (auto&& index : currentModelIndices) {
            if (not selected.contains(index)) {
                candidateIndex = index;
                break;
            }
        }
        auto candidatePath = SelectionPath::fromIndex(candidateIndex);
        for (auto&& index : selectedModelIndices) {
            auto path = SelectionPath::fromIndex(index);
            if (not candidatePath.isSibling(path)) {
                toBeDeselectedIndices.append(QItemSelectionRange(index));
            }
        }
        if (toBeDeselectedIndices.isEmpty()) {
            // OK.
        } else {
            selectionModel()->select(
                toBeDeselectedIndices,
                QItemSelectionModel::SelectionFlag::Deselect);
            shouldEmitSignal = false;
        }
    }

    if (shouldEmitSignal) {
        Q_EMIT selectionTreeChanged(currentSelection());
    }
}

void Self::updateSelectionProperty(const SelectionPath& path,
                                   const QString& propertyName,
                                   const cocos2d::Value& value) {
    auto&& graph = path.find(*nodeGraph_);
    auto&& writer = graph.getPropertyWriter();
    writer.setProperty(propertyName.toStdString(), value);
}
} // namespace ee
