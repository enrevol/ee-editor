#include "widgetinspectorloader.hpp"
#include "widgetinspector.hpp"

#include <parser/widgetloader.hpp>

namespace ee {
using Self = WidgetInspectorLoader;

InspectorLoaderPtr Self::create() {
    return std::unique_ptr<Self>(new Self());
}

Self::WidgetInspectorLoader() {}

Self::~WidgetInspectorLoader() {}

QVector<InspectorGroup*> Self::createInspectors() const {
    auto inspectors = Super::createInspectors();
    inspectors.append(new WidgetInspector());
    return inspectors;
}

QString Self::getClassName() const {
    return QString::fromStdString(WidgetLoader::ClassName);
}
} // namespace ee
