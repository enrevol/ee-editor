#include "nodeloader.hpp"
#include "propertyreader.hpp"
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
const std::string Self::Property::Name = "name";
const std::string Self::Property::Opacity = "opacity";
const std::string Self::Property::OpacityModifyRGB = "opacity_modify_rgb";
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

PropertyReader Self::getDefaultPropertyReader() const {
    return PropertyReader(defaultProperties_);
}

void Self::addReadHandlers(PropertyHandler& handler) {
    handler.addReadFloatHandler(
        Property::AnchorPointX,
        [](const cocos2d::Node* node) { return node->getAnchorPoint().x; });

    handler.addReadFloatHandler(
        Property::AnchorPointY,
        [](const cocos2d::Node* node) { return node->getAnchorPoint().y; });

    handler.addReadBoolHandler(Property::CascadeColorEnabled,
                               [](const cocos2d::Node* node) {
                                   return node->isCascadeColorEnabled();
                               });

    handler.addReadBoolHandler(Property::CascadeOpacityEnabled,
                               [](const cocos2d::Node* node) {
                                   return node->isCascadeOpacityEnabled();
                               });

    handler.addReadIntHandler(Property::ColorB, [](const cocos2d::Node* node) {
        return static_cast<int>(node->getColor().b);
    });

    handler.addReadIntHandler(Property::ColorG, [](const cocos2d::Node* node) {
        return static_cast<int>(node->getColor().g);
    });

    handler.addReadIntHandler(Property::ColorR, [](const cocos2d::Node* node) {
        return static_cast<int>(node->getColor().r);
    });

    handler.addReadFloatHandler(Property::ContentSizeHeight,
                                [](const cocos2d::Node* node) {
                                    return node->getContentSize().height;
                                });

    handler.addReadFloatHandler(
        Property::ContentSizeWidth,
        [](const cocos2d::Node* node) { return node->getContentSize().width; });

    handler.addReadBoolHandler(
        Property::IgnoreAnchorPointForPosition, [](const cocos2d::Node* node) {
            return node->isIgnoreAnchorPointForPosition();
        });

    handler.addReadIntHandler(
        Property::LocalZOrder,
        [](const cocos2d::Node* node) { return node->getLocalZOrder(); });

    handler.addReadStringHandler(Property::Name, [](const cocos2d::Node* node) {
        return node->getName();
    });

    handler.addReadIntHandler(Property::Opacity, [](const cocos2d::Node* node) {
        return static_cast<int>(node->getOpacity());
    });

    handler.addReadBoolHandler(
        Property::OpacityModifyRGB,
        [](const cocos2d::Node* node) { return node->isOpacityModifyRGB(); });

    handler.addReadFloatHandler(
        Property::PositionX,
        [](const cocos2d::Node* node) { return node->getPosition().x; });

    handler.addReadFloatHandler(
        Property::PositionY,
        [](const cocos2d::Node* node) { return node->getPosition().y; });

    handler.addReadFloatHandler(
        Property::Rotation,
        [](const cocos2d::Node* node) { return node->getRotation(); });

    handler.addReadFloatHandler(
        Property::ScaleX,
        [](const cocos2d::Node* node) { return node->getScaleX(); });

    handler.addReadFloatHandler(
        Property::ScaleY,
        [](const cocos2d::Node* node) { return node->getScaleY(); });

    handler.addReadFloatHandler(Property::SkewX, [](const cocos2d::Node* node) {
        return node->getSkewX();
    });

    handler.addReadFloatHandler(Property::SkewY, [](const cocos2d::Node* node) {
        return node->getSkewY();
    });

    handler.addReadIntHandler(Property::Tag, [](const cocos2d::Node* node) {
        return node->getTag();
    });

    handler.addReadBoolHandler(
        Property::Visible,
        [](const cocos2d::Node* node) { return node->isVisible(); });
}

