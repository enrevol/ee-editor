#include <ciso646>

#include "config.hpp"
#include "projectsettingsdialog.hpp"
#include "ui_projectsettingsdialog.h"

#include <QDebug>
#include <QFileDialog>
#include <QStringListModel>

namespace ee {
ProjectSettingsDialog::ProjectSettingsDialog(QWidget* parent,
                                             const ProjectSettings& settings)
    : Super(parent)
    , settings_(settings)
    , ui_(new Ui::ProjectSettingsDialog) {
    ui_->setupUi(this);

    updateResourcesDirectories();
    updatePublishDirectory();

    connect(ui_->contentProtectionKeyInput, &QLineEdit::textChanged,
            [this](const QString& value) {
                settings_.setContentProtectionKey(value);
            });

    connect(ui_->publishDirectoryInput, &QLineEdit::textChanged,
            [this](const QString& value) { //
                settings_.setPublishDirectory(value);
            });

    connect(ui_->selectPublishDirectoryButton, &QPushButton::clicked,
            [this](bool) {
                auto directory = QFileDialog::getExistingDirectory(
                    this, "Select publish directory",
                    settings_.getPublishDirectory().absolutePath(),
                    QFileDialog::Option::ShowDirsOnly);
                if (directory.isEmpty()) {
                    return;
                }
                qDebug() << "select: " << directory;
                settings_.setPublishDirectory(directory);
                updatePublishDirectory(directory);
            });

    connect(ui_->addResourceDirButton, &QPushButton::clicked, [this] {
        auto directory = QFileDialog::getExistingDirectory(
            this, "Add resource directory",
            settings_.getProjectDirectory().absolutePath(),
            QFileDialog::Option::ShowDirsOnly);
        if (directory.isEmpty()) {
            return;
        }
        qDebug() << "select: " << directory;
        if (not settings_.addResourceDirectory(directory)) {
            return;
        }
        updateResourcesDirectories();
    });

    connect(ui_->removeResourceDirButton, &QPushButton::clicked, [this] {
        auto currentIndex = ui_->resoucesDirList->currentIndex();
        auto text = currentIndex.data(Qt::ItemDataRole::DisplayRole).toString();
        auto directory = settings_.getProjectDirectory().filePath(text);
        qDebug() << "select: " << directory;
        if (not settings_.removeResourceDirectory(directory)) {
            return;
        }
        updateResourcesDirectories();
    });
}

ProjectSettingsDialog::~ProjectSettingsDialog() {
    delete ui_;
}

const ProjectSettings& ProjectSettingsDialog::getProjectSettings() const {
    return settings_;
}

void ProjectSettingsDialog::updateResourcesDirectories() {
    updateResourcesDirectories(getProjectSettings().getResourceDirectories());
}

void ProjectSettingsDialog::updateResourcesDirectories(
    const QVector<QDir>& directories) {
    auto list = QStringList();

    for (const QDir& directory : directories) {
        list.append(settings_.getRelativePath(directory));
    }

    auto model = new QStringListModel(list);
    ui_->resoucesDirList->setModel(model);
}

void ProjectSettingsDialog::updateContentProtectionKey() {
    auto&& key = getProjectSettings().getContentProtectionKey();
    updateContentProtectionKey(key.toString());
}

void ProjectSettingsDialog::updateContentProtectionKey(const QString& key) {
    ui_->contentProtectionKeyInput->setText(key);
}

void ProjectSettingsDialog::updatePublishDirectory() {
    auto&& dir = getProjectSettings().getPublishDirectory();
    updatePublishDirectory(dir);
}

void ProjectSettingsDialog::updatePublishDirectory(const QDir& directory) {
    ui_->publishDirectoryInput->setText(settings_.getRelativePath(directory));
}
} // namespace ee
