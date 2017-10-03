#include "inspectorgroup.hpp"
#include "ui_inspectorgroup.h"

#include <QVBoxLayout>

namespace ee {
using Self = InspectorGroup;

Self::InspectorGroup(QWidget* parent)
    : Super(parent)
    , ui_(new Ui::InspectorGroup) {
    ui_->setupUi(this);
    connect(ui_->expandButton, &QPushButton::clicked, [this] {
        if (ui_->containerWidget->isHidden()) {
            ui_->containerWidget->setVisible(true);
        } else {
            ui_->containerWidget->setVisible(false);
        }
    });
}

Self::~InspectorGroup() {
    delete ui_;
}

void Self::setDisplayName(const QString& name) {
    ui_->expandButton->setText(name);
}

void Self::addInspector(Inspector* inspector) {
    Q_ASSERT(layout() != nullptr);
    ui_->containerWidget->layout()->addWidget(inspector);
    inspectors_.append(inspector);
    connect(inspector, &Inspector::propertyValueChanged,
            [this](const QString& propertyName, const cocos2d::Value& value) {
                Q_EMIT propertyValueChanged(propertyName, value);
            });
    connect(inspector, &Inspector::propertyNeedRefreshed,
            [this](const QString& propertyName) {
                Q_EMIT propertyNeedRefreshed(propertyName);
            });
}

bool Self::doesHandleProperty(const QString& propertyName) const {
    for (auto&& inspector : inspectors_) {
        if (inspector->doesHandleProperty(propertyName)) {
            return true;
        }
    }
    return false;
}

void Self::refreshInspector(const NodeGraph& graph,
                            const SelectionTree& selection) {
    for (auto&& inspector : inspectors_) {
        inspector->refreshInspector(graph, selection);
    }
}

bool Self::refreshProperty(const NodeGraph& graph,
                           const SelectionTree& selection,
                           const QString& propertyName) {
    int counter = 0;
    for (auto&& inspector : inspectors_) {
        if (inspector->doesHandleProperty(propertyName)) {
            inspector->refreshInspector(graph, selection);
            Q_ASSERT(counter == 0);
            ++counter;
        }
    }
    if (counter == 0) {
        return false;
    }
    return true;
}
} // namespace ee
