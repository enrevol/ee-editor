#include "nodeinspector.hpp"
#include "inspectorbool.hpp"
#include "inspectorfloat.hpp"
#include "inspectorfloatxy.hpp"
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
            ->setSubPropertyDisplayName("Width", "Height")
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

    inspectors.append(new InspectorScale());

    inspectors.append((new InspectorFloat())
                          ->setPropertyName(QString::fromStdString(
                              NodeLoader::Property::Rotation))
                          ->setSingleStep(1.0f)
                          ->setValuePrecision(3)
                          ->setPropertyDisplayName("Rotation")
                          ->setMinimumValue(-359.999f)
                          ->setMaximumValue(+359.999f));

    inspectors.append(
        (new InspectorBool())
            ->setPropertyName(QString::fromStdString(
                NodeLoader::Property::IgnoreAnchorPointForPosition))
            ->setPropertyDisplayName("Ignore anchor point for position"));

    return inspectors;
}
} // namespace ee
