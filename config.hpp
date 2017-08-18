#ifndef EE_EDITOR_CONFIG_HPP
#define EE_EDITOR_CONFIG_HPP

#include "optional.hpp"
#include "projectsettings.hpp"

namespace ee {
class Config {
private:
    using Self = Config;

public:
    static Self& getInstance();

    /// Gets the current project settings.
    /// @return std::nullopt if there is not any loaded project.
    const std::optional<ProjectSettings>& getProjectSettings() const;

    /// Sets the project settings.
    /// @param settings The desired project settings.
    void setProjectSettings(const ProjectSettings& settings);

    /// Attempts to load a project whose the specified path.
    /// @param path The project file's path.
    bool loadProject(const QDir& path);

    /// Attempts to save the current project.
    bool saveProject() const;

    /// Attempts to create a project at the specified path.
    /// @param path The project's path.
    bool createProject(const QDir& path);

protected:
    Config();
    ~Config();

    Config(const Self&) = delete;
    Self& operator=(const Self&) = delete;

private:
    std::optional<ProjectSettings> projectSettings_;
};
} // namespace ee

#endif // EE_EDITOR_CONFIG_HPP
