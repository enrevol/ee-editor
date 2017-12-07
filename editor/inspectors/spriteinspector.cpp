#include "spriteinspector.hpp"
#include "inspectorblend.hpp"
#include "inspectorbool.hpp"
#include "inspectortexture.hpp"

#include <parser/spriteloader.hpp>

namespace ee {
using Self = SpriteInspector;

namespace {
auto createFlippedXInspector() {
    return (new InspectorBool())
        ->setPropertyDisplayName("Flipped X")
        ->setReader(SpriteLoader::Property::FlippedX.getReader())
        ->setWriter(SpriteLoader::Property::FlippedX.getWriter());
}

auto createFlippedYInspector() {
    return (new InspectorBool())
        ->setPropertyDisplayName("Flipped Y")
        ->setReader(SpriteLoader::Property::FlippedY.getReader())
        ->setWriter(SpriteLoader::Property::FlippedY.getWriter());
}

auto createStretchEnabledInspector() {
    return (new InspectorBool())
        ->setPropertyDisplayName("Stretch enabled")
        ->setReader(SpriteLoader::Property::StretchEnabled.getReader())
        ->setWriter(SpriteLoader::Property::StretchEnabled.getWriter());
}

auto createTextureInspector() {
    return (new InspectorTexture())
        ->setPropertyDisplayName("Texture")
        ->setReader(SpriteLoader::Property::Texture.getReader())
        ->setWriter(SpriteLoader::Property::Texture.getWriter());
}

auto createBlendFuncInspector() {
    return (new InspectorBlend())
        ->setReader(SpriteLoader::Property::BlendFunc.getReader())
        ->setWriter(SpriteLoader::Property::BlendFunc.getWriter());
}
} // namespace

Self::SpriteInspector(QWidget* parent)
    : Super(parent) {
    setDisplayName("Sprite");
    addInspector(createFlippedXInspector());
    addInspector(createFlippedYInspector());
    addInspector(createStretchEnabledInspector());
    addInspector(createTextureInspector());
    addInspector(createBlendFuncInspector());
}
} // namespace ee
