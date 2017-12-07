#include <ciso646>

#include "config.hpp"
#include "scenetreemodel.hpp"
#include "scenetreeview.hpp"
#include "selection/selectionpath.hpp"
#include "selection/selectiontree.hpp"

#include <parser/nodegraph.hpp>

#include <2d/CCNode.h>

#include <QDebug>

namespace ee {
using Self = SceneTreeView;

Self::SceneTreeView(QWidget* parent)
    : Super(parent)
    , selecting_(false) {
    setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
    setNodeGraph(NodeGraph());
}

Self::~SceneTreeView() {}

const NodeGraph& Self::getNodeGraph() const {
    return *nodeGraph_;
}

void Self::setNodeGraph(const NodeGraph& graph) {
    nodeGraph_ = std::make_unique<NodeGraph>(graph);
    treeModel_ = std::make_unique<SceneTreeModel>(this);
    treeModel_->setNodeGraph(*nodeGraph_);
    setModel(treeModel_.get());
}

SelectionTree Self::getCurrentSelection() const {
    auto selection = SelectionTree::emptySelection();
    auto modelIndices = selectedIndexes();
    for (auto&& index : modelIndices) {
        auto path = SelectionPath::fromIndex(index, treeModel_->rootIndex());
        selection.addPath(path);
    }
    return selection;
}

void Self::selectTree(const SelectionTree& selection) {
    Q_ASSERT(not selecting_);
    selecting_ = true;
    QItemSelection itemSelection;
    auto&& paths = selection.getPaths();
    for (auto&& path : paths) {
        auto modelIndex = path.find(*treeModel_);
        itemSelection.select(modelIndex, modelIndex);
    }
    selectionModel()->select(
        itemSelection, QItemSelectionModel::SelectionFlag::ClearAndSelect);
    selecting_ = false;
}

void Self::selectionChanged(const QItemSelection& selected,
                            const QItemSelection& deselected) {
    Super::selectionChanged(selected, deselected);

    if (selecting_) {
        return;
    }

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
        Q_EMIT selectionTreeChanged(getCurrentSelection());
    }
}
} // namespace ee
