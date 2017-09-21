#include "nodeloader.hpp"
#include "propertywriter.hpp"

#include <2d/CCNode.h>
#include <base/ccTypes.h>

namespace ee {
using Self = NodeLoader;

const std::string Self::Property::AnchorPointX = "anchor_point_x";
const std::string Self::Property::AnchorPointY = "anchor_point_y";
const std::string Self::Property::CascadeColorEnabled = "cascade_color_enabled";
const std::string Self::Property::CascadeOpacityEnabled =
    "cascade_opacity_enabled";
const std::string Self::Property::ColorR = "color_r";
const std::string Self::Property::ColorG = "color_g";
const std::string Self::Property::ColorB = "color_b";
const std::string Self::Property::ContentSizeHeight = "content_size_height";
const std::string Self::Property::ContentSizeWidth = "content_size_width";
const std::string Self::Property::IgnoreAnchorPointForPosition =
    "ignore_anchor_point_for_position";
const std::string Self::Property::LocalZOrder = "local_z_order";
const std::string Self::Property::Opacity = "opacity";
const std::string Self::Property::PositionX = "position_x";
const std::string Self::Property::PositionY = "position_y";
const std::string Self::Property::Rotation = "rotation";
const std::string Self::Property::ScaleX = "scale_x";
const std::string Self::Property::ScaleY = "scale_y";
const std::string Self::Property::SkewX = "skew_x";
const std::string Self::Property::SkewY = "skew_y";
const std::string Self::Property::Tag = "tag";
const std::string Self::Property::Visible = "visible";

namespace {
bool isInColorRange(int value) {
    auto min = std::numeric_limits<GLubyte>::min();
    auto max = std::numeric_limits<GLubyte>::max();
    if (value < static_cast<int>(min)) {
        return false;
    }
    if (value > static_cast<int>(max)) {
        return false;
    }
    return true;
}
} // namespace

NodeLoaderPtr Self::create() {
    auto result = std::unique_ptr<Self>(new Self());
    result->initialize();
    return result;
}

Self::NodeLoader() {}

Self::~NodeLoader() {}

void Self::initialize() {
    addReadHandlers(propertyHandler_);
    addWriteHandlers(propertyHandler_);

    auto writer = PropertyWriter(defaultProperties_);
    addDefaultProperties(writer);
}

cocos2d::Node* Self::createNode() const {
    return cocos2d::Node::create();
}

const PropertyHandler& Self::getPropertyHandler() const {
    return propertyHandler_;
}

void Self::addReadHandlers(PropertyHandler& handler) {
    handler.addReadFloatHandler(
        Property::AnchorPointX,
        [this](const cocos2d::Node* node) { return node->getAnchorPoint().x; });

    handler.addReadFloatHandler(
        Property::AnchorPointY,
        [this](const cocos2d::Node* node) { return node->getAnchorPoint().y; });

    handler.addReadBoolHandler(Property::CascadeColorEnabled,
                               [this](const cocos2d::Node* node) {
                                   return node->isCascadeColorEnabled();
                               });

    handler.addReadBoolHandler(Property::CascadeOpacityEnabled,
                               [this](const cocos2d::Node* node) {
                                   return node->isCascadeOpacityEnabled();
                               });

    handler.addReadIntHandler(Property::ColorB,
                              [this](const cocos2d::Node* node) {
                                  return static_cast<int>(node->getColor().b);
                              });

    handler.addReadIntHandler(Property::ColorG,
                              [this](const cocos2d::Node* node) {
                                  return static_cast<int>(node->getColor().g);
                              });

    handler.addReadIntHandler(Property::ColorR,
                              [this](const cocos2d::Node* node) {
                                  return static_cast<int>(node->getColor().r);
                              });

    handler.addReadFloatHandler(Property::ContentSizeHeight,
                                [this](const cocos2d::Node* node) {
                                    return node->getContentSize().height;
                                });

    handler.addReadFloatHandler(Property::ContentSizeWidth,
                                [this](const cocos2d::Node* node) {
                                    return node->getContentSize().width;
                                });

    handler.addReadBoolHandler(
        Property::IgnoreAnchorPointForPosition,
        [this](const cocos2d::Node* node) {
            return node->isIgnoreAnchorPointForPosition();
        });

    handler.addReadIntHandler(
        Property::LocalZOrder,
        [this](const cocos2d::Node* node) { return node->getLocalZOrder(); });

    handler.addReadIntHandler(Property::Opacity,
                              [this](const cocos2d::Node* node) {
                                  return static_cast<int>(node->getOpacity());
                              });

    handler.addReadFloatHandler(
        Property::PositionX,
        [this](const cocos2d::Node* node) { return node->getPosition().x; });

    handler.addReadFloatHandler(
        Property::PositionY,
        [this](const cocos2d::Node* node) { return node->getPosition().y; });

    handler.addReadFloatHandler(
        Property::Rotation,
        [this](const cocos2d::Node* node) { return node->getRotation(); });

    handler.addReadFloatHandler(
        Property::ScaleX,
        [this](const cocos2d::Node* node) { return node->getScaleX(); });

    handler.addReadFloatHandler(
        Property::ScaleY,
        [this](const cocos2d::Node* node) { return node->getScaleY(); });

    handler.addReadFloatHandler(
        Property::SkewX,
        [this](const cocos2d::Node* node) { return node->getSkewX(); });

    handler.addReadFloatHandler(
        Property::SkewY,
        [this](const cocos2d::Node* node) { return node->getSkewY(); });

    handler.addReadIntHandler(Property::Tag, [this](const cocos2d::Node* node) {
        return node->getTag();
    });

    handler.addReadBoolHandler(
        Property::Visible,
        [this](const cocos2d::Node* node) { return node->isVisible(); });
}

void Self::addWriteHandlers(PropertyHandler& handler) {
    handler.addWriteFloatHandler(Property::AnchorPointX,
                                 [this](cocos2d::Node* node, float value) {
                                     auto anchor = node->getAnchorPoint();
                                     anchor.x = value;
                                     node->setAnchorPoint(anchor);
                                     return true;
                                 });

    handler.addWriteFloatHandler(Property::AnchorPointY,
                                 [this](cocos2d::Node* node, float value) {
                                     auto anchor = node->getAnchorPoint();
                                     anchor.y = value;
                                     node->setAnchorPoint(anchor);
                                     return true;
                                 });

    handler.addWriteBoolHandler(Property::CascadeColorEnabled,
                                [this](cocos2d::Node* node, bool value) {
                                    node->setCascadeColorEnabled(value);
                                    return true;
                                });

    handler.addWriteBoolHandler(Property::CascadeOpacityEnabled,
                                [this](cocos2d::Node* node, bool value) {
                                    node->setCascadeOpacityEnabled(value);
                                    return true;
                                });

    handler.addWriteIntHandler(Property::ColorB,
                               [this](cocos2d::Node* node, int value) {
                                   if (not isInColorRange(value)) {
                                       return false;
                                   }
                                   auto color = node->getColor();
                                   color.b = static_cast<GLubyte>(value);
                                   node->setColor(color);
                                   return true;
                               });

    handler.addWriteIntHandler(Property::ColorG,
                               [this](cocos2d::Node* node, int value) {
                                   if (not isInColorRange(value)) {
                                       return false;
                                   }
                                   auto color = node->getColor();
                                   color.g = static_cast<GLubyte>(value);
                                   node->setColor(color);
                                   return true;
                               });

    handler.addWriteIntHandler(Property::ColorR,
                               [this](cocos2d::Node* node, int value) {
                                   if (not isInColorRange(value)) {
                                       return false;
                                   }
                                   auto color = node->getColor();
                                   color.r = static_cast<GLubyte>(value);
                                   node->setColor(color);
                                   return true;
                               });

    handler.addWriteFloatHandler(Property::ContentSizeHeight,
                                 [this](cocos2d::Node* node, float value) {
                                     auto size = node->getContentSize();
                                     size.height = value;
                                     node->setContentSize(size);
                                     return true;
                                 });

    handler.addWriteFloatHandler(Property::ContentSizeWidth,
                                 [this](cocos2d::Node* node, float value) {
                                     auto size = node->getContentSize();
                                     size.width = value;
                                     node->setContentSize(size);
                                     return true;
                                 });

    handler.addWriteBoolHandler(Property::IgnoreAnchorPointForPosition,
                                [this](cocos2d::Node* node, bool value) {
                                    node->setIgnoreAnchorPointForPosition(
                                        value);
                                    return true;
                                });

    handler.addWriteIntHandler(Property::LocalZOrder,
                               [this](cocos2d::Node* node, int value) {
                                   node->setLocalZOrder(value);
                                   return true;
                               });

    handler.addWriteIntHandler(
        Property::Opacity, [this](cocos2d::Node* node, int value) {
            if (not isInColorRange(value)) {
                return false;
            }
            node->setOpacity(static_cast<GLubyte>(value));
            return true;
        });

    handler.addWriteFloatHandler(Property::PositionX,
                                 [this](cocos2d::Node* node, float value) {
                                     auto position = node->getPosition();
                                     position.x = value;
                                     node->setPosition(position);
                                     return true;
                                 });

    handler.addWriteFloatHandler(Property::PositionY,
                                 [this](cocos2d::Node* node, float value) {
                                     auto position = node->getPosition();
                                     position.y = value;
                                     node->setPosition(position);
                                     return true;
                                 });

    handler.addWriteFloatHandler(Property::Rotation,
                                 [this](cocos2d::Node* node, float value) {
                                     node->setRotation(value);
                                     return true;
                                 });

    handler.addWriteFloatHandler(Property::ScaleX,
                                 [this](cocos2d::Node* node, float value) {
                                     node->setScaleX(value);
                                     return true;
                                 });

    handler.addWriteFloatHandler(Property::ScaleY,
                                 [this](cocos2d::Node* node, float value) {
                                     node->setScaleY(value);
                                     return true;
                                 });

    handler.addWriteFloatHandler(Property::SkewX,
                                 [this](cocos2d::Node* node, float value) {
                                     node->setSkewX(value);
                                     return true;
                                 });

    handler.addWriteFloatHandler(Property::SkewY,
                                 [this](cocos2d::Node* node, float value) {
                                     node->setSkewY(value);
                                     return true;
                                 });

    handler.addWriteIntHandler(Property::Tag,
                               [this](cocos2d::Node* node, int value) {
                                   node->setTag(value);
                                   return true;
                               });

    handler.addWriteBoolHandler(Property::Visible,
                                [this](cocos2d::Node* node, bool value) {
                                    node->setVisible(value);
                                    return true;
                                });
}

void Self::addDefaultProperties(PropertyWriter& writer) {
    writer.addProperty(Property::AnchorPointX, 0.0f);
    writer.addProperty(Property::AnchorPointY, 0.0f);
    writer.addProperty(Property::CascadeColorEnabled, false);
    writer.addProperty(Property::CascadeOpacityEnabled, false);
    writer.addProperty(Property::ColorB, cocos2d::Color3B::WHITE.b);
    writer.addProperty(Property::ColorG, cocos2d::Color3B::WHITE.g);
    writer.addProperty(Property::ColorR, cocos2d::Color3B::WHITE.r);
    writer.addProperty(Property::ContentSizeHeight, cocos2d::Size::ZERO.height);
    writer.addProperty(Property::ContentSizeWidth, cocos2d::Size::ZERO.width);
    writer.addProperty(Property::IgnoreAnchorPointForPosition, false);
    writer.addProperty(Property::LocalZOrder, 0);
    writer.addProperty(Property::Opacity, 255);
    writer.addProperty(Property::PositionX, 0.0f);
    writer.addProperty(Property::PositionY, 0.0f);
    writer.addProperty(Property::Rotation, 0.0f);
    writer.addProperty(Property::ScaleX, 1.0f);
    writer.addProperty(Property::ScaleY, 1.0f);
    writer.addProperty(Property::SkewX, 0.0f);
    writer.addProperty(Property::SkewY, 0.0f);
    writer.addProperty(Property::Tag, cocos2d::Node::INVALID_TAG);
    writer.addProperty(Property::Visible, true);
}

NodeLoaderPtr Self::clone() const {
    return NodeLoaderPtr(cloneRaw());
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
