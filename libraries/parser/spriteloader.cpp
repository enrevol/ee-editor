#include "spriteloader.hpp"
#include "nodeinforeader.hpp"
#include "nodeinfowriter.hpp"

#include <2d/CCSprite.h>

namespace ee {
using Self = SpriteLoader;

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

    handler.addReadStringHandler(
        Property::Texture, [this](const cocos2d::Node* node) {
            return NodeInfoReader(node).readString(Property::Texture, "");
        });
}

void Self::addWriteHandlers(PropertyHandler& handler) {
    Super::addWriteHandlers(handler);

    handler.addWriteStringHandler(
        Property::Texture,
        [this](cocos2d::Node* node_, const std::string& value) {
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
