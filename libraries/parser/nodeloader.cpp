#include <ciso646>

#include "nodeloader.hpp"
#include "propertyreader.hpp"
#include "propertywriter.hpp"

#include <2d/CCNode.h>
#include <base/ccTypes.h>

namespace ee {
using Self = NodeLoader;

const PropertyPoint Self::Property::AnchorPoint("anchor_point");
const PropertyBool Self::Property::CascadeColorEnabled("cascade_color_enabled");
const PropertyBool
    Self::Property::CascadeOpacityEnabled("cascade_opacity_enabled");
const PropertyColor Self::Property::Color("color");
const PropertySize Self::Property::ContentSize("content_size");
const PropertyBool Self::Property::IgnoreAnchorPointForPosition(
    "ignore_anchor_point_for_position");
const PropertyInt Self::Property::LocalZOrder("local_z_order");
const PropertyString Self::Property::Name("name");
const PropertyInt Self::Property::Opacity("opacity");
const PropertyBool Self::Property::OpacityModifyRGB("opacity_modify_rgb");
const PropertyPoint Self::Property::Position("position");
const PropertyFloat Self::Property::Rotation("rotation");
const PropertyFloat Self::Property::ScaleX("scale_x");
const PropertyFloat Self::Property::ScaleY("scale_y");
const PropertyFloat Self::Property::SkewX("skew_x");
const PropertyFloat Self::Property::SkewY("skew_y");
const PropertyInt Self::Property::Tag("tag");
const PropertyBool Self::Property::Visible("visible");

const std::string Self::ClassName = "_Node";

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

std::string Self::getClassName() const {
    return ClassName;
}

const PropertyHandler& Self::getPropertyHandler() const {
    return propertyHandler_;
}

PropertyReader Self::getDefaultPropertyReader() const {
    return PropertyReader(defaultProperties_);
}

void Self::addReadHandlers(PropertyHandler& handler) {
    handler.addReadHandler(
        Property::AnchorPoint,
        [](const cocos2d::Node* node) { return node->getAnchorPoint(); });

    handler.addReadHandler(Property::CascadeColorEnabled,
                           [](const cocos2d::Node* node) {
                               return node->isCascadeColorEnabled();
                           });

    handler.addReadHandler(Property::CascadeOpacityEnabled,
                           [](const cocos2d::Node* node) {
                               return node->isCascadeOpacityEnabled();
                           });

    handler.addReadHandler(Property::Color, [](const cocos2d::Node* node) {
        return node->getColor();
    });

    handler.addReadHandler(
        Property::ContentSize,
        [](const cocos2d::Node* node) { return node->getContentSize(); });

    handler.addReadHandler(Property::IgnoreAnchorPointForPosition,
                           [](const cocos2d::Node* node) {
                               return node->isIgnoreAnchorPointForPosition();
                           });

    handler.addReadHandler(
        Property::LocalZOrder,
        [](const cocos2d::Node* node) { return node->getLocalZOrder(); });

    handler.addReadHandler(Property::Name, [](const cocos2d::Node* node) {
        return node->getName();
    });

    handler.addReadHandler(Property::Opacity, [](const cocos2d::Node* node) {
        return static_cast<int>(node->getOpacity());
    });

    handler.addReadHandler(
        Property::OpacityModifyRGB,
        [](const cocos2d::Node* node) { return node->isOpacityModifyRGB(); });

    handler.addReadHandler(Property::Position, [](const cocos2d::Node* node) {
        return node->getPosition();
    });

    handler.addReadHandler(Property::Rotation, [](const cocos2d::Node* node) {
        return node->getRotation();
    });

    handler.addReadHandler(Property::ScaleX, [](const cocos2d::Node* node) {
        return node->getScaleX();
    });

    handler.addReadHandler(Property::ScaleY, [](const cocos2d::Node* node) {
        return node->getScaleY();
    });

    handler.addReadHandler(Property::SkewX, [](const cocos2d::Node* node) {
        return node->getSkewX();
    });

    handler.addReadHandler(Property::SkewY, [](const cocos2d::Node* node) {
        return node->getSkewY();
    });

    handler.addReadHandler(Property::Tag, [](const cocos2d::Node* node) {
        return node->getTag();
    });

    handler.addReadHandler(Property::Visible, [](const cocos2d::Node* node) {
        return node->isVisible();
    });
}

void Self::addWriteHandlers(PropertyHandler& handler) {
    handler.addWriteHandler(
        Property::AnchorPoint,
        [](cocos2d::Node* node, const cocos2d::Vec2& value) {
            node->setAnchorPoint(value);
            return true;
        });

    handler.addWriteHandler(Property::CascadeColorEnabled,
                            [](cocos2d::Node* node, bool value) {
                                node->setCascadeColorEnabled(value);
                                return true;
                            });

    handler.addWriteHandler(Property::CascadeOpacityEnabled,
                            [](cocos2d::Node* node, bool value) {
                                node->setCascadeOpacityEnabled(value);
                                return true;
                            });

    handler.addWriteHandler(Property::Color, [](cocos2d::Node* node,
                                                const cocos2d::Color3B& value) {
        node->setColor(value);
        return true;
    });

    handler.addWriteHandler(
        Property::ContentSize,
        [](cocos2d::Node* node, const cocos2d::Size& value) {
            node->setContentSize(value);
            return true;
        });

    handler.addWriteHandler(Property::IgnoreAnchorPointForPosition,
                            [](cocos2d::Node* node, bool value) {
                                node->setIgnoreAnchorPointForPosition(value);
                                return true;
                            });

    handler.addWriteHandler(Property::LocalZOrder,
                            [](cocos2d::Node* node, int value) {
                                node->setLocalZOrder(value);
                                return true;
                            });

    handler.addWriteHandler(Property::Name,
                            [](cocos2d::Node* node, const std::string& name) {
                                node->setName(name);
                                return true;
                            });

    handler.addWriteHandler(Property::Opacity,
                            [](cocos2d::Node* node, int value) {
                                if (not isInColorRange(value)) {
                                    return false;
                                }
                                node->setOpacity(static_cast<GLubyte>(value));
                                return true;
                            });

    handler.addWriteHandler(Property::OpacityModifyRGB,
                            [](cocos2d::Node* node, bool value) {
                                node->setOpacityModifyRGB(value);
                                return true;
                            });

    handler.addWriteHandler(
        Property::Position,
        [](cocos2d::Node* node, const cocos2d::Point& value) {
            node->setPosition(value);
            return true;
        });

    handler.addWriteHandler(Property::Rotation,
                            [](cocos2d::Node* node, float value) {
                                node->setRotation(value);
                                return true;
                            });

    handler.addWriteHandler(Property::ScaleX,
                            [](cocos2d::Node* node, float value) {
                                node->setScaleX(value);
                                return true;
                            });

    handler.addWriteHandler(Property::ScaleY,
                            [](cocos2d::Node* node, float value) {
                                node->setScaleY(value);
                                return true;
                            });

    handler.addWriteHandler(Property::SkewX,
                            [](cocos2d::Node* node, float value) {
                                node->setSkewX(value);
                                return true;
                            });

    handler.addWriteHandler(Property::SkewY,
                            [](cocos2d::Node* node, float value) {
                                node->setSkewY(value);
                                return true;
                            });

    handler.addWriteHandler(Property::Tag, [](cocos2d::Node* node, int value) {
        node->setTag(value);
        return true;
    });

    handler.addWriteHandler(Property::Visible,
                            [](cocos2d::Node* node, bool value) {
                                node->setVisible(value);
                                return true;
                            });
}

void Self::addDefaultProperties(PropertyWriter& writer) {
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
