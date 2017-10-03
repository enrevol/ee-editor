#include <ciso646>

#include "inspectortexture.hpp"
#include "selectionpath.hpp"
#include "selectiontree.hpp"
#include "ui_inspectortexture.h"

#include <parser/nodegraph.hpp>
#include <parser/propertyreader.hpp>

#include <base/CCDirector.h>
#include <renderer/CCTextureCache.h>

#include <QDebug>
#include <QDragEnterEvent>
#include <QMimeData>

namespace ee {
using Self = InspectorTexture;

Self::InspectorTexture(QWidget* parent)
    : Super(parent)
    , ui_(new Ui::InspectorTexture)
    , updating_(false) {
    ui_->setupUi(this);
    setAcceptDrops(true);
    connect(ui_->propertyInput, &QLineEdit::textChanged,
            [this](const QString& value) {
                if (updating_) {
                    return;
                }
                Q_EMIT propertyValueChanged(
                    propertyTex_->name(), cocos2d::Value(value.toStdString()));
            });
    connect(ui_->clearButton, &QPushButton::clicked,
            [this] { setPropertyValue("", true); });
    connect(ui_->resetSizeButton, &QPushButton::clicked, [this] {
        auto cache = cocos2d::Director::getInstance()->getTextureCache();
        auto texture =
            cache->getTextureForKey(ui_->propertyInput->text().toStdString());
        if (texture != nullptr) {
            Q_EMIT propertyValueChanged(
                propertyW_->name(),
                cocos2d::Value(texture->getContentSize().width));
            Q_EMIT propertyValueChanged(
                propertyH_->name(),
                cocos2d::Value(texture->getContentSize().height));
            Q_EMIT propertyNeedRefreshed(propertyW_->name());
            Q_EMIT propertyNeedRefreshed(propertyH_->name());
        }
    });
}

Self::~InspectorTexture() {
    delete ui_;
}

Self* Self::setPropertyName(const QString& tex, const QString& w,
                            const QString& h) {
    propertyTex_ = std::make_unique<StringPropertyGetter>(tex);
    propertyW_ = std::make_unique<FloatPropertyGetter>(w);
    propertyH_ = std::make_unique<FloatPropertyGetter>(h);
    return this;
}

Self* Self::setPropertyDisplayName(const QString& name) {
    ui_->propertyDisplayName->setText(name);
    return this;
}

void Self::setPropertyValue(const QString& value, bool notify) {
    Q_ASSERT(not updating_);
    if (not notify) {
        updating_ = true;
    }
    ui_->propertyInput->setText(value);
    if (not notify) {
        updating_ = false;
    }
}

bool Self::doesHandleProperty(const QString& propertyName) const {
    if (propertyName != propertyTex_->name()) {
        return false;
    }
    return true;
}

void Self::refreshInspector(const NodeGraph& graph,
                            const SelectionTree& selection) {
    Q_ASSERT(not selection.isEmpty());
    auto&& paths = selection.getPaths();
    auto&& path = paths.front();
    auto value = propertyTex_->get(path.find(graph));
    setPropertyValue(value, false);
}

void Self::dragEnterEvent(QDragEnterEvent* event) {
    auto data = event->mimeData();
    if (data->hasFormat("ee-editor/resources–path")) {
        event->acceptProposedAction();
        event->setDropAction(Qt::DropAction::IgnoreAction);
    }
}

void Self::dragMoveEvent(QDragMoveEvent* event) {
    auto data = event->mimeData();
    if (not data->hasFormat("ee-editor/resources–path")) {
        event->ignore();
        return;
    }
    auto pos = event->pos();
    auto localPos = ui_->propertyInput->mapFrom(this, pos);
    if (not ui_->propertyInput->rect().contains(localPos)) {
        event->ignore();
        return;
    }
    event->acceptProposedAction();
}

void Self::dropEvent(QDropEvent* event) {
    event->acceptProposedAction();
    auto data = event->mimeData();
    auto path = QString(data->data("ee-editor/resources–path"));
    setPropertyValue(path, true);
}
} // namespace ee
