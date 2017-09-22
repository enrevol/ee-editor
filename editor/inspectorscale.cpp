#include "inspectorscale.hpp"
#include "selectionpath.hpp"
#include "selectiontree.hpp"
#include "ui_inspectorscale.h"

#include <parser/nodegraph.hpp>
#include <parser/nodeloader.hpp>
#include <parser/propertyreader.hpp>

namespace ee {
using Self = InspectorScale;

Self::InspectorScale(QWidget* parent)
    : Super(parent)
    , ui_(new Ui::InspectorScale)
    , scaleXProperty_(QString::fromStdString(NodeLoader::Property::ScaleX))
    , scaleYProperty_(QString::fromStdString(NodeLoader::Property::ScaleY)) {
    ui_->setupUi(this);
    setupSpinner(ui_->scaleXInput);
    setupSpinner(ui_->scaleYInput);
    connect(ui_->scaleXInput,
            static_cast<void (QDoubleSpinBox::*)(double)>(
                &QDoubleSpinBox::valueChanged),
            [this](double value) {
                auto floatValue = static_cast<float>(value);
                Q_EMIT propertyValueChanged(scaleXProperty_.name(),
                                            cocos2d::Value(floatValue));
            });
    connect(ui_->scaleYInput,
            static_cast<void (QDoubleSpinBox::*)(double)>(
                &QDoubleSpinBox::valueChanged),
            [this](double value) {
                auto floatValue = static_cast<float>(value);
                Q_EMIT propertyValueChanged(scaleYProperty_.name(),
                                            cocos2d::Value(floatValue));
            });
}

Self::~InspectorScale() {
    delete ui_;
}

void Self::setupSpinner(QDoubleSpinBox* spinner) {
    spinner->setRange(-99, +99);
    spinner->setDecimals(3);
    spinner->setSingleStep(0.05);
}

void Self::setScaleX(float value) {
    ui_->scaleXInput->setValue(static_cast<double>(value));
}

void Self::setScaleY(float value) {
    ui_->scaleYInput->setValue(static_cast<double>(value));
}

void Self::refreshPropertyValue(const NodeGraph& graph,
                                const SelectionTree& selection) {
    Q_ASSERT(not selection.isEmpty());
    auto&& paths = selection.getPaths();
    auto&& path = paths.front();
    setScaleX(scaleXProperty_.get(path.find(graph)));
    setScaleY(scaleYProperty_.get(path.find(graph)));
}
} // namespace ee
