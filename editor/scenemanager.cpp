#include "scenemanager.hpp"
#include "inspectors/inspectorlist.hpp"
#include "scene/mainscene.hpp"
#include "scenetree/scenetree.hpp"
#include "selection/selectionpath.hpp"
#include "selection/selectiontree.hpp"

#include <parser/nodegraph.hpp>

namespace ee {
using Self = SceneManager;

Self::SceneManager(MainScene* mainScene, SceneTree* sceneTree,
                   InspectorList* inspectorList)
    : mainScene_(mainScene)
    , sceneTree_(sceneTree)
    , inspectorList_(inspectorList) {}

Self::~SceneManager() {}

void Self::setNodeGraph(const NodeGraph& graph) {
    graph_ = std::make_unique<NodeGraph>(graph);
    mainScene_->setNodeGraph(*graph_);
    sceneTree_->setNodeGraph(*graph_);
}

void Self::connect() {
    Q_ASSERT(connections_.isEmpty());

    connections_ << QObject::connect(
        sceneTree_, &SceneTree::selectionTreeChanged,
        [this](const SelectionTree& selectionTree) {
            selectionTree_ = std::make_unique<SelectionTree>(selectionTree);
            mainScene_->selectTree(selectionTree);
        });

    connections_ << QObject::connect(
        mainScene_, &MainScene::selectionTreeChanged,
        [this](const SelectionTree& selectionTree) {
            selectionTree_ = std::make_unique<SelectionTree>(selectionTree);
            sceneTree_->selectTree(selectionTree);
        });

    connections_ << QObject::connect(
        inspectorList_, &InspectorList::propertyChanged,
        [this](const Inspector::Applier& applier) { //
            //
        });
}

void Self::disconnect() {
    for (auto&& connection : connections_) {
        QObject::disconnect(connection);
    }
    connections_.clear();
}
} // namespace ee
