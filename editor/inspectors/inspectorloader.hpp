#ifndef EE_EDITOR_INSPECTOR_LOADER_HPP
#define EE_EDITOR_INSPECTOR_LOADER_HPP

#include <memory>

#include <QString>

namespace ee {
class Inspector;
class InspectorLoader;

using InspectorLoaderPtr = std::unique_ptr<InspectorLoader>;

class InspectorLoader {
public:
    virtual ~InspectorLoader();

    virtual Inspector* createInspector() const = 0;

    virtual bool isRoot() const = 0;

    virtual QString getParent() const = 0;

    virtual QString getName() const = 0;

protected:
    InspectorLoader();
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_LOADER_HPP
