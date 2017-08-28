#include "mainwindow.hpp"
#include "config.hpp"
#include "projectsettingsdialog.hpp"
#include "settings.hpp"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>

namespace ee {
using Self = MainWindow;

namespace {
constexpr auto filter = "CocosBuilder Project File (*.ccbproj);;All Files (.*)";
} // namespace

Self::MainWindow(QWidget* parent)
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
            qDebug() << "Create new project: " << path;
            auto&& filePath = QDir(path);
            settings.setLastBrowsingPath(filePath);
            auto&& config = Config::getInstance();
            if (config.createProject(filePath)) {
                if (config.loadProject(filePath)) {
                    ui_->actionProject_Settings->setEnabled(true);
                }
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
            if (config.loadProject(filePath)) {
                ui_->actionProject_Settings->setEnabled(true);
            }
        }
    });

    ui_->actionProject_Settings->setEnabled(false);
}

Self::~MainWindow() {
    delete ui_;
}

OpenGLWidget* Self::getOpenGLView() {
    return ui_->sceneView;
}

void Self::onProjectSettingsButtonPressed() {
    qDebug() << __PRETTY_FUNCTION__;

    auto&& config = Config::getInstance();
    auto&& settings = config.getProjectSettings();
    Q_ASSERT(settings.has_value());

    auto dialog = new ProjectSettingsDialog(this, settings.value());
    connect(dialog, &ProjectSettingsDialog::accepted, [dialog, &config] {
        config.setProjectSettings(dialog->getProjectSettings());
        config.saveProject();
    });
    dialog->exec();
}
} // namespace ee
