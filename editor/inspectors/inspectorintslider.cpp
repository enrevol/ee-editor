#include <ciso646>

#include "inspectorintslider.hpp"
#include "ui_inspectorintslider.h"

namespace ee {
using Self = InspectorIntSlider;

Self::InspectorIntSlider(QWidget* parent)
    : Super(parent)
    , ui_(new Ui::InspectorIntSlider)
    , updating_(false) {
    ui_->setupUi(this);
    auto onValueChanged = [this](int value) {
        if (updating_) {
            return;
        }
        setPropertyValue(value);
        Q_EMIT propertyValueChanged(value);
    };
    connect(ui_->propertySlider,
            static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),
            onValueChanged);
    connect(ui_->propertyInput,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            onValueChanged);

    connect(this, &Self::propertyValueChanged, [this](int value) {
        Q_EMIT propertyChanged(
            std::bind(writer_, std::placeholders::_1, value));
    });
}

Self::~InspectorIntSlider() {
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

Self* Self::setPropertyValue(int value) {
    Q_ASSERT(not updating_);
    updating_ = true;
    ui_->propertyInput->setValue(value);
    ui_->propertySlider->setValue(value);
    updating_ = false;
    return this;
}

Self* Self::setPropertyDisplayName(const QString& name) {
    ui_->propertyDisplayName->setText(name);
    return this;
}

Self* Self::setSingleStep(int value) {
    ui_->propertyInput->setSingleStep(value);
    ui_->propertySlider->setSingleStep(value);
    return this;
}

Self* Self::setMinimumValue(int value) {
    ui_->propertyInput->setMinimum(value);
    ui_->propertySlider->setMinimum(value);
    return this;
}

Self* Self::setMaximumValue(int value) {
    ui_->propertyInput->setMaximum(value);
    ui_->propertySlider->setMaximum(value);
    return this;
}

void Self::refreshInspector(const std::vector<const cocos2d::Node*>& nodes) {
    auto value = reader_(nodes.at(0));
    setPropertyValue(value.value());
}
} // namespace ee
