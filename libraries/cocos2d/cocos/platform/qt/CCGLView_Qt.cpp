#include <ciso646>

#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "base/CCEventKeyboard.h"
#include "base/CCEventMouse.h"
#include "base/CCTouch.h"
#include "base/ccUTF8.h"
#include "platform/qt/CCGLView_Qt.hpp"
#include "platform/qt/CCOpenGLWidget_Qt.hpp"

#include <QDesktopWidget>
#include <QVBoxLayout>

NS_CC_BEGIN
namespace {
std::unordered_map<Qt::Key, EventKeyboard::KeyCode>& getKeyCodeMap() {
    static std::unordered_map<Qt::Key, EventKeyboard::KeyCode> map;
    static bool initialized = false;
    if (initialized) {
        return map;
    }
    initialized = true;

    map[Qt::Key::Key_unknown] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_Escape] = EventKeyboard::KeyCode::KEY_ESCAPE;
    map[Qt::Key::Key_Tab] = EventKeyboard::KeyCode::KEY_TAB;
    map[Qt::Key::Key_Backtab] = EventKeyboard::KeyCode::KEY_NONE; // FIXME.
    map[Qt::Key::Key_Backspace] = EventKeyboard::KeyCode::KEY_BACKSPACE;
    map[Qt::Key::Key_Return] = EventKeyboard::KeyCode::KEY_ENTER;
    map[Qt::Key::Key_Enter] = EventKeyboard::KeyCode::KEY_KP_ENTER;
    map[Qt::Key::Key_Insert] = EventKeyboard::KeyCode::KEY_INSERT;
    map[Qt::Key::Key_Delete] = EventKeyboard::KeyCode::KEY_DELETE;
    map[Qt::Key::Key_Pause] = EventKeyboard::KeyCode::KEY_PAUSE;
    map[Qt::Key::Key_Tab] = EventKeyboard::KeyCode::KEY_TAB;
    map[Qt::Key::Key_Print] = EventKeyboard::KeyCode::KEY_PRINT;
    map[Qt::Key::Key_SysReq] = EventKeyboard::KeyCode::KEY_SYSREQ;
    map[Qt::Key::Key_Clear] = EventKeyboard::KeyCode::KEY_NONE; // FIXME.
    map[Qt::Key::Key_Home] = EventKeyboard::KeyCode::KEY_HOME;
    map[Qt::Key::Key_End] = EventKeyboard::KeyCode::KEY_END;
    map[Qt::Key::Key_Left] = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
    map[Qt::Key::Key_Up] = EventKeyboard::KeyCode::KEY_UP_ARROW;
    map[Qt::Key::Key_Right] = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
    map[Qt::Key::Key_Down] = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
    map[Qt::Key::Key_PageUp] = EventKeyboard::KeyCode::KEY_PG_UP;
    map[Qt::Key::Key_PageDown] = EventKeyboard::KeyCode::KEY_PG_DOWN;
    map[Qt::Key::Key_Shift] = EventKeyboard::KeyCode::KEY_SHIFT;
    map[Qt::Key::Key_Control] = EventKeyboard::KeyCode::KEY_CTRL;
    map[Qt::Key::Key_Meta] = EventKeyboard::KeyCode::KEY_NONE; // FIXME.
    map[Qt::Key::Key_Alt] = EventKeyboard::KeyCode::KEY_ALT;
    map[Qt::Key::Key_CapsLock] = EventKeyboard::KeyCode::KEY_CAPS_LOCK;
    map[Qt::Key::Key_NumLock] = EventKeyboard::KeyCode::KEY_NUM_LOCK;
    map[Qt::Key::Key_ScrollLock] = EventKeyboard::KeyCode::KEY_SCROLL_LOCK;
    map[Qt::Key::Key_F1] = EventKeyboard::KeyCode::KEY_F1;
    map[Qt::Key::Key_F2] = EventKeyboard::KeyCode::KEY_F2;
    map[Qt::Key::Key_F3] = EventKeyboard::KeyCode::KEY_F3;
    map[Qt::Key::Key_F4] = EventKeyboard::KeyCode::KEY_F4;
    map[Qt::Key::Key_F5] = EventKeyboard::KeyCode::KEY_F5;
    map[Qt::Key::Key_F6] = EventKeyboard::KeyCode::KEY_F6;
    map[Qt::Key::Key_F7] = EventKeyboard::KeyCode::KEY_F7;
    map[Qt::Key::Key_F8] = EventKeyboard::KeyCode::KEY_F8;
    map[Qt::Key::Key_F9] = EventKeyboard::KeyCode::KEY_F9;
    map[Qt::Key::Key_F10] = EventKeyboard::KeyCode::KEY_F10;
    map[Qt::Key::Key_F11] = EventKeyboard::KeyCode::KEY_F11;
    map[Qt::Key::Key_F12] = EventKeyboard::KeyCode::KEY_F12;
    map[Qt::Key::Key_F13] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F14] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F15] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F16] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F17] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F18] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F19] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F20] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F21] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F22] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F23] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F24] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F25] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F26] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F27] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F28] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F29] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F30] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F31] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F32] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F33] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F34] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_F35] = EventKeyboard::KeyCode::KEY_NONE;
    map[Qt::Key::Key_Menu] = EventKeyboard::KeyCode::KEY_MENU;
    map[Qt::Key::Key_Hyper_L] = EventKeyboard::KeyCode::KEY_HYPER;
    map[Qt::Key::Key_Hyper_R] = EventKeyboard::KeyCode::KEY_HYPER;
    map[Qt::Key::Key_Space] = EventKeyboard::KeyCode::KEY_SPACE;
    map[Qt::Key::Key_Exclam] = EventKeyboard::KeyCode::KEY_EXCLAM;
    map[Qt::Key::Key_QuoteDbl] = EventKeyboard::KeyCode::KEY_QUOTE;
    map[Qt::Key::Key_NumberSign] = EventKeyboard::KeyCode::KEY_NUMBER;
    map[Qt::Key::Key_Dollar] = EventKeyboard::KeyCode::KEY_DOLLAR;
    map[Qt::Key::Key_Percent] = EventKeyboard::KeyCode::KEY_PERCENT;
    map[Qt::Key::Key_Ampersand] = EventKeyboard::KeyCode::KEY_AMPERSAND;
    map[Qt::Key::Key_Apostrophe] = EventKeyboard::KeyCode::KEY_APOSTROPHE;
    map[Qt::Key::Key_ParenLeft] = EventKeyboard::KeyCode::KEY_LEFT_PARENTHESIS;
    map[Qt::Key::Key_ParenRight] =
        EventKeyboard::KeyCode::KEY_RIGHT_PARENTHESIS;
    map[Qt::Key::Key_Asterisk] = EventKeyboard::KeyCode::KEY_ASTERISK;
    map[Qt::Key::Key_Plus] = EventKeyboard::KeyCode::KEY_PLUS;
    map[Qt::Key::Key_Comma] = EventKeyboard::KeyCode::KEY_COMMA;
    map[Qt::Key::Key_Minus] = EventKeyboard::KeyCode::KEY_MINUS;
    map[Qt::Key::Key_Period] = EventKeyboard::KeyCode::KEY_PERIOD;
    map[Qt::Key::Key_Slash] = EventKeyboard::KeyCode::KEY_SLASH;
    map[Qt::Key::Key_0] = EventKeyboard::KeyCode::KEY_0;
    map[Qt::Key::Key_1] = EventKeyboard::KeyCode::KEY_1;
    map[Qt::Key::Key_2] = EventKeyboard::KeyCode::KEY_2;
    map[Qt::Key::Key_3] = EventKeyboard::KeyCode::KEY_3;
    map[Qt::Key::Key_4] = EventKeyboard::KeyCode::KEY_4;
    map[Qt::Key::Key_5] = EventKeyboard::KeyCode::KEY_5;
    map[Qt::Key::Key_6] = EventKeyboard::KeyCode::KEY_6;
    map[Qt::Key::Key_7] = EventKeyboard::KeyCode::KEY_7;
    map[Qt::Key::Key_8] = EventKeyboard::KeyCode::KEY_8;
    map[Qt::Key::Key_9] = EventKeyboard::KeyCode::KEY_9;
    map[Qt::Key::Key_Colon] = EventKeyboard::KeyCode::KEY_COLON;
    map[Qt::Key::Key_Semicolon] = EventKeyboard::KeyCode::KEY_SEMICOLON;
    map[Qt::Key::Key_Less] = EventKeyboard::KeyCode::KEY_LESS_THAN;
    map[Qt::Key::Key_Equal] = EventKeyboard::KeyCode::KEY_EQUAL;
    map[Qt::Key::Key_Greater] = EventKeyboard::KeyCode::KEY_GREATER_THAN;
    map[Qt::Key::Key_Question] = EventKeyboard::KeyCode::KEY_QUESTION;
    map[Qt::Key::Key_At] = EventKeyboard::KeyCode::KEY_AT;
    map[Qt::Key::Key_A] = EventKeyboard::KeyCode::KEY_A;
    map[Qt::Key::Key_B] = EventKeyboard::KeyCode::KEY_B;
    map[Qt::Key::Key_C] = EventKeyboard::KeyCode::KEY_C;
    map[Qt::Key::Key_D] = EventKeyboard::KeyCode::KEY_D;
    map[Qt::Key::Key_E] = EventKeyboard::KeyCode::KEY_E;
    map[Qt::Key::Key_F] = EventKeyboard::KeyCode::KEY_F;
    map[Qt::Key::Key_G] = EventKeyboard::KeyCode::KEY_G;
    map[Qt::Key::Key_H] = EventKeyboard::KeyCode::KEY_H;
    map[Qt::Key::Key_I] = EventKeyboard::KeyCode::KEY_I;
    map[Qt::Key::Key_J] = EventKeyboard::KeyCode::KEY_J;
    map[Qt::Key::Key_K] = EventKeyboard::KeyCode::KEY_K;
    map[Qt::Key::Key_L] = EventKeyboard::KeyCode::KEY_L;
    map[Qt::Key::Key_M] = EventKeyboard::KeyCode::KEY_M;
    map[Qt::Key::Key_N] = EventKeyboard::KeyCode::KEY_N;
    map[Qt::Key::Key_O] = EventKeyboard::KeyCode::KEY_O;
    map[Qt::Key::Key_P] = EventKeyboard::KeyCode::KEY_P;
    map[Qt::Key::Key_Q] = EventKeyboard::KeyCode::KEY_Q;
    map[Qt::Key::Key_R] = EventKeyboard::KeyCode::KEY_R;
    map[Qt::Key::Key_S] = EventKeyboard::KeyCode::KEY_S;
    map[Qt::Key::Key_T] = EventKeyboard::KeyCode::KEY_T;
    map[Qt::Key::Key_U] = EventKeyboard::KeyCode::KEY_U;
    map[Qt::Key::Key_V] = EventKeyboard::KeyCode::KEY_V;
    map[Qt::Key::Key_W] = EventKeyboard::KeyCode::KEY_W;
    map[Qt::Key::Key_X] = EventKeyboard::KeyCode::KEY_X;
    map[Qt::Key::Key_Y] = EventKeyboard::KeyCode::KEY_Y;
    map[Qt::Key::Key_Z] = EventKeyboard::KeyCode::KEY_Z;
    map[Qt::Key::Key_BracketLeft] = EventKeyboard::KeyCode::KEY_LEFT_BRACKET;
    map[Qt::Key::Key_Backslash] = EventKeyboard::KeyCode::KEY_BACK_SLASH;
    map[Qt::Key::Key_BracketRight] = EventKeyboard::KeyCode::KEY_RIGHT_BRACKET;
    map[Qt::Key::Key_AsciiCircum] = EventKeyboard::KeyCode::KEY_CIRCUMFLEX;
    map[Qt::Key::Key_Underscore] = EventKeyboard::KeyCode::KEY_UNDERSCORE;
    map[Qt::Key::Key_QuoteLeft] = EventKeyboard::KeyCode::KEY_GRAVE;
    map[Qt::Key::Key_BraceLeft] = EventKeyboard::KeyCode::KEY_LEFT_BRACE;
    map[Qt::Key::Key_Bar] = EventKeyboard::KeyCode::KEY_BAR;
    map[Qt::Key::Key_BraceRight] = EventKeyboard::KeyCode::KEY_RIGHT_BRACE;
    map[Qt::Key::Key_AsciiTilde] = EventKeyboard::KeyCode::KEY_TILDE;

    return map;
}

