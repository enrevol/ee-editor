#ifndef EE_EDITOR_RULER_LINE_HPP
#define EE_EDITOR_RULER_LINE_HPP

#include <ui/UIWidget.h>

namespace cocos2d {
class LayerColor;

namespace ui {
class Text;
} // namespace ui
} // namespace cocos2d

namespace ee {
class RulerLine : public cocos2d::ui::Widget {
private:
    using Self = RulerLine;
    using Super = cocos2d::ui::Widget;

public:
    static Self* create();

    Self* setCoordinate(float value);
    Self* hideCoordinate();
    Self* setLineOpacity(int opacity);
    Self* setLineWidth(float width);
    Self* alignHorizontal(float length);
    Self* alignVertical(float length);

protected:
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;

private:
    void updateLine();

    cocos2d::LayerColor* layerColor_;
    cocos2d::ui::Text* coordLabel_;
    float lineWidth_;
    float lineLength_;
    bool vertical_;
};
} // namespace ee

#endif // EE_EDITOR_RULER_LINE_HPP
