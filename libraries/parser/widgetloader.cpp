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

    handler.addReadHandler(Property::Bright, [](const cocos2d::Node* node) {
        auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
        if (widget == nullptr) {
            CC_ASSERT(false);
            return false;
        }
        return widget->isBright();
    });

    handler.addReadHandler(Property::Enabled, [](const cocos2d::Node* node) {
        auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
        if (widget == nullptr) {
            CC_ASSERT(false);
            return false;
        }
        return widget->isEnabled();
    });

    handler.addReadHandler(Property::FlippedX, [](const cocos2d::Node* node) {
        auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
        if (widget == nullptr) {
            CC_ASSERT(false);
            return false;
        }
        return widget->isFlippedX();
    });

    handler.addReadHandler(Property::FlippedY, [](const cocos2d::Node* node) {
        auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
        if (widget == nullptr) {
            CC_ASSERT(false);
            return false;
        }
        return widget->isFlippedY();
    });

    handler.addReadHandler(
        Property::Highlighted, [](const cocos2d::Node* node) {
            auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            return widget->isHighlighted();
        });

    handler.addReadHandler(
        Property::IgnoreContentAdaptWithSize, [](const cocos2d::Node* node) {
            auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            return widget->isIgnoreContentAdaptWithSize();
        });

    handler.addReadHandler(
        Property::LayoutComponentEnabled, [](const cocos2d::Node* node) {
            auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            return widget->isLayoutComponentEnabled();
        });

    handler.addReadHandler(
        Property::PositionPercent, [](const cocos2d::Node* node) {
            // FIXME: non-const getter.
            auto widget = const_cast<cocos2d::ui::Widget*>(
                dynamic_cast<const cocos2d::ui::Widget*>(node));
            if (widget == nullptr) {
                CC_ASSERT(false);
                return cocos2d::Vec2::ZERO;
            }
            return widget->getPositionPercent();
        });

    handler.addReadHandler(
        Property::PropagateTouchEvents, [](const cocos2d::Node* node) {
            auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            return widget->isPropagateTouchEvents();
        });

    handler.addReadHandler(
        Property::SizePercent, [](const cocos2d::Node* node) {
            // FIXME: non-const getter.
            auto widget = const_cast<cocos2d::ui::Widget*>(
                dynamic_cast<const cocos2d::ui::Widget*>(node));
            if (widget == nullptr) {
                CC_ASSERT(false);
                return cocos2d::Vec2::ZERO;
            }
            return widget->getSizePercent();
        });

    handler.addReadHandler(
        Property::SwallowTouches, [](const cocos2d::Node* node) {
            auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            return widget->isSwallowTouches();
        });

    handler.addReadHandler(
        Property::TouchEnabled, [](const cocos2d::Node* node) {
            auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            return widget->isTouchEnabled();
        });

    handler.addReadHandler(
        Property::UnifySizeEnabled, [](const cocos2d::Node* node) {
            auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            return widget->isUnifySizeEnabled();
        });
}

void Self::addWriteHandlers(PropertyHandler& handler) {
    Super::addWriteHandlers(handler);

    handler.addWriteHandler(
        Property::Bright, [](cocos2d::Node* node, bool value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setBright(value);
            return true;
        });

    handler.addWriteHandler(
        Property::Enabled, [](cocos2d::Node* node, bool value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setEnabled(value);
            return true;
        });

    handler.addWriteHandler(
        Property::FlippedX, [](cocos2d::Node* node, bool value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setFlippedX(value);
            return true;
        });

    handler.addWriteHandler(
        Property::FlippedY, [](cocos2d::Node* node, bool value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setFlippedY(value);
            return true;
        });

    handler.addWriteHandler(
        Property::Highlighted, [](cocos2d::Node* node, bool value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setHighlighted(value);
            return true;
        });

    handler.addWriteHandler(Property::IgnoreContentAdaptWithSize,
                            [](cocos2d::Node* node, bool value) {
                                auto widget =
                                    dynamic_cast<cocos2d::ui::Widget*>(node);
                                if (widget == nullptr) {
                                    CC_ASSERT(false);
                                    return false;
                                }
                                widget->ignoreContentAdaptWithSize(value);
                                return true;
                            });

    handler.addWriteHandler(
        Property::LayoutComponentEnabled, [](cocos2d::Node* node, bool value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setLayoutComponentEnabled(value);
            return true;
        });

    handler.addWriteHandler(
        Property::PositionPercent,
        [](cocos2d::Node* node, const cocos2d::Vec2& value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setPositionPercent(value);
            return true;
        });

    handler.addWriteHandler(
        Property::PropagateTouchEvents, [](cocos2d::Node* node, bool value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setPropagateTouchEvents(value);
            return true;
        });

    handler.addWriteHandler(
        Property::SizePercent,
        [](cocos2d::Node* node, const cocos2d::Vec2& value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setSizePercent(value);
            return true;
        });

    handler.addWriteHandler(
        Property::SwallowTouches, [](cocos2d::Node* node, bool value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setSwallowTouches(value);
            return true;
        });

    handler.addWriteHandler(
        Property::TouchEnabled, [](cocos2d::Node* node, bool value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setTouchEnabled(value);
            return true;
        });

    handler.addWriteHandler(
        Property::UnifySizeEnabled, [](cocos2d::Node* node, bool value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setUnifySizeEnabled(value);
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
