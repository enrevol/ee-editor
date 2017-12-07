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

QVector<InspectorGroup*> Self::createInspectors() const {
    return Super::createInspectors();
}

QString Self::getClassName() const {
    return QString::fromStdString(LayerColorLoader::ClassName);
}
} // namespace ee
