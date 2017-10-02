#include "layoutloader.hpp"
#include "propertywriter.hpp"

#include <ui/UILayout.h>

namespace ee {
using Self = LayoutLoader;

const PropertyColor BackgroundColor("background_color");
const PropertyInt BackgroundColorOpacity("background_color_opacity");
const PropertyInt BackgroundColorType("background_color_type");
const PropertyPoint BackgroundColorVector("background_color_vector");
const PropertyColor BackgroundEndColor("background_end_color");
const PropertyRect BackgroundImageCapInsets("background_image_cap_insets");
const PropertyColor BackgroundImageColor("background_image_color");
const PropertyInt BackgroundImageOpacity("background_image_opacity");
const PropertyString BackgroundImageName("background_image_name");
const PropertyInt BackgroundImageTexType("background_image_tex_type");
const PropertyBool
    BackgroundImageScale9Enabled("background_image_scale_9_enabled");
const PropertyColor BackgroundStartColor("background_start_color");
const PropertyBool ClippingEnabled("clipping_enabled");
const PropertyInt ClippingType("clipping_type");
const PropertyInt LayoutType("layout_type");

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

    writer.setProperty(NodeLoader::Property::AnchorPoint,
                       cocos2d::Vec2::ANCHOR_MIDDLE);

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
