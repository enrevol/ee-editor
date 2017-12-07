#include <ciso646>

#include "inspectorlistwidget.hpp"

#include <QLayout>
#include <QLayoutItem>

namespace ee {
using Self = InspectorListWidget;

namespace {
/// https://stackoverflow.com/questions/4857188/clearing-a-layout-in-qt
void clearLayout(QLayout* layout) {
    while (true) {
        auto item = layout->takeAt(0);
        if (item == nullptr) {
            break;
        }
        if (item->layout() != nullptr) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget() != nullptr) {
            delete item->widget();
        }
        delete item;
    }
}
} // namespace

Self::InspectorListWidget(QWidget* parent)
    : Super(parent) {}

Self::~InspectorListWidget() {}

void Self::addInspector(Inspector* inspector) {
    auto boxLayout = dynamic_cast<QBoxLayout*>(layout());
    boxLayout->addWidget(inspector);
    connections_ << connect(inspector, &Inspector::propertyChanged,
                            [this](const Applier& applier) { //
                                Q_EMIT propertyChanged(applier);
                            });
    inspectors_.append(inspector);
}

void Self::clearInspectors() {
    clearLayout(layout());
    inspectors_.clear();
    for (auto&& connection : connections_) {
        disconnect(connection);
    }
    connections_.clear();
}

void Self::refreshInspector(const std::vector<const cocos2d::Node*>& nodes) {
    for (auto&& inspector : inspectors_) {
        inspector->refreshInspector(nodes);
    }
}
} // namespace ee
