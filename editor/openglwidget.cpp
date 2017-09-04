#include "openglwidget.hpp"

#include <QDebug>

namespace ee {
using Self = OpenGLWidget;

Self::OpenGLWidget(QWidget* parent)
    : Super(parent) {
    qDebug() << Q_FUNC_INFO;
}

Self::~OpenGLWidget() {
    qDebug() << Q_FUNC_INFO;
}
} // namespace ee
