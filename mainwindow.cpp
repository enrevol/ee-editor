#include "mainwindow.hpp"
#include "config.hpp"
#include "projectsettingsdialog.hpp"
#include "settings.hpp"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>

namespace ee {
namespace {
constexpr auto filter = "CocosBuilder Project File (*.ccbproj);;All Files (.*)";
} // namespace

MainWindow::MainWindow(QWidget* parent)
    : Super(parent)
    , ui_(new Ui::MainWindow()) {
    ui_->setupUi(this);

    connect(ui_->actionProject_Settings, &QAction::triggered, this,
            &Self::onProjectSettingsButtonPressed);

    connect(ui_->actionProject, &QAction::triggered, [this] {
        Settings settings;
        auto path = QFileDialog::getSaveFileName(
            this, "New Project", settings.getLastBrowsingPath().absolutePath(),
            filter);

        if (not path.isEmpty()) {
            qDebug() << "select: " << path;
            auto&& filePath = QDir(path);
            settings.setLastBrowsingPath(filePath);
            auto&& config = Config::getInstance();
            if (config.createProject(filePath)) {
                config.loadProject(filePath);
            }
        }
    });

    connect(ui_->actionOpen, &QAction::triggered, [this] {
        Settings settings;
        auto path = QFileDialog::getOpenFileName(
            this, "Open Project", settings.getLastBrowsingPath().absolutePath(),
            filter);

        if (not path.isEmpty()) {
            qDebug() << "select: " << path;
            auto&& filePath = QDir(path);
            settings.setLastBrowsingPath(filePath);
            auto&& config = Config::getInstance();
            config.loadProject(filePath);
        }
    });
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
        config.saveProject();
    });

    auto&& settings = config.getProjectSettings();
    Q_ASSERT(settings.has_value());
    dialog->setProjectSettings(settings.value());
    dialog->exec();
}
} // namespace ee
