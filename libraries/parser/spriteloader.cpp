#include "spriteloader.hpp"
#include "nodeinforeader.hpp"
#include "nodeinfowriter.hpp"

#include <2d/CCSprite.h>

namespace ee {
using Self = SpriteLoader;

const std::string Self::Property::BlendFuncDst = "blend_func_dst";
const std::string Self::Property::BlendFuncSrc = "blend_func_src";
const std::string Self::Property::FlippedX = "flipped_x";
const std::string Self::Property::FlippedY = "flipped_y";
const std::string Self::Property::SpriteFrame = "sprite_frame";
const std::string Self::Property::StretchEnabled = "stretch_enabled";
const std::string Self::Property::Texture = "texture";

NodeLoaderPtr Self::create() {
    auto result = std::unique_ptr<Self>(new Self());
    result->initialize();
    return std::move(result);
}

Self::SpriteLoader() {}

Self::~SpriteLoader() {}

void Self::addReadHandlers(PropertyHandler& handler) {
    Super::addReadHandlers(handler);

    handler.addReadIntHandler(
        Property::BlendFuncDst, [](const cocos2d::Node* node) {
            auto sprite = dynamic_cast<const cocos2d::Sprite*>(node);
            if (sprite == nullptr) {
                CC_ASSERT(false);
                return 0;
            }
            return static_cast<int>(sprite->getBlendFunc().dst);
        });

    handler.addReadIntHandler(
        Property::BlendFuncSrc, [](const cocos2d::Node* node) {
            auto sprite = dynamic_cast<const cocos2d::Sprite*>(node);
            if (sprite == nullptr) {
                CC_ASSERT(false);
                return 0;
            }
            return static_cast<int>(sprite->getBlendFunc().src);
        });

    handler.addReadBoolHandler(
        Property::FlippedX, [](const cocos2d::Node* node) {
            auto sprite = dynamic_cast<const cocos2d::Sprite*>(node);
            if (sprite == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            return sprite->isFlippedX();
        });

    handler.addReadBoolHandler(
        Property::FlippedY, [](const cocos2d::Node* node) {
            auto sprite = dynamic_cast<const cocos2d::Sprite*>(node);
            if (sprite == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            return sprite->isFlippedY();
        });

    handler.addReadBoolHandler(
        Property::StretchEnabled, [](const cocos2d::Node* node) {
            auto sprite = dynamic_cast<const cocos2d::Sprite*>(node);
            if (sprite == nullptr) {
                CC_ASSERT(false);
                return false;
            }
            return sprite->isStretchEnabled();
        });

    handler.addReadStringHandler(
        Property::Texture, [](const cocos2d::Node* node) {
            return NodeInfoReader(node).readString(Property::Texture, "");
        });
}

void Self::addWriteHandlers(PropertyHandler& handler) {
    Super::addWriteHandlers(handler);

    handler.addWriteIntHandler(
        Property::BlendFuncDst, [](cocos2d::Node* node, int value) {
            auto sprite = dynamic_cast<cocos2d::Sprite*>(node);
            if (sprite == nullptr) {
                return false;
            }
            auto blendFunc = sprite->getBlendFunc();
            blendFunc.dst = static_cast<GLenum>(value);
            sprite->setBlendFunc(blendFunc);
            return true;
        });

    handler.addWriteIntHandler(
        Property::BlendFuncSrc, [](cocos2d::Node* node, int value) {
            auto sprite = dynamic_cast<cocos2d::Sprite*>(node);
            if (sprite == nullptr) {
                return false;
            }
            auto blendFunc = sprite->getBlendFunc();
            blendFunc.src = static_cast<GLenum>(value);
            sprite->setBlendFunc(blendFunc);
            return true;
        });

    handler.addWriteBoolHandler(
        Property::FlippedX, [](cocos2d::Node* node, bool value) {
            auto sprite = dynamic_cast<cocos2d::Sprite*>(node);
            if (sprite == nullptr) {
                return false;
            }
            sprite->setFlippedX(value);
            return true;
        });

    handler.addWriteBoolHandler(
        Property::FlippedY, [](cocos2d::Node* node, bool value) {
            auto sprite = dynamic_cast<cocos2d::Sprite*>(node);
            if (sprite == nullptr) {
                return false;
            }
            sprite->setFlippedY(value);
            return true;
        });

    handler.addWriteBoolHandler(
        Property::StretchEnabled, [](cocos2d::Node* node, bool value) {
            auto sprite = dynamic_cast<cocos2d::Sprite*>(node);
            if (sprite == nullptr) {
                return false;
            }
            sprite->setStretchEnabled(value);
            return true;
        });

    handler.addWriteStringHandler(
        Property::Texture, [](cocos2d::Node* node_, const std::string& value) {
            auto node = dynamic_cast<cocos2d::Sprite*>(node_);
            if (node == nullptr) {
                return false;
            }
            node->setTexture(value);
            NodeInfoWriter(node).writeString(Property::Texture, value);
            return true;
        });
}

void Self::addDefaultProperties(PropertyWriter& writer) {
    Super::addDefaultProperties(writer);
}

cocos2d::Node* Self::createNode() const {
    return cocos2d::Sprite::create();
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
