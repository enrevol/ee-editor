#ifndef EE_EDITOR_MAIN_SCENE_VIEW_HPP
#define EE_EDITOR_MAIN_SCENE_VIEW_HPP

#include "scene/mainscene.hpp"
#include "selection/selectionpath.hpp"
#include "selection/selectiontree.hpp"

#include <parser/nodegraph.hpp>
#include <parser/parserfwd.hpp>

#include <2d/CCLayer.h>
#include <2d/CCScene.h>
#include <base/CCRefPtr.h>
#include <base/CCValue.h>

namespace cocos2d {
class EventListenerCustom;
class EventListenerMouse;
class EventListenerTouchOneByOne;
class EventMouse;
class LayerColor;
class Sprite;

template <class T>
class RefPtr;

namespace ui {
class Layout;
} // namespace ui
} // namespace cocos2d

namespace ee {
class Gizmo;
class NodeHighlighter;
class NodeHighlighterLayer;

class MainSceneView : public MainScene, public cocos2d::Scene {
private:
    using Self = MainSceneView;
    using Super = cocos2d::Scene;

public:
    static Self* create();

    /// @see Super.
    virtual void setNodeGraph(const NodeGraph& graph) override;

    /// @see Super.
    virtual void selectTree(const SelectionTree& selection) override;

    /// Moves the currently selection by the specified amount.
    void moveSelectionBy(const cocos2d::Vec2& delta);

protected:
    virtual bool init() override;

    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;

    virtual void onExitTransitionDidStart() override;
    virtual void onExit() override;

    virtual void update(float delta) override;

    bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void touchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    void mousePressed(cocos2d::EventMouse* event);
    void mouseMoved(cocos2d::EventMouse* event);
    void mouseReleased(cocos2d::EventMouse* event);

private:
    void updateSelection();

    void updateSelection(const SelectionTree& selection);

    void updateGizmo();

    void updateHighlighter();

    void updateWindowSize();

    /// Current node graph.
    std::unique_ptr<NodeGraph> nodeGraph_;

    /// Current selection.
    std::unique_ptr<SelectionTree> selection_;

    /// The root node.
    cocos2d::Node* rootNode_;
    cocos2d::LayerColor* background_;

    Gizmo* gizmo_;
    NodeHighlighterLayer* highlighter_;

    bool mousePressing_;
    bool mouseMoved_;

    cocos2d::EventListenerTouchOneByOne* touchListener_;
    cocos2d::EventListenerMouse* mouseListener_;
    cocos2d::EventListenerCustom* windowResizedListener_;
};
} // namespace ee

#endif // EE_EDITOR_MAIN_SCENE_VIEW_HPP
