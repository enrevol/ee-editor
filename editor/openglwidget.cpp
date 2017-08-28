#include "openglwidget.hpp"

#include <QDebug>

namespace ee {
using Self = OpenGLWidget;

Self::OpenGLWidget(QWidget* parent)
    : Super(parent) {
    qDebug() << __PRETTY_FUNCTION__;
}

Self::~OpenGLWidget() {
    qDebug() << __PRETTY_FUNCTION__;
}
} // namespace ee
