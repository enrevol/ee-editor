#include "projectsettingsdialog.hpp"
#include "config.hpp"
#include "ui_projectsettingsdialog.h"

#include <QStringListModel>

namespace ee {
ProjectSettingsDialog::ProjectSettingsDialog(QWidget* parent)
    : QDialog(parent)
    , ui_(new Ui::ProjectSettingsDialog) {
    ui_->setupUi(this);

    connect(ui_->contentProtectionKeyInput, &QLineEdit::textChanged,
            [this](const QString& value) {
                settings_.setContentProtectionKey(value.toStdString());
            });

    connect(ui_->publishDirectoryInput, &QLineEdit::textChanged,
            [this](const QString& value) {
                settings_.setPublishDirectory(value.toStdString());
            });
}

ProjectSettingsDialog::~ProjectSettingsDialog() {
    delete ui_;
}

const ProjectSettings& ProjectSettingsDialog::getProjectSettings() const {
    return settings_;
}

void ProjectSettingsDialog::setProjectSettings(
    const ProjectSettings& settings) {
    settings_ = settings;

    ui_->contentProtectionKeyInput->setText(
        QString::fromStdString(settings.getContentProtectionKey()));

    ui_->publishDirectoryInput->setText(
        QString::fromStdString(settings.getPublishDirectory()));

    updateResourcesPaths();
}

void ProjectSettingsDialog::updateResourcesPaths() {
    auto list = QStringList();

    auto&& resourcesPaths = settings_.getResourcesPaths();
    for (auto&& path : resourcesPaths) {
        list.append(QString::fromStdString(path));
    }

    auto model = new QStringListModel(list);
    ui_->resoucesPathList->setModel(model);
}
} // namespace ee
