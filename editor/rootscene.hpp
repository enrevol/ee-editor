#ifndef EE_EDITOR_ROOT_SCENE_HPP
#define EE_EDITOR_ROOT_SCENE_HPP

#include <parser/parserfwd.hpp>

/// Moc compile error.
#include "selectionpath.hpp"
#include "selectiontree.hpp"
#include <2d/CCLayer.h>
#include <base/CCRefPtr.h>
#include <parser/nodegraph.hpp>

#include <QObject>

#include <2d/CCScene.h>
#include <base/CCValue.h>

namespace cocos2d {
class EventListenerMouse;
class EventListenerTouchOneByOne;
class LayerColor;
class Sprite;

template <class T> class RefPtr;
} // namespace cocos2d

namespace ee {
class Gizmo;
class NodeGraph;
class NodeLoader;
class SelectionPath;
class SelectionTree;

class RootScene : public QObject, public cocos2d::Scene {
    Q_OBJECT

private:
    using Self = RootScene;
    using Super = cocos2d::Scene;

public:
    static Self* create();

    void setNodeGraph(const NodeGraph& graph);

    void setSelection(const SelectionTree& selection);

    void updateSelectionProperty(const NodeGraph& graph,
                                 const SelectionPath& path,
                                 const QString& propertyName,
                                 const cocos2d::Value& value);

    void updateSelectionProperty(cocos2d::Node* node,
                                 const NodeLoaderPtr& nodeLoader,
                                 const QString& propertyName,
                                 const cocos2d::Value& value);

Q_SIGNALS:
    void propertyValueChanged(const SelectionPath& path,
                              const QString& propertyName,
                              const cocos2d::Value& value);

protected Q_SLOTS:
    void moveSelectionBy(const cocos2d::Vec2& delta);

protected:
    virtual bool init() override;

    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;

    virtual void onExitTransitionDidStart() override;
    virtual void onExit() override;

    virtual void update(float delta) override;

    bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

private:
    void updateSelection();

    void updateSelection(const SelectionTree& selection);

    void highlightNodes(const std::vector<cocos2d::Node*>& nodes);

    void highlightNode(cocos2d::LayerColor* highlighter,
                       const cocos2d::Node* node);

    void unhighlightNodes();

    void unhighlightNode(cocos2d::LayerColor* highlighter);

    void ensureHighlighters(std::size_t size);

    void updateGizmo();

    std::unique_ptr<NodeGraph> nodeGraph_;
    std::unique_ptr<SelectionTree> selection_;
    std::vector<cocos2d::RefPtr<cocos2d::LayerColor>> highlighters_;

    cocos2d::Node* rootNode_;
    cocos2d::LayerColor* background_;

    Gizmo* gizmo_;

    cocos2d::EventListenerTouchOneByOne* listener_;
    cocos2d::EventListenerMouse* mouseListener_;
};
} // namespace ee

#endif // EE_EDITOR_ROOT_SCENE_HPP
