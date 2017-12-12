#include "skeletonanimationinspector.hpp"
#include "inspectorblend.hpp"
#include "inspectorbool.hpp"
#include "inspectorfloat.hpp"
#include "inspectorfloatxy.hpp"
#include "inspectorselect.hpp"
#include "inspectorstring.hpp"

#include <parser/skeletonanimationloader.hpp>

#undef slots
#include <spine/SkeletonAnimation.h>

namespace ee {
using Self = SkeletonAnimationInspector;

namespace {
using Property = SkeletonAnimationLoader::Property;

std::vector<std::string> readAnimations(const spine::SkeletonAnimation* node) {
    std::vector<std::string> animations;
    auto skeleton = static_cast<const spSkeleton*>(
        const_cast<spine::SkeletonAnimation*>(node)->getSkeleton());
    auto skeletonData = skeleton->data;
    for (int i = 0; i < skeletonData->animationsCount; ++i) {
        animations.emplace_back(skeletonData->animations[i]->name);
    }
    return animations;
}

auto createDataFileInspector() {
    QVector<Inspector*> inspectors;

    auto animation =
        (new InspectorSelect())
            ->setReader([](const cocos2d::Node* node_) {
                auto value = Property::Animation.read(node_);
                if (not value) {
                    return -1;
                }
                auto node =
                    dynamic_cast<const spine::SkeletonAnimation*>(node_);
                auto animations = readAnimations(node);
                auto iter = std::find(animations.cbegin(), animations.cend(),
                                      value.value());
                if (iter == animations.cend()) {
                    return -1;
                }
                return static_cast<int>(iter - animations.cbegin());
            })
            ->setWriter([](cocos2d::Node* node_, int value) {
                auto node = dynamic_cast<spine::SkeletonAnimation*>(node_);
                if (node == nullptr) {
                    return false;
                }
                auto animations = readAnimations(node);
                if (static_cast<std::size_t>(value) < animations.size()) {
                    return Property::Animation.write(
                        node, animations.at(static_cast<std::size_t>(value)));
                }
                return false;
            })
            ->setPropertyDisplayName("Animation");

    auto dataFile =
        (new InspectorString())
            ->setReader([animation](const cocos2d::Node* node_) {
                auto value = Property::DataFile.read(node_);
                if (value) {
                    auto node =
                        dynamic_cast<const spine::SkeletonAnimation*>(node_);
                    auto animations = readAnimations(node);
                    animation->clearSelections();
                    for (auto&& name : animations) {
                        animation->addSelection(QString::fromStdString(name));
                    }
                }
                return value;
            })
            ->setWriter(
                [animation](cocos2d::Node* node_, const std::string& value) {
                    if (not Property::DataFile.write(node_, value)) {
                        return false;
                    }
                    auto node = dynamic_cast<spine::SkeletonAnimation*>(node_);
                    animation->clearSelections();
                    auto animations = readAnimations(node);
                    for (auto&& name : animations) {
                        animation->addSelection(QString::fromStdString(name));
                    }
                    return true;
                })
            ->setPropertyDisplayName("Data file");

    inspectors.append(dataFile);
    inspectors.append(animation);
    return inspectors;
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
    auto inspectors = createDataFileInspector();
    addInspector(inspectors[0]);
    addInspector(createAtlasFileInspector());
    addInspector(createAnimationScaleInspector());
    addInspector(inspectors[1]);
    // addInspector(createAnimationInspector());
    addInspector(createSkinInspector());
    addInspector(createLoopInspector());
    addInspector(createTimeScaleInspector());
    addInspector(createBlendFuncInspector());
    addInspector(createDebugBonesInspector());
    addInspector(createDebugSlotsInspector());
}
} // namespace ee
