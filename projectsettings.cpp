#include "projectsettings.hpp"

namespace ee {
ProjectSettings::ProjectSettings() {}
ProjectSettings::~ProjectSettings() {}

const std::vector<std::string>& ProjectSettings::getResourcesPaths() const {
    return resourcesPaths_;
}

void ProjectSettings::setResourcesPaths(const std::vector<std::string>& paths) {
    resourcesPaths_ = paths;
}

const std::string& ProjectSettings::getContentProtectionKey() const {
    return contentProtectionKey_;
}

void ProjectSettings::setContentProtectionKey(const std::string& key) {
    contentProtectionKey_ = key;
}

const std::string& ProjectSettings::getPublishDirectory() const {
    return publishDirectory_;
}

void ProjectSettings::setPublishDirectory(const std::string& directory) {
    publishDirectory_ = directory;
}
} // namespace ee