EventKeyboard::KeyCode parseKey(Qt::Key key) {
    return getKeyCodeMap().at(key);
}
} // namespace

using Self = GLViewImpl;

Self* Self::create(OpenGLWidget* view) {
    auto result = new (std::nothrow) Self();
    if (result != nullptr && result->initWithView(view)) {
        result->autorelease();
    } else {
        CC_SAFE_DELETE(result);
    }
    return result;
}

Self::GLViewImpl()
    : captured_(false)
    , view_(nullptr) {
    qDebug() << Q_FUNC_INFO;
}

Self::~GLViewImpl() {
    qDebug() << Q_FUNC_INFO;
}

bool Self::initWithView(OpenGLWidget* view) {
    Q_ASSERT(view != nullptr);
    view_ = view;

    QObject::connect(view, &OpenGLWidget::onMouseMoved,
                     std::bind(&Self::mouseMove, this, std::placeholders::_1));

    QObject::connect(view, &OpenGLWidget::onMousePressed,
                     std::bind(&Self::mousePress, this, std::placeholders::_1));

    QObject::connect(
        view, &OpenGLWidget::onMouseReleased,
        std::bind(&Self::mouseRelease, this, std::placeholders::_1));

    QObject::connect(view, &OpenGLWidget::onKeyPressed,
                     std::bind(&Self::keyPress, this, std::placeholders::_1));

    QObject::connect(view, &OpenGLWidget::onKeyReleased,
                     std::bind(&Self::keyRelease, this, std::placeholders::_1));

    QObject::connect(view, &OpenGLWidget::onPainted,
                     std::bind(&Self::paint, this));

    QObject::connect(view, &OpenGLWidget::onResized,
                     std::bind(&Self::resize, this, std::placeholders::_1));

    QObject::connect(view, &OpenGLWidget::onWheeled,
                     std::bind(&Self::wheel, this, std::placeholders::_1));

    qDebug() << "width = " << view->size().width()
             << " height = " << view->size().height();
    resizeFrame(view->size().width(), view->size().height());
    return true;
}

