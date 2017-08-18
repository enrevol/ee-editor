#include "projectsettings.hpp"

#include <QJsonArray>
#include <QJsonObject>

namespace ee {
ProjectSettings::ProjectSettings(const QDir& projectPath)
    : projectPath_(projectPath) {}

ProjectSettings::~ProjectSettings() {}

const QDir& ProjectSettings::getProjectPath() const {
    return projectPath_;
}

const QString& ProjectSettings::getRelativeFilePath(const QDir& path) const {
    return path.relativeFilePath(projectPath_.absolutePath());
}

const QVector<QDir>& ProjectSettings::getResourceDirectories() const {
    return resourcesDirectories_;
}

void ProjectSettings::setResourceDirectories(const QVector<QDir>& directories) {
    resourcesDirectories_ = directories;
}

const std::optional<QString>& ProjectSettings::getContentProtectionKey() const {
    return contentProtectionKey_;
}

void ProjectSettings::setContentProtectionKey(const QString& key) {
    contentProtectionKey_ = key;
}

const std::optional<QDir>& ProjectSettings::getPublishDirectory() const {
    return publishDirectory_;
}

void ProjectSettings::setPublishDirectory(const QDir& directory) {
    publishDirectory_ = directory;
}

void ProjectSettings::readFromFile() {}

void ProjectSettings::writeToFile() {}

void ProjectSettings::read(const QJsonObject& json) {
    // setContentProtectionKey(json["AA"].toString());
}

QJsonObject ProjectSettings::write() const {
    QJsonObject dict;

    QJsonArray dirs;
    for (const QDir& dir : getResourceDirectories()) {
        QJsonObject obj;
        obj["path"] = getRelativeFilePath(dir);
    }
    dict["resourcePaths"] = dirs;

    if (getContentProtectionKey().has_value()) {
        dict["contentProtectionKey"] = getContentProtectionKey().value();
    }

    if (getPublishDirectory().has_value()) {
        dict["publishDirectory"] =
            getRelativeFilePath(getPublishDirectory().value());
    }

    return dict;
}
} // namespace ee
