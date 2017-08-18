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

void Config::loadProject(const QDir& path) {
    setProjectSettings(ProjectSettings(path));
}
} // namespace ee
