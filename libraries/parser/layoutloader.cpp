#include "layoutloader.hpp"

#include <ui/UILayout.h>

namespace ee {
using Self = LayoutLoader;
using Target = cocos2d::ui::Layout;
using Helper = PropertyHelper<Target>;

const PropertyColor3B Self::Property::BackgroundColor(
    "background_color",
    Helper::makeReader<cocos2d::Color3B>(
        std::mem_fn(&Target::getBackGroundColor)),
    Helper::makeWriter<cocos2d::Color3B>([](Target* node,
                                            const cocos2d::Color3B& value) {
        node->setBackGroundColor(value);
    }));

const PropertyInt Self::Property::BackgroundColorOpacity(
    "background_color_opacity",
    Helper::makeReader<int>(std::mem_fn(&Target::getBackGroundColorOpacity)),
    Helper::makeWriter<int>(std::mem_fn(&Target::setBackGroundColorOpacity)));

const PropertyEnum<Target::BackGroundColorType>
    Self::Property::BackgroundColorType(
        "background_color_type",
        Helper::makeReader<Target::BackGroundColorType>(
            std::mem_fn(&Target::getBackGroundColorType)),
        Helper::makeWriter<Target::BackGroundColorType>(
            std::mem_fn(&Target::setBackGroundColorType)));

const PropertyPoint Self::Property::BackgroundColorVector(
    "background_color_vector",
    Helper::makeReader<cocos2d::Point>(
        std::mem_fn(&Target::getBackGroundColorVector)),
    Helper::makeWriter<cocos2d::Point>(
        std::mem_fn(&Target::setBackGroundColorVector)));

// const PropertyColor3B<Target> BackgroundEndColor("background_end_color",
// std::mem_fn(&Target::getBackGroundEndColor),
// std::mem_fn(&Target::SetBackgroundE)); const PropertyColor3B<Target>
// BackgroundStartColor("background_start_color");

const PropertyRect Self::Property::BackgroundImageCapInsets(
    "background_image_cap_insets",
    Helper::makeReader<cocos2d::Rect>(
        std::mem_fn(&Target::getBackGroundImageCapInsets)),
    Helper::makeWriter<cocos2d::Rect>(
        std::mem_fn(&Target::setBackGroundImageCapInsets)));

const PropertyColor3B Self::Property::BackgroundImageColor(
    "background_image_color",
    Helper::makeReader<cocos2d::Color3B>(
        std::mem_fn(&Target::getBackGroundImageColor)),
    Helper::makeWriter<cocos2d::Color3B>(
        std::mem_fn(&Target::setBackGroundImageColor)));

const PropertyInt Self::Property::BackgroundImageOpacity(
    "background_image_opacity",
    Helper::makeReader<int>(std::mem_fn(&Target::getBackGroundImageOpacity)),
    Helper::makeWriter<int>(std::mem_fn(&Target::setBackGroundImageOpacity)));

// const PropertyString<Target> BackgroundImageName("background_image_name",
// std::mem_fn(&Target::getBackgroundIma));

// const PropertyInt<Target>
// BackgroundImageTexType("background_image_tex_type");

// const PropertyBool<Target>
// BackgroundImageScale9Enabled("background_image_scale_9_enabled");

const PropertyBool Self::Property::ClippingEnabled(
    "clipping_enabled",
    Helper::makeReader<bool>(std::mem_fn(&Target::isClippingEnabled)),
    Helper::makeWriter<bool>(std::mem_fn(&Target::setClippingEnabled)));

const PropertyEnum<Target::ClippingType>
    Self::Property::ClippingType("clipping_type",
                                 Helper::makeReader<Target::ClippingType>(
                                     std::mem_fn(&Target::getClippingType)),
                                 Helper::makeWriter<Target::ClippingType>(
                                     std::mem_fn(&Target::setClippingType)));

const PropertyEnum<Target::Type> Self::Property::LayoutType(
    "layout_type",
    Helper::makeReader<Target::Type>(std::mem_fn(&Target::getLayoutType)),
    Helper::makeWriter<Target::Type>(std::mem_fn(&Target::setLayoutType)));

const std::string Self::Name = "_Layout";

Self::LayoutLoader() {
    addProperty(Property::BackgroundColor);
    addProperty(Property::BackgroundColorOpacity);
    addProperty(Property::BackgroundColorType);
    addProperty(Property::BackgroundColorVector);
    addProperty(Property::BackgroundImageCapInsets);
    addProperty(Property::BackgroundImageColor);
    addProperty(Property::BackgroundImageOpacity);
    addProperty(Property::ClippingEnabled);
    addProperty(Property::ClippingType);
    addProperty(Property::LayoutType);
}

Self::~LayoutLoader() {}

std::string Self::getName() const {
    return Name;
}

cocos2d::Node* Self::createNode() const {
    return cocos2d::ui::Layout::create();
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
