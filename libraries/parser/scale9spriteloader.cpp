#include "scale9spriteloader.hpp"

#include <ui/UIScale9Sprite.h>

namespace ee {
using Self = Scale9SpriteLoader;

const PropertyEnum<Self::Target, cocos2d::ui::Scale9Sprite::State>
    Self::Property::State("state", std::mem_fn(&Target::getState),
                          std::mem_fn(&Target::setState));

const PropertyEnum<Self::Target, cocos2d::ui::Scale9Sprite::RenderingType>
    Self::Property::RenderingType("rendering_type",
                                  std::mem_fn(&Target::getRenderingType),
                                  std::mem_fn(&Target::setRenderingType));

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

std::string Self::getClassName() const {
    return ClassName;
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
