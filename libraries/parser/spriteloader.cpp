#include "spriteloader.hpp"
#include "nodeinforeader.hpp"
#include "nodeinfowriter.hpp"

#include <2d/CCSprite.h>

namespace ee {
namespace property {
constexpr auto texture = "texture";
} // namespace property

using Self = SpriteLoader;

Self::SpriteLoader() {
    auto&& handler = getPropertyHandler();
    handler.addWriteStringHandler(
        property::texture,
        [this](cocos2d::Node* node_, const std::string& value) {
            auto node = dynamic_cast<cocos2d::Sprite*>(node_);
            if (node == nullptr) {
                return false;
            }
            node->setTexture(value);
            NodeInfoWriter(node).writeString(property::texture, value);
            return true;
        });

    handler.addReadStringHandler(
        property::texture, [this](const cocos2d::Node* node) {
            return NodeInfoReader(node).readString(property::texture, "");
        });
}

Self::~SpriteLoader() {}

cocos2d::Node* Self::createNode() const {
    return cocos2d::Sprite::create();
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
