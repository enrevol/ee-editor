#include "scale9spriteloader.hpp"

#include <ui/UIScale9Sprite.h>

namespace ee {
using Self = Scale9SpriteLoader;
using Target = cocos2d::ui::Scale9Sprite;
using Helper = PropertyHelper<Target>;

const PropertyEnum<Target::State> Self::Property::State(
    "state", //
    Helper::makeReader<Target::State>(std::mem_fn(&Target::getState)),
    Helper::makeWriter<Target::State>(std::mem_fn(&Target::setState)));

const PropertyEnum<Target::RenderingType>
    Self::Property::RenderingType("rendering_type",
                                  Helper::makeReader<Target::RenderingType>(
                                      std::mem_fn(&Target::getRenderingType)),
                                  Helper::makeWriter<Target::RenderingType>(
                                      std::mem_fn(&Target::setRenderingType)));

const std::string Self::Name = "_Scale9Sprite";

Self::Scale9SpriteLoader() {
    addProperty(Property::State);
    addProperty(Property::RenderingType);
}

Self::~Scale9SpriteLoader() {}

std::string Self::getName() const {
    return Name;
}

cocos2d::Node* Self::createNode() const {
    return Target::create();
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
