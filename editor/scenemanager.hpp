#ifndef EE_EDITOR_SCENE_MANAGER_HPP
#define EE_EDITOR_SCENE_MANAGER_HPP

#include <QList>

namespace ee {
class NodeGraph;
class SelectionTree;
class MainScene;
class SceneTree;
class InspectorList;

/// Manages connections between:
/// - Scene tree.
/// - Scene.
/// - Inspectors.
class SceneManager {
public:
    explicit SceneManager(MainScene* mainScene, SceneTree* sceneTree,
                          InspectorList* inspectorList);

    ~SceneManager();

    void setNodeGraph(const NodeGraph& graph);

    void connect();
    void disconnect();

private:
    std::unique_ptr<NodeGraph> graph_;
    std::unique_ptr<SelectionTree> selectionTree_;
    MainScene* mainScene_;
    SceneTree* sceneTree_;
    InspectorList* inspectorList_;
    QList<QMetaObject::Connection> connections_;
};
} // namespace ee

#endif // EE_EDITOR_SCENE_MANAGER_HPP
