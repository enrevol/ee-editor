#include <ciso646>

#include "config.hpp"
#include "filesystemwatcher.hpp"
#include "mainwindow.hpp"
#include "nodeinspector.hpp"
#include "projectsettings.hpp"
#include "projectsettingsdialog.hpp"
#include "rootscene.hpp"
#include "selectiontree.hpp"
#include "settings.hpp"
#include "ui_mainwindow.h"
#include "widgetinspector.hpp"

#include <base/CCDirector.h>

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
                // Nothing.
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
    });

    connect(ui_->actionSave, &QAction::triggered, [this] {
        auto&& config = Config::getInstance();
        auto&& settings = config.getInterfaceSettings();
        Q_ASSERT(settings.has_value());
        InterfaceSettings newSettings(settings->getInterfacePath());
        newSettings.setNodeGraph(ui_->sceneTree->getNodeGraph());
        config.setInterfaceSettings(newSettings);
        newSettings.write();
    });

    connect(&Config::getInstance(), &Config::projectLoaded,
            [this](const QFileInfo& path) {
                Q_UNUSED(path);
                ui_->actionProject_Settings->setEnabled(true);
                ui_->actionInterface_File->setEnabled(true);
                ui_->resourceTree->setListenToFileChangeEvents(true);
            });

    connect(&Config::getInstance(), &Config::interfaceLoaded,
            [this](const QFileInfo& path) {
                Q_UNUSED(path);
                ui_->actionSave->setEnabled(true);
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
        auto scene = dynamic_cast<RootScene*>(
            cocos2d::Director::getInstance()->getRunningScene());
        // ui_->sceneTree->setRootNode(scene);
    });

    connect(ui_->sceneTree, &SceneTree::selectionTreeChanged,
            [this](const SelectionTree& selection) {
                auto rootScene = dynamic_cast<RootScene*>(
                    cocos2d::Director::getInstance()->getRunningScene());

                rootScene->setSelection(selection);

                auto list = ui_->inspectorList;
                list->clearInspectors();

                if (selection.isEmpty()) {
                    return;
                }
                list->addInspector(new NodeInspector());
                list->addInspector(new WidgetInspector());
                list->refreshPropertyValue(ui_->sceneTree->getNodeGraph(),
                                           selection);
            });

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

    // FIXME: RootScene hasn't been initialized.
    QTimer::singleShot(1, [this] {
        auto rootScene = dynamic_cast<RootScene*>(
            cocos2d::Director::getInstance()->getRunningScene());
        connect(rootScene, &RootScene::propertyValueChanged,
                [this](const SelectionPath& path, const QString& propertyName,
                       const cocos2d::Value& value) {
                    qDebug() << "root scene change property " << propertyName;
                    auto sceneTree = ui_->sceneTree;
                    auto inspectorList = ui_->inspectorList;
                    sceneTree->updateSelectionProperty(path, propertyName,
                                                       value);
                    inspectorList->refreshPropertyValue(
                        sceneTree->getNodeGraph(),
                        sceneTree->currentSelection(), propertyName);
                });

        connect(rootScene, &RootScene::selectionTreeChanged,
                [this](const SelectionTree& selection) {
                    auto sceneTree = ui_->sceneTree;
                    sceneTree->selectTree(selection);

                    auto list = ui_->inspectorList;
                    list->clearInspectors();

                    if (selection.isEmpty()) {
                        return;
                    }
                    list->addInspector(new NodeInspector());
                    list->addInspector(new WidgetInspector());
                    list->refreshPropertyValue(ui_->sceneTree->getNodeGraph(),
                                               selection);
                });
    });

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

    ui_->actionProject_Settings->setEnabled(false);
    ui_->actionInterface_File->setEnabled(false);
    ui_->actionSave->setEnabled(false);
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
