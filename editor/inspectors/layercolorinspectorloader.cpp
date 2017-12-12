#include "layercolorinspectorloader.hpp"
#include "inspectorgroup.hpp"

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
    // FIXME.
    auto inspector = new InspectorGroup();
    inspector->setVisible(false);
    return inspector;
}

bool Self::isRoot() const {
    return false;
}

QString Self::getParent() const {
    return QString::fromStdString(NodeLoader::Name);
}

QString Self::getName() const {
    return QString::fromStdString(LayerColorLoader::Name);
}
} // namespace ee
