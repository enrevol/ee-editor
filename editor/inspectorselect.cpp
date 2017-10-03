#include <ciso646>

#include "inspectorselect.hpp"
#include "selectionpath.hpp"
#include "selectiontree.hpp"
#include "ui_inspectorselect.h"

#include <parser/nodegraph.hpp>
#include <parser/propertyreader.hpp>

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
                Q_EMIT propertyValueChanged(property_->name(),
                                            cocos2d::Value(index));
            });
}

Self::~InspectorSelect() {
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

Self* Self::addSelection(const QString& name) {
    ui_->propertySelection->addItem(name);
    return this;
}

void Self::setPropertyValue(int value) {
    Q_ASSERT(not updating_);
    updating_ = true;
    ui_->propertySelection->setCurrentIndex(value);
    updating_ = false;
}

bool Self::doesHandleProperty(const QString& propertyName) const {
    if (propertyName != property_->name()) {
        return false;
    }
    return true;
}

void Self::refreshInspector(const NodeGraph& graph,
                            const SelectionTree& selection) {
    Q_ASSERT(not selection.isEmpty());
    auto&& paths = selection.getPaths();
    auto&& path = paths.front();
    auto value = property_->get(path.find(graph));
    setPropertyValue(value);
}
} // namespace ee
