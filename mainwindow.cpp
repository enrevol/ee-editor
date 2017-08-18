#include "mainwindow.hpp"
#include "config.hpp"
#include "projectsettingsdialog.hpp"
#include "ui_mainwindow.h"

#include <QDebug>

namespace ee {
MainWindow::MainWindow(QWidget* parent)
    : Super(parent)
    , ui_(new Ui::MainWindow()) {
    ui_->setupUi(this);

    connect(ui_->actionProject_Settings, &QAction::triggered, this,
            &Self::onProjectSettingsButtonPressed);
}

MainWindow::~MainWindow() {
    delete ui_;
}

void MainWindow::onProjectSettingsButtonPressed() {
    qDebug() << __PRETTY_FUNCTION__;
    auto dialog = new ProjectSettingsDialog(this);

    connect(dialog, &ProjectSettingsDialog::accepted, [dialog] {
        Config::getInstance().setProjectSettings(dialog->getProjectSettings());
    });

    dialog->setProjectSettings(Config::getInstance().getProjectSettings());
    dialog->exec();
}
} // namespace ee
