#include "inspectorcolor.hpp"
#include "clickablewidget.hpp"
#include "selectionpath.hpp"
#include "selectiontree.hpp"
#include "ui_inspectorcolor.h"

#include <parser/nodegraph.hpp>
#include <parser/propertyreader.hpp>

#include <QColorDialog>

namespace ee {
using Self = InspectorColor;

Self::InspectorColor(QWidget* parent)
    : Super(parent)
    , ui_(new Ui::InspectorColor) {
    ui_->setupUi(this);
    ui_->colorWidget->setAutoFillBackground(true);
    connect(ui_->colorWidget, &ClickableWidget::clicked, [this] {
        auto pal = ui_->colorWidget->palette();
        auto currentColor = pal.color(QPalette::ColorRole::Background);
        QColorDialog dialog(currentColor, this);
        connect(&dialog, &QColorDialog::currentColorChanged,
                [this](const QColor& color) { changeColor(color); });
        dialog.exec();
        auto selectedColor = dialog.selectedColor();
        if (not selectedColor.isValid()) {
            changeColor(currentColor);
            return;
        }
        changeColor(selectedColor);
    });
}

Self::~InspectorColor() {
    delete ui_;
}

Self* Self::setPropertyName(const QString& r, const QString& g,
                            const QString& b) {
    propertyR_ = std::make_unique<IntPropertyGetter>(r);
    propertyG_ = std::make_unique<IntPropertyGetter>(g);
    propertyB_ = std::make_unique<IntPropertyGetter>(b);
    return this;
}

Self* Self::setPropertyDisplayName(const QString& name) {
    ui_->propertyDisplayName->setText(name);
    return this;
}

void Self::setPropertyValue(int r, int g, int b) {
    auto pal = ui_->colorWidget->palette();
    pal.setColor(QPalette::ColorRole::Background, QColor::fromRgb(r, g, b));
    ui_->colorWidget->setPalette(pal);
}

void Self::changeColor(const QColor& color) {
    auto r = color.red();
    auto g = color.green();
    auto b = color.blue();
    setPropertyValue(r, g, b);
    Q_EMIT propertyValueChanged(propertyR_->name(), cocos2d::Value(r));
    Q_EMIT propertyValueChanged(propertyG_->name(), cocos2d::Value(g));
    Q_EMIT propertyValueChanged(propertyB_->name(), cocos2d::Value(b));
}

void Self::refreshPropertyValue(const NodeGraph& graph,
                                const SelectionTree& selection) {
    Q_ASSERT(not selection.isEmpty());
    auto&& paths = selection.getPaths();
    auto&& path = paths.front();
    auto r = propertyR_->get(path.find(graph));
    auto g = propertyG_->get(path.find(graph));
    auto b = propertyB_->get(path.find(graph));
    setPropertyValue(r, g, b);
}
} // namespace ee
