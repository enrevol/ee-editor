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

    auto&& config = Config::getInstance();
    connect(dialog, &ProjectSettingsDialog::accepted, [dialog, &config] {
        config.setProjectSettings(dialog->getProjectSettings());
    });

    auto&& settings = config.getProjectSettings();
    Q_ASSERT(settings.has_value());
    dialog->setProjectSettings(settings.value());
    dialog->exec();
}
} // namespace ee
