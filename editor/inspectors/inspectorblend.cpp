#include <ciso646>

#include "inspectorblend.hpp"
#include "ui_inspectorblend.h"

#include <2d/CCNode.h>
#include <base/CCProtocols.h>
#include <base/ccTypes.h>
#include <platform/CCGL.h>

namespace ee {
using Self = InspectorBlend;

std::map<GLenum, QString> getBlendMap() {
    std::map<GLenum, QString> map;
    map[GL_ZERO] = "ZERO";
    map[GL_ONE] = "ONE";
    map[GL_SRC_ALPHA] = "SRC_ALPHA";
    map[GL_ONE_MINUS_SRC_ALPHA] = "ONE_MINUS_SRC_ALPHA";
    map[GL_SRC_COLOR] = "SRC_COLOR";
    map[GL_ONE_MINUS_SRC_COLOR] = "ONE_MINUS_SRC_COLOR";
    map[GL_DST_ALPHA] = "DST_ALPHA";
    map[GL_ONE_MINUS_DST_ALPHA] = "ONE_MINUS_DST_ALPHA";
    map[GL_DST_COLOR] = "DST_COLOR";
    map[GL_ONE_MINUS_DST_COLOR] = "ONE_MINUS_DST_COLOR";
    return map;
}

Self::InspectorBlend(QWidget* parent)
    : Super(parent)
    , ui_(new Ui::InspectorBlend)
    , updating_(false) {
    ui_->setupUi(this);

    for (auto&& elt : getBlendMap()) {
        auto mode = elt.first;
        auto text = elt.second;
        ui_->propertySrcInput->addItem(text, mode);
        ui_->propertyDstInput->addItem(text, mode);
    }

    connect(ui_->premultipliedAlphaButton, &QPushButton::clicked, [this] {
        auto&& blend = cocos2d::BlendFunc::ALPHA_PREMULTIPLIED;
        auto src = static_cast<int>(blend.src);
        auto dst = static_cast<int>(blend.dst);
        setPropertyValue(src, dst);
        Q_EMIT propertyValueChanged(src, dst);
    });
    connect(ui_->straightAlphaButton, &QPushButton::clicked, [this] {
        auto&& blend = cocos2d::BlendFunc::ALPHA_NON_PREMULTIPLIED;
        auto src = static_cast<int>(blend.src);
        auto dst = static_cast<int>(blend.dst);
        setPropertyValue(src, dst);
        Q_EMIT propertyValueChanged(src, dst);
    });

    connect(ui_->propertySrcInput,
            static_cast<void (QComboBox::*)(int index)>(
                &QComboBox::currentIndexChanged),
            [this](int index) {
                if (updating_) {
                    return;
                }
                src_ = ui_->propertySrcInput
                           ->itemData(index, Qt::ItemDataRole::UserRole)
                           .toInt();
                Q_EMIT propertyValueChanged(src_, dst_);
            });
    connect(ui_->propertyDstInput,
            static_cast<void (QComboBox::*)(int index)>(
                &QComboBox::currentIndexChanged),
            [this](int index) {
                if (updating_) {
                    return;
                }
                dst_ = ui_->propertyDstInput
                           ->itemData(index, Qt::ItemDataRole::UserRole)
                           .toInt();
                Q_EMIT propertyValueChanged(src_, dst_);
            });

    connect(this, &Self::propertyValueChanged, [this](int src, int dst) {
        cocos2d::BlendFunc value;
        value.src = static_cast<GLenum>(src);
        value.dst = static_cast<GLenum>(dst);
        Q_EMIT propertyChanged(
            std::bind(writer_, std::placeholders::_1, value));
    });
}

Self::~InspectorBlend() {
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

Self* Self::setPropertyValue(int src, int dst) {
    Q_ASSERT(not updating_);
    updating_ = true;
    src_ = src;
    dst_ = dst;
    auto srcText = getBlendMap().at(static_cast<GLenum>(src));
    auto dstText = getBlendMap().at(static_cast<GLenum>(dst));
    ui_->propertySrcInput->setCurrentText(srcText);
    ui_->propertyDstInput->setCurrentText(dstText);
    updating_ = false;
    return this;
}

void Self::refreshInspector(const std::vector<const cocos2d::Node*>& nodes) {
    auto value = reader_(nodes.at(0));
    auto src = static_cast<int>(value.src);
    auto dst = static_cast<int>(value.dst);
    setPropertyValue(src, dst);
}
} // namespace ee
