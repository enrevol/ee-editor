#include "layoutloader.hpp"
#include "propertywriter.hpp"

#include <ui/UILayout.h>

namespace ee {
using Self = LayoutLoader;

// clang-format off
const std::string Self::Property::BackgroundColorR = "background_color_r";
const std::string Self::Property::BackgroundColorG = "background_color_g";
const std::string Self::Property::BackgroundColorB = "background_color_b";
const std::string Self::Property::BackgroundColorOpacity = "background_color_opacity";
const std::string Self::Property::BackgroundColorType = "background_color_type";
const std::string Self::Property::BackgroundColorVectorX = "background_color_vector_x";
const std::string Self::Property::BackgroundColorVectorY = "background_color_vector_y";
const std::string Self::Property::BackgroundEndColorR = "background_end_color_r";
const std::string Self::Property::BackgroundEndColorG = "background_end_color_g";
const std::string Self::Property::BackgroundEndColorB = "background_end_color_b";
const std::string Self::Property::BackgroundImageCapInsetsX = "background_image_cap_insets_x";
const std::string Self::Property::BackgroundImageCapInsetsY = "background_image_cap_insets_y";
const std::string Self::Property::BackgroundImageCapInsetsW = "background_image_cap_insets_width";
const std::string Self::Property::BackgroundImageCapInsetsH = "background_image_cap_insets_height";
const std::string Self::Property::BackgroundImageColorR = "background_image_color_r";
const std::string Self::Property::BackgroundImageColorG = "background_image_color_g";
const std::string Self::Property::BackgroundImageColorB = "background_image_color_b";
const std::string Self::Property::BackgroundImageOpacity = "background_image_opacity";
const std::string Self::Property::BackgroundImageName = "background_image_name";
const std::string Self::Property::BackgroundImageTexType = "background_image_tex_type";
const std::string Self::Property::BackgroundImageScale9Enabled = "background_image_scale_9_enabled";
const std::string Self::Property::BackgroundStartColorR = "background_start_color_r";
const std::string Self::Property::BackgroundStartColorG = "background_start_color_g";
const std::string Self::Property::BackgroundStartColorB = "background_start_color_b";
const std::string Self::Property::ClippingEnabled = "clipping_enabled";
const std::string Self::Property::ClippingType = "clipping_type";
const std::string Self::Property::LayoutType = "layout_type";
// clang-format on

const std::string Self::ClassName = "_Layout";

NodeLoaderPtr Self::create() {
    auto result = std::unique_ptr<Self>(new Self());
    result->initialize();
    return std::move(result);
}

Self::LayoutLoader() {}

Self::~LayoutLoader() {}

void Self::addReadHandlers(PropertyHandler& handler) {
    Super::addReadHandlers(handler);
    // FIXME.
}

void Self::addDefaultProperties(PropertyWriter& writer) {
    Super::addDefaultProperties(writer);

    writer.setProperty(NodeLoader::Property::AnchorPointX, 0.5f);
    writer.setProperty(NodeLoader::Property::AnchorPointY, 0.5f);

    bool flag = true;
    /*
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
    */
    Q_ASSERT(flag);
}

cocos2d::Node* Self::createNode() const {
    return cocos2d::ui::Layout::create();
}

std::string Self::getClassName() const {
    return ClassName;
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
