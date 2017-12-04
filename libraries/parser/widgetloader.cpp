#include "widgetloader.hpp"

#include <ui/UIWidget.h>

namespace ee {
using Self = WidgetLoader;

const PropertyBool<Self::Target>
    Self::Property::Bright("bright", std::mem_fn(&Target::isBright),
                           std::mem_fn(&Target::setBright));

const PropertyBool<Self::Target>
    Self::Property::Enabled("enabled", std::mem_fn(&Target::isEnabled),
                            std::mem_fn(&Target::setEnabled));

const PropertyBool<Self::Target>
    Self::Property::FlippedX("flipped_x", std::mem_fn(&Target::isFlippedX),
                             std::mem_fn(&Target::setFlippedX));

const PropertyBool<Self::Target>
    Self::Property::FlippedY("flipped_y", std::mem_fn(&Target::isFlippedY),
                             std::mem_fn(&Target::setFlippedY));

const PropertyBool<Self::Target>
    Self::Property::Highlighted("highlighted",
                                std::mem_fn(&Target::isHighlighted),
                                std::mem_fn(&Target::setHighlighted));

const PropertyBool<Self::Target> Self::Property::IgnoreContentAdaptWithSize(
    "ignore_content_adapt_with_size",
    std::mem_fn(&Target::isIgnoreContentAdaptWithSize),
    std::mem_fn(&Target::setIgnoreAnchorPointForPosition));

const PropertyBool<Self::Target> Self::Property::LayoutComponentEnabled(
    "layout_component_enabled", std::mem_fn(&Target::isLayoutComponentEnabled),
    std::mem_fn(&Target::setLayoutComponentEnabled));

const PropertyPoint<Self::Target> Self::Property::PositionPercent(
    "position_percent",
    [](const Target* node) {
        // FIXME:
        return const_cast<Target*>(node)->getPositionPercent();
    },
    std::mem_fn(&Target::setPositionPercent));

const PropertyEnum<Self::Target, cocos2d::ui::Widget::PositionType>
    Self::Property::PositionType("position_type",
                                 std::mem_fn(&Target::getPositionType),
                                 std::mem_fn(&Target::setPositionType));

const PropertyBool<Self::Target> Self::Property::PropagateTouchEvents(
    "propagate_touch_events", std::mem_fn(&Target::isPropagateTouchEvents),
    std::mem_fn(&Target::setPropagateTouchEvents));

const PropertyPoint<Self::Target> Self::Property::SizePercent(
    "size_percent",
    [](const Target* node) {
        // FIXME
        return const_cast<Target*>(node)->getSizePercent();
    },
    std::mem_fn(&Target::setSizePercent));

const PropertyEnum<Self::Target, cocos2d::ui::Widget::SizeType>
    Self::Property::SizeType("size_type", std::mem_fn(&Target::getSizeType),
                             std::mem_fn(&Target::setSizeType));

const PropertyBool<Self::Target>
    Self::Property::SwallowTouches("swallow_touches",
                                   std::mem_fn(&Target::isSwallowTouches),
                                   std::mem_fn(&Target::setSwallowTouches));

const PropertyBool<Self::Target>
    Self::Property::TouchEnabled("touch_enabled",
                                 std::mem_fn(&Target::isTouchEnabled),
                                 std::mem_fn(&Target::setTouchEnabled));

const PropertyBool<Self::Target>
    Self::Property::UnifySizeEnabled("unify_size_enabled",
                                     std::mem_fn(&Target::isUnifySizeEnabled),
                                     std::mem_fn(&Target::setUnifySizeEnabled));

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

std::string Self::getClassName() const {
    return ClassName;
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
