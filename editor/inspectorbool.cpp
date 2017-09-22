#include "inspectorbool.hpp"
#include "selectionpath.hpp"
#include "selectiontree.hpp"
#include "ui_inspectorbool.h"

#include <parser/nodegraph.hpp>
#include <parser/propertyreader.hpp>

namespace ee {
using Self = InspectorBool;

Self::InspectorBool(const QString& propertyName, QWidget* parent)
    : Super(parent)
    , property_(propertyName)
    , ui_(new Ui::InspectorBool) {
    ui_->setupUi(this);
    connect(ui_->checkBox, &QCheckBox::stateChanged, [this](int state) {
        if (state == Qt::CheckState::Unchecked) {
            Q_EMIT propertyValueChanged(property_.name(),
                                        cocos2d::Value(false));
        } else if (state == Qt::CheckState::Checked) {
            Q_EMIT propertyValueChanged(property_.name(), cocos2d::Value(true));
        }
    });
}

Self::~InspectorBool() {
    delete ui_;
}

Self* Self::setPropertyDisplayName(const QString& name) {
    ui_->checkBox->setText(name);
    return this;
}

void Self::setPropertyValue(bool value) {
    ui_->checkBox->setChecked(value);
}

void Self::refreshPropertyValue(const NodeGraph& graph,
                                const SelectionTree& selection) {
    Q_ASSERT(not selection.isEmpty());
    auto&& paths = selection.getPaths();
    auto&& path = paths.front();
    auto value = property_.get(path.find(graph));
    setPropertyValue(value);
}
} // namespace ee
