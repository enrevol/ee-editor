#include "scale9spriteinspector.hpp"
#include "inspectors/inspectorselect.hpp"

#include <parser/scale9spriteloader.hpp>

namespace ee {
using Self = Scale9SpriteInspector;

namespace {
auto createStateInspector() {
    return (new InspectorSelect())
        ->setReader([](const cocos2d::Node* node) {
            return static_cast<int>(
                Scale9SpriteLoader::Property::State.read(node));
        })
        ->setWriter([](cocos2d::Node* node, int value) {
            return Scale9SpriteLoader::Property::State.write(
                node, static_cast<cocos2d::ui::Scale9Sprite::State>(value));
        })
        ->setPropertyDisplayName("State")
        ->addSelection("Normal")
        ->addSelection("Gray");
}
} // namespace

Self::Scale9SpriteInspector(QWidget* parent)
    : Super(parent) {
    setDisplayName("Scale9Sprite");
    addInspector(createStateInspector());
}
} // namespace ee
