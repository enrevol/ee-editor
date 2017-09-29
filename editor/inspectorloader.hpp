#ifndef EE_EDITOR_INSPECTOR_LOADER_HPP
#define EE_EDITOR_INSPECTOR_LOADER_HPP

#include <memory>

#include <QString>

namespace ee {
class InspectorGroup;
class InspectorLoader;

using InspectorLoaderPtr = std::unique_ptr<InspectorLoader>;

class InspectorLoader {
public:
    virtual ~InspectorLoader();

    virtual QVector<InspectorGroup*> createInspectors() const = 0;

    virtual QString getClassName() const = 0;

protected:
    InspectorLoader();
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_LOADER_HPP
