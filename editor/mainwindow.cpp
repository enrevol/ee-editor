#include <ciso646>

#include "config.hpp"
#include "filesystemwatcher.hpp"
#include "inspectors/nodeinspector.hpp"
#include "mainwindow.hpp"
#include "projectresources.hpp"
#include "projectsettings.hpp"
#include "projectsettingsdialog.hpp"
#include "scene/mainsceneview.hpp"
#include "selection/selectiontree.hpp"
#include "settings.hpp"
#include "ui_mainwindow.h"

#include <base/CCDirector.h>

#include <QDebug>
#include <QFileDialog>

namespace ee {
using Self = MainWindow;

#ifdef interface // win32
#undef interface
#endif // interface

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
    ui_->closeProjectButton->setVisible(false);
    ui_->actionSave_As->setVisible(false);
    ui_->actionSave_All->setVisible(false);
    ui_->actionPublish->setVisible(false);
    ui_->actionPublish_Settings->setVisible(false);

    connect(ui_->createProjectButton, &QAction::triggered, this,
            &Self::createProject);

    connect(ui_->openProjectButton, &QAction::triggered, this,
            &Self::openProject);

    connect(ui_->saveButton, &QAction::triggered, this, &Self::saveInterface);

    connect(&Config::getInstance(), &Config::projectClosed, this,
            &Self::closeProject);

    connect(ui_->openProjectSettingsButton, &QAction::triggered, this,
            &Self::openProjectSettings);

    connect(ui_->createInterfaceButton, &QAction::triggered, this,
            &Self::createInterface);

    connect(ui_->resourceTree, &ResourceTree::imageSelected,
            [this](const QString& imagePath) {
                ui_->imageView->setImagePath(imagePath);
            });

    connect(ui_->resourceTree, &ResourceTree::spriteFrameSelected,
            [this](const QString& spriteFrameName) {
                ui_->imageView->setSpriteFrameName(spriteFrameName);
            });

    connect(ui_->resourceTree, &ResourceTree::noneSelected,
            [this] { ui_->imageView->clearDisplay(); });

    connect(ui_->resourceTree, &ResourceTree::interfaceSelected,
            [](const QString& path) {
                qDebug() << "open interface: " << path;
                Config::getInstance().loadInterface(QFileInfo(path));
            });

    connect(ui_->straightAlphaButton, &QPushButton::clicked,
            [this] { ui_->imageView->setBlendStraightAlpha(); });

    connect(ui_->premultipliedAlphaButton, &QPushButton::clicked,
            [this] { ui_->imageView->setBlendPremultipliedAlpha(); });

    // connect(ui_->addNodeButton, &QPushButton::clicked, [this] {
    //    auto scene = dynamic_cast<RootScene*>(
    //        cocos2d::Director::getInstance()->getRunningScene());
    // ui_->sceneTree->setRootNode(scene);
    //});

    /*
    connect(ui_->inspectorList, &InspectorListWidget::propertyValueChanged,
            [this](const SelectionPath& path, const QString& propertyName,
                   const cocos2d::Value& value) {
                auto sceneTree = ui_->sceneTree;
                auto rootScene = dynamic_cast<RootScene*>(
                    cocos2d::Director::getInstance()->getRunningScene());
                rootScene->updateSelectionProperty(sceneTree->getNodeGraph(),
                                                   path, propertyName, value);
                sceneTree->updateSelectionProperty(path, propertyName, value);
            });
            */

    // FIXME: RootScene hasn't been initialized.
    /*
    QTimer::singleShot(1, [this] {
        auto rootScene = dynamic_cast<RootScene*>(
            cocos2d::Director::getInstance()->getRunningScene());
        connect(
            rootScene, &RootScene::propertyValueChanged,
            [this](const SelectionPath& path, const QString& propertyName,
                   const cocos2d::Value& value) {
                qDebug() << "root scene change property " << propertyName;
                auto sceneTree = ui_->sceneTree;
                auto inspectorList = ui_->inspectorList;
                sceneTree->updateSelectionProperty(path, propertyName, value);
                inspectorList->refreshProperty(sceneTree->getNodeGraph(),
                                               sceneTree->currentSelection(),
                                               propertyName);
            });

        connect(rootScene, &RootScene::selectionTreeChanged,
                [this](const SelectionTree& selection) {
                    auto sceneTree = ui_->sceneTree;
                    auto list = ui_->inspectorList;

                    sceneTree->selectTree(selection);
                    list->setSelection(sceneTree->getNodeGraph(), selection);
                });
    });
    */

