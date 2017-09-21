#include "inspectorfloat.hpp"
#include "sceneselection.hpp"
#include "ui_inspectorfloat.h"

#include <parser/nodegraph.hpp>
#include <parser/propertyreader.hpp>

namespace ee {
using Self = InspectorFloat;

Self::InspectorFloat(const QString& propertyName, QWidget* parent)
    : Super(parent)
    , propertyName_(propertyName)
    , ui_(new Ui::InspectorFloat) {
    ui_->setupUi(this);
    connect(ui_->propertyValue,
            static_cast<void (QDoubleSpinBox::*)(double)>(
                &QDoubleSpinBox::valueChanged),
            [this](double value) {
                auto floatValue = static_cast<float>(value);
                Q_EMIT valueChanged(floatValue);
                Q_EMIT propertyValueChanged(propertyName_,
                                            cocos2d::Value(floatValue));
            });
}

Self::~InspectorFloat() {
    delete ui_;
}

Self* Self::setPropertyDisplayName(const QString& name) {
    ui_->propertyName->setText(name);
    return this;
}

Self* Self::setValuePrecision(int precision) {
    ui_->propertyValue->setDecimals(precision);
    return this;
}

Self* Self::setMinimumValue(float value) {
    ui_->propertyValue->setMinimum(static_cast<double>(value));
    return this;
}

Self* Self::setMaximumValue(float value) {
    ui_->propertyValue->setMaximum(static_cast<double>(value));
    return this;
}

Self* Self::setValueRange(float minimum, float maximum) {
    setMinimumValue(minimum);
    setMaximumValue(maximum);
    return this;
}

void Self::setPropertyValue(float value) {
    ui_->propertyValue->setValue(static_cast<double>(value));
}

float Self::getGraphPropertyValue(const NodeGraph& graph) const {
    auto reader = graph.getPropertyReader();
    return reader.getFloatProperty(propertyName_.toStdString());
}

void Self::refreshPropertyValue(const NodeGraph& graph,
                                const SceneSelection& selection) {
    float sum = 0;
    std::size_t count = 0;
    if (selection.isRoot()) {
        sum += getGraphPropertyValue(graph);
        ++count;
    } else {
        const NodeGraph* parent = &graph;
        for (auto&& index : selection.getAncestorIndices()) {
            parent = &parent->getChild(static_cast<std::size_t>(index));
        }
        for (auto&& index : selection.getChildrenIndices()) {
            auto&& child = graph.getChild(static_cast<std::size_t>(index));
            sum += getGraphPropertyValue(child);
            ++count;
        }
    }
    setPropertyValue(sum / static_cast<float>(count));
}
} // namespace ee
