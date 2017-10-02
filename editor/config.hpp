#ifndef EE_EDITOR_CONFIG_HPP
#define EE_EDITOR_CONFIG_HPP

#include "interfacesettings.hpp"
#include "optional.hpp"
#include "projectsettings.hpp"

#include <QObject>

namespace ee {
class Config : public QObject {
    Q_OBJECT

private:
    using Self = Config;

public:
    static Self& getInstance();

    /// Checks whether there is any opened project.
    bool hasOpenedProject() const;

    /// Gets the current project settings.
    const ProjectSettings& getProjectSettings() const;

    /// Sets the project settings.
    /// @param settings The desired project settings.
    void setProjectSettings(const ProjectSettings& settings);

    /// Attempts to load a project whose the specified path.
    /// @param path The project file's path.
    bool loadProject(const QFileInfo& path);

    /// Attempts to save the current project.
    bool saveProject() const;

    /// Attempts to create a project at the specified path.
    /// @param path The project's path.
    bool createProject(const QFileInfo& path);

    const std::optional<InterfaceSettings>& getInterfaceSettings() const;

    void setInterfaceSettings(const InterfaceSettings& settings);

    /// Attempts to load an interface whose the specified path.
    /// @param path The interface file's path.
    bool loadInterface(const QFileInfo& path);

    /// Attempts to save the current interface file.
    bool saveInterface() const;

    /// Attempts to create an interface at the specified path.
    /// @param path The interface file's path.
    bool createInterface(const QFileInfo& path);

Q_SIGNALS:
    void interfaceLoaded(const QFileInfo& path);
    void projectLoaded(const QFileInfo& path);
    void projectClosed(const QFileInfo& path);

protected:
    Config();
    ~Config();

    Config(const Self&) = delete;
    Self& operator=(const Self&) = delete;

private:
    std::optional<ProjectSettings> projectSettings_;
    std::optional<InterfaceSettings> interfaceSettings_;
};
} // namespace ee

#endif // EE_EDITOR_CONFIG_HPP
