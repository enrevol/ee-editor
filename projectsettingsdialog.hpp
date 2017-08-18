#ifndef EE_EDITOR_PROJECT_SETTINGS_DIALOG_HPP
#define EE_EDITOR_PROJECT_SETTINGS_DIALOG_HPP

#include "projectsettings.hpp"

#include <QDialog>

namespace Ui {
class ProjectSettingsDialog;
} // namespace Ui

namespace ee {
class ProjectSettingsDialog : public QDialog {
    Q_OBJECT

    using Self = ProjectSettingsDialog;
    using Super = QDialog;

public:
    explicit ProjectSettingsDialog(QWidget* parent = nullptr);
    virtual ~ProjectSettingsDialog() override;

    const ProjectSettings& getProjectSettings() const;
    void setProjectSettings(const ProjectSettings& settings);

private:
    void updateResourcesPaths();

    Ui::ProjectSettingsDialog* ui_;

    ProjectSettings settings_;
};
} // namespace ee

#endif // EE_EDITOR_PROJECT_SETTINGS_DIALOG_HPP
