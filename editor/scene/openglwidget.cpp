#include "openglwidget.hpp"

#include <QDebug>

namespace ee {
using Self = OpenGLWidget;

Self::OpenGLWidget(QWidget* parent)
    : Super(parent) {
    qDebug() << Q_FUNC_INFO;

    QSurfaceFormat format;
    format.setVersion(2, 1);
    format.setProfile(QSurfaceFormat::OpenGLContextProfile::CoreProfile);
    format.setRenderableType(QSurfaceFormat::RenderableType::OpenGL);
    format.setSwapBehavior(QSurfaceFormat::SwapBehavior::DoubleBuffer);
    format.setRedBufferSize(8);
    format.setGreenBufferSize(8);
    format.setBlueBufferSize(8);
    format.setAlphaBufferSize(8);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    setFormat(format);
}

Self::~OpenGLWidget() {
    qDebug() << Q_FUNC_INFO;
}

void Self::initializeGL() {
    Super::initializeGL();
    qDebug() << QString::asprintf(
        "initializeGL: context %p sharedContext %p",
        static_cast<const void*>(context()),
        static_cast<const void*>(context()->shareContext()));
}
} // namespace ee
