#include "nodeinspector.hpp"
#include "inspectorbool.hpp"
#include "inspectorcolor.hpp"
#include "inspectorfloat.hpp"
#include "inspectorfloatxy.hpp"
#include "inspectorint.hpp"
#include "inspectorintslider.hpp"
#include "inspectorscale.hpp"
#include "inspectorstring.hpp"

#include <parser/nodeloader.hpp>

#include <base/ccTypes.h>
#include <math/Vec2.h>

namespace ee {
using Self = NodeInspector;

namespace {
auto createVisibleInspector() {
    return (new InspectorBool())
        ->setPropertyDisplayName("Visible")
        ->setReader(NodeLoader::Property::Visible.getReader())
        ->setWriter(NodeLoader::Property::Visible.getWriter());
}

auto createNameInspector() {
    return (new InspectorString())
        ->setPropertyDisplayName("Name")
        ->setReader(NodeLoader::Property::Name.getReader())
        ->setWriter(NodeLoader::Property::Name.getWriter());
}

auto createPositionInspector() {
    return (new InspectorFloatXY())
        ->setReader([](const cocos2d::Node* node) {
            auto value = NodeLoader::Property::Position.read(node);
            return std::make_pair(value->x, value->y);
        })
        ->setWriter([](cocos2d::Node* node, float x, float y) {
            return NodeLoader::Property::Position.write(node,
                                                        cocos2d::Point(x, y));
        })
        ->setPropertyDisplayName("Position")
        ->setSubPropertyDisplayName("X", "Y")
        ->setSingleStep(1.0f)
        ->setValuePrecision(2)
        ->setMinimumValue(-9999.99f)
        ->setMaximumValue(+9999.99f);
}

auto createContentSizeInspector() {
    return (new InspectorFloatXY())
        ->setReader([](const cocos2d::Node* node) {
            auto value = NodeLoader::Property::ContentSize.read(node);
            return std::make_pair(value->width, value->height);
        })
        ->setWriter([](cocos2d::Node* node, float x, float y) {
            return NodeLoader::Property::ContentSize.write(node,
                                                           cocos2d::Size(x, y));
        })
        ->setPropertyDisplayName("Content size")
        ->setSubPropertyDisplayName("W", "H")
        ->setSingleStep(1.0f)
        ->setValuePrecision(2)
        ->setMinimumValue(-9999.99f)
        ->setMaximumValue(+9999.99f);
}

auto createAnchorPointInspector() {
    return (new InspectorFloatXY())
        ->setReader([](const cocos2d::Node* node) {
            auto value = NodeLoader::Property::AnchorPoint.read(node);
            return std::make_pair(value->x, value->y);
        })
        ->setWriter([](cocos2d::Node* node, float x, float y) {
            return NodeLoader::Property::AnchorPoint.write(node,
                                                           cocos2d::Vec2(x, y));
        })
        ->setPropertyDisplayName("Anchor point")
        ->setSubPropertyDisplayName("X", "Y")
        ->setSingleStep(0.05f)
        ->setValuePrecision(3)
        ->setMinimumValue(-99.99f)
        ->setMaximumValue(+99.99f);
}

auto createScaleInspector() {
    return (new InspectorFloatXY())
        ->setReader([](const cocos2d::Node* node) {
            auto x = NodeLoader::Property::ScaleX.read(node);
            auto y = NodeLoader::Property::ScaleY.read(node);
            return std::make_pair(*x, *y);
        })
        ->setWriter([](cocos2d::Node* node, float x, float y) {
            return NodeLoader::Property::ScaleX.write(node, x) &&
                   NodeLoader::Property::ScaleY.write(node, y);
        })
        ->setPropertyDisplayName("Scale")
        ->setSubPropertyDisplayName("X", "Y")
        ->setSingleStep(0.05f)
        ->setValuePrecision(3)
        ->setMinimumValue(-99.99f)
        ->setMaximumValue(+99.99f);
}

auto createRotationInspector() {
    return (new InspectorFloat())
        ->setReader(NodeLoader::Property::Rotation.getReader())
        ->setWriter(NodeLoader::Property::Rotation.getWriter())
        ->setPropertyDisplayName("Rotation")
        ->setSingleStep(1.0f)
        ->setValuePrecision(2)
        ->setMinimumValue(-359.99f)
        ->setMaximumValue(+359.99f);
}

auto createSkewInspector() {
    return (new InspectorFloatXY())
        ->setReader([](const cocos2d::Node* node) {
            auto x = NodeLoader::Property::SkewX.read(node);
            auto y = NodeLoader::Property::SkewY.read(node);
            return std::make_pair(*x, *y);
        })
        ->setWriter([](cocos2d::Node* node, float x, float y) {
            return NodeLoader::Property::SkewX.write(node, x) &&
                   NodeLoader::Property::SkewY.write(node, y);
        })
        ->setPropertyDisplayName("Skew")
        ->setSubPropertyDisplayName("X", "Y")
        ->setSingleStep(0.05f)
        ->setValuePrecision(3)
        ->setMinimumValue(-99.99f)
        ->setMaximumValue(+99.99f);
};

auto createTagInspector() {
    return (new InspectorInt())
        ->setReader(NodeLoader::Property::Tag.getReader())
        ->setWriter(NodeLoader::Property::Tag.getWriter())
        ->setPropertyDisplayName("Tag")
        ->setSingleStep(1)
        ->setMinimumValue(-1)
        ->setMaximumValue(+9999);
}

auto createLocalZOrderInspector() {
    return (new InspectorInt())
        ->setReader(NodeLoader::Property::LocalZOrder.getReader())
        ->setWriter(NodeLoader::Property::LocalZOrder.getWriter())
        ->setPropertyDisplayName("Local z-order")
        ->setSingleStep(1)
        ->setMinimumValue(-9999)
        ->setMaximumValue(+9999);
}

auto createColorInspector() {
    return (new InspectorColor())
        ->setReader(NodeLoader::Property::Color.getReader())
        ->setWriter(NodeLoader::Property::Color.getWriter())
        ->setPropertyDisplayName("Color");
}

auto createOpacityInspector() {
    return (new InspectorIntSlider())
        ->setReader(NodeLoader::Property::Opacity.getReader())
        ->setWriter(NodeLoader::Property::Opacity.getWriter())
        ->setPropertyDisplayName("Opacity")
        ->setSingleStep(1)
        ->setMinimumValue(+0)
        ->setMaximumValue(+255);
}

auto createCascadeColorEnabledInspector() {
    return (new InspectorBool())
        ->setReader(NodeLoader::Property::CascadeColorEnabled.getReader())
        ->setWriter(NodeLoader::Property::CascadeColorEnabled.getWriter())
        ->setPropertyDisplayName("Cascade color enabled");
}

auto createCascadeOpacityEnabledInspector() {
    return (new InspectorBool())
        ->setReader(NodeLoader::Property::CascadeOpacityEnabled.getReader())
        ->setWriter(NodeLoader::Property::CascadeOpacityEnabled.getWriter())
        ->setPropertyDisplayName("Cascade opacity enabled");
}

auto createOpacityModifyRGBInspector() {
    return (new InspectorBool())
        ->setReader(NodeLoader::Property::OpacityModifyRGB.getReader())
        ->setWriter(NodeLoader::Property::OpacityModifyRGB.getWriter())
        ->setPropertyDisplayName("Opacity modify RGB");
}

auto createIgnoreAnchorPointForPositionInspector() {
    return (new InspectorBool())
        ->setReader(
            NodeLoader::Property::IgnoreAnchorPointForPosition.getReader())
        ->setWriter(
            NodeLoader::Property::IgnoreAnchorPointForPosition.getWriter())
        ->setPropertyDisplayName("Ignore anchor point for position");
}
} // namespace

Self::NodeInspector(QWidget* parent)
    : Super(parent) {
    setDisplayName("Node");
    addInspector(createVisibleInspector());
    addInspector(createNameInspector());
    addInspector(createPositionInspector());
    addInspector(createContentSizeInspector());
    addInspector(createAnchorPointInspector());
    addInspector(createScaleInspector());
    addInspector(createRotationInspector());
    addInspector(createSkewInspector());
    addInspector(createTagInspector());
    addInspector(createLocalZOrderInspector());
    addInspector(createColorInspector());
    addInspector(createOpacityInspector());
    addInspector(createCascadeColorEnabledInspector());
    addInspector(createCascadeOpacityEnabledInspector());
    addInspector(createOpacityModifyRGBInspector());
    addInspector(createIgnoreAnchorPointForPositionInspector());
}
} // namespace ee
