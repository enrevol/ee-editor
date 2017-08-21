#ifndef EE_EDITOR_PROJECT_SETTINGS_HPP
#define EE_EDITOR_PROJECT_SETTINGS_HPP

#include "contentprotectionkey.hpp"
#include "iserializable.hpp"
#include "optional.hpp"

#include <QDir>
#include <QVector>

namespace ee {
class ProjectSettings : public ISerializable {
private:
    using Self = ProjectSettings;

public:
    /// Constructs a project settings.
    /// @param projectPath The project's path.
    ProjectSettings(const QDir& projectPath);
    ~ProjectSettings();

    /// Gets the project's path.
    const QDir& getProjectPath() const;

    /// Gets the relative path to the project path.
    QString getRelativePath(const QDir& path) const;

    /// Gets the resource directories.
    const QVector<QDir>& getResourceDirectories() const;

    /// Sets the resource directories.
    /// @param directories The desired directories.
    void setResourceDirectories(const QVector<QDir>& directories);

    /// Gets the content protection key, used by TexturePacker.
    const ContentProtectionKey& getContentProtectionKey() const;

    /// Sets the content protection key.
    /// @param key The content protection key.
    void setContentProtectionKey(const ContentProtectionKey& key);

    /// Gets the publish directory.
    /// Defaults is projectPath/generated.
    const QDir& getPublishDirectory() const;
    void setPublishDirectory(const QDir& directory);

    virtual bool deserialize(const QJsonObject& json) override;
    virtual void serialize(QJsonObject& json) const override;

    /// Attempts to read from file.
    bool read();

    /// Attempts to write to file.
    bool write() const;

private:
    QDir projectPath_;
    QVector<QDir> resourcesDirectories_;
    ContentProtectionKey contentProtectionKey_;
    QDir publishDirectory_;
};
} // namespace ee

#endif // EE_EDITOR_PROJECT_SETTINGS_HPP
