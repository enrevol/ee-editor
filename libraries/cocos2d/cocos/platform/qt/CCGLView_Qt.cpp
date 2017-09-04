#include <ciso646>

#include "platform/qt/CCGLView_Qt.hpp"
#include "base/CCDirector.h"
#include "base/CCTouch.h"
#include "base/ccUTF8.h"
#include "platform/qt/CCOpenGLWidget_Qt.hpp"

#include <QDesktopWidget>
#include <QVBoxLayout>

NS_CC_BEGIN
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
    , frameZoomFactor_(1.0f)
    , screenScaleFactor_(1.f)
    , touch_(nullptr)
    , view_(nullptr) {
    qDebug() << Q_FUNC_INFO;
}

Self::~GLViewImpl() {
    qDebug() << Q_FUNC_INFO;
    CC_SAFE_DELETE(touch_);
}

bool Self::initWithView(OpenGLWidget* view) {
    Q_ASSERT(view != nullptr);
    view_ = view;

    view->setMouseMoveCallback(
        std::bind(&Self::mouseMove, this, std::placeholders::_1));

    view->setMousePressCallback(
        std::bind(&Self::mousePress, this, std::placeholders::_1));

    view->setMouseReleaseCallback(
        std::bind(&Self::mouseRelease, this, std::placeholders::_1));

    view->setKeyPressCallback(
        std::bind(&Self::keyPress, this, std::placeholders::_1));

    view->setKeyReleaseCallback(
        std::bind(&Self::keyRelease, this, std::placeholders::_1));

    view->setResizeCallback([this](QResizeEvent* event) {
        setFrameSize(event->size().width(), event->size().height());
        updateDesignResolutionSize();
        auto director = Director::getInstance();
        director->setProjection(director->getProjection());
    });

    view->setRepaintCallback([this] {
        auto director = Director::getInstance();
        director->mainLoop();
    });

    _screenSize.width = _designResolutionSize.width = view->size().width();
    _screenSize.height = _designResolutionSize.height = view->size().height();

    return true;
}

bool Self::isOpenGLReady() {
    return true;
}

void Self::end() {
    qDebug() << Q_FUNC_INFO;
    CC_SAFE_DELETE(touch_);
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
    frameZoomFactor_ = zoomFactor;

    auto director = Director::getInstance();
    director->setProjection(director->getProjection());
}

float Self::getFrameZoomFactor() const {
    return frameZoomFactor_;
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

void Self::mouseMove(QMouseEvent* event) {
    if (touch_ == nullptr) {
        return;
    }

    if (not captured_) {
        return;
    }

    captured_ = true;
    touch_->setTouchInfo(0, static_cast<float>(event->x()) / screenScaleFactor_,
                         static_cast<float>(event->y()) / screenScaleFactor_);

    std::intptr_t id = touch_->getID();
    auto x = touch_->getLocationInView().x;
    auto y = touch_->getLocationInView().y;
    handleTouchesMove(1, &id, &x, &y);
}

void Self::mousePress(QMouseEvent* event) {
    if (touch_ == nullptr) {
        return;
    }

    if (event->button() != Qt::MouseButton::LeftButton) {
        return;
    }

    captured_ = true;
    touch_->setTouchInfo(0, static_cast<float>(event->x()) / screenScaleFactor_,
                         static_cast<float>(event->y()) / screenScaleFactor_);

    touches_.push_back(touch_);
    std::intptr_t id = touch_->getID();
    auto x = touch_->getLocationInView().x;
    auto y = touch_->getLocationInView().y;
    handleTouchesBegin(1, &id, &x, &y);
}

void Self::mouseRelease(QMouseEvent* event) {
    if (touch_ == nullptr) {
        return;
    }

    if (event->button() != Qt::MouseButton::LeftButton) {
        return;
    }

    captured_ = false;
    touch_->setTouchInfo(0, static_cast<float>(event->x()) / screenScaleFactor_,
                         static_cast<float>(event->y()) / screenScaleFactor_);

    std::intptr_t id = touch_->getID();
    auto x = touch_->getLocationInView().x;
    auto y = touch_->getLocationInView().y;
    handleTouchesEnd(1, &id, &x, &y);

    for (auto i = touches_.cbegin(); i != touches_.cend(); ++i) {
        if (*i == touch_) {
            touches_.erase(i);
            break;
        }
    }
}

void Self::keyPress(QKeyEvent* event) {
    Q_UNUSED(event);
    //
}

void Self::keyRelease(QKeyEvent* event) {
    Q_UNUSED(event);
    //
}
NS_CC_END
