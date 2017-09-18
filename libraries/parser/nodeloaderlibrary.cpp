#include <cassert>

#include "nodeloader.hpp"
#include "nodeloaderlibrary.hpp"
#include "spriteloader.hpp"

namespace ee {
using Self = NodeLoaderLibrary;

Self::NodeLoaderLibrary() {}

Self::~NodeLoaderLibrary() {}

void Self::addDefaultLoaders() {
    addLoader("_Node", std::make_unique<NodeLoader>());
    addLoader("_Sprite", std::make_unique<SpriteLoader>());
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

const NodeLoaderPtr& Self::getLoader(const std::string& name) {
    assert(loaders_.count(name) != 0);
    return loaders_.at(name);
}
} // namespace ee
