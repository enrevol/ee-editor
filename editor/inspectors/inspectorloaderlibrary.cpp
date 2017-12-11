#include "inspectorloaderlibrary.hpp"
#include "layercolorinspectorloader.hpp"
#include "nodeinspectorloader.hpp"
#include "scale9spriteinspectorloader.hpp"
#include "spriteinspectorloader.hpp"
#include "widgetinspectorloader.hpp"

namespace ee {
using Self = InspectorLoaderLibrary;

Self::InspectorLoaderLibrary() {}
Self::~InspectorLoaderLibrary() {}

void Self::addDefaultLoaders() {
    addLoader(LayerColorInspectorLoader::create());
    addLoader(NodeInspectorLoader::create());
    addLoader(SpriteInspectorLoader::create());
    addLoader(Scale9SpriteInspectorLoader::create());
    addLoader(WidgetInspectorLoader::create());
}

bool Self::addLoader(InspectorLoaderPtr loader) {
    return addLoader(loader->getClassName(), std::move(loader));
}

bool Self::addLoader(const QString& name, InspectorLoaderPtr loader) {
    if (loaders_.count(name) != 0) {
        return false;
    }
    loaders_.emplace(name, std::move(loader));
    return true;
}

const InspectorLoaderPtr& Self::getLoader(const QString& name) const {
    Q_ASSERT(loaders_.count(name) != 0);
    return loaders_.at(name);
}

QVector<InspectorGroup*> Self::createInspectors(const QString& name) const {
    auto&& loader = getLoader(name);
    return loader->createInspectors();
}
} // namespace ee