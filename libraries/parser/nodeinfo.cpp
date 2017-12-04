#include "nodeinfo.hpp"

#include <2d/CCNode.h>

namespace ee {
using Self = NodeInfo;

const PropertyHandler& Self::getPropertyHandler(const cocos2d::Node* node) {
    auto obj = node->getUserObject();
    auto info = dynamic_cast<const NodeInfo*>(obj);
    return info->getPropertyHandler();
}

PropertyHandler& Self::getPropertyHandler(cocos2d::Node* node) {
    auto obj = node->getUserObject();
    auto info = dynamic_cast<NodeInfo*>(obj);
    return info->getPropertyHandler();
}

Self* Self::create() {
    auto result = new Self();
    result->autorelease();
    return result;
}

Self::NodeInfo() {}

const PropertyHandler& Self::getPropertyHandler() const {
    return propertyHandler_;
}

PropertyHandler& Self::getPropertyHandler() {
    return propertyHandler_;
}
} // namespace ee
