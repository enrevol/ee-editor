#ifndef EE_EDITOR_INSPECTOR_LOADER_LIBRARY_HPP
#define EE_EDITOR_INSPECTOR_LOADER_LIBRARY_HPP

#include <map>

#include "inspectorloader.hpp"

#include <QString>
#include <QVector>

namespace ee {
class InspectorGroup;

class InspectorLoaderLibrary final {
private:
    using Self = InspectorLoaderLibrary;

public:
    InspectorLoaderLibrary();
    ~InspectorLoaderLibrary();

    InspectorLoaderLibrary(Self&&) = default;

    void addDefaultLoaders();

    bool addLoader(InspectorLoaderPtr loader);

    bool addLoader(const QString& name, InspectorLoaderPtr loader);

    const InspectorLoaderPtr& getLoader(const QString& name) const;

    QVector<InspectorGroup*> createInspectors(const QString& name) const;

private:
    std::map<QString, InspectorLoaderPtr> loaders_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_LOADER_LIBRARY_HPP
