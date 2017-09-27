#include "platform/qt/CCOpenGLWidget_Qt.hpp"
#include "base/CCDirector.h"

#include <QDebug>

NS_CC_BEGIN
using Self = OpenGLWidget;

Self::OpenGLWidget(QWidget* parent)
    : Super(parent) {
    qDebug() << Q_FUNC_INFO;
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, [this] { update(); });

    setUpdatesEnabled(true);
    setRepaintInterval(static_cast<int>(1.0f / 60 * 1000));
    timer_->start();
}

Self::~OpenGLWidget() {
    qDebug() << Q_FUNC_INFO;
}

void Self::initializeGL() {
    qDebug() << Q_FUNC_INFO;
    auto f = context()->functions();
    f->initializeOpenGLFunctions();

    // Enable point size by default.
    f->glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

void Self::resizeGL(int width, int height) {
    Q_UNUSED(width);
    Q_UNUSED(height);
}

void Self::paintGL() {
    // qDebug() << __PRETTY_FUNCTION__;
    Q_EMIT onPainted();
}

void Self::setRepaintInterval(int milliseconds) {
    repaintInterval_ = milliseconds;
    timer_->setInterval(milliseconds);
}

void Self::mouseMoveEvent(QMouseEvent* event) {
    Super::mouseMoveEvent(event);
    Q_EMIT onMouseMoved(event);
}

void Self::mousePressEvent(QMouseEvent* event) {
    Super::mousePressEvent(event);
    Q_EMIT onMousePressed(event);
}

void Self::mouseReleaseEvent(QMouseEvent* event) {
    Super::mouseReleaseEvent(event);
    Q_EMIT onMouseReleased(event);
}

void Self::keyPressEvent(QKeyEvent* event) {
    qDebug() << Q_FUNC_INFO << ": " << event->text();
    Super::keyPressEvent(event);
    Q_EMIT onKeyPressed(event);
}

void Self::keyReleaseEvent(QKeyEvent* event) {
    qDebug() << Q_FUNC_INFO << ": " << event->text();
    Super::keyReleaseEvent(event);
    Q_EMIT onKeyReleased(event);
}

void Self::resizeEvent(QResizeEvent* event) {
    qDebug() << Q_FUNC_INFO << ": width = " << event->size().width()
             << " height = " << event->size().height();
    Super::resizeEvent(event);
    Q_EMIT onResized(event);
}

void Self::wheelEvent(QWheelEvent* event) {
    Super::wheelEvent(event);
    Q_EMIT onWheeled(event);
}

NS_CC_END
