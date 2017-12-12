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
using Target = spine::SkeletonAnimation;

namespace {
using Property = SkeletonAnimationLoader::Property;

auto getSkeletonData(const Target* node) {
    auto skeleton = static_cast<const spSkeleton*>(
        const_cast<Target*>(node)->getSkeleton());
    return skeleton->data;
}

std::vector<std::string> readAnimations(const Target* node) {
    std::vector<std::string> animations;
    auto skeletonData = getSkeletonData(node);
    for (int i = 0; i < skeletonData->animationsCount; ++i) {
        animations.emplace_back(skeletonData->animations[i]->name);
    }
    return animations;
}

std::vector<std::string> readSkins(const Target* node) {
    std::vector<std::string> skins;
    auto skeletonData = getSkeletonData(node);
    for (int i = 0; i < skeletonData->skinsCount; ++i) {
        skins.emplace_back(skeletonData->skins[i]->name);
    }
    return skins;
}

int findIndex(const std::vector<std::string>& values,
              const std::string& value) {
    auto iter = std::find(values.cbegin(), values.cend(), value);
    if (iter == values.cend()) {
        return -1;
    }
    return static_cast<int>(iter - values.cbegin());
}

auto createDataFileInspector(InspectorSelect* animationInspector,
                             InspectorSelect* skinInspector) {
    return (new InspectorString())
        ->setReader([animationInspector,
                     skinInspector](const cocos2d::Node* node_) {
            auto value = Property::DataFile.read(node_);
            if (value) {
                auto node =
                    dynamic_cast<const spine::SkeletonAnimation*>(node_);
                auto animations = readAnimations(node);
                animationInspector->clearSelections();
                for (auto&& name : animations) {
                    animationInspector->addSelection(
                        QString::fromStdString(name));
                }

                auto skins = readSkins(node);
                skinInspector->clearSelections();
                for (auto&& name : skins) {
                    skinInspector->addSelection(QString::fromStdString(name));
                }
            }
            return value;
        })
        ->setWriter([animationInspector, skinInspector](
                        cocos2d::Node* node_, const std::string& value) {
            if (not Property::DataFile.write(node_, value)) {
                return false;
            }
            auto node = dynamic_cast<spine::SkeletonAnimation*>(node_);
            animationInspector->clearSelections();
            auto animations = readAnimations(node);
            for (auto&& name : animations) {
                animationInspector->addSelection(QString::fromStdString(name));
            }
            auto animation = Property::Animation.read(node).value();
            animationInspector->setPropertyValue(
                findIndex(animations, animation));

            skinInspector->clearSelections();
            auto skins = readSkins(node);
            for (auto&& name : skins) {
                skinInspector->addSelection(QString::fromStdString(name));
            }
            auto skin = Property::Skin.read(node).value();
            skinInspector->setPropertyValue(findIndex(skins, skin));
            return true;
        })
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
    return (new InspectorSelect())
        ->setReader([](const cocos2d::Node* node_) {
            auto value = Property::Animation.read(node_);
            if (not value) {
                return -1;
            }
            auto node = dynamic_cast<const Target*>(node_);
            auto animations = readAnimations(node);
            return findIndex(animations, value.value());
        })
        ->setWriter([](cocos2d::Node* node_, int value) {
            auto node = dynamic_cast<Target*>(node_);
            if (node == nullptr) {
                return false;
            }
            auto animations = readAnimations(node);
            auto index = static_cast<std::size_t>(value);
            if (index < animations.size()) {
                return Property::Animation.write(node, animations.at(index));
            }
            return false;
        })
        ->setPropertyDisplayName("Animation");
}

auto createSkinInspector() {
    return (new InspectorSelect())
        ->setReader([](const cocos2d::Node* node_) {
            auto value = Property::Skin.read(node_);
            if (not value) {
                return -1;
            }
            auto node = dynamic_cast<const Target*>(node_);
            auto skins = readSkins(node);
            return findIndex(skins, value.value());
        })
        ->setWriter([](cocos2d::Node* node_, int value) {
            auto node = dynamic_cast<Target*>(node_);
            if (node == nullptr) {
                return false;
            }
            auto skins = readSkins(node);
            auto index = static_cast<std::size_t>(value);
            if (index < skins.size()) {
                return Property::Skin.write(node, skins.at(index));
            }
            return false;
        })
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
    auto animationInspector = createAnimationInspector();
    auto skinInspector = createSkinInspector();
    auto dataFileInspector =
        createDataFileInspector(animationInspector, skinInspector);
    addInspector(dataFileInspector);
    addInspector(createAtlasFileInspector());
    addInspector(createAnimationScaleInspector());
    addInspector(animationInspector);
    addInspector(skinInspector);
    addInspector(createLoopInspector());
    addInspector(createTimeScaleInspector());
    addInspector(createBlendFuncInspector());
    addInspector(createDebugBonesInspector());
    addInspector(createDebugSlotsInspector());
}
} // namespace ee
