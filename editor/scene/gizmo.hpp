#ifndef EE_EDITOR_GIZMO_HPP
#define EE_EDITOR_GIZMO_HPP

#include <QObject>

#include <ui/UIWidget.h>

namespace cocos2d {
class Sprite;
class EventListenerMouse;
class EventListenerTouchOneByOne;
class EventMouse;
} // namespace cocos2d

namespace ee {
class Gizmo : public QObject, public cocos2d::ui::Widget {
    Q_OBJECT

private:
    using Self = Gizmo;
    using Super = cocos2d::ui::Widget;

public:
    CREATE_FUNC(Self)

    void setMovable(bool movable);

Q_SIGNALS:
    void moveBy(const cocos2d::Vec2& delta);

protected:
    virtual bool init() override;

    virtual void onEnter() override;
    virtual void onExit() override;

    void mousePressed(cocos2d::EventMouse* event);
    void mouseMoved(cocos2d::EventMouse* event);
    void mouseReleased(cocos2d::EventMouse* event);

private:
    void resetImages();

    cocos2d::EventListenerMouse* mouseListener_;

    cocos2d::Sprite* box_;
    cocos2d::Sprite* axisX_;
    cocos2d::Sprite* axisY_;

    int capturedMask_;
};
} // namespace ee

#endif // EE_EDITOR_GIZMO_HPP
