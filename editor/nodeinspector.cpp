#include "nodeinspector.hpp"
#include "inspectorbool.hpp"
#include "inspectorfloat.hpp"
#include "inspectorscale.hpp"

#include <parser/nodeloader.hpp>

namespace ee {
using Self = NodeInspector;

Self::NodeInspector(QWidget* parent)
    : Super(parent) {}

QVector<Inspector*> Self::buildInspectors() {
    QVector<Inspector*> inspectors;

    inspectors.append((new InspectorBool(QString::fromStdString(
                           NodeLoader::Property::Visible)))
                          ->setPropertyDisplayName("Visible"));

    inspectors.append((new InspectorFloat(QString::fromStdString(
                           NodeLoader::Property::PositionX)))
                          ->setPropertyDisplayName("Position X")
                          ->setMinimumValue(-9999)
                          ->setMaximumValue(+9999)
                          ->setValuePrecision(3));

    inspectors.append((new InspectorFloat(QString::fromStdString(
                           NodeLoader::Property::PositionY)))
                          ->setPropertyDisplayName("Position Y")
                          ->setMinimumValue(-9999)
                          ->setMaximumValue(+9999)
                          ->setValuePrecision(3));

    inspectors.append((new InspectorFloat(QString::fromStdString(
                           NodeLoader::Property::ContentSizeWidth)))
                          ->setPropertyDisplayName("Content width")
                          ->setMinimumValue(0)
                          ->setMaximumValue(+999)
                          ->setValuePrecision(3));

    inspectors.append((new InspectorFloat(QString::fromStdString(
                           NodeLoader::Property::ContentSizeHeight)))
                          ->setPropertyDisplayName("Content height")
                          ->setMinimumValue(0)
                          ->setMaximumValue(+999)
                          ->setValuePrecision(3));

    inspectors.append((new InspectorFloat(QString::fromStdString(
                           NodeLoader::Property::AnchorPointX)))
                          ->setPropertyDisplayName("Anchor point X")
                          ->setMinimumValue(-99)
                          ->setMaximumValue(+99)
                          ->setValuePrecision(3));

    inspectors.append((new InspectorFloat(QString::fromStdString(
                           NodeLoader::Property::AnchorPointY)))
                          ->setPropertyDisplayName("Anchor point Y")
                          ->setMinimumValue(-99)
                          ->setMaximumValue(+99)
                          ->setValuePrecision(3));

    inspectors.append(new InspectorScale());

    inspectors.append((new InspectorFloat(QString::fromStdString(
                           NodeLoader::Property::Rotation)))
                          ->setPropertyDisplayName("Rotation")
                          ->setMinimumValue(-360)
                          ->setMaximumValue(+360)
                          ->setValuePrecision(3));

    inspectors.append(
        (new InspectorBool(QString::fromStdString(
             NodeLoader::Property::IgnoreAnchorPointForPosition)))
            ->setPropertyDisplayName("Ignore anchor point for position"));

    return inspectors;
}
} // namespace ee
