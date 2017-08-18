#include "mainwindow.hpp"
#include "ui_mainwindow.h"

namespace ee {
MainWindow::MainWindow(QWidget* parent)
    : Super(parent)
    , view_(new Ui::MainWindow()) {
    view_->setupUi(this);
}

MainWindow::~MainWindow() {
}
} // namespace ee
