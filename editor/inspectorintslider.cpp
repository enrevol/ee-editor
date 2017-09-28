#include "inspectorintslider.hpp"
#include "selectionpath.hpp"
#include "selectiontree.hpp"
#include "ui_inspectorintslider.h"

#include <parser/nodegraph.hpp>
#include <parser/propertyreader.hpp>

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
        Q_EMIT propertyValueChanged(property_->name(), cocos2d::Value(value));
    };
    connect(ui_->propertySlider,
            static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),
            onValueChanged);
    connect(ui_->propertyInput,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            onValueChanged);
}

Self::~InspectorIntSlider() {
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

void Self::setPropertyValue(int value) {
    Q_ASSERT(not updating_);
    updating_ = true;
    ui_->propertyInput->setValue(value);
    ui_->propertySlider->setValue(value);
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
