#include "inspectorint.hpp"
#include "selectionpath.hpp"
#include "selectiontree.hpp"
#include "ui_inspectorint.h"

#include <parser/nodegraph.hpp>
#include <parser/propertyreader.hpp>

namespace ee {
using Self = InspectorInt;

Self::InspectorInt(QWidget* parent)
    : Super(parent)
    , ui_(new Ui::InspectorInt) {
    ui_->setupUi(this);
    connect(ui_->propertyInput,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            [this](int value) {
                Q_EMIT propertyValueChanged(property_->name(),
                                            cocos2d::Value(value));
            });
}

Self::~InspectorInt() {
    delete ui_;
}

Self* Self::setPropertyName(const QString& name) {
    property_ = std::make_unique<IntPropertyGetter>(name);
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

void Self::setPropertyValue(int value) {
    ui_->propertyInput->setValue(value);
}

void Self::refreshPropertyValue(const NodeGraph& graph,
                                const SelectionTree& selection) {
    Q_ASSERT(not selection.isEmpty());
    auto&& paths = selection.getPaths();
    auto&& path = paths.front();
    auto value = property_->get(path.find(graph));
    setPropertyValue(value);
}
} // namespace ee
