#ifndef EE_EDITOR_WIDGET_INSPECTOR_LOADER_HPP
#define EE_EDITOR_WIDGET_INSPECTOR_LOADER_HPP

#include "nodeinspectorloader.hpp"

namespace ee {
class WidgetInspectorLoader : public NodeInspectorLoader {
private:
    using Self = WidgetInspectorLoader;
    using Super = NodeInspectorLoader;

public:
    static InspectorLoaderPtr create();

    virtual ~WidgetInspectorLoader() override;

    virtual QVector<InspectorGroup*> createInspectors() const override;

    virtual QString getClassName() const override;

protected:
    WidgetInspectorLoader();
};
} // namespace ee

#endif // EE_EDITOR_WIDGET_INSPECTOR_LOADER_HPP
