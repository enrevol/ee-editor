#include "spriteloader.hpp"
#include "nodeinforeader.hpp"
#include "nodeinfowriter.hpp"
#include "propertywriter.hpp"

#include <2d/CCSprite.h>

namespace ee {
using Self = SpriteLoader;

const PropertyBlend Self::Property::BlendFunc("blend_func");
const PropertyBool Self::Property::FlippedX("flipped_x");
const PropertyBool Self::Property::FlippedY("flipped_y");
const PropertyBool Self::Property::StretchEnabled("stretch_enabled");
const PropertyString Self::Property::Texture("texture");

const std::string Self::ClassName = "_Sprite";

NodeLoaderPtr Self::create() {
    auto result = std::unique_ptr<Self>(new Self());
    result->initialize();
    return std::move(result);
}

Self::SpriteLoader() {}

Self::~SpriteLoader() {}

void Self::addReadHandlers(PropertyHandler& handler) {
    Super::addReadHandlers(handler);

    using Node = cocos2d::Sprite;

    handler.addReadHandler<Node>(Property::BlendFunc, [](const Node* node) {
        return node->getBlendFunc();
    });

    handler.addReadHandler<Node>(Property::FlippedX, [](const Node* node) {
        return node->isFlippedX();
    });

    handler.addReadHandler<Node>(Property::FlippedY, [](const Node* node) {
        return node->isFlippedY();
    });

    handler.addReadHandler<Node>(
        Property::StretchEnabled,
        [](const Node* node) { return node->isStretchEnabled(); });

    handler.addReadHandler<Node>(Property::Texture, [](const Node* node) {
        return NodeInfoReader(node).readString(Property::Texture.name(), "");
    });
}

void Self::addWriteHandlers(PropertyHandler& handler) {
    Super::addWriteHandlers(handler);

    using Node = cocos2d::Sprite;

    handler.addWriteHandler<Node>(
        Property::BlendFunc, [](Node* node, const cocos2d::BlendFunc& value) {
            node->setBlendFunc(value);
            return true;
        });

    handler.addWriteHandler<Node>(Property::FlippedX,
                                  [](Node* node, bool value) {
                                      node->setFlippedX(value);
                                      return true;
                                  });

    handler.addWriteHandler<Node>(Property::FlippedY,
                                  [](Node* node, bool value) {
                                      node->setFlippedY(value);
                                      return true;
                                  });

    handler.addWriteHandler<Node>(Property::StretchEnabled,
                                  [](Node* node, bool value) {
                                      node->setStretchEnabled(value);
                                      return true;
                                  });

    handler.addWriteHandler<Node>(
        Property::Texture, [](Node* node, const std::string& value) {
            node->setTexture(value);
            NodeInfoWriter(node).writeString(Property::Texture.name(), value);
            return true;
        });
}

void Self::addDefaultProperties(PropertyWriter& writer) {
    Super::addDefaultProperties(writer);

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
}

cocos2d::Node* Self::createNode() const {
    return cocos2d::Sprite::create();
}

std::string Self::getClassName() const {
    return ClassName;
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
