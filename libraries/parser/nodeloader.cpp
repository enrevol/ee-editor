#include "nodeloader.hpp"

#include <2d/CCNode.h>

namespace ee {
using Self = NodeLoader;

const std::string Self::Property::PositionX = "position_x";
const std::string Self::Property::PositionY = "position_y";
const std::string Self::Property::ContentSizeWidth = "content_size_width";
const std::string Self::Property::ContentSizeHeight = "content_size_height";

Self::NodeLoader() {
    auto&& handler = getPropertyHandler();
    handler.addWriteFloatHandler(Property::ContentSizeWidth,
                                 [this](cocos2d::Node* node, float value) {
                                     auto size = node->getContentSize();
                                     size.width = value;
                                     node->setContentSize(size);
                                     return true;
                                 });

    handler.addWriteFloatHandler(Property::ContentSizeHeight,
                                 [this](cocos2d::Node* node, float value) {
                                     auto size = node->getContentSize();
                                     size.height = value;
                                     node->setContentSize(size);
                                     return true;
                                 });

    handler.addWriteFloatHandler(Property::PositionX,
                                 [this](cocos2d::Node* node, float value) {
                                     auto position = node->getPosition();
                                     position.x = value;
                                     node->setPosition(position);
                                 });

    handler.addWriteFloatHandler(property::position_y,
                                 [this](cocos2d::Node* node, float value) {
                                     auto position = node->getPosition();
                                     position.y = value;
                                     node->setPosition(position);
                                 });

    handler.addReadFloatHandler(property::content_size_width,
                                [this](const cocos2d::Node* node) {
                                    return node->getContentSize().width;
                                });

    handler.addReadFloatHandler(property::content_size_height,
                                [this](const cocos2d::Node* node) {
                                    return node->getContentSize().height;
                                });

    handler.addReadFloatHandler(
        property::position_x,
        [this](const cocos2d::Node* node) { return node->getPosition().x; });

    handler.addReadFloatHandler(
        Property::PositionY,
        [this](const cocos2d::Node* node) { return node->getPosition().y; });
}

Self::~NodeLoader() {}

cocos2d::Node* Self::createNode() const {
    return cocos2d::Node::create();
}

PropertyHandler& Self::getPropertyHandler() {
    return propertyHandler_;
}

const PropertyHandler& Self::getPropertyHandler() const {
    return propertyHandler_;
}

NodeLoaderPtr Self::clone() const {
    return NodeLoaderPtr(cloneRaw());
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
