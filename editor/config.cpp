#include <ciso646>

#include "config.hpp"

namespace ee {
Config& Config::getInstance() {
    static Self sharedInstance;
    return sharedInstance;
}

Config::Config() {}

Config::~Config() {}

const std::optional<ProjectSettings>& Config::getProjectSettings() const {
    return projectSettings_;
}

void Config::setProjectSettings(const ProjectSettings& settings) {
    projectSettings_ = settings;
}

bool Config::loadProject(const QDir& path) {
    setProjectSettings(ProjectSettings(path));
    return true;
}

bool Config::saveProject() const {
    auto&& settings = getProjectSettings();
    if (not settings.has_value()) {
        return false;
    }
    return settings->write();
}

bool Config::createProject(const QDir& path) {
    QFile file(path.absolutePath());
    if (not file.open(QIODevice::OpenModeFlag::WriteOnly)) {
        return false;
    }

    ProjectSettings settings(path);
    settings.write();

    return true;
}
} // namespace ee
