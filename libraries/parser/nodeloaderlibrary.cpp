#include <cassert>

#include "layercolorloader.hpp"
#include "nodeloader.hpp"
#include "nodeloaderlibrary.hpp"
#include "scale9spriteloader.hpp"
#include "skeletonanimationloader.hpp"
#include "spriteloader.hpp"
#include "widgetloader.hpp"

namespace ee {
using Self = NodeLoaderLibrary;

Self::NodeLoaderLibrary() {}

Self::~NodeLoaderLibrary() {}

Self::NodeLoaderLibrary(const Self& other) {
    for (auto&& elt : other.loaders_) {
        loaders_.emplace(elt.first, elt.second->clone());
    }
}

void Self::addDefaultLoaders() {
    addLoader(std::make_unique<NodeLoader>());
    addLoader(std::make_unique<Scale9SpriteLoader>());
    addLoader(std::make_unique<SpriteLoader>());
    addLoader(std::make_unique<WidgetLoader>());
    addLoader(std::make_unique<LayerColorLoader>());
    addLoader(std::make_unique<SkeletonAnimationLoader>());
}

bool Self::hasLoader(const std::string& name) const {
    return loaders_.count(name) != 0;
}

bool Self::addLoader(NodeLoaderPtr loader) {
    return addLoader(loader->getClassName(), std::move(loader));
}

bool Self::addLoader(const std::string& name, NodeLoaderPtr loader) {
    if (loaders_.count(name) != 0) {
        return false;
    }
    loaders_.emplace(name, std::move(loader));
    return true;
}

bool Self::removeLoader(const std::string& name) {
    if (loaders_.count(name) == 0) {
        return false;
    }
    loaders_.erase(name);
    return true;
}

const NodeLoaderPtr& Self::getLoader(const std::string& name) const {
    assert(hasLoader(name));
    return loaders_.at(name);
}
} // namespace ee
