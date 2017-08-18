#include "config.hpp"

namespace ee {
Config& Config::getInstance() {
    static Self sharedInstance;
    return sharedInstance;
}

Config::Config() {}

Config::~Config() {}

const ProjectSettings& Config::getProjectSettings() const {
    return projectSettings_;
}

void Config::setProjectSettings(const ProjectSettings& settings) {
    projectSettings_ = settings;
}
} // namespace ee
