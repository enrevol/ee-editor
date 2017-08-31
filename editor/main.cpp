#include "appdelegate.hpp"
#include "mainwindow.hpp"
#include "openglwidget.hpp"

#include "platform/qt/CCOpenGLWidget_Qt.hpp"

#include <QApplication>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSurfaceFormat>

int main(int argc, char* argv[]) {
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
    QSurfaceFormat::setDefaultFormat(format);

    ee::AppDelegate app(argc, argv);
    // QApplication app(argc, argv);

    ee::MainWindow window;
    window.show();

    app.setOpenGLView(window.getOpenGLView());

    return cocos2d::Application::getInstance()->run();
    // return app.exec();
}
