#include "inspectorlistwidget.hpp"
#include "inspectorcontainer.hpp"

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

void Self::addInspector(InspectorContainer* inspector) {
    auto boxLayout = dynamic_cast<QBoxLayout*>(layout());
    QFlags<Qt::AlignmentFlag> alignment;
    alignment |= Qt::AlignmentFlag::AlignTop;
    alignment |= Qt::AlignmentFlag::AlignJustify;
    boxLayout->addWidget(inspector, 0, alignment);
}

void Self::clearInspectors() {
    clearLayout(layout());
}
} // namespace ee
