#include <cassert>

#include "layercolorloader.hpp"
#include "nodeloader.hpp"
#include "nodeloaderlibrary.hpp"
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
    addLoader("_Node", NodeLoader::create());
    addLoader("_Sprite", SpriteLoader::create());
    addLoader("_Widget", WidgetLoader::create());
    addLoader("_LayerColor", LayerColorLoader::create());
}

cocos2d::Node* Self::createNode(const std::string& name) const {
    return getLoader(name)->createNode();
}

bool Self::hasLoader(const std::string& name) const {
    return loaders_.count(name) != 0;
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