void Self::addWriteHandlers(PropertyHandler& handler) {
    handler.addWriteFloatHandler(Property::AnchorPointX,
                                 [](cocos2d::Node* node, float value) {
                                     auto anchor = node->getAnchorPoint();
                                     anchor.x = value;
                                     node->setAnchorPoint(anchor);
                                     return true;
                                 });

    handler.addWriteFloatHandler(Property::AnchorPointY,
                                 [](cocos2d::Node* node, float value) {
                                     auto anchor = node->getAnchorPoint();
                                     anchor.y = value;
                                     node->setAnchorPoint(anchor);
                                     return true;
                                 });

    handler.addWriteBoolHandler(Property::CascadeColorEnabled,
                                [](cocos2d::Node* node, bool value) {
                                    node->setCascadeColorEnabled(value);
                                    return true;
                                });

    handler.addWriteBoolHandler(Property::CascadeOpacityEnabled,
                                [](cocos2d::Node* node, bool value) {
                                    node->setCascadeOpacityEnabled(value);
                                    return true;
                                });

    handler.addWriteIntHandler(Property::ColorB,
                               [](cocos2d::Node* node, int value) {
                                   if (not isInColorRange(value)) {
                                       return false;
                                   }
                                   auto color = node->getColor();
                                   color.b = static_cast<GLubyte>(value);
                                   node->setColor(color);
                                   return true;
                               });

    handler.addWriteIntHandler(Property::ColorG,
                               [](cocos2d::Node* node, int value) {
                                   if (not isInColorRange(value)) {
                                       return false;
                                   }
                                   auto color = node->getColor();
                                   color.g = static_cast<GLubyte>(value);
                                   node->setColor(color);
                                   return true;
                               });

    handler.addWriteIntHandler(Property::ColorR,
                               [](cocos2d::Node* node, int value) {
                                   if (not isInColorRange(value)) {
                                       return false;
                                   }
                                   auto color = node->getColor();
                                   color.r = static_cast<GLubyte>(value);
                                   node->setColor(color);
                                   return true;
                               });

    handler.addWriteFloatHandler(Property::ContentSizeHeight,
                                 [](cocos2d::Node* node, float value) {
                                     auto size = node->getContentSize();
                                     size.height = value;
                                     node->setContentSize(size);
                                     return true;
                                 });

    handler.addWriteFloatHandler(Property::ContentSizeWidth,
                                 [](cocos2d::Node* node, float value) {
                                     auto size = node->getContentSize();
                                     size.width = value;
                                     node->setContentSize(size);
                                     return true;
                                 });

    handler.addWriteBoolHandler(Property::IgnoreAnchorPointForPosition,
                                [](cocos2d::Node* node, bool value) {
                                    node->setIgnoreAnchorPointForPosition(
                                        value);
                                    return true;
                                });

    handler.addWriteIntHandler(Property::LocalZOrder,
                               [](cocos2d::Node* node, int value) {
                                   node->setLocalZOrder(value);
                                   return true;
                               });

    handler.addWriteStringHandler(
        Property::Name, [](cocos2d::Node* node, const std::string& name) {
            node->setName(name);
            return true;
        });

    handler.addWriteIntHandler(
        Property::Opacity, [](cocos2d::Node* node, int value) {
            if (not isInColorRange(value)) {
                return false;
            }
            node->setOpacity(static_cast<GLubyte>(value));
            return true;
        });

    handler.addWriteBoolHandler(Property::OpacityModifyRGB,
                                [](cocos2d::Node* node, bool value) {
                                    node->setOpacityModifyRGB(value);
                                    return true;
                                });

    handler.addWriteFloatHandler(Property::PositionX,
                                 [](cocos2d::Node* node, float value) {
                                     auto position = node->getPosition();
                                     position.x = value;
                                     node->setPosition(position);
                                     return true;
                                 });

    handler.addWriteFloatHandler(Property::PositionY,
                                 [](cocos2d::Node* node, float value) {
                                     auto position = node->getPosition();
                                     position.y = value;
                                     node->setPosition(position);
                                     return true;
                                 });

    handler.addWriteFloatHandler(Property::Rotation,
                                 [](cocos2d::Node* node, float value) {
                                     node->setRotation(value);
                                     return true;
                                 });

    handler.addWriteFloatHandler(Property::ScaleX,
                                 [](cocos2d::Node* node, float value) {
                                     node->setScaleX(value);
                                     return true;
                                 });

    handler.addWriteFloatHandler(Property::ScaleY,
                                 [](cocos2d::Node* node, float value) {
                                     node->setScaleY(value);
                                     return true;
                                 });

    handler.addWriteFloatHandler(Property::SkewX,
                                 [](cocos2d::Node* node, float value) {
                                     node->setSkewX(value);
                                     return true;
                                 });

    handler.addWriteFloatHandler(Property::SkewY,
                                 [](cocos2d::Node* node, float value) {
                                     node->setSkewY(value);
                                     return true;
                                 });

    handler.addWriteIntHandler(Property::Tag,
                               [](cocos2d::Node* node, int value) {
                                   node->setTag(value);
                                   return true;
                               });

    handler.addWriteBoolHandler(Property::Visible,
                                [](cocos2d::Node* node, bool value) {
                                    node->setVisible(value);
                                    return true;
                                });
}

void Self::addDefaultProperties(PropertyWriter& writer) {
    bool flag = true;
    flag &= writer.addProperty(Property::AnchorPointX, 0.0f);
    flag &= writer.addProperty(Property::AnchorPointY, 0.0f);
    flag &= writer.addProperty(Property::CascadeColorEnabled, false);
    flag &= writer.addProperty(Property::CascadeOpacityEnabled, false);
    flag &= writer.addProperty(Property::ColorB, cocos2d::Color3B::WHITE.b);
    flag &= writer.addProperty(Property::ColorG, cocos2d::Color3B::WHITE.g);
    flag &= writer.addProperty(Property::ColorR, cocos2d::Color3B::WHITE.r);
    flag &= writer.addProperty(Property::ContentSizeHeight,
                               cocos2d::Size::ZERO.height);
    flag &= writer.addProperty(Property::ContentSizeWidth,
                               cocos2d::Size::ZERO.width);
    flag &= writer.addProperty(Property::IgnoreAnchorPointForPosition, false);
    flag &= writer.addProperty(Property::LocalZOrder, 0);
    flag &= writer.addProperty(Property::Name, std::string());
    flag &= writer.addProperty(Property::Opacity, 255);
    flag &= writer.addProperty(Property::OpacityModifyRGB, false);
    flag &= writer.addProperty(Property::PositionX, 0.0f);
    flag &= writer.addProperty(Property::PositionY, 0.0f);
    flag &= writer.addProperty(Property::Rotation, 0.0f);
    flag &= writer.addProperty(Property::ScaleX, 1.0f);
    flag &= writer.addProperty(Property::ScaleY, 1.0f);
    flag &= writer.addProperty(Property::SkewX, 0.0f);
    flag &= writer.addProperty(Property::SkewY, 0.0f);
    flag &= writer.addProperty(Property::Tag, cocos2d::Node::INVALID_TAG);
    flag &= writer.addProperty(Property::Visible, true);
    Q_ASSERT(flag);
}

NodeLoaderPtr Self::clone() const {
    auto result = cloneRaw();
    result->propertyHandler_ = propertyHandler_;
    result->defaultProperties_ = defaultProperties_;
    return NodeLoaderPtr(result);
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
