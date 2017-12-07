#include <ciso646>

#include "inspectorint.hpp"
#include "ui_inspectorint.h"

namespace ee {
using Self = InspectorInt;

Self::InspectorInt(QWidget* parent)
    : Super(parent)
    , ui_(new Ui::InspectorInt)
    , updating_(false) {
    ui_->setupUi(this);
    connect(ui_->propertyInput,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            [this](int value) {
                if (updating_) {
                    return;
                }
                Q_EMIT propertyValueChanged(value);
            });
    connect(this, &Self::propertyValueChanged, [this](int value) {
        Q_EMIT propertyChanged(
            std::bind(writer_, std::placeholders::_1, value));
    });
}

Self::~InspectorInt() {
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
    updating_ = false;
    return this;
}

Self* Self::setPropertyDisplayName(const QString& name) {
    ui_->propertyDisplayName->setText(name);
    return this;
}

Self* Self::setSingleStep(int value) {
    ui_->propertyInput->setSingleStep(value);
    return this;
}

Self* Self::setMinimumValue(int value) {
    ui_->propertyInput->setMinimum(value);
    return this;
}

Self* Self::setMaximumValue(int value) {
    ui_->propertyInput->setMaximum(value);
    return this;
}

void Self::refreshInspector(const std::vector<const cocos2d::Node*>& nodes) {
    auto value = reader_(nodes.at(0));
    setPropertyValue(value);
}
} // namespace ee
