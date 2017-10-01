#include <ciso646>

#include "inspectorfloat.hpp"
#include "selectionpath.hpp"
#include "selectiontree.hpp"
#include "ui_inspectorfloat.h"

#include <parser/nodegraph.hpp>
#include <parser/propertyreader.hpp>

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
                Q_EMIT propertyValueChanged(property_->name(),
                                            cocos2d::Value(floatValue));
            });
}

Self::~InspectorFloat() {
    delete ui_;
}

Self* Self::setPropertyName(const QString& name) {
    property_ = std::make_unique<FloatPropertyGetter>(name);
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

void Self::setPropertyValue(float value) {
    Q_ASSERT(not updating_);
    updating_ = true;
    ui_->propertyInput->setValue(static_cast<double>(value));
    updating_ = false;
}

void Self::refreshPropertyValue(const NodeGraph& graph,
                                const SelectionTree& selection) {
    Q_ASSERT(not selection.isEmpty());
    auto&& paths = selection.getPaths();
    auto&& path = paths.front();
    auto value = property_->get(path.find(graph));
    setPropertyValue(value);
}

bool Self::refreshPropertyValue(const NodeGraph& graph,
                                const SelectionTree& selection,
                                const QString& propertyName) {
    if (propertyName != property_->name()) {
        return false;
    }
    refreshPropertyValue(graph, selection);
    return true;
}
} // namespace ee
