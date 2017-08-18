#ifndef PROJECTSETTINGSDIALOG_HPP
#define PROJECTSETTINGSDIALOG_HPP

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
    Ui::ProjectSettingsDialog* ui_;

    ProjectSettings settings_;
};
} // namespace ee

#endif // PROJECTSETTINGSDIALOG_HPP
