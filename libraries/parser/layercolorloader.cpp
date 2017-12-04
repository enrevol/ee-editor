#include "layercolorloader.hpp"

#include <2d/CCLayer.h>

namespace ee {
using Self = LayerColorLoader;

const std::string Self::ClassName = "_LayerColor";

Self::LayerColorLoader() {}

Self::~LayerColorLoader() {}

cocos2d::Node* Self::createNode() const {
    return Target::create();
}

void Self::loadProperties(cocos2d::Node* node_,
                          const PropertyHandler& handler) const {
    auto node = dynamic_cast<Target*>(node_);
    Super::loadProperties(node, handler);
}

std::string Self::getClassName() const {
    return ClassName;
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
