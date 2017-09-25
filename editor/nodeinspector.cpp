#include "nodeinspector.hpp"
#include "inspectorbool.hpp"
#include "inspectorcolor.hpp"
#include "inspectorfloat.hpp"
#include "inspectorfloatxy.hpp"
#include "inspectorint.hpp"
#include "inspectorscale.hpp"

#include <parser/nodeloader.hpp>

namespace ee {
using Self = NodeInspector;

Self::NodeInspector(QWidget* parent)
    : Super(parent) {}

QVector<Inspector*> Self::buildInspectors() {
    QVector<Inspector*> inspectors;

    inspectors.append((new InspectorBool())
                          ->setPropertyName(QString::fromStdString(
                              NodeLoader::Property::Visible))
                          ->setPropertyDisplayName("Visible"));

    inspectors.append(
        (new InspectorFloatXY())
            ->setPropertyName(
                QString::fromStdString(NodeLoader::Property::PositionX),
                QString::fromStdString(NodeLoader::Property::PositionY))
            ->setPropertyDisplayName("Position")
            ->setSubPropertyDisplayName("X", "Y")
            ->setSingleStep(1.0f)
            ->setValuePrecision(2)
            ->setMinimumValue(-9999.99f)
            ->setMaximumValue(+9999.99f));

    inspectors.append(
        (new InspectorFloatXY())
            ->setPropertyName(
                QString::fromStdString(NodeLoader::Property::ContentSizeWidth),
                QString::fromStdString(NodeLoader::Property::ContentSizeHeight))
            ->setPropertyDisplayName("Content size")
            ->setSubPropertyDisplayName("W", "H")
            ->setSingleStep(1.0f)
            ->setValuePrecision(2)
            ->setMinimumValue(-9999.99f)
            ->setMaximumValue(+9999.99f));

    inspectors.append(
        (new InspectorFloatXY())
            ->setPropertyName(
                QString::fromStdString(NodeLoader::Property::AnchorPointX),
                QString::fromStdString(NodeLoader::Property::AnchorPointY))
            ->setPropertyDisplayName("Anchor point")
            ->setSubPropertyDisplayName("X", "Y")
            ->setSingleStep(0.05f)
            ->setValuePrecision(3)
            ->setMinimumValue(-99.999f)
            ->setMaximumValue(+99.999f));

    inspectors.append(
        (new InspectorFloatXY())
            ->setPropertyName(
                QString::fromStdString(NodeLoader::Property::ScaleX),
                QString::fromStdString(NodeLoader::Property::ScaleY))
            ->setPropertyDisplayName("Scale")
            ->setSubPropertyDisplayName("X", "Y")
            ->setSingleStep(0.05f)
            ->setValuePrecision(3)
            ->setMinimumValue(-99.999f)
            ->setMaximumValue(+99.999f));

    inspectors.append((new InspectorFloat())
                          ->setPropertyName(QString::fromStdString(
                              NodeLoader::Property::Rotation))
                          ->setPropertyDisplayName("Rotation")
                          ->setSingleStep(1.0f)
                          ->setValuePrecision(2)
                          ->setMinimumValue(-359.99f)
                          ->setMaximumValue(+359.99f));

    inspectors.append(
        (new InspectorFloatXY())
            ->setPropertyName(
                QString::fromStdString(NodeLoader::Property::SkewX),
                QString::fromStdString(NodeLoader::Property::SkewY))
            ->setPropertyDisplayName("Skew")
            ->setSubPropertyDisplayName("X", "Y")
            ->setSingleStep(0.05f)
            ->setValuePrecision(3)
            ->setMinimumValue(-99.999f)
            ->setMaximumValue(+99.999f));

    inspectors.append(
        (new InspectorInt())
            ->setPropertyName(QString::fromStdString(NodeLoader::Property::Tag))
            ->setPropertyDisplayName("Tag")
            ->setSingleStep(1)
            ->setMinimumValue(-1)
            ->setMaximumValue(+9999));

    inspectors.append(
        (new InspectorBool())
            ->setPropertyName(QString::fromStdString(
                NodeLoader::Property::IgnoreAnchorPointForPosition))
            ->setPropertyDisplayName("Ignore anchor point for position"));

    inspectors.append(
        (new InspectorColor)
            ->setPropertyName(
                QString::fromStdString(NodeLoader::Property::ColorR),
                QString::fromStdString(NodeLoader::Property::ColorG),
                QString::fromStdString(NodeLoader::Property::ColorB))
            ->setPropertyDisplayName("Color"));

    inspectors.append((new InspectorInt())
                          ->setPropertyName(QString::fromStdString(
                              NodeLoader::Property::Opacity))
                          ->setPropertyDisplayName("Opacity")
                          ->setSingleStep(1)
                          ->setMinimumValue(+0)
                          ->setMaximumValue(+255));

    inspectors.append((new InspectorBool())
                          ->setPropertyName(QString::fromStdString(
                              NodeLoader::Property::CascadeColorEnabled))
                          ->setPropertyDisplayName("Cascade color enabled"));

    inspectors.append((new InspectorBool())
                          ->setPropertyName(QString::fromStdString(
                              NodeLoader::Property::CascadeOpacityEnabled))
                          ->setPropertyDisplayName("Cascade opacity enabled"));

    return inspectors;
}
} // namespace ee
