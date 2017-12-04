#include <ciso646>

#include "nodeloader.hpp"

#include <2d/CCNode.h>
#include <base/ccTypes.h>

namespace ee {
using Self = NodeLoader;

const PropertyPoint
    Self::Property::AnchorPoint("anchor_point",
                                std::mem_fn(&Target::getAnchorPoint),
                                std::mem_fn(&Target::setAnchorPoint));

const PropertyBool Self::Property::CascadeColorEnabled(
    "cascade_color_enabled", std::mem_fn(&Target::isCascadeColorEnabled),
    std::mem_fn(&Target::setCascadeColorEnabled));

const PropertyBool Self::Property::CascadeOpacityEnabled(
    "cascade_opacity_enabled", std::mem_fn(&Target::isCascadeOpacityEnabled),
    std::mem_fn(&Target::setCascadeOpacityEnabled));

const PropertyColor3B Self::Property::Color("color",
                                            std::mem_fn(&Target::getColor),
                                            std::mem_fn(&Target::setColor));

const PropertySize
    Self::Property::ContentSize("content_size",
                                std::mem_fn(&Target::getContentSize),
                                std::mem_fn(&Target::setContentSize));

const PropertyBool Self::Property::IgnoreAnchorPointForPosition(
    "ignore_anchor_point_for_position",
    std::mem_fn(&Target::isIgnoreAnchorPointForPosition),
    std::mem_fn(&Target::setIgnoreAnchorPointForPosition));

const PropertyInt
    Self::Property::LocalZOrder("local_z_order",
                                std::mem_fn(&Target::getLocalZOrder),
                                std::mem_fn(&Target::setLocalZOrder));

const PropertyString Self::Property::Name("name", std::mem_fn(&Target::getName),
                                          std::mem_fn(&Target::setName));

const PropertyInt Self::Property::Opacity("opacity",
                                          std::mem_fn(&Target::getOpacity),
                                          std::mem_fn(&Target::setOpacity));

const PropertyBool
    Self::Property::OpacityModifyRGB("opacity_modify_rgb",
                                     std::mem_fn(&Target::isOpacityModifyRGB),
                                     std::mem_fn(&Target::setOpacityModifyRGB));

const PropertyPoint Self::Property::Position(
    "position", [](const Target* node) { return node->getPosition(); },
    [](Target* node, const cocos2d::Point& position) {
        node->setPosition(position);
    });

const PropertyFloat Self::Property::Rotation("rotation",
                                             std::mem_fn(&Target::getRotation),
                                             std::mem_fn(&Target::setRotation));

const PropertyFloat Self::Property::ScaleX("scale_x",
                                           std::mem_fn(&Target::getScaleX),
                                           std::mem_fn(&Target::setScaleX));

const PropertyFloat Self::Property::ScaleY("scale_y",
                                           std::mem_fn(&Target::getScaleY),
                                           std::mem_fn(&Target::setScaleY));

const PropertyFloat Self::Property::SkewX("skew_x",
                                          std::mem_fn(&Target::getSkewX),
                                          std::mem_fn(&Target::setSkewX));

const PropertyFloat Self::Property::SkewY("skew_y",
                                          std::mem_fn(&Target::getSkewY),
                                          std::mem_fn(&Target::setSkewY));

const PropertyInt Self::Property::Tag("tag", std::mem_fn(&Target::getTag),
                                      std::mem_fn(&Target::setTag));

const PropertyBool Self::Property::Visible("visible",
                                           std::mem_fn(&Target::isVisible),
                                           std::mem_fn(&Target::setVisible));

const std::string Self::ClassName = "_Node";

namespace {
/*
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
*/
} // namespace

Self::NodeLoader() {}

Self::~NodeLoader() {}

cocos2d::Node* Self::createNode() const {
    return Target::create();
}

/*
bool flag = true;
flag &= writer.addProperty(Property::AnchorPoint, cocos2d::Vec2::ZERO);
flag &= writer.addProperty(Property::CascadeColorEnabled, false);
flag &= writer.addProperty(Property::CascadeOpacityEnabled, false);
flag &= writer.addProperty(Property::Color, cocos2d::Color3B::WHITE);
flag &= writer.addProperty(Property::ContentSize, cocos2d::Size::ZERO);
flag &= writer.addProperty(Property::IgnoreAnchorPointForPosition, false);
flag &= writer.addProperty(Property::LocalZOrder, 0);
flag &= writer.addProperty(Property::Name, std::string());
flag &= writer.addProperty(Property::Opacity, 255);
flag &= writer.addProperty(Property::OpacityModifyRGB, false);
flag &= writer.addProperty(Property::Position, cocos2d::Point::ZERO);
flag &= writer.addProperty(Property::Rotation, 0.0f);
flag &= writer.addProperty(Property::ScaleX, 1.0f);
flag &= writer.addProperty(Property::ScaleY, 1.0f);
flag &= writer.addProperty(Property::SkewX, 0.0f);
flag &= writer.addProperty(Property::SkewY, 0.0f);
flag &=
    writer.addProperty(Property::Tag, -1); // cocos2d::Node::INVALID_TAG);
flag &= writer.addProperty(Property::Visible, true);
*/

void Self::loadProperties(cocos2d::Node* node,
                          const PropertyHandler& handler) const {
    handler.loadProperty(Property::AnchorPoint, node);
    handler.loadProperty(Property::CascadeColorEnabled, node);
    handler.loadProperty(Property::CascadeOpacityEnabled, node);
    handler.loadProperty(Property::Color, node);
    handler.loadProperty(Property::ContentSize, node);
    handler.loadProperty(Property::IgnoreAnchorPointForPosition, node);
    handler.loadProperty(Property::LocalZOrder, node);
    handler.loadProperty(Property::Name, node);
    handler.loadProperty(Property::Opacity, node);
    handler.loadProperty(Property::OpacityModifyRGB, node);
    handler.loadProperty(Property::Position, node);
    handler.loadProperty(Property::Rotation, node);
    handler.loadProperty(Property::ScaleX, node);
    handler.loadProperty(Property::ScaleY, node);
    handler.loadProperty(Property::Position, node);
    handler.loadProperty(Property::SkewX, node);
    handler.loadProperty(Property::SkewY, node);
    handler.loadProperty(Property::Tag, node);
    handler.loadProperty(Property::Visible, node);
}

std::string Self::getClassName() const {
    return ClassName;
}

NodeLoaderPtr Self::clone() const {
    auto result = cloneRaw();
    // result->propertyHandler_ = propertyHandler_;
    // result->defaultProperties_ = defaultProperties_;
    return NodeLoaderPtr(result);
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
