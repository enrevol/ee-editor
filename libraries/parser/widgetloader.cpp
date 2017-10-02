#include "widgetloader.hpp"
#include "propertywriter.hpp"

#include <ui/UIWidget.h>

namespace ee {
using Self = WidgetLoader;

const PropertyBool Self::Property::Bright("bright");
const PropertyBool Self::Property::Enabled("enabled");
const PropertyBool Self::Property::FlippedX("flipped_x");
const PropertyBool Self::Property::FlippedY("flipped_y");
const PropertyBool Self::Property::Highlighted("highlighted");
const PropertyBool Self::Property::IgnoreContentAdaptWithSize(
    "ignore_content_adapt_with_size");
const PropertyBool
    Self::Property::LayoutComponentEnabled("layout_component_enabled");
const PropertyPoint Self::Property::PositionPercent("position_percent");
const PropertyInt Self::Property::PositionType("position_type");
const PropertyBool
    Self::Property::PropagateTouchEvents("propagate_touch_events");
const PropertyPoint Self::Property::SizePercent("size_percent");
const PropertyInt Self::Property::SizeType("size_type");
const PropertyBool Self::Property::SwallowTouches("swallow_touches");
const PropertyBool Self::Property::TouchEnabled("touch_enabled");
const PropertyBool Self::Property::UnifySizeEnabled("unify_size_enabled");

const std::string Self::ClassName = "_Widget";

NodeLoaderPtr Self::create() {
    auto result = std::unique_ptr<Self>(new Self());
    result->initialize();
    return std::move(result);
}

Self::WidgetLoader() {}

Self::~WidgetLoader() {}

void Self::addReadHandlers(PropertyHandler& handler) {
    Super::addReadHandlers(handler);

    using Node = cocos2d::ui::Widget;

    handler.addReadHandler<Node>(
        Property::Bright, [](const Node* node) { return node->isBright(); });

    handler.addReadHandler<Node>(
        Property::Enabled, [](const Node* node) { return node->isEnabled(); });

    handler.addReadHandler<Node>(Property::FlippedX, [](const Node* node) {
        return node->isFlippedX();
    });

    handler.addReadHandler<Node>(Property::FlippedY, [](const Node* node) {
        return node->isFlippedY();
    });

    handler.addReadHandler<Node>(Property::Highlighted, [](const Node* node) {
        return node->isHighlighted();
    });

    handler.addReadHandler<Node>(
        Property::IgnoreContentAdaptWithSize,
        [](const Node* node) { return node->isIgnoreContentAdaptWithSize(); });

    handler.addReadHandler<Node>(
        Property::LayoutComponentEnabled,
        [](const Node* node) { return node->isLayoutComponentEnabled(); });

    handler.addReadHandler<Node>(
        Property::PositionPercent, [](const Node* node) {
            return const_cast<Node*>(node)->getPositionPercent();
        });

    handler.addReadHandler<Node>(
        Property::PropagateTouchEvents,
        [](const Node* node) { return node->isPropagateTouchEvents(); });

    handler.addReadHandler<Node>(Property::SizePercent, [](const Node* node) {
        return const_cast<Node*>(node)->getSizePercent();
    });

    handler.addReadHandler<Node>(
        Property::SwallowTouches,
        [](const Node* node) { return node->isSwallowTouches(); });

    handler.addReadHandler<Node>(Property::TouchEnabled, [](const Node* node) {
        return node->isTouchEnabled();
    });

    handler.addReadHandler<Node>(
        Property::UnifySizeEnabled,
        [](const Node* node) { return node->isUnifySizeEnabled(); });
}

void Self::addWriteHandlers(PropertyHandler& handler) {
    Super::addWriteHandlers(handler);

    using Node = cocos2d::ui::Widget;

    handler.addWriteHandler<Node>(Property::Bright, [](Node* node, bool value) {
        node->setBright(value);
        return true;
    });

    handler.addWriteHandler<Node>(Property::Enabled,
                                  [](Node* node, bool value) {
                                      node->setEnabled(value);
                                      return true;
                                  });

    handler.addWriteHandler<Node>(Property::FlippedX,
                                  [](Node* node, bool value) {
                                      node->setFlippedX(value);
                                      return true;
                                  });

    handler.addWriteHandler<Node>(Property::FlippedY,
                                  [](Node* node, bool value) {
                                      node->setFlippedY(value);
                                      return true;
                                  });

    handler.addWriteHandler<Node>(Property::Highlighted,
                                  [](Node* node, bool value) {
                                      node->setHighlighted(value);
                                      return true;
                                  });

    handler.addWriteHandler<Node>(Property::IgnoreContentAdaptWithSize,
                                  [](Node* node, bool value) {
                                      node->ignoreContentAdaptWithSize(value);
                                      return true;
                                  });

    handler.addWriteHandler<Node>(Property::LayoutComponentEnabled,
                                  [](Node* node, bool value) {
                                      node->setLayoutComponentEnabled(value);
                                      return true;
                                  });

    handler.addWriteHandler<Node>(Property::PositionPercent,
                                  [](Node* node, const cocos2d::Vec2& value) {
                                      node->setPositionPercent(value);
                                      return true;
                                  });

    handler.addWriteHandler<Node>(Property::PropagateTouchEvents,
                                  [](Node* node, bool value) {
                                      node->setPropagateTouchEvents(value);
                                      return true;
                                  });

    handler.addWriteHandler<Node>(Property::SizePercent,
                                  [](Node* node, const cocos2d::Vec2& value) {
                                      node->setSizePercent(value);
                                      return true;
                                  });

    handler.addWriteHandler<Node>(Property::SwallowTouches,
                                  [](Node* node, bool value) {
                                      node->setSwallowTouches(value);
                                      return true;
                                  });

    handler.addWriteHandler<Node>(Property::TouchEnabled,
                                  [](Node* node, bool value) {
                                      node->setTouchEnabled(value);
                                      return true;
                                  });

    handler.addWriteHandler<Node>(Property::UnifySizeEnabled,
                                  [](Node* node, bool value) {
                                      node->setUnifySizeEnabled(value);
                                      return true;
                                  });
}

void Self::addDefaultProperties(PropertyWriter& writer) {
    Super::addDefaultProperties(writer);

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
}

cocos2d::Node* Self::createNode() const {
    return cocos2d::ui::Widget::create();
}

std::string Self::getClassName() const {
    return ClassName;
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
