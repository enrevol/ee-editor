#include "platform/qt/CCOpenGLWidget_Qt.hpp"

NS_CC_BEGIN
using Self = OpenGLWidget;

Self::OpenGLWidget(QWidget* parent, int width, int height)
    : Super(parent)
    , mouseMoveCallback_(nullptr)
    , mousePressCallback_(nullptr)
    , mouseReleaseCallback_(nullptr)
    , resizeCallback_(nullptr)
    , keyEventCallback_(nullptr) {
    resize(width, height);
}

Self::~OpenGLWidget() {}

void Self::setMouseMoveCallback(const MouseEventCallback& callback) {
    mouseMoveCallback_ = callback;
}

void Self::setMousePressCallback(const MouseEventCallback& callback) {
    mousePressCallback_ = callback;
}

void Self::setMouseReleaseCallback(const MouseEventCallback& callback) {
    mouseReleaseCallback_ = callback;
}

void Self::setResizeCallback(const ResizeEventCallback& callback) {
    resizeCallback_ = callback;
}

void Self::setKeyEventCallback(const KeyEventCallback& callback) {
    keyEventCallback_ = callback;
}

void Self::mouseMoveEvent(QMouseEvent* event) {
    if (mouseMoveCallback_) {
        mouseMoveCallback_(event);
    }
    Super::mouseMoveEvent(event);
}

void Self::mousePressEvent(QMouseEvent* event) {
    if (mousePressCallback_) {
        mousePressCallback_(event);
    }
    Super::mousePressEvent(event);
}

void Self::mouseReleaseEvent(QMouseEvent* event) {
    if (mouseReleaseCallback_) {
        mouseReleaseCallback_(event);
    }
    Super::mouseReleaseEvent(event);
}

void Self::keyPressEvent(QKeyEvent* event) {
    if (keyEventCallback_) {
        keyEventCallback_(event);
    }
    Super::keyPressEvent(event);
}

void Self::keyReleaseEvent(QKeyEvent* event) {
    if (keyEventCallback_) {
        keyEventCallback_(event);
    }
    Super::keyReleaseEvent(event);
}

void Self::resizeEvent(QResizeEvent* event) {
    if (resizeCallback_) {
        resizeCallback_(event);
    }
    Super::resizeEvent(event);
}

NS_CC_END
