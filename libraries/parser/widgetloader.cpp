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

const std::string Self::Name = "_Widget";

Self::WidgetLoader() {
    addProperty(Property::Bright);
    addProperty(Property::Enabled);
    addProperty(Property::FlippedX);
    addProperty(Property::FlippedY);
    addProperty(Property::Highlighted);
    addProperty(Property::IgnoreContentAdaptWithSize);
    addProperty(Property::LayoutComponentEnabled);
    addProperty(Property::PositionPercent);
    addProperty(Property::PropagateTouchEvents);
    addProperty(Property::SizePercent);
    addProperty(Property::SwallowTouches);
    addProperty(Property::TouchEnabled);
    addProperty(Property::UnifySizeEnabled);
}

Self::~WidgetLoader() {}

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
