#include <ciso646>

#include "inspectorstring.hpp"
#include "ui_inspectorstring.h"

namespace ee {
using Self = InspectorString;

Self::InspectorString(QWidget* parent)
    : Super(parent)
    , ui_(new Ui::InspectorString) {
    ui_->setupUi(this);
    connect(ui_->propertyInput, &QLineEdit::textEdited,
            [this](const QString& value) { //
                Q_EMIT propertyValueChanged(value);
            });
    connect(this, &Self::propertyValueChanged, [this](const QString& value) {
        Q_EMIT propertyChanged(
            std::bind(writer_, std::placeholders::_1, value.toStdString()));
    });
}

Self::~InspectorString() {
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

Self* Self::setPropertyValue(const QString& value) {
    ui_->propertyInput->setText(value);
    return this;
}

Self* Self::setPropertyDisplayName(const QString& name) {
    ui_->propertyDisplayName->setText(name);
    return this;
}

void Self::refreshInspector(const std::vector<const cocos2d::Node*>& nodes) {
    auto value = reader_(nodes.at(0));
    setPropertyValue(QString::fromStdString(value));
}
} // namespace ee
