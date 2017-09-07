#include <ciso646>

#include "config.hpp"
#include "mainwindow.hpp"
#include "projectsettingsdialog.hpp"
#include "rootscene.hpp"
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
            filter);

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
            filter);

        if (path.isEmpty()) {
            return;
        }
        qDebug() << "select: " << path;
        QFileInfo filePath(path);
        settings.setLastBrowsingPath(QDir(filePath.absolutePath()));
        auto&& config = Config::getInstance();
        if (config.loadProject(filePath)) {
            ui_->actionProject_Settings->setEnabled(true);
        ui_->actionProject_Settings->setEnabled(true);
        ui_->actionInterface_File->setEnabled(true);
        ui_->actionClose->setEnabled(true);
        ui_->actionClose_Project->setEnabled(true);
        ui_->actionSave->setEnabled(true);
        ui_->actionSave_As->setEnabled(true);
        ui_->actionSave_All->setEnabled(true);
        ui_->actionPublish->setEnabled(true);
        ui_->actionPublish_Settings->setEnabled(true);
        }
    });

    connect(ui_->selectTextureButton, &QPushButton::clicked, [this] {
        auto path = QFileDialog::getOpenFileName(
            this, "Select image", "",
            "Portable Network Graphics (*.png);;All Files (.*)");

        if (path.isEmpty()) {
            return;
        }
        qDebug() << "select image: " << path;
        if (not RootScene::getInstance()->setTexturePath(path)) {
            QMessageBox::critical(this, "Error", "Invalid image",
                                  QMessageBox::StandardButton::Ok);
        } else {
            ui_->textureInput->setText(path);
        }
    });

    connect(ui_->compileShaderButton, &QPushButton::clicked, [this] {
        auto vertexShader = ui_->vertexShaderInput->toPlainText();
        auto fragmentShader = ui_->fragmentShaderInput->toPlainText();
        auto succeeded =
            RootScene::getInstance()->setShader(vertexShader, fragmentShader);
        if (not succeeded) {
            QMessageBox::critical(this, "Error", "Failed to compile the shader",
                                  QMessageBox::StandardButton::Ok);
        }
    });

    connect(ui_->addNodeButton, &QPushButton::clicked, [this] {
        auto scene = RootScene::getInstance();
        // ui_->sceneTree->setRootNode(scene);
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

    ui_->fragmentShaderInput->setLineNumbersVisible(true);
    ui_->vertexShaderInput->setLineNumbersVisible(true);
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
    connect(dialog, &ProjectSettingsDialog::accepted, [dialog, &config] {
        config.setProjectSettings(dialog->getProjectSettings());
        config.saveProject();
    });
    dialog->exec();
}
} // namespace ee
