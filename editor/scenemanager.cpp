#include "scenemanager.hpp"
#include "inspectors/inspectorlist.hpp"
#include "inspectors/inspectorloaderlibrary.hpp"
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
    , inspectorList_(inspectorList) {
    inspectorLoaderLibrary_ = std::make_unique<InspectorLoaderLibrary>();
    inspectorLoaderLibrary_->addDefaultLoaders();
}

Self::~SceneManager() {}

void Self::setNodeGraph(const NodeGraph& graph) {
    nodeGraph_ = std::make_unique<NodeGraph>(graph);
    mainScene_->setNodeGraph(*nodeGraph_);
    sceneTree_->setNodeGraph(*nodeGraph_);
}

void Self::connect() {
    Q_ASSERT(connections_.isEmpty());

    connections_ << QObject::connect(
        sceneTree_, &SceneTree::selectionTreeChanged,
        [this](const SelectionTree& selectionTree) {
            selectionTree_ = std::make_unique<SelectionTree>(selectionTree);
            mainScene_->selectTree(selectionTree);
            updateInspectors(selectionTree);
        });

    connections_ << QObject::connect(
        mainScene_, &MainScene::selectionTreeChanged,
        [this](const SelectionTree& selectionTree) {
            selectionTree_ = std::make_unique<SelectionTree>(selectionTree);
            sceneTree_->selectTree(selectionTree);
            updateInspectors(selectionTree);
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

void Self::updateInspectors(const SelectionTree& selectionTree) {
    inspectorList_->clearInspectors();
    if (selectionTree.isEmpty()) {
        //
    } else {
        QVector<QString> names;
        for (auto&& path : selectionTree.getPaths()) {
            auto&& graph = path.find(*nodeGraph_);
            auto name = QString::fromStdString(graph.getBaseClass());
            names.append(name);
        }
        auto&& loader = inspectorLoaderLibrary_->getLoader(names);
        auto inspectors = inspectorLoaderLibrary_->createInspectors(loader);
        for (auto&& inspector : inspectors) {
            inspectorList_->addInspector(inspector);
        }
    }
}
} // namespace ee
