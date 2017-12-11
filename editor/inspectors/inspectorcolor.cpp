#include <ciso646>

#include "clickablewidget.hpp"
#include "inspectorcolor.hpp"
#include "ui_inspectorcolor.h"

#include <base/ccTypes.h>

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
                [this](const QColor& color) {
                    setPropertyValue(color);
                    Q_EMIT propertyValueChanged(color);
                });
        dialog.exec();
        auto selectedColor = dialog.selectedColor();
        if (not selectedColor.isValid()) {
            setPropertyValue(currentColor);
            Q_EMIT propertyValueChanged(currentColor);
            return;
        }
        setPropertyValue(selectedColor);
        Q_EMIT propertyValueChanged(selectedColor);
    });
    connect(this, &Self::propertyValueChanged, [this](const QColor& color) {
        auto value = cocos2d::Color3B(static_cast<GLubyte>(color.red()),
                                      static_cast<GLubyte>(color.green()),
                                      static_cast<GLubyte>(color.blue()));
        Q_EMIT propertyChanged(
            std::bind(writer_, std::placeholders::_1, value));
    });
}

Self::~InspectorColor() {
    delete ui_;
}

Self* Self::setReader(const Reader& reader) {
    reader_ = reader;
    return this;
}

Self* Self::setWriter(const Writer& writer) {
    writer_ = writer;
    return this;
}

Self* Self::setPropertyValue(const QColor& color) {
    auto pal = ui_->colorWidget->palette();
    pal.setColor(QPalette::ColorRole::Background, color);
    ui_->colorWidget->setPalette(pal);
    auto text = QString("(%1, %2, %3)")
                    .arg(color.red())
                    .arg(color.green())
                    .arg(color.blue());
    ui_->rgbValue->setText(text);
    return this;
}

Self* Self::setPropertyDisplayName(const QString& name) {
    ui_->propertyDisplayName->setText(name);
    return this;
}

void Self::refreshInspector(const std::vector<const cocos2d::Node*>& nodes) {
    auto color = reader_(nodes.at(0));
    auto r = color->r;
    auto g = color->g;
    auto b = color->b;
    setPropertyValue(QColor::fromRgb(r, g, b));
}
} // namespace ee
