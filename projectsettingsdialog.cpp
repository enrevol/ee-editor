#include "projectsettingsdialog.hpp"
#include "config.hpp"
#include "ui_projectsettingsdialog.h"

#include <QFileDialog>
#include <QStringListModel>

namespace ee {
ProjectSettingsDialog::ProjectSettingsDialog(QWidget* parent)
    : QDialog(parent)
    , ui_(new Ui::ProjectSettingsDialog) {
    ui_->setupUi(this);

    connect(ui_->contentProtectionKeyInput, &QLineEdit::textChanged,
            [this](const QString& value) {
                settings_->setContentProtectionKey(value);
            });

    connect(ui_->publishDirectoryInput, &QLineEdit::textChanged,
            [this](const QString& value) {
                settings_->setPublishDirectory(value);
            });

    connect(ui_->selectPublishDirectoryButton, &QPushButton::clicked,
            [this](bool) {
                QFileDialog dialog;
                dialog.setFileMode(QFileDialog::FileMode::Directory);
                dialog.setOption(QFileDialog::Option::ShowDirsOnly);

                auto&& currentDir = settings_->getPublishDirectory();
                if (currentDir.has_value()) {
                    dialog.setDirectory(currentDir.value());
                }

                dialog.exec();

                auto&& directory = dialog.directory();
                settings_->setPublishDirectory(directory);
                updatePublishDirectory(directory);
            });
}

ProjectSettingsDialog::~ProjectSettingsDialog() {
    delete ui_;
}

const ProjectSettings& ProjectSettingsDialog::getProjectSettings() const {
    return *settings_;
}

void ProjectSettingsDialog::setProjectSettings(
    const ProjectSettings& settings) {
    settings_ = std::make_unique<ProjectSettings>(settings);

    updateResourcesDirectories();
    updatePublishDirectory();
}

void ProjectSettingsDialog::updateResourcesDirectories() {
    updateResourcesDirectories(getProjectSettings().getResourceDirectories());
}

void ProjectSettingsDialog::updateResourcesDirectories(
    const QVector<QDir>& directories) {
    auto list = QStringList();

    for (const QDir& directory : directories) {
        list.append(directory.absolutePath());
    }

    auto model = new QStringListModel(list);
    ui_->resoucesPathList->setModel(model);
}

void ProjectSettingsDialog::updateContentProtectionKey() {
    auto&& key = getProjectSettings().getContentProtectionKey();
    if (key.has_value()) {
        updateContentProtectionKey(key.value());
    }
}

void ProjectSettingsDialog::updateContentProtectionKey(const QString& key) {
    ui_->contentProtectionKeyInput->setText(key);
}

void ProjectSettingsDialog::updatePublishDirectory() {
    auto&& dir = getProjectSettings().getPublishDirectory();
    if (dir.has_value()) {
        updatePublishDirectory(dir.value());
    }
}

void ProjectSettingsDialog::updatePublishDirectory(const QDir& directory) {
    ui_->publishDirectoryInput->setText(settings_->getRelativePath(directory));
}
} // namespace ee
