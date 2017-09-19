#include "inspectorfloat.hpp"
#include "ui_inspectorfloat.h"

#include <parser/nodegraph.hpp>

namespace ee {
using Self = InspectorFloat;

Self::InspectorFloat(const QString& propertyName, QWidget* parent)
    : Super(parent)
    , propertyName_(propertyName)
    , ui_(new Ui::InspectorFloat) {
    ui_->setupUi(this);
    connect(ui_->propertyValue,
            static_cast<void (QDoubleSpinBox::*)(double)>(
                &QDoubleSpinBox::valueChanged),
            [this](double value) {
                auto floatValue = static_cast<float>(value);
                Q_EMIT valueChanged(floatValue);
                Q_EMIT propertyValueChanged(propertyName_,
                                            cocos2d::Value(floatValue));
            });
}

Self::~InspectorFloat() {
    delete ui_;
}

Self* Self::setPropertyDisplayName(const QString& name) {
    ui_->propertyName->setText(name);
    return this;
}

Self* Self::setValuePrecision(int precision) {
    ui_->propertyValue->setDecimals(precision);
    return this;
}

Self* Self::setMinimumValue(float value) {
    ui_->propertyValue->setMinimum(static_cast<double>(value));
    return this;
}

Self* Self::setMaximumValue(float value) {
    ui_->propertyValue->setMaximum(static_cast<double>(value));
    return this;
}

Self* Self::setValueRange(float minimum, float maximum) {
    setMinimumValue(minimum);
    setMaximumValue(maximum);
    return this;
}

void Self::refreshPropertyValue(const NodeGraph& graph) {
    ui_->propertyValue->setValue(static_cast<double>(
        graph.getFloatProperty(propertyName_.toStdString())));
}
} // namespace ee
