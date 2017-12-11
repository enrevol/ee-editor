#include "skeletonanimationloader.hpp"
#include "nodeinfo.hpp"
#include "skeletonanimationmanager.hpp"

#include <spine/SkeletonAnimation.h>

namespace ee {
using Self = SkeletonAnimationLoader;
using Target = spine::SkeletonAnimation;
using Helper = PropertyHelper<Target>;

namespace key {
constexpr auto initialized = "initialized";
constexpr auto data_file = "data_file";
constexpr auto atlas_file = "atlas_file";
constexpr auto animation_scale = "animation_scale";
constexpr auto animation = "animation";
constexpr auto skin = "skin";
constexpr auto loop = "loop";
constexpr auto time_scale = "time_scale";
constexpr auto blend_func = "blend_func";
constexpr auto debug_bones = "debug_bones";
constexpr auto debug_slots = "debug_slots";
} // namespace key

namespace defaults {
constexpr auto initialized = false;
constexpr auto animation_scale = 1.0f;
constexpr auto animation = "";
constexpr auto skin = "";
constexpr auto loop = false;
} // namespace defaults

const PropertyString Self::Property::DataFile(
    key::data_file, Helper::makeReader<std::string>([](const Target* node) {
        auto&& handler = NodeInfo::getPropertyHandler(node);
        return handler.getProperty<std::string>(key::data_file);
    }),
    Helper::makeWriter<std::string>([](Target* node, const std::string& value) {
        auto&& handler = NodeInfo::getPropertyHandler(node);
        handler.setProperty(key::data_file, value);
        auto animationScale = AnimationScale.read(node);
        auto atlasFile = AtlasFile.read(node);
        if (animationScale && atlasFile) {
            auto initialized = handler.getProperty<bool>(key::initialized)
                                   .value_or(defaults::initialized);
            if (initialized) {
                spSkeleton_dispose(node->getSkeleton());
            }
            auto data = SkeletonAnimationManager::getInstance().getSkeletonData(
                value, atlasFile.value(), animationScale.value());
            node->initWithData(data);
            handler.setProperty(key::initialized, true);
        }
    }));

const PropertyString Self::Property::AtlasFile(
    key::atlas_file, Helper::makeReader<std::string>([](const Target* node) {
        auto&& handler = NodeInfo::getPropertyHandler(node);
        return handler.getProperty<std::string>(key::atlas_file);
    }),
    Helper::makeWriter<std::string>([](Target* node, const std::string& value) {
        auto&& handler = NodeInfo::getPropertyHandler(node);
        handler.setProperty(key::atlas_file, value);
        auto animationScale = AnimationScale.read(node);
        auto dataFile = DataFile.read(node);
        if (animationScale && dataFile) {
            auto initialized = handler.getProperty<bool>(key::initialized)
                                   .value_or(defaults::initialized);
            if (initialized) {
                spSkeleton_dispose(node->getSkeleton());
            }
            auto data = SkeletonAnimationManager::getInstance().getSkeletonData(
                dataFile.value(), value, animationScale.value());
            node->initWithData(data);
            handler.setProperty(key::initialized, true);
        }
    }));

const PropertyFloat Self::Property::AnimationScale(
    key::animation_scale, Helper::makeReader<float>([](const Target* node) {
        auto&& handler = NodeInfo::getPropertyHandler(node);
        return handler.getProperty<float>(key::animation_scale)
            .value_or(defaults::animation_scale);
    }),
    Helper::makeWriter<float>([](Target* node, float value) {
        auto&& handler = NodeInfo::getPropertyHandler(node);
        handler.setProperty(key::animation_scale, value);
        auto atlasFile = AtlasFile.read(node);
        auto dataFile = DataFile.read(node);
        if (atlasFile && dataFile) {
            auto initialized = handler.getProperty<bool>(key::initialized)
                                   .value_or(defaults::initialized);
            if (initialized) {
                spSkeleton_dispose(node->getSkeleton());
            }
            auto data = SkeletonAnimationManager::getInstance().getSkeletonData(
                dataFile.value(), atlasFile.value(), value);
            node->initWithData(data);
            handler.setProperty(key::initialized, true);
        }
    }));

const PropertyString Self::Property::Animation(
    key::animation, Helper::makeReader<std::string>([](const Target* node) {
        auto&& handler = NodeInfo::getPropertyHandler(node);
        return handler.getProperty<std::string>(key::animation)
            .value_or(defaults::animation);
    }),
    Helper::makeWriter<std::string>([](Target* node, const std::string& value) {
        auto&& handler = NodeInfo::getPropertyHandler(node);
        handler.setProperty(key::animation, value);
        auto loop = Loop.read(node).value();
        auto entry = node->setAnimation(0, value, loop);
    }));

const PropertyString Self::Property::Skin(
    key::skin, Helper::makeReader<std::string>([](const Target* node) {
        auto&& handler = NodeInfo::getPropertyHandler(node);
        return handler.getProperty<std::string>(key::skin).value_or(
            defaults::skin);
    }),
    Helper::makeWriter<std::string>([](Target* node, const std::string& value) {
        auto&& handler = NodeInfo::getPropertyHandler(node);
        handler.setProperty(key::skin, value);
        node->setSkin(value);
    }));

const PropertyBool Self::Property::Loop(
    key::loop, Helper::makeReader<bool>([](const Target* node) {
        auto&& handler = NodeInfo::getPropertyHandler(node);
        return handler.getProperty<bool>(key::loop).value_or(defaults::loop);
    }),
    Helper::makeWriter<bool>([](Target* node, bool value) {
        auto&& handler = NodeInfo::getPropertyHandler(node);
        handler.setProperty(key::loop, value);
        auto animation = Animation.read(node).value();
        auto entry = node->setAnimation(0, animation, value);
    }));

const PropertyFloat Self::Property::TimeScale(
    key::time_scale, //
    Helper::makeReader<float>(std::mem_fn(&Target::getTimeScale)),
    Helper::makeWriter<float>(std::mem_fn(&Target::setTimeScale)));

const PropertyBlend Self::Property::BlendFunc(
    key::blend_func,
    Helper::makeReader<cocos2d::BlendFunc>(std::mem_fn(&Target::getBlendFunc)),
    Helper::makeWriter<cocos2d::BlendFunc>(std::mem_fn(&Target::setBlendFunc)));

const PropertyBool Self::Property::DebugBones(
    key::debug_bones,
    Helper::makeReader<bool>(std::mem_fn(&Target::getDebugBonesEnabled)),
    Helper::makeWriter<bool>(std::mem_fn(&Target::setDebugBonesEnabled)));

const PropertyBool Self::Property::DebugSlots(
    key::debug_slots,
    Helper::makeReader<bool>(std::mem_fn(&Target::getDebugSlotsEnabled)),
    Helper::makeWriter<bool>(std::mem_fn(&Target::setDebugSlotsEnabled)));

const std::string Self::ClassName = "_SkeletonAnimation";

Self::SkeletonAnimationLoader() {
    addProperty(Property::DataFile);
    addProperty(Property::AtlasFile);
    addProperty(Property::AnimationScale);
    addProperty(Property::Animation);
    addProperty(Property::Skin);
    addProperty(Property::Loop);
    addProperty(Property::TimeScale);
    addProperty(Property::BlendFunc);
    addProperty(Property::DebugBones);
    addProperty(Property::DebugSlots);
}

Self::~SkeletonAnimationLoader() {}

std::string Self::getClassName() const {
    return ClassName;
}

cocos2d::Node* Self::createNode() const {
    return Target::create();
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
