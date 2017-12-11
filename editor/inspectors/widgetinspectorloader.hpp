#ifndef EE_EDITOR_WIDGET_INSPECTOR_LOADER_HPP
#define EE_EDITOR_WIDGET_INSPECTOR_LOADER_HPP

#include "inspectorloader.hpp"

namespace ee {
class WidgetInspectorLoader : public InspectorLoader {
private:
    using Self = WidgetInspectorLoader;
    using Super = InspectorLoader;

public:
    static InspectorLoaderPtr create();

    virtual ~WidgetInspectorLoader() override;

    virtual Inspector* createInspector() const override;

    virtual bool isRoot() const override;

    virtual QString getParent() const override;

    virtual QString getName() const override;

protected:
    WidgetInspectorLoader();
};
} // namespace ee

#endif // EE_EDITOR_WIDGET_INSPECTOR_LOADER_HPP
