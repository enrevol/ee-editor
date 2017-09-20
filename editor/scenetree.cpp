#include "scenetree.hpp"
#include "config.hpp"
#include "scenetreemodel.hpp"

#include <parser/nodegraph.hpp>

#include <2d/CCNode.h>

namespace ee {
using Self = SceneTree;

namespace {
QVector<int> findTreeIndices(QModelIndex modelIndex) {
    QVector<int> treeIndices;
    while (modelIndex.isValid()) {
        treeIndices.append(modelIndex.row());
        modelIndex = modelIndex.parent();
    }
    std::reverse(treeIndices.begin(), treeIndices.end());
    return treeIndices;
}
} // namespace

Self::SceneTree(QWidget* parent)
    : Super(parent) {
    setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
    connect(&Config::getInstance(), &Config::interfaceLoaded,
            [this](const QFileInfo& path) {
                setNodeGraph(Config::getInstance()
                                 .getInterfaceSettings()
                                 ->getNodeGraph()
                                 .value());
            });
}

void Self::setNodeGraph(const NodeGraph& graph) {
    treeModel_ = new SceneTreeModel(this);
    treeModel_->setNodeGraph(graph);
    setModel(treeModel_);
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
        auto currentTreeIndices = findTreeIndices(candidateModelIndex);
        currentTreeIndices.removeLast();
        for (auto&& modelIndex : selectedModelIndices) {
            auto treeIndices = findTreeIndices(modelIndex);
            treeIndices.removeLast();
            if (currentTreeIndices != treeIndices) {
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
} // namespace ee
