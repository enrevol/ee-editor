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

Self* Self::setDisplayName(const QString& name) {
    ui_->expandButton->setText(name);
    return this;
}

void Self::addInspector(Inspector* inspector) {
    Q_ASSERT(layout() != nullptr);
    ui_->containerWidget->layout()->addWidget(inspector);
    inspectors_.append(inspector);
}

void Self::refreshInspector(const std::vector<const cocos2d::Node*>& nodes) {
    for (auto&& inspector : inspectors_) {
        inspector->refreshInspector(nodes);
    }
}
} // namespace ee
