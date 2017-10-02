#include <ciso646>

#include "inspectorblend.hpp"
#include "selectionpath.hpp"
#include "selectiontree.hpp"
#include "ui_inspectorblend.h"

#include <base/ccTypes.h>

#include <parser/nodegraph.hpp>
#include <parser/propertyreader.hpp>
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
        auto src =
            static_cast<int>(cocos2d::BlendFunc::ALPHA_PREMULTIPLIED.src);
        auto dst =
            static_cast<int>(cocos2d::BlendFunc::ALPHA_PREMULTIPLIED.dst);
        setPropertyValue(src, dst);
        Q_EMIT propertyValueChanged(propertySrc_->name(), cocos2d::Value(src));
        Q_EMIT propertyValueChanged(propertyDst_->name(), cocos2d::Value(dst));
    });
    connect(ui_->straightAlphaButton, &QPushButton::clicked, [this] {
        auto src =
            static_cast<int>(cocos2d::BlendFunc::ALPHA_NON_PREMULTIPLIED.src);
        auto dst =
            static_cast<int>(cocos2d::BlendFunc::ALPHA_NON_PREMULTIPLIED.dst);
        setPropertyValue(src, dst);
        Q_EMIT propertyValueChanged(propertySrc_->name(), cocos2d::Value(src));
        Q_EMIT propertyValueChanged(propertyDst_->name(), cocos2d::Value(dst));
    });

    connect(ui_->propertySrcInput,
            static_cast<void (QComboBox::*)(int index)>(
                &QComboBox::currentIndexChanged),
            [this](int index) {
                if (updating_) {
                    return;
                }
                auto mode = ui_->propertySrcInput
                                ->itemData(index, Qt::ItemDataRole::UserRole)
                                .toInt();
                Q_EMIT propertyValueChanged(propertySrc_->name(),
                                            cocos2d::Value(mode));
            });
    connect(ui_->propertyDstInput,
            static_cast<void (QComboBox::*)(int index)>(
                &QComboBox::currentIndexChanged),
            [this](int index) {
                if (updating_) {
                    return;
                }
                auto mode = ui_->propertyDstInput
                                ->itemData(index, Qt::ItemDataRole::UserRole)
                                .toInt();
                Q_EMIT propertyValueChanged(propertyDst_->name(),
                                            cocos2d::Value(mode));
            });
}

Self::~InspectorBlend() {
    delete ui_;
}

Self* Self::setPropertyName(const QString& src, const QString& dst) {
    propertySrc_ = std::make_unique<IntPropertyGetter>(src);
    propertyDst_ = std::make_unique<IntPropertyGetter>(dst);
    return this;
}

void Self::setPropertyValue(int src, int dst) {
    Q_ASSERT(not updating_);
    updating_ = true;
    auto srcText = getBlendMap().at(static_cast<GLenum>(src));
    auto dstText = getBlendMap().at(static_cast<GLenum>(dst));
    ui_->propertySrcInput->setCurrentText(srcText);
    ui_->propertyDstInput->setCurrentText(dstText);
    updating_ = false;
}

void Self::refreshPropertyValue(const NodeGraph& graph,
                                const SelectionTree& selection) {
    Q_ASSERT(not selection.isEmpty());
    auto&& paths = selection.getPaths();
    auto&& path = paths.front();
    auto src = propertySrc_->get(path.find(graph));
    auto dst = propertyDst_->get(path.find(graph));
    setPropertyValue(src, dst);
}

bool Self::refreshPropertyValue(const NodeGraph& graph,
                                const SelectionTree& selection,
                                const QString& propertyName) {
    if (propertyName != propertySrc_->name() &&
        propertyName != propertyDst_->name()) {
        return false;
    }
    refreshPropertyValue(graph, selection);
    return true;
}
} // namespace ee
