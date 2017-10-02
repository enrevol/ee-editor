#include <ciso646>

#include "config.hpp"
#include "filesystemwatcher.hpp"

#include <parser/nodegraph.hpp>

#include <QDebug>

namespace ee {
using Self = Config;

Self& Self::getInstance() {
    static Self sharedInstance;
    return sharedInstance;
}

Self::Config() {}

Self::~Config() {}

bool Self::hasOpenedProject() const {
    return projectSettings_.has_value();
}

const ProjectSettings& Self::getProjectSettings() const {
    Q_ASSERT(hasOpenedProject());
    return projectSettings_.value();
}

void Self::setProjectSettings(const ProjectSettings& settings) {
    projectSettings_ = settings;
}

bool Self::loadProject(const QFileInfo& path) {
    ProjectSettings settings(path);
    if (not settings.read()) {
        return false;
    }
    if (hasOpenedProject()) {
        Q_EMIT projectClosed(getProjectSettings().getProjectPath());
    }
    setProjectSettings(settings);
    auto&& watcher = FileSystemWatcher::getInstance();
    watcher.setDirectories(settings.getResourceDirectories());
    Q_EMIT projectLoaded(path);
    return true;
}

bool Self::saveProject() const {
    if (not hasOpenedProject()) {
        return false;
    }
    auto&& settings = getProjectSettings();
    return settings.write();
}

bool Self::createProject(const QFileInfo& path) {
    QFile file(path.absoluteFilePath());
    if (not file.open(QIODevice::OpenModeFlag::WriteOnly)) {
        qWarning() << "Couldn't create a new project at "
                   << path.absoluteFilePath();
        return false;
    }
    ProjectSettings settings(path);
    return settings.write();
}

const std::optional<InterfaceSettings>& Self::getInterfaceSettings() const {
    return interfaceSettings_;
}

void Self::setInterfaceSettings(const InterfaceSettings& settings) {
    interfaceSettings_ = settings;
}

bool Self::loadInterface(const QFileInfo& path) {
    InterfaceSettings settings(path);
    if (not settings.read()) {
        return false;
    }
    setInterfaceSettings(settings);
    Q_EMIT interfaceLoaded(path);
    return true;
}

bool Self::saveInterface() const {
    auto&& settings = getInterfaceSettings();
    if (not settings.has_value()) {
        return false;
    }
    return settings->write();
}

bool Self::createInterface(const QFileInfo& path) {
    QFile file(path.absoluteFilePath());
    if (not file.open(QIODevice::OpenModeFlag::WriteOnly)) {
        qWarning() << "Couldn't create a new interface at "
                   << path.absoluteFilePath();
        return false;
    }
    InterfaceSettings settings(path);

    NodeGraph graph;
    graph.setBaseClass("_Node");
    settings.setNodeGraph(graph);

    return settings.write();
}
} // namespace ee
