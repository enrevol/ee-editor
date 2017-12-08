#ifndef EE_EDITOR_RULER_VIEW_HPP
#define EE_EDITOR_RULER_VIEW_HPP

#include <ui/UIWidget.h>

namespace ee {
class RulerLine;

class RulerView : public cocos2d::ui::Widget {
private:
    using Self = RulerView;
    using Super = cocos2d::ui::Widget;

public:
    static Self* create();

    Self* setLineWidth(float width);
    Self* setUnitLength(float length);
    Self* setMinDisplayLength(float length);
    Self* setMaxDisplayLength(float length);
    Self* setOrigin(const cocos2d::Point& position);
    Self* setRegion(const cocos2d::Size& region);

protected:
    virtual bool init() override;

    virtual void onEnter() override;
    virtual void onExit() override;

    virtual void update(float delta) override;

    void updateView();

    using Drawer = std::function<void(float position, int opacity)>;

    void drawLines(bool base5, float from, float length, int opacity,
                   const Drawer& drawer);
    void drawVerticalLine(float x, int opacity, bool showCoordinate);
    void drawHorizontalLine(float y, int opacity, bool showCoordinate);

private:
    void updateViewBegin();
    void updateViewEnd();
    RulerLine* createLine();

    bool dirty_;
    std::size_t lineIndex_;
    float lineWidth_;
    float unitLength_;
    float minDisplayLength_;
    float maxDisplayLength_;
    cocos2d::Point origin_;
    cocos2d::Size region_;

    std::vector<RulerLine*> rulerLines_;
};
} // namespace ee

#endif // EE_EDITOR_RULER_VIEW_HPP
