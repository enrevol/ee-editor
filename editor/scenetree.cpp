#include "scenetree.hpp"
#include "config.hpp"
#include "sceneselection.hpp"
#include "scenetreemodel.hpp"

#include <parser/nodegraph.hpp>

#include <2d/CCNode.h>

#include <QDebug>

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

Self::~SceneTree() {}

void Self::setNodeGraph(const NodeGraph& graph) {
    nodeGraph_ = std::make_unique<NodeGraph>(graph);
    treeModel_ = new SceneTreeModel(this);
    treeModel_->setNodeGraph(nodeGraph_.get());
    setModel(treeModel_);
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

    QVector<int> childrenIndices;
    childrenIndices.reserve(treeIndices.size());
    for (auto&& elt : treeIndices) {
        childrenIndices.append(elt.last());
    }

    auto ancestorIndices = treeIndices.first();
    ancestorIndices.pop_back();
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
