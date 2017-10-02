#include "nodeinspector.hpp"
#include "inspectorbool.hpp"
#include "inspectorcolor.hpp"
#include "inspectorfloat.hpp"
#include "inspectorfloatxy.hpp"
#include "inspectorint.hpp"
#include "inspectorintslider.hpp"
#include "inspectorscale.hpp"
#include "inspectorstring.hpp"

#include <parser/nodeloader.hpp>

namespace ee {
using Self = NodeInspector;

Self::NodeInspector(QWidget* parent)
    : Super(parent) {
    setDisplayName("Node");

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         NodeLoader::Property::Visible.name()))
                     ->setPropertyDisplayName("Visible"));

    addInspector((new InspectorString())
                     ->setPropertyName(QString::fromStdString(
                         NodeLoader::Property::Name.name()))
                     ->setPropertyDisplayName("Name"));

    addInspector(
        (new InspectorFloatXY())
            ->setPropertyName(
                QString::fromStdString(NodeLoader::Property::Position.nameX()),
                QString::fromStdString(NodeLoader::Property::Position.nameY()))
            ->setPropertyDisplayName("Position")
            ->setSubPropertyDisplayName("X", "Y")
            ->setSingleStep(1.0f)
            ->setValuePrecision(2)
            ->setMinimumValue(-9999.99f)
            ->setMaximumValue(+9999.99f));

    addInspector(
        (new InspectorFloatXY())
            ->setPropertyName(QString::fromStdString(
                                  NodeLoader::Property::ContentSize.nameX()),
                              QString::fromStdString(
                                  NodeLoader::Property::ContentSize.nameY()))
            ->setPropertyDisplayName("Content size")
            ->setSubPropertyDisplayName("W", "H")
            ->setSingleStep(1.0f)
            ->setValuePrecision(2)
            ->setMinimumValue(-9999.99f)
            ->setMaximumValue(+9999.99f));

    addInspector(
        (new InspectorFloatXY())
            ->setPropertyName(QString::fromStdString(
                                  NodeLoader::Property::AnchorPoint.nameX()),
                              QString::fromStdString(
                                  NodeLoader::Property::AnchorPoint.nameY()))
            ->setPropertyDisplayName("Anchor point")
            ->setSubPropertyDisplayName("X", "Y")
            ->setSingleStep(0.05f)
            ->setValuePrecision(3)
            ->setMinimumValue(-99.999f)
            ->setMaximumValue(+99.999f));

    addInspector(
        (new InspectorFloatXY())
            ->setPropertyName(
                QString::fromStdString(NodeLoader::Property::ScaleX.name()),
                QString::fromStdString(NodeLoader::Property::ScaleY.name()))
            ->setPropertyDisplayName("Scale")
            ->setSubPropertyDisplayName("X", "Y")
            ->setSingleStep(0.05f)
            ->setValuePrecision(3)
            ->setMinimumValue(-99.999f)
            ->setMaximumValue(+99.999f));

    addInspector((new InspectorFloat())
                     ->setPropertyName(QString::fromStdString(
                         NodeLoader::Property::Rotation.name()))
                     ->setPropertyDisplayName("Rotation")
                     ->setSingleStep(1.0f)
                     ->setValuePrecision(2)
                     ->setMinimumValue(-359.99f)
                     ->setMaximumValue(+359.99f));

    addInspector(
        (new InspectorFloatXY())
            ->setPropertyName(
                QString::fromStdString(NodeLoader::Property::SkewX.name()),
                QString::fromStdString(NodeLoader::Property::SkewY.name()))
            ->setPropertyDisplayName("Skew")
            ->setSubPropertyDisplayName("X", "Y")
            ->setSingleStep(0.05f)
            ->setValuePrecision(3)
            ->setMinimumValue(-99.999f)
            ->setMaximumValue(+99.999f));

    addInspector((new InspectorInt())
                     ->setPropertyName(QString::fromStdString(
                         NodeLoader::Property::Tag.name()))
                     ->setPropertyDisplayName("Tag")
                     ->setSingleStep(1)
                     ->setMinimumValue(-1)
                     ->setMaximumValue(+9999));

    addInspector(
        (new InspectorColor)
            ->setPropertyName(
                QString::fromStdString(NodeLoader::Property::Color.nameR()),
                QString::fromStdString(NodeLoader::Property::Color.nameG()),
                QString::fromStdString(NodeLoader::Property::Color.nameB()))
            ->setPropertyDisplayName("Color"));

    addInspector((new InspectorIntSlider())
                     ->setPropertyName(QString::fromStdString(
                         NodeLoader::Property::Opacity.name()))
                     ->setPropertyDisplayName("Opacity")
                     ->setSingleStep(1)
                     ->setMinimumValue(+0)
                     ->setMaximumValue(+255));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         NodeLoader::Property::CascadeColorEnabled.name()))
                     ->setPropertyDisplayName("Cascade color enabled"));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         NodeLoader::Property::CascadeOpacityEnabled.name()))
                     ->setPropertyDisplayName("Cascade opacity enabled"));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         NodeLoader::Property::OpacityModifyRGB.name()))
                     ->setPropertyDisplayName("Opacity modify RGB"));

    addInspector(
        (new InspectorBool())
            ->setPropertyName(QString::fromStdString(
                NodeLoader::Property::IgnoreAnchorPointForPosition.name()))
            ->setPropertyDisplayName("Ignore anchor point for position"));
}
} // namespace ee
