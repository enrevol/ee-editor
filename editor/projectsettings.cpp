#include <ciso646>

#include "projectsettings.hpp"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace ee {
namespace key {
constexpr auto resource_paths = "resourcePaths";
constexpr auto publish_directory = "publishDirectory";
} // namespace key

ProjectSettings::ProjectSettings(const QDir& projectPath)
    : projectPath_(projectPath) {
    setPublishDirectory(getProjectPath().filePath("generated"));
}

ProjectSettings::~ProjectSettings() {}

const QDir& ProjectSettings::getProjectPath() const {
    return projectPath_;
}

QString ProjectSettings::getRelativePath(const QDir& path) const {
    return getProjectPath().relativeFilePath(path.absolutePath());
}

const QVector<QDir>& ProjectSettings::getResourceDirectories() const {
    return resourcesDirectories_;
}

void ProjectSettings::setResourceDirectories(const QVector<QDir>& directories) {
    resourcesDirectories_ = directories;
}

const ContentProtectionKey& ProjectSettings::getContentProtectionKey() const {
    return contentProtectionKey_;
}

void ProjectSettings::setContentProtectionKey(const ContentProtectionKey& key) {
    contentProtectionKey_ = key;
}

const QDir& ProjectSettings::getPublishDirectory() const {
    return publishDirectory_;
}

void ProjectSettings::setPublishDirectory(const QDir& directory) {
    publishDirectory_ = directory;
}

bool ProjectSettings::read() {
    QFile file(getProjectPath().absolutePath());
    if (not file.open(QIODevice::OpenModeFlag::ReadOnly)) {
        qWarning() << "Could't open project file to read";
        return false;
    }

    auto obj = QJsonDocument().fromJson(file.readAll()).object();
    return deserialize(obj);
}

bool ProjectSettings::write() const {
    QFile file(getProjectPath().absolutePath());
    if (not file.open(QIODevice::OpenModeFlag::WriteOnly)) {
        qWarning() << "Could't open project file to write";
        return false;
    }

    QJsonObject json;
    serialize(json);
    QJsonDocument doc(json);
    file.write(doc.toJson());
    return true;
}

bool ProjectSettings::deserialize(const QJsonObject& json) {
    if (not contentProtectionKey_.deserialize(json)) {
        return false;
    }

    auto&& v = json.value(key::publish_directory);
    if (v.isUndefined()) {
        setPublishDirectory(getProjectPath().filePath("generated"));
    } else if (v.isString()) {
        setPublishDirectory(v.toString());
    } else {
        return false;
    }

    return true;
}

void ProjectSettings::serialize(QJsonObject& json) const {
    QJsonArray dirs;
    for (const QDir& dir : getResourceDirectories()) {
        QJsonObject obj;
        obj["path"] = getRelativePath(dir);
        dirs.append(obj);
    }
    json[key::resource_paths] = dirs;

    contentProtectionKey_.serialize(json);

    json.insert(key::publish_directory, getRelativePath(getPublishDirectory()));
}
} // namespace ee
