#include "scale9spriteloader.hpp"
#include "nodeinforeader.hpp"
#include "nodeinfowriter.hpp"
#include "propertywriter.hpp"

#include <ui/UIScale9Sprite.h>

namespace ee {
using Self = Scale9SpriteLoader;

const PropertyInt Self::Property::State("state");
const PropertyInt Self::Property::RenderingType("rendering_type");

const std::string Self::ClassName = "_Scale9Sprite";

NodeLoaderPtr Self::create() {
    auto result = std::unique_ptr<Self>(new Self());
    result->initialize();
    return std::move(result);
}

Self::Scale9SpriteLoader() {}

Self::~Scale9SpriteLoader() {}

void Self::addReadHandlers(PropertyHandler& handler) {
    Super::addReadHandlers(handler);

    using Node = cocos2d::ui::Scale9Sprite;

    handler.addReadHandler<Node>(Property::State, [](const Node* node) {
        return static_cast<int>(node->getState());
    });
}

void Self::addWriteHandlers(PropertyHandler& handler) {
    Super::addWriteHandlers(handler);

    using Node = cocos2d::ui::Scale9Sprite;

    handler.addWriteHandler<Node>(Property::State, [](Node* node, int value) {
        node->setState(static_cast<cocos2d::ui::Scale9Sprite::State>(value));
        return true;
    });
}

void Self::addDefaultProperties(PropertyWriter& writer) {
    Super::addDefaultProperties(writer);

    bool flag = true;
    flag &= writer.addProperty(
        Property::State,
        static_cast<int>(cocos2d::ui::Scale9Sprite::State::NORMAL));
    Q_ASSERT(flag);
}

cocos2d::Node* Self::createNode() const {
    return cocos2d::ui::Scale9Sprite::create();
}

std::string Self::getClassName() const {
    return ClassName;
}

Self* Self::cloneRaw() const {
    return new Self();
}
} // namespace ee
