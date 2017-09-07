#include <ciso646>

#include "projectsettings.hpp"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace ee {
namespace key {
constexpr auto resource_paths = "resource_paths";
constexpr auto publish_directory = "publish_directory";
} // namespace key

namespace defaults {
constexpr auto publish_directory = "generated";
} // namespace defaults

using Self = ProjectSettings;

Self::ProjectSettings(const QFileInfo& projectPath)
    : projectPath_(projectPath)
    , projectDirectory_(projectPath.absolutePath()) {
    setPublishDirectory(
        getProjectDirectory().filePath(defaults::publish_directory));
}

Self::~ProjectSettings() {}

const QFileInfo& Self::getProjectPath() const {
    return projectPath_;
}

const QDir& Self::getProjectDirectory() const {
    return projectDirectory_;
}

QString Self::getRelativePath(const QDir& path) const {
    return getProjectDirectory().relativeFilePath(path.absolutePath());
}

const QVector<QDir>& Self::getResourceDirectories() const {
    return resourcesDirectories_;
}

bool Self::addResourceDirectory(const QDir& directory) {
    if (resourcesDirectories_.contains(directory)) {
        // Exist.
        return false;
    }
    resourcesDirectories_.push_back(directory);
    std::sort(resourcesDirectories_.begin(), resourcesDirectories_.end(),
              [](const QDir& lhs, const QDir& rhs) {
                  return lhs.absolutePath() < rhs.absolutePath();
              });
    return true;
}

void Self::setResourceDirectories(const QVector<QDir>& directories) {
    resourcesDirectories_ = directories;
}

const ContentProtectionKey& Self::getContentProtectionKey() const {
    return contentProtectionKey_;
}

void Self::setContentProtectionKey(const ContentProtectionKey& key) {
    contentProtectionKey_ = key;
}

const QDir& Self::getPublishDirectory() const {
    return publishDirectory_;
}

void Self::setPublishDirectory(const QDir& directory) {
    publishDirectory_ = directory;
}

bool Self::read() {
    QFile file(getProjectPath().absoluteFilePath());
    if (not file.open(QIODevice::OpenModeFlag::ReadOnly)) {
        qWarning() << "Could't open project file to read";
        return false;
    }

    auto obj = QJsonDocument().fromJson(file.readAll()).object();
    return deserialize(obj);
}

bool Self::write() const {
    QFile file(getProjectPath().absoluteFilePath());
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

bool Self::deserialize(const QJsonObject& json) {
    if (not contentProtectionKey_.deserialize(json)) {
        return false;
    }

    {
        auto&& v = json.value(key::publish_directory)
                       .toString(defaults::publish_directory);
        setPublishDirectory(getProjectDirectory().filePath(v));
    }
    {
        auto&& v = json.value(key::resource_paths).toArray();
        QVector<QDir> dirs;
        for (auto&& x : v) {
            dirs.append(getProjectDirectory().filePath(
                x.toObject()["path"].toString()));
        }
        setResourceDirectories(dirs);
    }

    return true;
}

void Self::serialize(QJsonObject& json) const {
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
