#include "scenemanager.hpp"

namespace ee {
using Self = SceneManager;

Self::SceneManager(MainScene* mainScene, SceneTree* sceneTree,
                   InspectorList* inspectorList)
    : mainScene_(mainScene)
    , sceneTree_(sceneTree)
    , inspectorList_(inspectorList) {}

void Self::connect() {
    //
}

void Self::disconnect() {
    //
}
} // namespace ee
