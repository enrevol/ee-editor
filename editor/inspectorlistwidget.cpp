#include "inspectorlistwidget.hpp"
#include "inspector.hpp"
#include "inspectorgroup.hpp"
#include "inspectorloaderlibrary.hpp"
#include "selectionpath.hpp"
#include "selectiontree.hpp"

#include <parser/nodegraph.hpp>

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
    connect(inspector, &Inspector::propertyValueChanged,
            [this](const QString& propertyName, const cocos2d::Value& value) {
                if (selection_->isEmpty()) {
                    return;
                }
                Q_EMIT propertyValueChanged(selection_->getPaths().front(),
                                            propertyName, value);
            });
    inspectors_.append(inspector);
}

void Self::clearInspectors() {
    clearLayout(layout());
    inspectors_.clear();
}

void Self::setSelection(const NodeGraph& graph,
                        const SelectionTree& selection) {
    nodeGraph_ = &graph;
    selection_ = std::make_unique<SelectionTree>(selection);
    clearInspectors();
    if (selection.isEmpty()) {
        return;
    }
    auto library = InspectorLoaderLibrary();
    library.addDefaultLoaders();
    auto&& path = selection.getPaths().front();
    auto&& subGraph = path.find(graph);
    auto&& className = subGraph.getBaseClass();
    auto&& inspectors =
        library.createInspectors(QString::fromStdString(className));
    for (auto&& inspector : inspectors) {
        addInspector(inspector);
    }

    refreshPropertyValue(graph, selection);
}

void Self::refreshPropertyValue(const NodeGraph& graph,
                                const SelectionTree& selection) {
    for (auto&& inspector : inspectors_) {
        inspector->refreshPropertyValue(graph, selection);
    }
}

bool Self::refreshPropertyValue(const NodeGraph& graph,
                                const SelectionTree& selection,
                                const QString& propertyName) {
    Q_ASSERT(not selection.isEmpty());
    for (auto&& inspector : inspectors_) {
        if (inspector->refreshPropertyValue(graph, selection, propertyName)) {
            return true;
        }
    }
    return false;
}
} // namespace ee
