#ifndef EE_EDITOR_SCENE_MANAGER_HPP
#define EE_EDITOR_SCENE_MANAGER_HPP

namespace ee {
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

    void connect();
    void disconnect();

private:
    MainScene* mainScene_;
    SceneTree* sceneTree_;
    InspectorList* inspectorList_;
};
} // namespace ee

#endif // EE_EDITOR_SCENE_MANAGER_HPP