bool Self::isOpenGLReady() {
    return true;
}

void Self::end() {
    qDebug() << Q_FUNC_INFO;
    CC_SAFE_DELETE(view_);
    delete this;
}

void Self::swapBuffers() {
    // QOpenGLWidget already does this.
    // auto context = view_->context();
    // context->makeCurrent(context->surface());
    // context->swapBuffers(context->surface());
}

void Self::setIMEKeyboardState(bool open) {
    CC_UNUSED_PARAM(open);
}

void Self::setViewName(const std::string& viewName) {
    Super::setViewName(viewName);
}

void Self::setFrameZoomFactor(float zoomFactor) {
    // Has no effect.
    Q_UNUSED(zoomFactor);
    Q_ASSERT(false);
}

float Self::getFrameZoomFactor() const {
    Q_ASSERT(false);
    return 1.0f;
}

void Self::setFrameSize(float width, float height) {
    Super::setFrameSize(width, height);
}

void Self::setViewPortInPoints(float x, float y, float w, float h) {
    Super::setViewPortInPoints(x, y, w, h);
}

void Self::setScissorInPoints(float x, float y, float w, float h) {
    Super::setScissorInPoints(x, y, w, h);
}

QOpenGLContext* Self::getOpenGLContext() const {
    return view_->context();
}

