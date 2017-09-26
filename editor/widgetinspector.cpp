#include "widgetinspector.hpp"
#include "inspectorbool.hpp"
#include "inspectorfloatxy.hpp"

#include <parser/widgetloader.hpp>

namespace ee {
using Self = WidgetInspector;

Self::WidgetInspector(QWidget* parent)
    : Super(parent) {
    setDisplayName("Widget");

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         WidgetLoader::Property::Enabled))
                     ->setPropertyDisplayName("Enabled"));

    addInspector((new InspectorBool())
                     ->setPropertyName(
                         QString::fromStdString(WidgetLoader::Property::Bright))
                     ->setPropertyDisplayName("Bright"));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         WidgetLoader::Property::Highlighted))
                     ->setPropertyDisplayName("Highlighted"));

    addInspector(
        (new InspectorBool())
            ->setPropertyName(QString::fromStdString(
                WidgetLoader::Property::IgnoreContentAdaptWithSize))
            ->setPropertyDisplayName("Ignore content adapt with size"));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         WidgetLoader::Property::UnifySizeEnabled))
                     ->setPropertyDisplayName("Unify size enabled"));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         WidgetLoader::Property::TouchEnabled))
                     ->setPropertyDisplayName("Touch enabled"));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         WidgetLoader::Property::SwallowTouches))
                     ->setPropertyDisplayName("Swallow touches"));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         WidgetLoader::Property::PropagateTouchEvents))
                     ->setPropertyDisplayName("Propagate touch events"));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         WidgetLoader::Property::FlippedX))
                     ->setPropertyDisplayName("Flipped X"));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         WidgetLoader::Property::FlippedY))
                     ->setPropertyDisplayName("Flipped Y"));

    addInspector(
        (new InspectorFloatXY())
            ->setPropertyName(QString::fromStdString(
                                  WidgetLoader::Property::PositionPercentX),
                              QString::fromStdString(
                                  WidgetLoader::Property::PositionPercentY))
            ->setPropertyDisplayName("Position percent")
            ->setSubPropertyDisplayName("X", "Y")
            ->setSingleStep(0.5f)
            ->setValuePrecision(3)
            ->setMinimumValue(0.000f)
            ->setMaximumValue(999.999f));

    addInspector(
        (new InspectorFloatXY())
            ->setPropertyName(
                QString::fromStdString(WidgetLoader::Property::SizePercentX),
                QString::fromStdString(WidgetLoader::Property::SizePercentY))
            ->setPropertyDisplayName("Size percent")
            ->setSubPropertyDisplayName("W", "Y")
            ->setSingleStep(0.5f)
            ->setValuePrecision(3)
            ->setMinimumValue(0.000f)
            ->setMaximumValue(999.999f));
}
} // namespace ee
