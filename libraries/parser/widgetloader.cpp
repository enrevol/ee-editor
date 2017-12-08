#include "widgetloader.hpp"

#include <ui/UIWidget.h>

namespace ee {
using Self = WidgetLoader;
using Target = cocos2d::ui::Widget;
using Helper = PropertyHelper<Target>;

const PropertyBool Self::Property::Bright(
    "bright", //
    Helper::makeReader<bool>(std::mem_fn(&Target::isBright)),
    Helper::makeWriter<bool>(std::mem_fn(&Target::setBright)));

const PropertyBool Self::Property::Enabled(
    "enabled", //
    Helper::makeReader<bool>(std::mem_fn(&Target::isEnabled)),
    Helper::makeWriter<bool>(std::mem_fn(&Target::setEnabled)));

const PropertyBool Self::Property::FlippedX(
    "flipped_x", //
    Helper::makeReader<bool>(std::mem_fn(&Target::isFlippedX)),
    Helper::makeWriter<bool>(std::mem_fn(&Target::setFlippedX)));

const PropertyBool Self::Property::FlippedY(
    "flipped_y", //
    Helper::makeReader<bool>(std::mem_fn(&Target::isFlippedY)),
    Helper::makeWriter<bool>(std::mem_fn(&Target::setFlippedY)));

const PropertyBool Self::Property::Highlighted(
    "highlighted", //
    Helper::makeReader<bool>(std::mem_fn(&Target::isHighlighted)),
    Helper::makeWriter<bool>(std::mem_fn(&Target::setHighlighted)));

const PropertyBool Self::Property::IgnoreContentAdaptWithSize(
    "ignore_content_adapt_with_size",
    Helper::makeReader<bool>(
        std::mem_fn(&Target::isIgnoreContentAdaptWithSize)),
    Helper::makeWriter<bool>(std::mem_fn(&Target::ignoreContentAdaptWithSize)));

const PropertyBool Self::Property::LayoutComponentEnabled(
    "layout_component_enabled",
    Helper::makeReader<bool>(std::mem_fn(&Target::isLayoutComponentEnabled)),
    Helper::makeWriter<bool>(std::mem_fn(&Target::setLayoutComponentEnabled)));

const PropertyPoint Self::Property::PositionPercent(
    "position_percent",
    Helper::makeReader<cocos2d::Point>([](const Target* node) {
        // FIXME:
        return const_cast<Target*>(node)->getPositionPercent();
    }),
    Helper::makeWriter<cocos2d::Point>(
        std::mem_fn(&Target::setPositionPercent)));

const PropertyEnum<Target::PositionType>
    Self::Property::PositionType("position_type",
                                 Helper::makeReader<Target::PositionType>(
                                     std::mem_fn(&Target::getPositionType)),
                                 Helper::makeWriter<Target::PositionType>(
                                     std::mem_fn(&Target::setPositionType)));

const PropertyBool Self::Property::PropagateTouchEvents(
    "propagate_touch_events",
    Helper::makeReader<bool>(std::mem_fn(&Target::isPropagateTouchEvents)),
    Helper::makeWriter<bool>(std::mem_fn(&Target::setPropagateTouchEvents)));

const PropertyPoint Self::Property::SizePercent(
    "size_percent", //
    Helper ::makeReader<cocos2d::Point>([](const Target* node) {
        // FIXME
        return const_cast<Target*>(node)->getSizePercent();
    }),
    Helper::makeWriter<cocos2d::Point>(std::mem_fn(&Target::setSizePercent)));

const PropertyEnum<Target::SizeType> Self::Property::SizeType(
    "size_type",
    Helper::makeReader<Target::SizeType>(std::mem_fn(&Target::getSizeType)),
    Helper::makeWriter<Target::SizeType>(std::mem_fn(&Target::setSizeType)));

const PropertyBool Self::Property::SwallowTouches(
    "swallow_touches",
    Helper::makeReader<bool>(std::mem_fn(&Target::isSwallowTouches)),
    Helper::makeWriter<bool>(std::mem_fn(&Target::setSwallowTouches)));

const PropertyBool Self::Property::TouchEnabled(
    "touch_enabled",
    Helper::makeReader<bool>(std::mem_fn(&Target::isTouchEnabled)),
    Helper::makeWriter<bool>(std::mem_fn(&Target::setTouchEnabled)));

const PropertyBool Self::Property::UnifySizeEnabled(
    "unify_size_enabled",
    Helper::makeReader<bool>(std::mem_fn(&Target::isUnifySizeEnabled)),
    Helper::makeWriter<bool>(std::mem_fn(&Target::setUnifySizeEnabled)));

const std::string Self::ClassName = "_Widget";

Self::WidgetLoader() {}

Self::~WidgetLoader() {}

/*
writer.setProperty(NodeLoader::Property::AnchorPoint,
                   cocos2d::Vec2::ANCHOR_MIDDLE);

bool flag = true;
flag &= writer.addProperty(Property::Bright, true);
flag &= writer.addProperty(Property::Enabled, true);
flag &= writer.addProperty(Property::FlippedX, false);
flag &= writer.addProperty(Property::FlippedY, false);
flag &= writer.addProperty(Property::Highlighted, false);
flag &= writer.addProperty(Property::IgnoreContentAdaptWithSize, true);
flag &= writer.addProperty(Property::LayoutComponentEnabled, false);
flag &= writer.addProperty(Property::PositionPercent, cocos2d::Vec2::ZERO);
flag &= writer.addProperty(Property::PropagateTouchEvents, true);
flag &= writer.addProperty(Property::SizePercent, cocos2d::Vec2::ZERO);
flag &= writer.addProperty(Property::SwallowTouches, true);
flag &= writer.addProperty(Property::TouchEnabled, false);
flag &= writer.addProperty(Property::UnifySizeEnabled, false);
Q_ASSERT(flag);
*/

cocos2d::Node* Self::createNode() const {
    return Target::create();
}

void Self::loadProperties(cocos2d::Node* node_,
                          const PropertyHandler& handler) const {
    auto node = dynamic_cast<Target*>(node_);
    Super::loadProperties(node, handler);

    handler.loadProperty(Property::Bright, node);
    handler.loadProperty(Property::Enabled, node);
    handler.loadProperty(Property::FlippedX, node);
    handler.loadProperty(Property::FlippedY, node);
    handler.loadProperty(Property::Highlighted, node);
    handler.loadProperty(Property::IgnoreContentAdaptWithSize, node);
    handler.loadProperty(Property::LayoutComponentEnabled, node);
    handler.loadProperty(Property::PositionPercent, node);
    handler.loadProperty(Property::PropagateTouchEvents, node);
    handler.loadProperty(Property::SizePercent, node);
    handler.loadProperty(Property::SwallowTouches, node);
    handler.loadProperty(Property::TouchEnabled, node);
    handler.loadProperty(Property::UnifySizeEnabled, node);
}

void Self::storeProperties(const cocos2d::Node* node_,
                           PropertyHandler& handler) const {
    auto node = dynamic_cast<const Target*>(node_);
    Super::storeProperties(node, handler);

    handler.storeProperty(Property::Bright, node);
    handler.storeProperty(Property::Enabled, node);
    handler.storeProperty(Property::FlippedX, node);
    handler.storeProperty(Property::FlippedY, node);
    handler.storeProperty(Property::Highlighted, node);
    handler.storeProperty(Property::IgnoreContentAdaptWithSize, node);
    handler.storeProperty(Property::LayoutComponentEnabled, node);
    handler.storeProperty(Property::PositionPercent, node);
    handler.storeProperty(Property::PropagateTouchEvents, node);
    handler.storeProperty(Property::SizePercent, node);
    handler.storeProperty(Property::SwallowTouches, node);
    handler.storeProperty(Property::TouchEnabled, node);
    handler.storeProperty(Property::UnifySizeEnabled, node);
}

std::string Self::getClassName() const {
    return ClassName;
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
