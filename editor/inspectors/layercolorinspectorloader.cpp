#include "layercolorinspectorloader.hpp"

#include <parser/layercolorloader.hpp>

#include <QVector>

namespace ee {
using Self = LayerColorInspectorLoader;

InspectorLoaderPtr Self::create() {
    return std::unique_ptr<Self>(new Self());
}

Self::LayerColorInspectorLoader() {}

Self::~LayerColorInspectorLoader() {}

Inspector* Self::createInspector() const {
    return nullptr;
}

bool Self::isRoot() const {
    return false;
}

QString Self::getParent() const {
    return QString::fromStdString(NodeLoader::ClassName);
}

QString Self::getName() const {
    return QString::fromStdString(LayerColorLoader::ClassName);
}
} // namespace ee
