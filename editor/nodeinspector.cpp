#include "nodeinspector.hpp"
#include "inspectorfloat.hpp"

#include <parser/nodeloader.hpp>

namespace ee {
using Self = NodeInspector;

Self::NodeInspector(QWidget* parent)
    : Super(parent) {}

QVector<Inspector*> Self::buildInspectors() {
    auto inspector_position_x = new InspectorFloat(
        QString::fromStdString(NodeLoader::Property::PositionX));
    inspector_position_x->setPropertyDisplayName("Position X")
        ->setMinimumValue(-9999)
        ->setMaximumValue(+9999)
        ->setValuePrecision(3);

    auto inspector_position_y = new InspectorFloat(
        QString::fromStdString(NodeLoader::Property::PositionY));
    inspector_position_y->setPropertyDisplayName("Position Y")
        ->setMinimumValue(-9999)
        ->setMaximumValue(+9999)
        ->setValuePrecision(3);

    auto inspector_content_width = new InspectorFloat(
        QString::fromStdString(NodeLoader::Property::ContentSizeWidth));
    inspector_content_width->setPropertyDisplayName("Content width")
        ->setMinimumValue(0)
        ->setMaximumValue(+999)
        ->setValuePrecision(3);

    auto inspector_content_height = new InspectorFloat(
        QString::fromStdString(NodeLoader::Property::ContentSizeHeight));
    inspector_content_height->setPropertyDisplayName("Content height")
        ->setMinimumValue(0)
        ->setMaximumValue(+999)
        ->setValuePrecision(3);

    QVector<Inspector*> inspectors;
    inspectors.append(inspector_position_x);
    inspectors.append(inspector_position_y);
    inspectors.append(inspector_content_width);
    inspectors.append(inspector_content_height);
    return inspectors;
}
} // namespace ee
