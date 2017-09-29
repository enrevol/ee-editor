#include "nodehighlighter.hpp"

#include <base/CCDirector.h>
#include <renderer/CCTextureCache.h>
#include <ui/UIScale9Sprite.h>

namespace ee {
using Self = NodeHighlighter;

namespace images {
constexpr auto hovered = "selection_box_hovered.png";
constexpr auto selected = "selection_box_locked.png";
} // namespace images

namespace {
void addImages() {
    auto cache = cocos2d::Director::getInstance()->getTextureCache();
    cache->addImage(images::hovered)->setAliasTexParameters();
    cache->addImage(images::selected)->setAliasTexParameters();
}
} // namespace

bool Self::init() {
    if (not Super::init()) {
        return false;
    }

    addImages();

    border_ = cocos2d::ui::Scale9Sprite::create();
    border_->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    border_->setRenderingType(cocos2d::ui::Scale9Sprite::RenderingType::SLICE);
    addChild(border_);
    return true;
}

void Self ::onEnter() {
    Super::onEnter();
}

void Self::onExit() {
    Super::onExit();
}

void Self::hover() {
    border_->setTexture(images::hovered);
    resetInsets();
}

void Self::select() {
    border_->setTexture(images::selected);
    resetInsets();
}

void Self::setRegion(const cocos2d::Rect& rect) {
    border_->setPosition(rect.origin);
    border_->setContentSize(rect.size);
}

void Self::resetInsets() {
    border_->setInsetLeft(1);
    border_->setInsetRight(1);
    border_->setInsetTop(1);
    border_->setInsetBottom(1);
}
} // namespace ee
