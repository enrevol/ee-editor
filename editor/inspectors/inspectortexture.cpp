#include <ciso646>

#include "inspectortexture.hpp"
#include "selection/selectionpath.hpp"
#include "selection/selectiontree.hpp"
#include "ui_inspectortexture.h"

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
                Q_EMIT propertyValueChanged(value);
            });
    connect(ui_->clearButton, &QPushButton::clicked,
            [this] { //
                setPropertyValue("", true);
            });
    connect(ui_->resetSizeButton, &QPushButton::clicked, [this] {
        auto cache = cocos2d::Director::getInstance()->getTextureCache();
        auto texture =
            cache->getTextureForKey(ui_->propertyInput->text().toStdString());
        if (texture != nullptr) {
            Q_EMIT contentSizeResetRequested();
        }
    });
    connect(this, &Self::propertyValueChanged, [this](const QString& value) {
        Q_EMIT propertyChanged(
            std::bind(writer_, std::placeholders::_1, value.toStdString()));
    });
}

Self::~InspectorTexture() {
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

Self* Self::setPropertyValue(const QString& value) {
    return setPropertyValue(value, false);
}

Self* Self::setPropertyDisplayName(const QString& name) {
    ui_->propertyDisplayName->setText(name);
    return this;
}

Self* Self::setPropertyValue(const QString& value, bool notify) {
    Q_ASSERT(not updating_);
    if (not notify) {
        updating_ = true;
    }
    ui_->propertyInput->setText(value);
    if (not notify) {
        updating_ = false;
    }
    return this;
}

void Self::refreshInspector(const std::vector<const cocos2d::Node*>& nodes) {
    auto value = reader_(nodes.at(0));
    setPropertyValue(QString::fromStdString(value), false);
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
