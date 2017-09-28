#include "inspectorfloatxy.hpp"
#include "selectionpath.hpp"
#include "selectiontree.hpp"
#include "ui_inspectorfloatxy.h"

#include <parser/nodegraph.hpp>
#include <parser/propertyreader.hpp>

#include <QTimer>

namespace ee {
using Self = InspectorFloatXY;

Self::InspectorFloatXY(QWidget* parent)
    : Super(parent)
    , ui_(new Ui::InspectorFloatXY)
    , updating_(false) {
    ui_->setupUi(this);

    // http://www.qtcentre.org/threads/18787-QDoubleSpinBox-setValue()-performance-issue
    updater_ = new QTimer(this);
    updater_->setInterval(200);
    updater_->start();
    connect(updater_, &QTimer::timeout,
            [this] { setPropertyValue(valueX_, valueY_); });

    connect(ui_->propertyXInput,
            static_cast<void (QDoubleSpinBox::*)(double)>(
                &QDoubleSpinBox::valueChanged),
            [this](double value) {
                if (updating_) {
                    return;
                }
                auto floatValue = static_cast<float>(value);
                Q_EMIT propertyValueChanged(propertyX_->name(),
                                            cocos2d::Value(floatValue));
            });
    connect(ui_->propertyYInput,
            static_cast<void (QDoubleSpinBox::*)(double)>(
                &QDoubleSpinBox::valueChanged),
            [this](double value) {
                if (updating_) {
                    return;
                }
                auto floatValue = static_cast<float>(value);
                Q_EMIT propertyValueChanged(propertyY_->name(),
                                            cocos2d::Value(floatValue));
            });
}

Self::~InspectorFloatXY() {
    delete ui_;
}

Self* Self::setPropertyName(const QString& x, const QString& y) {
    propertyX_ = std::make_unique<FloatPropertyGetter>(x);
    propertyY_ = std::make_unique<FloatPropertyGetter>(y);
    return this;
}

Self* Self::setPropertyDisplayName(const QString& name) {
    ui_->propertyDisplayName->setText(name);
    return this;
}

Self* Self::setSubPropertyDisplayName(const QString& x, const QString& y) {
    ui_->propertyXDisplayName->setText(x);
    ui_->propertyYDisplayName->setText(y);
    return this;
}

Self* Self::setSingleStep(float value) {
    ui_->propertyXInput->setSingleStep(static_cast<double>(value));
    ui_->propertyYInput->setSingleStep(static_cast<double>(value));
    return this;
}

Self* Self::setValuePrecision(int precision) {
    ui_->propertyXInput->setDecimals(precision);
    ui_->propertyYInput->setDecimals(precision);
    return this;
}

Self* Self::setMinimumValue(float value) {
    ui_->propertyXInput->setMinimum(static_cast<double>(value));
    ui_->propertyYInput->setMinimum(static_cast<double>(value));
    return this;
}

Self* Self::setMaximumValue(float value) {
    ui_->propertyXInput->setMaximum(static_cast<double>(value));
    ui_->propertyYInput->setMaximum(static_cast<double>(value));
    return this;
}

void Self::setPropertyValue(float x, float y) {
    Q_ASSERT(not updating_);
    updating_ = true;
    ui_->propertyXInput->setValue(static_cast<double>(x));
    ui_->propertyYInput->setValue(static_cast<double>(y));
    updating_ = false;
}

void Self::setPropertyValueLazy(float x, float y) {
    valueX_ = x;
    valueY_ = y;
}

void Self::refreshPropertyValue(const NodeGraph& graph,
                                const SelectionTree& selection) {
    Q_ASSERT(not selection.isEmpty());
    auto&& paths = selection.getPaths();
    auto&& path = paths.front();
    auto x = propertyX_->get(path.find(graph));
    auto y = propertyY_->get(path.find(graph));
    setPropertyValueLazy(x, y);
}

bool Self::refreshPropertyValue(const NodeGraph& graph,
                                const SelectionTree& selection,
                                const QString& propertyName) {
    if (propertyName != propertyX_->name() &&
        propertyName != propertyY_->name()) {
        return false;
    }
    refreshPropertyValue(graph, selection);
    return true;
}
} // namespace ee
