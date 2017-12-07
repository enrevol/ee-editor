#include <ciso646>

#include "inspectorfloat.hpp"
#include "ui_inspectorfloat.h"

namespace ee {
using Self = InspectorFloat;

Self::InspectorFloat(QWidget* parent)
    : Super(parent)
    , ui_(new Ui::InspectorFloat)
    , updating_(false) {
    ui_->setupUi(this);
    connect(ui_->propertyInput,
            static_cast<void (QDoubleSpinBox::*)(double)>(
                &QDoubleSpinBox::valueChanged),
            [this](double value) {
                if (updating_) {
                    return;
                }
                auto floatValue = static_cast<float>(value);
                Q_EMIT propertyValueChanged(floatValue);
            });
    connect(this, &Self::propertyValueChanged, [this](float value) {
        Q_EMIT propertyChanged(
            std::bind(writer_, std::placeholders::_1, value));
    });
}

Self::~InspectorFloat() {
    delete ui_;
}

Self* Self::setReader(const Reader& reader) {
    reader_ = reader;
    return this;
}

Self* Self::setWriter(const Writer& writer) {
    writer_ = writer;
    return this;
}

Self* Self::setPropertyValue(float value) {
    Q_ASSERT(not updating_);
    updating_ = true;
    ui_->propertyInput->setValue(static_cast<double>(value));
    updating_ = false;
    return this;
}

Self* Self::setPropertyDisplayName(const QString& name) {
    ui_->propertyDisplayName->setText(name);
    return this;
}

Self* Self::setSingleStep(float value) {
    ui_->propertyInput->setSingleStep(static_cast<double>(value));
    return this;
}

Self* Self::setValuePrecision(int precision) {
    ui_->propertyInput->setDecimals(precision);
    return this;
}

Self* Self::setMinimumValue(float value) {
    ui_->propertyInput->setMinimum(static_cast<double>(value));
    return this;
}

Self* Self::setMaximumValue(float value) {
    ui_->propertyInput->setMaximum(static_cast<double>(value));
    return this;
}

void Self::refreshInspector(const std::vector<const cocos2d::Node*>& nodes) {
    auto value = reader_(nodes.at(0));
    setPropertyValue(value);
}
} // namespace ee
