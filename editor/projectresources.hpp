#ifndef EE_EDITOR_PROJECT_RESOURCES_HPP
#define EE_EDITOR_PROJECT_RESOURCES_HPP

#include <QString>
#include <QVector>

namespace ee {
class ProjectSettings;

class ProjectResources {
private:
    using Self = ProjectResources;

public:
    static Self& getInstance();

    void removeResources(const ProjectSettings& settings);
    void addResources(const ProjectSettings& settings);

private:
    ProjectResources();
    ~ProjectResources();

    ProjectResources(const Self&) = delete;
    Self& operator=(const Self&) = delete;

    QVector<QString> loadedResources_;
};
} // namespace ee

#endif // PROJECTRESOURCES_HPP
