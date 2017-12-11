#include "skeletonanimationinspector.hpp"
#include "inspectorblend.hpp"
#include "inspectorbool.hpp"
#include "inspectorfloat.hpp"
#include "inspectorfloatxy.hpp"
#include "inspectorstring.hpp"

#include <parser/skeletonanimationloader.hpp>

namespace ee {
using Self = SkeletonAnimationInspector;

namespace {
using Property = SkeletonAnimationLoader::Property;

auto createDataFileInspector() {
    return (new InspectorString())
        ->setReader(Property::DataFile.getReader())
        ->setWriter(Property::DataFile.getWriter())
        ->setPropertyDisplayName("Data file");
}

auto createAtlasFileInspector() {
    return (new InspectorString())
        ->setReader(Property::AtlasFile.getReader())
        ->setWriter(Property::AtlasFile.getWriter())
        ->setPropertyDisplayName("Atlas file");
}

auto createAnimationScaleInspector() {
    return (new InspectorFloat())
        ->setReader(Property::AnimationScale.getReader())
        ->setWriter(Property::AnimationScale.getWriter())
        ->setPropertyDisplayName("Scale")
        ->setSingleStep(0.05f)
        ->setValuePrecision(3)
        ->setMinimumValue(-9.99f)
        ->setMaximumValue(+9.99f);
}

auto createAnimationInspector() {
    return (new InspectorString())
        ->setReader(Property::Animation.getReader())
        ->setWriter(Property::Animation.getWriter())
        ->setPropertyDisplayName("Animation");
}

auto createSkinInspector() {
    return (new InspectorString())
        ->setReader(Property::Skin.getReader())
        ->setWriter(Property::Skin.getWriter())
        ->setPropertyDisplayName("Skin");
}

auto createLoopInspector() {
    return (new InspectorBool())
        ->setReader(Property::Loop.getReader())
        ->setWriter(Property::Loop.getWriter())
        ->setPropertyDisplayName("Loop");
}

auto createTimeScaleInspector() {
    return (new InspectorFloat())
        ->setReader(Property::TimeScale.getReader())
        ->setWriter(Property::TimeScale.getWriter())
        ->setPropertyDisplayName("Time scale")
        ->setSingleStep(0.05f)
        ->setValuePrecision(3)
        ->setMinimumValue(0.0f)
        ->setMaximumValue(9.99f);
}

auto createBlendFuncInspector() {
    return (new InspectorBlend())
        ->setReader(Property::BlendFunc.getReader())
        ->setWriter(Property::BlendFunc.getWriter());
}

auto createDebugBonesInspector() {
    return (new InspectorBool())
        ->setReader(Property::DebugBones.getReader())
        ->setWriter(Property::DebugBones.getWriter())
        ->setPropertyDisplayName("Debug bones");
}

auto createDebugSlotsInspector() {
    return (new InspectorBool())
        ->setReader(Property::DebugSlots.getReader())
        ->setWriter(Property::DebugSlots.getWriter())
        ->setPropertyDisplayName("Debug slots");
}
} // namespace

Self::SkeletonAnimationInspector(QWidget* parent)
    : Super(parent) {
    setDisplayName("Skeleton Animation");
    addInspector(createDataFileInspector());
    addInspector(createAtlasFileInspector());
    addInspector(createAnimationScaleInspector());
    addInspector(createAnimationInspector());
    addInspector(createSkinInspector());
    addInspector(createLoopInspector());
    addInspector(createTimeScaleInspector());
    addInspector(createBlendFuncInspector());
    addInspector(createDebugBonesInspector());
    addInspector(createDebugSlotsInspector());
}
} // namespace ee
