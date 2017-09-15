#ifndef EE_EDITOR_ROOT_SCENE_HPP
#define EE_EDITOR_ROOT_SCENE_HPP

#include <2d/CCScene.h>

namespace cocos2d {
class LayerColor;
class Sprite;
} // namespace cocos2d

namespace ee {
class NodeGraph;

class RootScene : public cocos2d::Scene {
private:
    using Self = RootScene;
    using Super = cocos2d::Scene;

public:
    static Self* getInstance();

    void setNodeGraph(const NodeGraph& graph);

    bool setTexturePath(const QString& path);

    bool setShader(const QString& vertexShader, const QString& fragmentShader);

protected:
    CREATE_FUNC(Self)

    virtual bool init() override;

    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;

    virtual void onExitTransitionDidStart() override;
    virtual void onExit() override;

private:
    cocos2d::Sprite* sprite_;
};
} // namespace ee

#endif // EE_EDITOR_ROOT_SCENE_HPP
