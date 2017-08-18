#ifndef EE_EDITOR_PROJECT_SETTINGS_HPP
#define EE_EDITOR_PROJECT_SETTINGS_HPP

#include "optional.hpp"

#include <QDir>
#include <QVector>

namespace ee {
class ProjectSettings {
private:
    using Self = ProjectSettings;

public:
    /// Constructs a project settings.
    /// @param projectPath The project's path.
    ProjectSettings(const QDir& projectPath);
    ~ProjectSettings();

    const QDir& getProjectPath() const;
    const QString& getRelativeFilePath(const QDir& path) const;

    const QVector<QDir>& getResourceDirectories() const;
    void setResourceDirectories(const QVector<QDir>& directories);

    /// Gets the content protection key, used by TexturePacker.
    const std::optional<QString>& getContentProtectionKey() const;
    void setContentProtectionKey(const QString& key);

    /// Gets the publish directory.
    const std::optional<QDir>& getPublishDirectory() const;
    void setPublishDirectory(const QDir& directory);

    void readFromFile();
    void writeToFile();

    void read(const QJsonObject& json);
    QJsonObject write() const;

private:
    QDir projectPath_;
    QVector<QDir> resourcesDirectories_;
    std::optional<QString> contentProtectionKey_;
    std::optional<QDir> publishDirectory_;
};
} // namespace ee

#endif // EE_EDITOR_PROJECT_SETTINGS_HPP
