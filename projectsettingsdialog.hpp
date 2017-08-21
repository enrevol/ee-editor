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
    explicit ProjectSettingsDialog(QWidget* parent,
                                   const ProjectSettings& settings);

    virtual ~ProjectSettingsDialog() override;

    /// Gets the project settings.
    const ProjectSettings& getProjectSettings() const;

private:
    void updateResourcesDirectories();
    void updateResourcesDirectories(const QVector<QDir>& directories);

    void updateContentProtectionKey();
    void updateContentProtectionKey(const QString& key);

    void updatePublishDirectory();
    void updatePublishDirectory(const QDir& directory);

    ProjectSettings settings_;
    Ui::ProjectSettingsDialog* ui_;
};
} // namespace ee

#endif // EE_EDITOR_PROJECT_SETTINGS_DIALOG_HPP
