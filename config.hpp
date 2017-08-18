#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "projectsettings.hpp"

namespace ee {
class Config {
private:
    using Self = Config;

public:
    static Self& getInstance();

    const ProjectSettings& getProjectSettings() const;
    void setProjectSettings(const ProjectSettings& settings);

protected:
    Config();
    ~Config();

    Config(const Self&) = delete;
    Self& operator=(const Self&) = delete;

private:
    ProjectSettings projectSettings_;
};
} // namespace ee

#endif // CONFIG_HPP
