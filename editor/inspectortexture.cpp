#include <ciso646>

#include "inspectortexture.hpp"
#include "selectionpath.hpp"
#include "selectiontree.hpp"
#include "ui_inspectortexture.h"

#include <parser/nodegraph.hpp>
#include <parser/propertyreader.hpp>

namespace ee {
using Self = InspectorTexture;

Self::InspectorTexture(QWidget* parent)
    : Super(parent)
    , ui_(new Ui::InspectorTexture)
    , updating_(false) {
    ui_->setupUi(this);
    connect(ui_->propertyInput, &QLineEdit::textEdited,
            [this](const QString& value) {
                if (updating_) {
                    return;
                }
                Q_EMIT propertyValueChanged(
                    property_->name(), cocos2d::Value(value.toStdString()));
            });
}

Self::~InspectorTexture() {
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
    Q_ASSERT(not updating_);
    updating_ = true;
    ui_->propertyInput->setText(value);
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
