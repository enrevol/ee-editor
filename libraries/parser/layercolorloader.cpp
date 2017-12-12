#include "layercolorloader.hpp"

#include <2d/CCLayer.h>

namespace ee {
using Self = LayerColorLoader;

const std::string Self::Name = "_LayerColor";

Self::LayerColorLoader() {}

Self::~LayerColorLoader() {}

std::string Self::getName() const {
    return Name;
}

cocos2d::Node* Self::createNode() const {
    return Target::create();
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
