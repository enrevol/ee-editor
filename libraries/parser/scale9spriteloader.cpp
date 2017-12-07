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

const std::string Self::ClassName = "_Scale9Sprite";

Self::Scale9SpriteLoader() {}

Self::~Scale9SpriteLoader() {}

/*
    bool flag = true;
    flag &= writer.addProperty(
        Property::State,
        static_cast<int>(cocos2d::ui::Scale9Sprite::State::NORMAL));
    Q_ASSERT(flag);
    */

cocos2d::Node* Self::createNode() const {
    return Target::create();
}

void Self::loadProperties(cocos2d::Node* node_,
                          const PropertyHandler& handler) const {
    auto node = dynamic_cast<Target*>(node_);
    Super::loadProperties(node, handler);

    handler.loadProperty(Property::State, node);
    handler.loadProperty(Property::RenderingType, node);
}

void Self::storeProperties(const cocos2d::Node* node_,
                           PropertyHandler& handler) const {
    auto node = dynamic_cast<const Target*>(node_);
    Super::storeProperties(node, handler);

    handler.storeProperty(Property::State, node);
    handler.storeProperty(Property::RenderingType, node);
}

std::string Self::getClassName() const {
    return ClassName;
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
