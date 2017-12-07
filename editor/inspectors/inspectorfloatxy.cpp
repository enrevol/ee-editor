#include <ciso646>

#include "inspectorfloatxy.hpp"
#include "ui_inspectorfloatxy.h"

#include <QTimer>

namespace ee {
using Self = InspectorFloatXY;

Self::InspectorFloatXY(QWidget* parent)
    : Super(parent)
    , ui_(new Ui::InspectorFloatXY)
    , updating_(false)
    , valueDirty_(true) {
    ui_->setupUi(this);

    // http://www.qtcentre.org/threads/18787-QDoubleSpinBox-setValue()-performance-issue
    updater_ = new QTimer(this);
    updater_->setInterval(200);
    updater_->start();
    connect(updater_, &QTimer::timeout, [this] {
        if (valueDirty_) {
            valueDirty_ = false;
            setPropertyValue(valueX_, valueY_);
        }
    });

    connect(ui_->propertyXInput,
            static_cast<void (QDoubleSpinBox::*)(double)>(
                &QDoubleSpinBox::valueChanged),
            [this](double value) {
                if (updating_) {
                    return;
                }
                auto floatValue = static_cast<float>(value);
                valueX_ = floatValue;
                Q_EMIT propertyValueChanged(valueX_, valueY_);
            });
    connect(ui_->propertyYInput,
            static_cast<void (QDoubleSpinBox::*)(double)>(
                &QDoubleSpinBox::valueChanged),
            [this](double value) {
                if (updating_) {
                    return;
                }
                auto floatValue = static_cast<float>(value);
                valueY_ = floatValue;
                Q_EMIT propertyValueChanged(valueX_, valueY_);
            });
    connect(this, &Self::propertyValueChanged, [this](float x, float y) {
        Q_EMIT propertyChanged(std::bind(writer_, std::placeholders::_1, x, y));
    });
}

Self::~InspectorFloatXY() {
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

Self* Self::setPropertyValue(float x, float y) {
    Q_ASSERT(not updating_);
    updating_ = true;
    ui_->propertyXInput->setValue(static_cast<double>(x));
    ui_->propertyYInput->setValue(static_cast<double>(y));
    updating_ = false;
    return this;
}

Self* Self::setPropertyDisplayName(const QString& name) {
    ui_->propertyDisplayName->setText(name);
    return this;
}

Self* Self::setSubPropertyDisplayName(const QString& x, const QString& y) {
    ui_->propertyXDisplayName->setText(x);
    ui_->propertyYDisplayName->setText(y);
    return this;
}

Self* Self::setSingleStep(float value) {
    ui_->propertyXInput->setSingleStep(static_cast<double>(value));
    ui_->propertyYInput->setSingleStep(static_cast<double>(value));
    return this;
}

Self* Self::setValuePrecision(int precision) {
    ui_->propertyXInput->setDecimals(precision);
    ui_->propertyYInput->setDecimals(precision);
    return this;
}

Self* Self::setMinimumValue(float value) {
    ui_->propertyXInput->setMinimum(static_cast<double>(value));
    ui_->propertyYInput->setMinimum(static_cast<double>(value));
    return this;
}

Self* Self::setMaximumValue(float value) {
    ui_->propertyXInput->setMaximum(static_cast<double>(value));
    ui_->propertyYInput->setMaximum(static_cast<double>(value));
    return this;
}

void Self::setPropertyValueLazy(float x, float y) {
    valueDirty_ = true;
    valueX_ = x;
    valueY_ = y;
}

void Self::refreshInspector(const std::vector<const cocos2d::Node*>& nodes) {
    auto value = reader_(nodes.at(0));
    setPropertyValue(value.first, value.second);
}
} // namespace ee
