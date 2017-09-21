#include "inspectorlistwidget.hpp"
#include "inspectorcontainer.hpp"
#include "sceneselection.hpp"

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
    QFlags<Qt::AlignmentFlag> alignment;
    alignment |= Qt::AlignmentFlag::AlignTop;
    alignment |= Qt::AlignmentFlag::AlignJustify;
    boxLayout->addWidget(inspector, 0, alignment);
    connect(inspector, &Inspector::propertyValueChanged,
            [this](const QString& propertyName, const cocos2d::Value& value) {
                Q_EMIT propertyValueChanged(*nodeGraph_, *selection_,
                                            propertyName, value);
            });
    inspectors_.append(inspector);
}

void Self::clearInspectors() {
    clearLayout(layout());
    inspectors_.clear();
}

void Self::refreshPropertyValue(const NodeGraph& graph,
                                const SceneSelection& selection) {
    nodeGraph_ = &graph;
    selection_ = std::make_unique<SceneSelection>(selection);
    for (auto&& inspector : inspectors_) {
        inspector->refreshPropertyValue(graph, selection);
    }
}
} // namespace ee
