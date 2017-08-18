#ifndef EE_EDITOR_PROJECT_SETTINGS_HPP
#define EE_EDITOR_PROJECT_SETTINGS_HPP

#include <string>
#include <vector>

namespace ee {
class ProjectSettings {
private:
    using Self = ProjectSettings;

public:
    ProjectSettings();
    ~ProjectSettings();

    const std::vector<std::string>& getResourcesPaths() const;
    void setResourcesPaths(const std::vector<std::string>& paths);

    const std::string& getContentProtectionKey() const;
    void setContentProtectionKey(const std::string& key);

    const std::string& getPublishDirectory() const;
    void setPublishDirectory(const std::string& directory);

private:
    std::vector<std::string> resourcesPaths_;
    std::string contentProtectionKey_;
    std::string publishDirectory_;
};
} // namespace ee

#endif // EE_EDITOR_PROJECT_SETTINGS_HPP
