#include "scale9spriteinspector.hpp"
#include "inspectorselect.hpp"

#include <parser/scale9spriteloader.hpp>

namespace ee {
using Self = Scale9SpriteInspector;

Self::Scale9SpriteInspector(QWidget* parent)
    : Super(parent) {
    setDisplayName("Scale9Sprite");

    addInspector((new InspectorSelect())
                     ->setPropertyDisplayName("State")
                     ->setPropertyName(QString::fromStdString(
                         Scale9SpriteLoader::Property::State.name()))
                     ->addSelection("Normal")
                     ->addSelection("Gray"));
}
} // namespace ee
