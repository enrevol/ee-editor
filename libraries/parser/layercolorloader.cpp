#include "layercolorloader.hpp"

#include <2d/CCLayer.h>

namespace ee {
using Self = LayerColorLoader;

const std::string Self::ClassName = "_LayerColor";

NodeLoaderPtr Self::create() {
    auto result = std::unique_ptr<Self>(new Self());
    result->initialize();
    return std::move(result);
}

Self::LayerColorLoader() {}

Self::~LayerColorLoader() {}

void Self::addReadHandlers(PropertyHandler& handler) {
    Super::addReadHandlers(handler);
}

void Self::addWriteHandlers(PropertyHandler& handler) {
    Super::addWriteHandlers(handler);
}

void Self::addDefaultProperties(PropertyWriter& writer) {
    Super::addDefaultProperties(writer);
}

cocos2d::Node* Self::createNode() const {
    return cocos2d::LayerColor::create();
}

std::string Self::getClassName() const {
    return ClassName;
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
