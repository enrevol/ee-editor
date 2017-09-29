#ifndef EE_EDITOR_NODE_HIGHLIGHTER_LAYER_HPP
#define EE_EDITOR_NODE_HIGHLIGHTER_LAYER_HPP

#include <ui/UIWidget.h>

namespace ee {
class NodeHighlighter;

class NodeHighlighterLayer : public cocos2d::ui::Widget {
private:
    using Self = NodeHighlighterLayer;
    using Super = cocos2d::ui::Widget;

public:
    CREATE_FUNC(Self)

    virtual ~NodeHighlighterLayer() override;

    void hover(const cocos2d::Node* node);
    void unhover();
    void select(const cocos2d::Node* node);
    void deselect(const cocos2d::Node* node);
    void deselectAll();
    void clearSelection();

protected:
    virtual bool init() override;

    virtual void onEnter() override;
    virtual void onExit() override;

    cocos2d::Rect getRegion(const cocos2d::Node* node) const;
    NodeHighlighter* getOrCreateSelectHighlighter(const cocos2d::Node* node);

private:
    NodeHighlighter* hoverHighlighter_;
    std::map<const cocos2d::Node*, NodeHighlighter*> selectHighlighters_;
};
} // namespace ee

#endif // EE_EDITOR_NODE_HIGHLIGHTER_LAYER_HPP
