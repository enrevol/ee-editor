#include "widgetinspector.hpp"
#include "inspectorbool.hpp"
#include "inspectorfloatxy.hpp"

#include <parser/widgetloader.hpp>

namespace ee {
using Self = WidgetInspector;

namespace {
auto createEnabledInspector() {
    return (new InspectorBool())
        ->setReader(WidgetLoader::Property::Enabled.getReader())
        ->setWriter(WidgetLoader::Property::Enabled.getWriter())
        ->setPropertyDisplayName("Enabled");
}

auto createBrightInspector() {
    return (new InspectorBool())
        ->setReader(WidgetLoader::Property::Bright.getReader())
        ->setWriter(WidgetLoader::Property::Bright.getWriter())
        ->setPropertyDisplayName("Bright");
}

auto createHighlightedInspector() {
    return (new InspectorBool())
        ->setReader(WidgetLoader::Property::Highlighted.getReader())
        ->setWriter(WidgetLoader::Property::Highlighted.getWriter())
        ->setPropertyDisplayName("Highlighted");
}

auto createIgnoreContentAdaptWithSizeInspector() {
    return (new InspectorBool())
        ->setReader(
            WidgetLoader::Property::IgnoreContentAdaptWithSize.getReader())
        ->setWriter(
            WidgetLoader::Property::IgnoreContentAdaptWithSize.getWriter())
        ->setPropertyDisplayName("Ignore content adapt with size");
}

auto createUnifySizeEnabledInspector() {
    return (new InspectorBool())
        ->setReader(WidgetLoader::Property::UnifySizeEnabled.getReader())
        ->setWriter(WidgetLoader::Property::UnifySizeEnabled.getWriter())
        ->setPropertyDisplayName("Unify size enabled");
}

auto createTouchEnabledInspector() {
    return (new InspectorBool())
        ->setReader(WidgetLoader::Property::TouchEnabled.getReader())
        ->setWriter(WidgetLoader::Property::TouchEnabled.getWriter())
        ->setPropertyDisplayName("Touch enabled");
}

auto createSwallowTouchesInspector() {
    return (new InspectorBool())
        ->setReader(WidgetLoader::Property::SwallowTouches.getReader())
        ->setWriter(WidgetLoader::Property::SwallowTouches.getWriter())
        ->setPropertyDisplayName("Swallow touches");
}

auto createPropagateTouchEventsInspector() {
    return (new InspectorBool())
        ->setReader(WidgetLoader::Property::PropagateTouchEvents.getReader())
        ->setWriter(WidgetLoader::Property::PropagateTouchEvents.getWriter())
        ->setPropertyDisplayName("Propagate touch events");
}

auto createFlippedXInspector() {
    return (new InspectorBool())
        ->setReader(WidgetLoader::Property::FlippedX.getReader())
        ->setWriter(WidgetLoader::Property::FlippedX.getWriter())
        ->setPropertyDisplayName("Flipped X");
}

auto createFlippedYInspector() {
    return (new InspectorBool())
        ->setReader(WidgetLoader::Property::FlippedY.getReader())
        ->setWriter(WidgetLoader::Property::FlippedY.getWriter())
        ->setPropertyDisplayName("Flipped Y");
}

auto createPositionPercentInspector() {
    return (new InspectorFloatXY())
        ->setReader([](const cocos2d::Node* node) {
            auto value = WidgetLoader::Property::PositionPercent.read(node);
            return std::make_pair(value->x, value->y);
        })
        ->setWriter([](cocos2d::Node* node, float x, float y) {
            return WidgetLoader::Property::PositionPercent.write(
                node, cocos2d::Vec2(x, y));
        })
        ->setPropertyDisplayName("Position percent")
        ->setSubPropertyDisplayName("X", "Y")
        ->setSingleStep(0.5f)
        ->setValuePrecision(3)
        ->setMinimumValue(0.000f)
        ->setMaximumValue(999.999f);
}

auto createSizePercentInspector() {
    return (+new InspectorFloatXY())
        ->setReader([](const cocos2d::Node* node) {
            auto value = WidgetLoader::Property::SizePercent.read(node);
            return std::make_pair(value->x, value->y);
        })
        ->setWriter([](cocos2d::Node* node, float x, float y) {
            return WidgetLoader::Property::SizePercent.write(
                node, cocos2d::Vec2(x, y));
        })
        ->setPropertyDisplayName("Size percent")
        ->setSubPropertyDisplayName("W", "H")
        ->setSingleStep(0.5f)
        ->setValuePrecision(3)
        ->setMinimumValue(0.000f)
        ->setMaximumValue(999.999f);
}
} // namespace

Self::WidgetInspector(QWidget* parent)
    : Super(parent) {
    setDisplayName("Widget");
    addInspector(createEnabledInspector());
    addInspector(createBrightInspector());
    addInspector(createHighlightedInspector());
    addInspector(createIgnoreContentAdaptWithSizeInspector());
    addInspector(createUnifySizeEnabledInspector());
    addInspector(createTouchEnabledInspector());
    addInspector(createSwallowTouchesInspector());
    addInspector(createPropagateTouchEventsInspector());
    addInspector(createFlippedXInspector());
    addInspector(createFlippedYInspector());
    addInspector(createPositionPercentInspector());
    addInspector(createSizePercentInspector());
}
} // namespace ee
