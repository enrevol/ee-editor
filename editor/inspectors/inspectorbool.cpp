#include <ciso646>

#include "inspectorbool.hpp"
#include "ui_inspectorbool.h"

namespace ee {
using Self = InspectorBool;

Self::InspectorBool(QWidget* parent)
    : Super(parent)
    , ui_(new Ui::InspectorBool)
    , updating_(false) {
    ui_->setupUi(this);
    connect(ui_->checkBox, &QCheckBox::stateChanged, [this](int state) {
        if (updating_) {
            return;
        }
        if (state == Qt::CheckState::Unchecked) {
            Q_EMIT propertyValueChanged(false);
        } else if (state == Qt::CheckState::Checked) {
            Q_EMIT propertyValueChanged(true);
        }
    });
    connect(this, &Self::propertyValueChanged, [this](bool value) {
        Q_EMIT propertyChanged(
            std::bind(writer_, std::placeholders::_1, value));
    });
}

Self::~InspectorBool() {
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

Self* Self::setPropertyValue(bool value) {
    Q_ASSERT(not updating_);
    updating_ = true;
    ui_->checkBox->setChecked(value);
    updating_ = false;
    return this;
}

Self* Self::setPropertyDisplayName(const QString& name) {
    ui_->checkBox->setText(name);
    return this;
}

void Self::refreshInspector(const std::vector<const cocos2d::Node*>& nodes) {
    auto value = reader_(nodes.at(0));
    setPropertyValue(value);
}
} // namespace ee
