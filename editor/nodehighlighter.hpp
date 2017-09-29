#ifndef EE_EDITOR_NODE_HIGHLIGHTER_HPP
#define EE_EDITOR_NODE_HIGHLIGHTER_HPP

#include <ui/UIWidget.h>

namespace cocos2d {
namespace ui {
class Scale9Sprite;
} // namespace ui
} // namespace cocos2d

namespace ee {
class NodeHighlighter : public cocos2d::ui::Widget {
private:
    using Self = NodeHighlighter;
    using Super = cocos2d::ui::Widget;

public:
    CREATE_FUNC(Self)

    void hover();
    void select();
    void setRegion(const cocos2d::Rect& rect);

protected:
    virtual bool init() override;

    virtual void onEnter() override;
    virtual void onExit() override;

    void resetInsets();

private:
    cocos2d::ui::Scale9Sprite* border_;
};
} // namespace ee

#endif // EE_EDITOR_NODE_HIGHLIGHTER_HPP
