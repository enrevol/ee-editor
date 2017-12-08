#include "layercolorloader.hpp"

#include <2d/CCLayer.h>

namespace ee {
using Self = LayerColorLoader;

const std::string Self::ClassName = "_LayerColor";

Self::LayerColorLoader() {}

Self::~LayerColorLoader() {}

std::string Self::getClassName() const {
    return ClassName;
}

cocos2d::Node* Self::createNode() const {
    return Target::create();
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
