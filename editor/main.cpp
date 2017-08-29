#include "appdelegate.hpp"
#include "mainwindow.hpp"
#include "openglwidget.hpp"

#include "platform/qt/CCOpenGLWidget_Qt.hpp"

#include <QApplication>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSurfaceFormat>

int main(int argc, char* argv[]) {
    ee::AppDelegate app(argc, argv);

    QSurfaceFormat format;
    format.setVersion(3, 1);
    format.setProfile(QSurfaceFormat::OpenGLContextProfile::CompatibilityProfile);
    format.setRenderableType(QSurfaceFormat::RenderableType::OpenGL);
    format.setSwapBehavior(QSurfaceFormat::SwapBehavior::DoubleBuffer);
    format.setRedBufferSize(8);
    format.setGreenBufferSize(8);
    format.setBlueBufferSize(8);
    format.setAlphaBufferSize(8);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    QSurfaceFormat::setDefaultFormat(format);

    // QApplication a(argc, argv);
    ee::MainWindow window;
    window.show();

    app.setOpenGLView(window.getOpenGLView());

    // QOpenGLFunctions gl(view->context());
    // gl.initializeOpenGLFunctions();

    return cocos2d::Application::getInstance()->run();
    return app.exec();
}
