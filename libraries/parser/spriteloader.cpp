#include "spriteloader.hpp"
#include "nodeinfo.hpp"

#include <2d/CCSprite.h>

namespace ee {
using Self = SpriteLoader;

const PropertyBlend<Self::Target>
    Self::Property::BlendFunc("blend_func", std::mem_fn(&Target::getBlendFunc),
                              std::mem_fn(&Target::setBlendFunc));

const PropertyBool<Self::Target>
    Self::Property::FlippedX("flipped_x", std::mem_fn(&Target::isFlippedX),
                             std::mem_fn(&Target::setFlippedX));

const PropertyBool<Self::Target>
    Self::Property::FlippedY("flipped_y", std::mem_fn(&Target::isFlippedY),
                             std::mem_fn(&Target::setFlippedY));

const PropertyBool<Self::Target>
    Self::Property::StretchEnabled("stretch_enabled",
                                   std::mem_fn(&Target::isStretchEnabled),
                                   std::mem_fn(&Target::setStretchEnabled));

const PropertyString<Self::Target> Self::Property::Texture(
    "texture",
    [](const Target* node) {
        auto&& handler = NodeInfo::getPropertyHandler(node);
        return handler.getProperty("texture").getString();
    },
    [](Target* node, const std::string& value) {
        auto&& handler = NodeInfo::getPropertyHandler(node);
        handler.setProperty("texture", Value(value));

        // Preserve content size and blend func.
        auto&& contentSize = node->getContentSize();
        auto&& blendFunc = node->getBlendFunc();
        node->setTexture(value);
        node->setContentSize(contentSize);
        node->setBlendFunc(blendFunc);
    });

const PropertyString<Self::Target> Self::Property::SpriteFrame(
    "sprite_frame",
    [](const Target* node) {
        auto&& handler = NodeInfo::getPropertyHandler(node);
        return handler.getProperty("sprite_frame").getString();
    },
    [](Target* node, const std::string& value) {
        auto&& handler = NodeInfo::getPropertyHandler(node);
        handler.setProperty("sprite_frame", Value(value));

        // Preserve blend func.
        auto&& blendFunc = node->getBlendFunc();
        node->setSpriteFrame(value);
        node->setBlendFunc(blendFunc);
    });

const std::string Self::ClassName = "_Sprite";

Self::SpriteLoader() {}

Self::~SpriteLoader() {}

/*
writer.setProperty(NodeLoader::Property::AnchorPoint,
                   cocos2d::Vec2::ANCHOR_MIDDLE);

bool flag = true;
flag &= writer.addProperty(Property::BlendFunc,
                           cocos2d::BlendFunc::ALPHA_PREMULTIPLIED);
flag &= writer.addProperty(Property::FlippedX, false);
flag &= writer.addProperty(Property::FlippedY, false);
flag &= writer.addProperty(Property::StretchEnabled, true);
flag &= writer.addProperty(Property::Texture, std::string());
Q_ASSERT(flag);
*/

cocos2d::Node* Self::createNode() const {
    return Target::create();
}

void Self::loadProperties(cocos2d::Node* node_,
                          const PropertyHandler& handler) const {
    auto node = dynamic_cast<Target*>(node_);
    Super::loadProperties(node, handler);
    handler.loadProperty(Property::BlendFunc, node);
    handler.loadProperty(Property::FlippedX, node);
    handler.loadProperty(Property::FlippedY, node);
    handler.loadProperty(Property::StretchEnabled, node);
    handler.loadProperty(Property::Texture, node);
    handler.loadProperty(Property::SpriteFrame, node);
}

std::string Self::getClassName() const {
    return ClassName;
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
