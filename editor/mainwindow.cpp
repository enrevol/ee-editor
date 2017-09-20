#include <ciso646>

#include "config.hpp"
#include "mainwindow.hpp"
#include "projectsettings.hpp"
#include "projectsettingsdialog.hpp"
#include "rootscene.hpp"
#include "settings.hpp"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>

namespace ee {
using Self = MainWindow;

namespace filter {
constexpr auto project = "eeEditor Project File (*.eeeproj);;All Files (.*)";
constexpr auto interface = "eeInterface File (*.eeei);;All Files (.*)";
} // namespace filter

Self::MainWindow(QWidget* parent)
    : Super(parent)
    , ui_(new Ui::MainWindow()) {
    ui_->setupUi(this);

    // Not supported yet.
    ui_->actionClose->setVisible(false);
    ui_->actionClose_Project->setVisible(false);
    ui_->actionSave->setVisible(false);
    ui_->actionSave_As->setVisible(false);
    ui_->actionSave_All->setVisible(false);
    ui_->actionPublish->setVisible(false);
    ui_->actionPublish_Settings->setVisible(false);

    connect(ui_->actionProject_Settings, &QAction::triggered, this,
            &Self::onProjectSettingsButtonPressed);

    connect(ui_->actionProject, &QAction::triggered, [this] {
        Settings settings;
        auto path = QFileDialog::getSaveFileName(
            this, "New Project", settings.getLastBrowsingPath().absolutePath(),
            filter::project);

        if (path.isEmpty()) {
            return;
        }
        qDebug() << "Create new project: " << path;
        QFileInfo filePath(path);
        settings.setLastBrowsingPath(QDir(filePath.absolutePath()));
        auto&& config = Config::getInstance();
        if (config.createProject(filePath)) {
            if (config.loadProject(filePath)) {
                ui_->actionProject_Settings->setEnabled(true);
            }
        }
    });

    connect(ui_->actionOpen, &QAction::triggered, [this] {
        Settings settings;
        auto path = QFileDialog::getOpenFileName(
            this, "Open Project", settings.getLastBrowsingPath().absolutePath(),
            filter::project);

        if (path.isEmpty()) {
            return;
        }
        qDebug() << "select: " << path;
        QFileInfo filePath(path);
        settings.setLastBrowsingPath(QDir(filePath.absolutePath()));
        auto&& config = Config::getInstance();
        if (not config.loadProject(filePath)) {
            return;
        }
        ui_->actionProject_Settings->setEnabled(true);
        ui_->actionInterface_File->setEnabled(true);
        ui_->actionClose->setEnabled(true);
        ui_->actionClose_Project->setEnabled(true);
        ui_->actionSave->setEnabled(true);
        ui_->actionSave_As->setEnabled(true);
        ui_->actionSave_All->setEnabled(true);
        ui_->actionPublish->setEnabled(true);
        ui_->actionPublish_Settings->setEnabled(true);
        ui_->resourceTree->setListenToFileChangeEvents(true);
    });

    connect(ui_->actionInterface_File, &QAction::triggered, [this] {
        auto&& config = Config::getInstance();
        auto path = QFileDialog::getSaveFileName(
            this, "New Interface",
            config.getProjectSettings()->getProjectDirectory().absolutePath(),
            filter::interface);
        if (path.isEmpty()) {
            return;
        }
        qDebug() << "Create new interface: " << path;
        QFileInfo info(path);
        if (config.createInterface(info)) {
            if (config.loadInterface(info)) {
                // Nothing.
            }
        }
    });

    connect(
        ui_->resourceTree, &ResourceTree::fileSelected,
        [this](const QString& path) { ui_->imageView->setImagePath(path); });

    connect(ui_->addNodeButton, &QPushButton::clicked, [this] {
        auto scene = RootScene::getInstance();
        // ui_->sceneTree->setRootNode(scene);
    });

    connect(ui_->sceneTree,
            static_cast<void (SceneTree::*)(const SceneSelection&)>(
                &SceneTree::selectionChanged),
            [this](const SceneSelection& selection) {
                auto rootScene = RootScene::getInstance();
                rootScene->setSelection(selection);
            });

    ui_->actionProject_Settings->setEnabled(false);
    ui_->actionInterface_File->setEnabled(false);
    ui_->actionClose->setEnabled(false);
    ui_->actionClose_Project->setEnabled(false);
    ui_->actionSave->setEnabled(false);
    ui_->actionSave_As->setEnabled(false);
    ui_->actionSave_All->setEnabled(false);
    ui_->actionPublish->setEnabled(false);
    ui_->actionPublish_Settings->setEnabled(false);
    ui_->resourceTree->setListenToFileChangeEvents(false);
}

Self::~MainWindow() {
    delete ui_;
}

OpenGLWidget* Self::getOpenGLView() {
    return ui_->sceneView;
}

void Self::onProjectSettingsButtonPressed() {
    qDebug() << Q_FUNC_INFO;

    auto&& config = Config::getInstance();
    auto&& settings = config.getProjectSettings();
    Q_ASSERT(settings.has_value());

    auto dialog = new ProjectSettingsDialog(this, settings.value());
    connect(dialog, &ProjectSettingsDialog::accepted, [this, dialog, &config] {
        config.setProjectSettings(dialog->getProjectSettings());
        config.saveProject();
        ui_->resourceTree->updateResourceDirectories();
    });
    dialog->exec();
}
} // namespace ee