void Self::setRepaintInterval(int milliseconds) {
    view_->setRepaintInterval(milliseconds);
}

namespace {
EventMouse::MouseButton parseMouseButton(Qt::MouseButton button) {
    std::map<Qt::MouseButton, EventMouse::MouseButton> map;
    map[Qt::MouseButton::LeftButton] = EventMouse::MouseButton::BUTTON_LEFT;
    map[Qt::MouseButton::RightButton] = EventMouse::MouseButton::BUTTON_RIGHT;
    map[Qt::MouseButton::MiddleButton] = EventMouse::MouseButton::BUTTON_MIDDLE;
    return map.at(button);
}
} // namespace

void Self::mouseMove(QMouseEvent* event) {
    auto x = static_cast<float>(event->localPos().x());
    auto y = static_cast<float>(event->localPos().y());
    if (captured_) {
        std::intptr_t id = 0;
        handleTouchesMove(1, &id, &x, &y);
    }
    auto cursorPosition = parseCursorPosition(x, y);
    EventMouse mouseEvent(EventMouse::MouseEventType::MOUSE_MOVE);
    mouseEvent.setCursorPosition(cursorPosition.x, cursorPosition.y);
    if (event->buttons() & Qt::MouseButton::LeftButton) {
        mouseEvent.setMouseButton(
            parseMouseButton(Qt::MouseButton::LeftButton));
    } else if (event->buttons() & Qt::MouseButton::RightButton) {
        mouseEvent.setMouseButton(
            parseMouseButton(Qt::MouseButton::RightButton));
    } else if (event->buttons() & Qt::MouseButton::MiddleButton) {
        mouseEvent.setMouseButton(
            parseMouseButton(Qt::MouseButton::MiddleButton));
    }
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&mouseEvent);
}

