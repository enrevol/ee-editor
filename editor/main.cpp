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
    // QApplication app(argc, argv);

    ee::MainWindow window;
    window.show();

    app.setOpenGLView(window.getOpenGLView());

    return cocos2d::Application::getInstance()->run();
    // return app.exec();
}
