#include "widgetloader.hpp"
#include "propertywriter.hpp"

#include <ui/UIWidget.h>

namespace ee {
using Self = WidgetLoader;

const std::string Self::Property::Bright = "bright";
const std::string Self::Property::Enabled = "enabled";
const std::string Self::Property::FlippedX = "flipped_x";
const std::string Self::Property::FlippedY = "flipped_y";
const std::string Self::Property::Highlighted = "highlighted";
const std::string Self::Property::IgnoreContentAdaptWithSize =
    "ignore_content_adapt_with_size";
const std::string Self::Property::LayoutComponentEnabled =
    "layout_component_enabled";
const std::string Self::Property::PositionPercentX = "position_percent_x";
const std::string Self::Property::PositionPercentY = "position_percent_y";
const std::string Self::Property::PositionType = "position_type";
const std::string Self::Property::PropagateTouchEvents =
    "propagate_touch_events";
const std::string Self::Property::SizePercentX = "size_percent_x";
const std::string Self::Property::SizePercentY = "size_percent_y";
const std::string Self::Property::SizeType = "size_type";
const std::string Self::Property::SwallowTouches = "swallow_touches";
const std::string Self::Property::TouchEnabled = "touch_enabled";
const std::string Self::Property::UnifySizeEnabled = "unify_size_enabled";

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

    handler.addReadBoolHandler(Property::Bright, [](const cocos2d::Node* node) {
        auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
        if (widget == nullptr) {
            CC_ASSERT(false);
            return false;
        }
        return widget->isBright();
    });

    handler.addReadBoolHandler(
        Property::Enabled, [](const cocos2d::Node* node) {
            auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            return widget->isEnabled();
        });

    handler.addReadBoolHandler(
        Property::FlippedX, [](const cocos2d::Node* node) {
            auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            return widget->isFlippedX();
        });

    handler.addReadBoolHandler(
        Property::FlippedY, [](const cocos2d::Node* node) {
            auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            return widget->isFlippedY();
        });

    handler.addReadBoolHandler(
        Property::Highlighted, [](const cocos2d::Node* node) {
            auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            return widget->isHighlighted();
        });

    handler.addReadBoolHandler(
        Property::IgnoreContentAdaptWithSize, [](const cocos2d::Node* node) {
            auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            return widget->isIgnoreContentAdaptWithSize();
        });

    handler.addReadBoolHandler(
        Property::LayoutComponentEnabled, [](const cocos2d::Node* node) {
            auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            return widget->isLayoutComponentEnabled();
        });

    handler.addReadFloatHandler(
        Property::PositionPercentX, [](const cocos2d::Node* node) {
            // FIXME: non-const getter.
            auto widget = const_cast<cocos2d::ui::Widget*>(
                dynamic_cast<const cocos2d::ui::Widget*>(node));
            if (widget == nullptr) {
                CC_ASSERT(false);
                return 0.0f;
            }
            return widget->getPositionPercent().x;
        });

    handler.addReadFloatHandler(
        Property::PositionPercentY, [](const cocos2d::Node* node) {
            // FIXME: non-const getter.
            auto widget = const_cast<cocos2d::ui::Widget*>(
                dynamic_cast<const cocos2d::ui::Widget*>(node));
            if (widget == nullptr) {
                CC_ASSERT(false);
                return 0.0f;
            }
            return widget->getPositionPercent().y;
        });

    handler.addReadBoolHandler(
        Property::PropagateTouchEvents, [](const cocos2d::Node* node) {
            auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            return widget->isPropagateTouchEvents();
        });

    handler.addReadBoolHandler(
        Property::SwallowTouches, [](const cocos2d::Node* node) {
            auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            return widget->isSwallowTouches();
        });

    handler.addReadBoolHandler(
        Property::TouchEnabled, [](const cocos2d::Node* node) {
            auto widget = dynamic_cast<const cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            return widget->isTouchEnabled();
        });

    handler.addReadBoolHandler(
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

    handler.addWriteBoolHandler(
        Property::Bright, [](cocos2d::Node* node, bool value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setBright(value);
            return true;
        });

    handler.addWriteBoolHandler(
        Property::Enabled, [](cocos2d::Node* node, bool value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setEnabled(value);
            return true;
        });

    handler.addWriteBoolHandler(
        Property::FlippedX, [](cocos2d::Node* node, bool value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setFlippedX(value);
            return true;
        });

    handler.addWriteBoolHandler(
        Property::FlippedY, [](cocos2d::Node* node, bool value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setFlippedY(value);
            return true;
        });

    handler.addWriteBoolHandler(
        Property::Highlighted, [](cocos2d::Node* node, bool value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setHighlighted(value);
            return true;
        });

    handler.addWriteBoolHandler(
        Property::IgnoreContentAdaptWithSize,
        [](cocos2d::Node* node, bool value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->ignoreContentAdaptWithSize(value);
            return true;
        });

    handler.addWriteBoolHandler(
        Property::LayoutComponentEnabled, [](cocos2d::Node* node, bool value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setLayoutComponentEnabled(value);
            return true;
        });

    handler.addWriteFloatHandler(
        Property::PositionPercentX, [](cocos2d::Node* node, float value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            auto position = widget->getPositionPercent();
            position.x = value;
            widget->setPositionPercent(position);
            return true;
        });

    handler.addWriteFloatHandler(
        Property::PositionPercentY, [](cocos2d::Node* node, float value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            auto position = widget->getPositionPercent();
            position.y = value;
            widget->setPositionPercent(position);
            return true;
        });

    handler.addWriteBoolHandler(
        Property::PropagateTouchEvents, [](cocos2d::Node* node, bool value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setPropagateTouchEvents(value);
            return true;
        });

    handler.addWriteFloatHandler(
        Property::SizePercentX, [](cocos2d::Node* node, float value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            auto size = widget->getSizePercent();
            size.x = value;
            widget->setSizePercent(size);
            return true;
        });

    handler.addWriteFloatHandler(
        Property::SizePercentY, [](cocos2d::Node* node, float value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            auto size = widget->getSizePercent();
            size.y = value;
            widget->setSizePercent(size);
            return true;
        });

    handler.addWriteBoolHandler(
        Property::SwallowTouches, [](cocos2d::Node* node, bool value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setSwallowTouches(value);
            return true;
        });

    handler.addWriteBoolHandler(
        Property::TouchEnabled, [](cocos2d::Node* node, bool value) {
            auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
            if (widget == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            widget->setTouchEnabled(value);
            return true;
        });

    handler.addWriteBoolHandler(
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

    writer.setProperty(NodeLoader::Property::AnchorPointX, 0.5f);
    writer.setProperty(NodeLoader::Property::AnchorPointY, 0.5f);

    bool flag = true;
    flag &= writer.addProperty(Property::Bright, true);
    flag &= writer.addProperty(Property::Enabled, true);
    flag &= writer.addProperty(Property::FlippedX, false);
    flag &= writer.addProperty(Property::FlippedY, false);
    flag &= writer.addProperty(Property::Highlighted, false);
    flag &= writer.addProperty(Property::IgnoreContentAdaptWithSize, true);
    flag &= writer.addProperty(Property::LayoutComponentEnabled, false);
    flag &= writer.addProperty(Property::PositionPercentX, 0.0f);
    flag &= writer.addProperty(Property::PositionPercentY, 0.0f);
    flag &= writer.addProperty(Property::PropagateTouchEvents, true);
    flag &= writer.addProperty(Property::SizePercentX, 0.0f);
    flag &= writer.addProperty(Property::SizePercentY, 0.0f);
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
