#ifndef EE_EDITOR_WIDGET_INSPECTOR_HPP
#define EE_EDITOR_WIDGET_INSPECTOR_HPP

#include "inspectorgroup.hpp"

namespace ee {
class WidgetInspector : public InspectorGroup {
private:
    using Self = WidgetInspector;
    using Super = InspectorGroup;

public:
    explicit WidgetInspector(QWidget* parent = nullptr);
};
} // namespace ee

#endif // EE_EDITOR_WIDGET_INSPECTOR_HPP
