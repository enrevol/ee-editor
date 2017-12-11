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

Inspector* Self::createInspector() const {
    return new WidgetInspector();
}

bool Self::isRoot() const {
    return false;
}

QString Self::getParent() const {
    return QString::fromStdString(NodeLoader::ClassName);
}

QString Self::getName() const {
    return QString::fromStdString(WidgetLoader::ClassName);
}
} // namespace ee
