#include "layoutloader.hpp"

#include <ui/UILayout.h>

namespace ee {
using Self = LayoutLoader;

const PropertyColor3B<Self::Target> Self::Property::BackgroundColor(
    "background_color", std::mem_fn(&Target::getBackGroundColor),
    [](Target* node, const cocos2d::Color3B& value) {
        node->setBackGroundColor(value);
    });

const PropertyInt<Self::Target> Self::Property::BackgroundColorOpacity(
    "background_color_opacity", std::mem_fn(&Target::getBackGroundColorOpacity),
    std::mem_fn(&Target::setBackGroundColorOpacity));

const PropertyEnum<Self::Target, cocos2d::ui::Layout::BackGroundColorType>
    Self::Property::BackgroundColorType(
        "background_color_type", std::mem_fn(&Target::getBackGroundColorType),
        std::mem_fn(&Target::setBackGroundColorType));

const PropertyPoint<Self::Target> Self::Property::BackgroundColorVector(
    "background_color_vector", std::mem_fn(&Target::getBackGroundColorVector),
    std::mem_fn(&Target::setBackGroundColorVector));

// const PropertyColor3B<Target> BackgroundEndColor("background_end_color",
// std::mem_fn(&Target::getBackGroundEndColor),
// std::mem_fn(&Target::SetBackgroundE)); const PropertyColor3B<Target>
// BackgroundStartColor("background_start_color");

const PropertyRect<Self::Target> Self::Property::BackgroundImageCapInsets(
    "background_image_cap_insets",
    std::mem_fn(&Target::getBackGroundImageCapInsets),
    std::mem_fn(&Target::setBackGroundImageCapInsets));

const PropertyColor3B<Self::Target> Self::Property::BackgroundImageColor(
    "background_image_color", std::mem_fn(&Target::getBackGroundImageColor),
    std::mem_fn(&Target::setBackGroundImageColor));

const PropertyInt<Self::Target> Self::Property::BackgroundImageOpacity(
    "background_image_opacity", std::mem_fn(&Target::getBackGroundImageOpacity),
    std::mem_fn(&Target::setBackGroundImageOpacity));

// const PropertyString<Target> BackgroundImageName("background_image_name",
// std::mem_fn(&Target::getBackgroundIma));

// const PropertyInt<Target>
// BackgroundImageTexType("background_image_tex_type");

// const PropertyBool<Target>
// BackgroundImageScale9Enabled("background_image_scale_9_enabled");

const PropertyBool<Self::Target>
    Self::Property::ClippingEnabled("clipping_enabled",
                                    std::mem_fn(&Target::isClippingEnabled),
                                    std::mem_fn(&Target::setClippingEnabled));

const PropertyEnum<Self::Target, cocos2d::ui::Layout::ClippingType>
    Self::Property::ClippingType("clipping_type",
                                 std::mem_fn(&Target::getClippingType),
                                 std::mem_fn(&Target::setClippingType));

const PropertyEnum<Self::Target, cocos2d::ui::Layout::Type>
    Self::Property::LayoutType("layout_type",
                               std::mem_fn(&Target::getLayoutType),
                               std::mem_fn(&Target::setLayoutType));

const std::string Self::ClassName = "_Layout";

Self::LayoutLoader() {}

Self::~LayoutLoader() {}

cocos2d::Node* Self::createNode() const {
    return cocos2d::ui::Layout::create();
}

void Self::loadProperties(cocos2d::Node* node_,
                          const PropertyHandler& handler) const {
    auto node = dynamic_cast<Target*>(node_);
    Super::loadProperties(node, handler);

    handler.loadProperty(Property::BackgroundColor, node);
    handler.loadProperty(Property::BackgroundColorOpacity, node);
    handler.loadProperty(Property::BackgroundColorType, node);
    handler.loadProperty(Property::BackgroundColorVector, node);
    handler.loadProperty(Property::BackgroundImageCapInsets, node);
    handler.loadProperty(Property::BackgroundImageColor, node);
    handler.loadProperty(Property::BackgroundImageOpacity, node);
    handler.loadProperty(Property::ClippingEnabled, node);
    handler.loadProperty(Property::ClippingType, node);
    handler.loadProperty(Property::LayoutType, node);
}

std::string Self::getClassName() const {
    return ClassName;
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