void Self::mousePress(QMouseEvent* event) {
    auto x = static_cast<float>(event->localPos().x());
    auto y = static_cast<float>(event->localPos().y());
    if (event->button() == Qt::MouseButton::LeftButton) {
        captured_ = true;
        auto&& viewPort = getViewPortRect();
        if (viewPort.equals(Rect::ZERO) ||
            viewPort.containsPoint(cocos2d::Point(x, y))) {
            std::intptr_t id = 0;
            handleTouchesBegin(1, &id, &x, &y);
        }
    }
    auto cursorPosition = parseCursorPosition(x, y);
    EventMouse mouseEvent(EventMouse::MouseEventType::MOUSE_DOWN);
    mouseEvent.setCursorPosition(cursorPosition.x, cursorPosition.y);
    mouseEvent.setMouseButton(parseMouseButton(event->button()));
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&mouseEvent);
}

void Self::mouseRelease(QMouseEvent* event) {
    auto x = static_cast<float>(event->localPos().x());
    auto y = static_cast<float>(event->localPos().y());
    if (event->button() == Qt::MouseButton::RightButton) {
        if (captured_) {
            captured_ = false;
            std::intptr_t id = 0;
            handleTouchesEnd(1, &id, &x, &y);
        }
    }
    auto cursorPosition = parseCursorPosition(x, y);
    EventMouse mouseEvent(EventMouse::MouseEventType::MOUSE_UP);
    mouseEvent.setCursorPosition(cursorPosition.x, cursorPosition.y);
    mouseEvent.setMouseButton(parseMouseButton(event->button()));
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&mouseEvent);
}

void Self::wheel(QWheelEvent* event) {
    auto x = static_cast<float>(event->posF().x());
    auto y = static_cast<float>(event->posF().y());
    EventMouse mouseEvent(EventMouse::MouseEventType::MOUSE_SCROLL);
    auto cursorPosition = parseCursorPosition(x, y);
    mouseEvent.setScrollData(x, -y);
    mouseEvent.setCursorPosition(cursorPosition.x, cursorPosition.y);
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&mouseEvent);
}

void Self::keyPress(QKeyEvent* event) {
    if (not event->isAutoRepeat()) {
        EventKeyboard keyboardEvent(
            parseKey(static_cast<Qt::Key>(event->key())), true);
        Director::getInstance()->getEventDispatcher()->dispatchEvent(
            &keyboardEvent);
    }
}

void Self::keyRelease(QKeyEvent* event) {
    if (not event->isAutoRepeat()) {
        EventKeyboard keyboardEvent(
            parseKey(static_cast<Qt::Key>(event->key())), false);
        Director::getInstance()->getEventDispatcher()->dispatchEvent(
            &keyboardEvent);
    }
}

void Self::paint() {
    auto director = Director::getInstance();
    director->mainLoop();
}

void Self::resize(QResizeEvent* event) {
    auto width = static_cast<float>(event->size().width());
    auto height = static_cast<float>(event->size().height());
    resizeFrame(width, height);
}

void Self::resizeFrame(float width, float height) {
    setDesignResolutionSize(width, height, ResolutionPolicy::EXACT_FIT);

    // Must setFrameSize later.
    setFrameSize(width, height);
}

cocos2d::Point Self::parseCursorPosition(float x, float y) const {
    return parseCursorPosition(
        QPointF(static_cast<qreal>(x), static_cast<qreal>(y)));
}

cocos2d::Point Self::parseCursorPosition(const QPointF& p) const {
    auto&& viewPort = getViewPortRect();
    auto x = static_cast<float>(p.x());
    auto y = static_cast<float>(p.y());
    auto cursorX = (x - viewPort.getMinX()) / getScaleX();
    auto cursorY = (viewPort.getMaxY() - y) / getScaleY();
    return cocos2d::Point(cursorX, cursorY);
}
NS_CC_END
