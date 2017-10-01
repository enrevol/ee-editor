#include <ciso646>

#include "inspectorbool.hpp"
#include "selectionpath.hpp"
#include "selectiontree.hpp"
#include "ui_inspectorbool.h"

#include <parser/nodegraph.hpp>
#include <parser/propertyreader.hpp>

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
            Q_EMIT propertyValueChanged(property_->name(),
                                        cocos2d::Value(false));
        } else if (state == Qt::CheckState::Checked) {
            Q_EMIT propertyValueChanged(property_->name(),
                                        cocos2d::Value(true));
        }
    });
}

Self::~InspectorBool() {
    delete ui_;
}

Self* Self::setPropertyName(const QString& name) {
    property_ = std::make_unique<BoolPropertyGetter>(name);
    return this;
}

Self* Self::setPropertyDisplayName(const QString& name) {
    ui_->checkBox->setText(name);
    return this;
}

void Self::setPropertyValue(bool value) {
    Q_ASSERT(not updating_);
    updating_ = true;
    ui_->checkBox->setChecked(value);
    updating_ = false;
}

void Self::refreshPropertyValue(const NodeGraph& graph,
                                const SelectionTree& selection) {
    Q_ASSERT(not selection.isEmpty());
    Q_ASSERT(property_);
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
