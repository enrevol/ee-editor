#include "nodeloader.hpp"

#include <2d/CCNode.h>

namespace ee {
namespace property {
constexpr auto position_x = "position_x";
constexpr auto position_y = "position_y";
constexpr auto content_size_width = "content_size_width";
constexpr auto content_size_height = "content_size_height";
} // namespace property

using Self = NodeLoader;

Self::NodeLoader() {
    auto&& handler = getPropertyHandler();
    handler.addWriteFloatHandler(property::content_size_width,
                                 [this](cocos2d::Node* node, float value) {
                                     auto size = node->getContentSize();
                                     size.width = value;
                                     node->setContentSize(size);
                                 });

    handler.addWriteFloatHandler(property::content_size_height,
                                 [this](cocos2d::Node* node, float value) {
                                     auto size = node->getContentSize();
                                     size.height = value;
                                     node->setContentSize(size);
                                 });

    handler.addWriteFloatHandler(property::position_x,
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
        property::position_y,
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
} // namespace ee
