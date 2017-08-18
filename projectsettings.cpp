#include "projectsettings.hpp"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace ee {
namespace key {
constexpr auto content_protection_key = "contentProtectionKey";
constexpr auto resource_paths = "resourcePaths";
constexpr auto publish_directory = "publishDirectory";
} // namespace key

ProjectSettings::ProjectSettings(const QDir& projectPath)
    : projectPath_(projectPath) {}

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

bool ProjectSettings::read() {
    QFile file(getProjectPath().absolutePath());
    if (not file.open(QIODevice::OpenModeFlag::ReadOnly)) {
        qWarning() << "Could't open project file to read";
        return false;
    }

    auto obj = QJsonDocument().fromJson(file.readAll()).object();
    return load(obj);
}

bool ProjectSettings::write() const {
    QFile file(getProjectPath().absolutePath());
    if (not file.open(QIODevice::OpenModeFlag::WriteOnly)) {
        qWarning() << "Could't open project file to write";
        return false;
    }

    auto obj = store();
    QJsonDocument doc(obj);
    file.write(doc.toJson());
    return true;
}

bool ProjectSettings::load(const QJsonObject& json) {
    if (json.contains(key::content_protection_key)) {
        setContentProtectionKey(json[key::content_protection_key].toString());
    }
    if (json.contains(key::publish_directory)) {
        setPublishDirectory(QDir(json[key::publish_directory].toString()));
    }
    return true;
}

QJsonObject ProjectSettings::store() const {
    QJsonObject dict;

    QJsonArray dirs;
    for (const QDir& dir : getResourceDirectories()) {
        QJsonObject obj;
        obj["path"] = getRelativePath(dir);
    }
    dict[key::resource_paths] = dirs;

    if (getContentProtectionKey().has_value()) {
        dict[key::content_protection_key] = getContentProtectionKey().value();
    }

    if (getPublishDirectory().has_value()) {
        dict[key::publish_directory] =
            getRelativePath(getPublishDirectory().value());
    }

    return dict;
}
} // namespace ee
