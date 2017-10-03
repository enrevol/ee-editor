#include <ciso646>

#include "inspectorstring.hpp"
#include "selectionpath.hpp"
#include "selectiontree.hpp"
#include "ui_inspectorstring.h"

#include <parser/nodegraph.hpp>
#include <parser/propertyreader.hpp>

namespace ee {
using Self = InspectorString;

Self::InspectorString(QWidget* parent)
    : Super(parent)
    , ui_(new Ui::InspectorString) {
    ui_->setupUi(this);
    connect(ui_->propertyInput, &QLineEdit::textEdited,
            [this](const QString& value) {
                Q_EMIT propertyValueChanged(
                    property_->name(), cocos2d::Value(value.toStdString()));
            });
}

Self::~InspectorString() {
    delete ui_;
}

Self* Self::setPropertyName(const QString& name) {
    property_ = std::make_unique<StringPropertyGetter>(name);
    return this;
}

Self* Self::setPropertyDisplayName(const QString& name) {
    ui_->propertyDisplayName->setText(name);
    return this;
}

void Self::setPropertyValue(const QString& value) {
    ui_->propertyInput->setText(value);
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
