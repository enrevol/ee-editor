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
                         WidgetLoader::Property::Enabled.name()))
                     ->setPropertyDisplayName("Enabled"));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         WidgetLoader::Property::Bright.name()))
                     ->setPropertyDisplayName("Bright"));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         WidgetLoader::Property::Highlighted.name()))
                     ->setPropertyDisplayName("Highlighted"));

    addInspector(
        (new InspectorBool())
            ->setPropertyName(QString::fromStdString(
                WidgetLoader::Property::IgnoreContentAdaptWithSize.name()))
            ->setPropertyDisplayName("Ignore content adapt with size"));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         WidgetLoader::Property::UnifySizeEnabled.name()))
                     ->setPropertyDisplayName("Unify size enabled"));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         WidgetLoader::Property::TouchEnabled.name()))
                     ->setPropertyDisplayName("Touch enabled"));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         WidgetLoader::Property::SwallowTouches.name()))
                     ->setPropertyDisplayName("Swallow touches"));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         WidgetLoader::Property::PropagateTouchEvents.name()))
                     ->setPropertyDisplayName("Propagate touch events"));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         WidgetLoader::Property::FlippedX.name()))
                     ->setPropertyDisplayName("Flipped X"));

    addInspector((new InspectorBool())
                     ->setPropertyName(QString::fromStdString(
                         WidgetLoader::Property::FlippedY.name()))
                     ->setPropertyDisplayName("Flipped Y"));

    addInspector((new InspectorFloatXY())
                     ->setPropertyName(
                         QString::fromStdString(
                             WidgetLoader::Property::PositionPercent.nameX()),
                         QString::fromStdString(
                             WidgetLoader::Property::PositionPercent.nameY()))
                     ->setPropertyDisplayName("Position percent")
                     ->setSubPropertyDisplayName("X", "Y")
                     ->setSingleStep(0.5f)
                     ->setValuePrecision(3)
                     ->setMinimumValue(0.000f)
                     ->setMaximumValue(999.999f));

    addInspector(
        (new InspectorFloatXY())
            ->setPropertyName(QString::fromStdString(
                                  WidgetLoader::Property::SizePercent.nameX()),
                              QString::fromStdString(
                                  WidgetLoader::Property::SizePercent.nameY()))
            ->setPropertyDisplayName("Size percent")
            ->setSubPropertyDisplayName("W", "H")
            ->setSingleStep(0.5f)
            ->setValuePrecision(3)
            ->setMinimumValue(0.000f)
            ->setMaximumValue(999.999f));
}
} // namespace ee
