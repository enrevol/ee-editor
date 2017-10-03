#include "spriteinspector.hpp"
#include "inspectorblend.hpp"
#include "inspectorbool.hpp"
#include "inspectortexture.hpp"

#include <parser/spriteloader.hpp>

namespace ee {
using Self = SpriteInspector;

Self::SpriteInspector(QWidget* parent)
    : Super(parent) {
    setDisplayName("Sprite");

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         SpriteLoader::Property::FlippedX.name()))
                     ->setPropertyDisplayName("Flipped X"));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         SpriteLoader::Property::FlippedY.name()))
                     ->setPropertyDisplayName("Flipped Y"));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         SpriteLoader::Property::StretchEnabled.name()))
                     ->setPropertyDisplayName("Stretch enabled"));

    addInspector((new InspectorTexture())
                     ->setPropertyName(QString::fromStdString(
                         SpriteLoader::Property::Texture.name()))
                     ->setPropertyDisplayName("Texture"));

    addInspector((new InspectorBlend())
                     ->setPropertyName(
                         QString::fromStdString(
                             SpriteLoader::Property::BlendFunc.nameSrc()),
                         QString::fromStdString(
                             SpriteLoader::Property::BlendFunc.nameDst())));
}
} // namespace ee
