#include "scenetree.hpp"
#include "config.hpp"
#include "sceneselection.hpp"
#include "scenetreemodel.hpp"

#include <parser/nodegraph.hpp>
#include <parser/propertywriter.hpp>

#include <2d/CCNode.h>

#include <QDebug>

namespace ee {
using Self = SceneTree;

namespace {
/// Finds the tree indices, start from the root node.
QVector<int> findTreeIndices(QModelIndex modelIndex) {
    QVector<int> treeIndices;
    while (modelIndex.isValid()) {
        treeIndices.append(modelIndex.row());
        modelIndex = modelIndex.parent();
    }
    Q_ASSERT(treeIndices.size() > 0);
    Q_ASSERT(treeIndices.last() == 0);
    // Remove root index.
    treeIndices.removeLast();
    std::reverse(treeIndices.begin(), treeIndices.end());
    return treeIndices;
}

/// Finds the ancestor indices, start from the root node.
QVector<int> findAncestorIndices(QModelIndex modelIndex, bool& root) {
    auto treeIndices = findTreeIndices(modelIndex);
    if (treeIndices.isEmpty()) {
        // Root.
        root = true;
    } else {
        // Remove the leaf index.
        treeIndices.removeLast();
        root = false;
    }
    return treeIndices;
}
} // namespace

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

SceneSelection Self::currentSelection() const {
    auto modelIndices = selectedIndexes();
    if (modelIndices.isEmpty()) {
        return SceneSelection::emptySelection();
    }

    QVector<QVector<int>> treeIndices;
    treeIndices.reserve(modelIndices.size());

    for (auto&& modelIndex : modelIndices) {
        treeIndices.append(findTreeIndices(modelIndex));
    }

    for (int i = 1; i < treeIndices.size(); ++i) {
        auto&& previous = treeIndices.at(i - 1);
        auto&& current = treeIndices.at(i);
        Q_ASSERT(previous.size() == current.size());
        Q_ASSERT(std::equal(previous.cbegin(), std::prev(previous.cend()),
                            current.cbegin()));
    }

    auto ancestorIndices = treeIndices.first();
    if (ancestorIndices.isEmpty()) {
        return SceneSelection::rootSelection();
    }
    ancestorIndices.pop_back();

    QVector<int> childrenIndices;
    childrenIndices.reserve(treeIndices.size());
    for (auto&& elt : treeIndices) {
        childrenIndices.append(elt.last());
    }
    return SceneSelection::multipleSelection(ancestorIndices, childrenIndices);
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
        QModelIndex candidateModelIndex;
        for (auto&& modelIndex : currentModelIndices) {
            if (not selected.contains(modelIndex)) {
                candidateModelIndex = modelIndex;
                break;
            }
        }
        bool isCurrentRoot;
        auto currentTreeIndices =
            findAncestorIndices(candidateModelIndex, isCurrentRoot);

        for (auto&& modelIndex : selectedModelIndices) {
            bool isRoot;
            auto treeIndices = findAncestorIndices(modelIndex, isRoot);
            if (currentTreeIndices != treeIndices || isCurrentRoot != isRoot) {
                toBeDeselectedIndices.append(QItemSelectionRange(modelIndex));
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
        Q_EMIT selectionChanged(currentSelection());
    }
}

void Self::updateProperty(const NodeGraph& graph,
                          const SceneSelection& selection,
                          const QString& propertyName,
                          const cocos2d::Value& value) {
    Q_ASSERT(not selection.isEmpty());
    Q_ASSERT(&graph == nodeGraph_.get());
    if (selection.isRoot()) {
        auto&& writer = nodeGraph_->getPropertyWriter();
        writer.setProperty(propertyName.toStdString(), value);
    } else {
        auto parentGraph = nodeGraph_.get();
        for (auto&& index : selection.getAncestorIndices()) {
            parentGraph =
                &parentGraph->getChild(static_cast<std::size_t>(index));
        }
        for (auto&& childIndex : selection.getChildrenIndices()) {
            auto&& childGraph =
                parentGraph->getChild(static_cast<std::size_t>(childIndex));
            auto&& writer = childGraph.getPropertyWriter();
            writer.setProperty(propertyName.toStdString(), value);
        }
    }
}
} // namespace ee
