#include "projectsettingsdialog.hpp"
#include "config.hpp"
#include "ui_projectsettingsdialog.h"

namespace ee {
ProjectSettingsDialog::ProjectSettingsDialog(QWidget* parent)
    : QDialog(parent)
    , ui_(new Ui::ProjectSettingsDialog) {
    ui_->setupUi(this);

    connect(ui_->contentProtectionKeyInput, &QLineEdit::textChanged,
            [this](const QString& value) {
                settings_.setContentProtectionKey(value.toStdString());
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
        settings.getContentProtectionKey().c_str());
}
} // namespace ee
