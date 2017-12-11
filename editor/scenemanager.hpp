#ifndef EE_EDITOR_SCENE_MANAGER_HPP
#define EE_EDITOR_SCENE_MANAGER_HPP

#include <QList>

namespace ee {
class NodeGraph;
class SelectionTree;
class MainScene;
class SceneTree;
class InspectorList;
class InspectorLoaderLibrary;

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

protected:
    void updateInspectors(const SelectionTree& selectionTree);

private:
    std::unique_ptr<NodeGraph> nodeGraph_;
    std::unique_ptr<SelectionTree> selectionTree_;
    std::unique_ptr<InspectorLoaderLibrary> inspectorLoaderLibrary_;
    MainScene* mainScene_;
    SceneTree* sceneTree_;
    InspectorList* inspectorList_;
    QList<QMetaObject::Connection> connections_;
};
} // namespace ee

#endif // EE_EDITOR_SCENE_MANAGER_HPP
