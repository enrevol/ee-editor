#include <ciso646>

#include "nodeloader.hpp"

#include <2d/CCNode.h>
#include <base/ccTypes.h>

namespace ee {
using Self = NodeLoader;
using Target = cocos2d::Node;
using Helper = PropertyHelper<Target>;

const PropertyPoint Self::Property::AnchorPoint(
    "anchor_point",
    Helper::makeReader<cocos2d::Point>(std::mem_fn(&Target::getAnchorPoint)),
    Helper::makeWriter<cocos2d::Point>(std::mem_fn(&Target::setAnchorPoint)));

const PropertyBool Self::Property::CascadeColorEnabled(
    "cascade_color_enabled",
    Helper::makeReader<bool>(std::mem_fn(&Target::isCascadeColorEnabled)),
    Helper::makeWriter<bool>(std::mem_fn(&Target::setCascadeColorEnabled)));

const PropertyBool Self::Property::CascadeOpacityEnabled(
    "cascade_opacity_enabled",
    Helper::makeReader<bool>(std::mem_fn(&Target::isCascadeOpacityEnabled)),
    Helper::makeWriter<bool>(std::mem_fn(&Target::setCascadeOpacityEnabled)));

const PropertyColor3B Self::Property::Color(
    "color",
    Helper::makeReader<cocos2d::Color3B>(std::mem_fn(&Target::getColor)),
    Helper::makeWriter<cocos2d::Color3B>(std::mem_fn(&Target::setColor)));

const PropertySize Self::Property::ContentSize(
    "content_size",
    Helper::makeReader<cocos2d::Size>(std::mem_fn(&Target::getContentSize)),
    Helper::makeWriter<cocos2d::Size>(std::mem_fn(&Target::setContentSize)));

const PropertyBool Self::Property::IgnoreAnchorPointForPosition(
    "ignore_anchor_point_for_position",
    Helper::makeReader<bool>(
        std::mem_fn(&Target::isIgnoreAnchorPointForPosition)),
    Helper::makeWriter<bool>(
        std::mem_fn(&Target::setIgnoreAnchorPointForPosition)));

const PropertyInt Self::Property::LocalZOrder(
    "local_z_order",
    Helper::makeReader<int>(std::mem_fn(&Target::getLocalZOrder)),
    Helper::makeWriter<int>(std::mem_fn(&Target::setLocalZOrder)));

const PropertyString Self::Property::Name(
    "name", //
    Helper::makeReader<std::string>(std::mem_fn(&Target::getName)),
    Helper::makeWriter<std::string>(std::mem_fn(&Target::setName)));

const PropertyInt Self::Property::Opacity(
    "opacity", //
    Helper::makeReader<int>(std::mem_fn(&Target::getOpacity)),
    Helper::makeWriter<int>(std::mem_fn(&Target::setOpacity)));

const PropertyBool Self::Property::OpacityModifyRGB(
    "opacity_modify_rgb",
    Helper::makeReader<bool>(std::mem_fn(&Target::isOpacityModifyRGB)),
    Helper::makeWriter<bool>(std::mem_fn(&Target::setOpacityModifyRGB)));

const PropertyPoint Self::Property::Position(
    "position", Helper ::makeReader<cocos2d::Point>([](const Target* node) {
        return node->getPosition();
    }),
    Helper::makeWriter<cocos2d::Point>([](Target* node,
                                          const cocos2d::Point& position) {
        node->setPosition(position);
    }));

const PropertyFloat Self::Property::Rotation(
    "rotation", //
    Helper::makeReader<float>(std::mem_fn(&Target::getRotation)),
    Helper::makeWriter<float>(std::mem_fn(&Target::setRotation)));

const PropertyFloat Self::Property::ScaleX(
    "scale_x", //
    Helper::makeReader<float>(std::mem_fn(&Target::getScaleX)),
    Helper::makeWriter<float>(std::mem_fn(&Target::setScaleX)));

const PropertyFloat Self::Property::ScaleY(
    "scale_y", //
    Helper::makeReader<float>(std::mem_fn(&Target::getScaleY)),
    Helper::makeWriter<float>(std::mem_fn(&Target::setScaleY)));

const PropertyFloat Self::Property::SkewX(
    "skew_x", //
    Helper::makeReader<float>(std::mem_fn(&Target::getSkewX)),
    Helper::makeWriter<float>(std::mem_fn(&Target::setSkewX)));

const PropertyFloat Self::Property::SkewY(
    "skew_y", //
    Helper::makeReader<float>(std::mem_fn(&Target::getSkewY)),
    Helper::makeWriter<float>(std::mem_fn(&Target::setSkewY)));

const PropertyInt
    Self::Property::Tag("tag",
                        Helper::makeReader<int>(std::mem_fn(&Target::getTag)),
                        Helper::makeWriter<int>(std::mem_fn(&Target::setTag)));

const PropertyBool Self::Property::Visible(
    "visible", //
    Helper::makeReader<bool>(std::mem_fn(&Target::isVisible)),
    Helper::makeWriter<bool>(std::mem_fn(&Target::setVisible)));

const std::string Self::Name = "_Node";

Self::NodeLoader() {
    addProperty(Property::AnchorPoint);
    addProperty(Property::CascadeColorEnabled);
    addProperty(Property::CascadeOpacityEnabled);
    addProperty(Property::Color);
    addProperty(Property::ContentSize);
    addProperty(Property::IgnoreAnchorPointForPosition);
    addProperty(Property::LocalZOrder);
    addProperty(Property::Name);
    addProperty(Property::Opacity);
    addProperty(Property::OpacityModifyRGB);
    addProperty(Property::Position);
    addProperty(Property::Rotation);
    addProperty(Property::ScaleX);
    addProperty(Property::ScaleY);
    addProperty(Property::Position);
    addProperty(Property::SkewX);
    addProperty(Property::SkewY);
    addProperty(Property::Tag);
    addProperty(Property::Visible);
}

Self::~NodeLoader() {}

std::string Self::getName() const {
    return Name;
}

cocos2d::Node* Self::createNode() const {
    return Target::create();
}

void Self::loadProperties(cocos2d::Node* node,
                          const PropertyHandler& handler) const {
    for (auto&& property : getProperties()) {
        if (not property->load(handler, node)) {
            CCLOG("Error loading property: %s", property->getName().c_str());
        }
    }
}

void Self::storeProperties(const cocos2d::Node* node,
                           PropertyHandler& handler) const {
    for (auto&& property : getProperties()) {
        if (not property->store(handler, node)) {
            CCLOG("Error storing property: %s", property->getName().c_str());
        }
    }
}

Self& Self::addProperty(const ee::Property& property) {
    properties_.push_back(&property);
    return *this;
}

const std::vector<const ee::Property*>& Self::getProperties() const {
    return properties_;
}

NodeLoaderPtr Self::clone() const {
    auto result = cloneRaw();
    result->properties_ = properties_;
    return NodeLoaderPtr(result);
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
