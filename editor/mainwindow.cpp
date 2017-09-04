#include <ciso646>

#include "mainwindow.hpp"
#include "config.hpp"
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

    connect(ui_->selectTextureButton, &QPushButton::clicked, [this] {
        auto path = QFileDialog::getOpenFileName(
            this, "Select image", "",
            "Portable Network Graphics (*.png);;All Files (.*)");

        if (not path.isEmpty()) {
            qDebug() << "select image: " << path;
            if (not RootScene::getInstance()->setTexturePath(path)) {
                QMessageBox::critical(this, "Error", "Invalid image",
                                      QMessageBox::StandardButton::Ok);
            } else {
                ui_->textureInput->setText(path);
            }
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

    ui_->actionProject_Settings->setEnabled(false);
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
