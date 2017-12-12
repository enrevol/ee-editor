#include <ciso646>

#include "inspectorselect.hpp"
#include "ui_inspectorselect.h"

namespace ee {
using Self = InspectorSelect;

Self::InspectorSelect(QWidget* parent)
    : Super(parent)
    , ui_(new Ui::InspectorSelect)
    , updating_(false) {
    ui_->setupUi(this);
    connect(ui_->propertySelection,
            static_cast<void (QComboBox::*)(int index)>(
                &QComboBox::currentIndexChanged),
            [this](int index) {
                if (updating_) {
                    return;
                }
                Q_EMIT propertyValueChanged(index);
            });
    connect(this, &Self::propertyValueChanged, [this](int value) {
        Q_EMIT propertyChanged(
            std::bind(writer_, std::placeholders::_1, value));
    });
}

Self::~InspectorSelect() {
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
    ui_->propertySelection->setCurrentIndex(value);
    updating_ = false;
    return this;
}

Self* Self::setPropertyDisplayName(const QString& name) {
    ui_->propertyDisplayName->setText(name);
    return this;
}

Self* Self::addSelection(const QString& name) {
    Q_ASSERT(not updating_);
    updating_ = true;
    ui_->propertySelection->addItem(name);
    updating_ = false;
    return this;
}

Self* Self::clearSelections() {
    Q_ASSERT(not updating_);
    updating_ = true;
    ui_->propertySelection->clear();
    updating_ = false;
    return this;
}

void Self::refreshInspector(const std::vector<const cocos2d::Node*>& nodes) {
    auto value = reader_(nodes.at(0));
    setPropertyValue(value.value());
}
} // namespace ee