    /*
    connect(&Config::getInstance(), &Config::interfaceLoaded,
            [this](const QFileInfo& path) {
                Q_UNUSED(path);
                auto sceneTree = ui_->sceneTree;
                sceneTree->setNodeGraph(Config::getInstance()
                                            .getInterfaceSettings()
                                            ->getNodeGraph()
                                            .value());

                auto rootScene = dynamic_cast<RootScene*>(
                    cocos2d::Director::getInstance()->getRunningScene());
                rootScene->setNodeGraph(Config::getInstance()
                                            .getInterfaceSettings()
                                            ->getNodeGraph()
                                            .value());
            });
            */

    auto&& watcher = FileSystemWatcher::getInstance();
    connect(&watcher, &FileSystemWatcher::fileChanged,
            [this](const QString& path) {
                Q_UNUSED(path);
                ui_->resourceTree->updateResourceDirectories();
            });

    connect(&watcher, &FileSystemWatcher::directoryChanged,
            [this](const QString& path) {
                Q_UNUSED(path);
                ui_->resourceTree->updateResourceDirectories();
            });

    //  ui_->actionProject_Settings->setEnabled(false);
    //   ui_->actionInterface_File->setEnabled(false);
    //   ui_->actionSave->setEnabled(false);
    //   ui_->resourceTree->setListenToFileChangeEvents(false);
}

Self::~MainWindow() {
    delete ui_;
}

OpenGLWidget* Self::getOpenGLView() {
    return ui_->sceneView;
}

void Self::createProject() {
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
            // Nothing.
        }
    }
}

void Self::openProject() {
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

    ProjectResources::getInstance().addResources(config.getProjectSettings());
    // ui_->actionProject_Settings->setEnabled(true);
    // ui_->actionInterface_File->setEnabled(true);
    // ui_->resourceTree->setListenToFileChangeEvents(true);
}

void Self::closeProject(const QFileInfo& path) {
    Q_UNUSED(path);
    ProjectResources::getInstance().removeResources(
        Config::getInstance().getProjectSettings());
}

void Self::openProjectSettings() {
    qDebug() << Q_FUNC_INFO;

    auto&& config = Config::getInstance();
    Q_ASSERT(config.hasOpenedProject());
    auto&& settings = config.getProjectSettings();

    auto dialog = new ProjectSettingsDialog(this, settings);
    connect(dialog, &ProjectSettingsDialog::accepted, [this, dialog, &config] {
        config.setProjectSettings(dialog->getProjectSettings());
        config.saveProject();
        ui_->resourceTree->updateResourceDirectories();
    });
    dialog->exec();
}

void Self::createInterface() {
    auto&& config = Config::getInstance();
    auto path = QFileDialog::getSaveFileName(
        this, "New Interface",
        config.getProjectSettings().getProjectDirectory().absolutePath(),
        filter::interface);
    if (path.isEmpty()) {
        return;
    }
    qDebug() << "Create new interface: " << path;
    QFileInfo info(path);
    if (config.createInterface(info)) {
        if (config.loadInterface(info)) {
            loadInterface(info);
        }
    }
}

void Self::loadInterface(const QFileInfo& path) {
    Q_UNUSED(path);
    ui_->saveButton->setEnabled(true);
}

void Self::saveInterface() {
    auto&& config = Config::getInstance();
    auto&& settings = config.getInterfaceSettings();
    Q_ASSERT(settings.has_value());
    InterfaceSettings newSettings(settings->getInterfacePath());
    newSettings.setNodeGraph(ui_->sceneTree->getNodeGraph());
    config.setInterfaceSettings(newSettings);
    newSettings.write();
}
} // namespace ee
