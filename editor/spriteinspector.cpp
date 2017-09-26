#include "spriteinspector.hpp"
#include "inspectorbool.hpp"

#include <parser/spriteloader.hpp>

namespace ee {
using Self = SpriteInspector;

Self::SpriteInspector(QWidget* parent)
    : Super(parent) {
    setDisplayName("Sprite");

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         SpriteLoader::Property::FlippedX))
                     ->setPropertyDisplayName("Flipped X"));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         SpriteLoader::Property::FlippedY))
                     ->setPropertyDisplayName("Flipped Y"));
}
} // namespace ee
