#include "platform/qt/CCOpenGLWidget_Qt.hpp"
#include "base/CCDirector.h"

#include <QDebug>

NS_CC_BEGIN
using Self = OpenGLWidget;

Self::OpenGLWidget(QWidget* parent)
    : Super(parent)
    , mouseMoveCallback_(nullptr)
    , mousePressCallback_(nullptr)
    , mouseReleaseCallback_(nullptr)
    , keyPressCallback_(nullptr)
    , keyReleaseCallback_(nullptr)
    , resizeCallback_(nullptr) {
    qDebug() << __PRETTY_FUNCTION__;
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, [this] { update(); });

    setUpdatesEnabled(true);
    setRepaintInterval(1.0f / 60);
    timer_->start();
}

Self::~OpenGLWidget() {
    qDebug() << __PRETTY_FUNCTION__;
}

void Self::initializeGL() {
    qDebug() << __PRETTY_FUNCTION__;
    initializeOpenGLFunctions();
}

void Self::resizeGL(int width, int height) {
    qDebug() << __PRETTY_FUNCTION__ << ": width = " << width
             << " height = " << height;
}

void Self::paintGL() {
    // qDebug() << __PRETTY_FUNCTION__;
    if (repaintCallback_) {
        repaintCallback_();
    }
}

void Self::setRepaintInterval(int milliseconds) {
    repaintInterval_ = milliseconds;
    timer_->setInterval(milliseconds);
}

void Self::setRepaintCallback(const RepaintCallback& callback) {
    repaintCallback_ = callback;
}

void Self::setMouseMoveCallback(const MouseEventCallback& callback) {
    mouseMoveCallback_ = callback;
}

void Self::setMousePressCallback(const MouseEventCallback& callback) {
    mousePressCallback_ = callback;
}

void Self::setMouseReleaseCallback(const MouseEventCallback& callback) {
    mouseReleaseCallback_ = callback;
}

void Self::setKeyPressCallback(const KeyEventCallback& callback) {
    keyPressCallback_ = callback;
}

void Self::setKeyReleaseCallback(const KeyEventCallback& callback) {
    keyReleaseCallback_ = callback;
}

void Self::setResizeCallback(const ResizeEventCallback& callback) {
    resizeCallback_ = callback;
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
    if (keyPressCallback_) {
        keyPressCallback_(event);
    }
    Super::keyPressEvent(event);
}

void Self::keyReleaseEvent(QKeyEvent* event) {
    if (keyReleaseCallback_) {
        keyReleaseCallback_(event);
    }
    Super::keyReleaseEvent(event);
}

void Self::resizeEvent(QResizeEvent* event) {
    qDebug() << __PRETTY_FUNCTION__ << ": width = " << event->size().width()
             << " height = " << event->size().height();
    if (resizeCallback_) {
        resizeCallback_(event);
    }
    Super::resizeEvent(event);
}
NS_CC_END
