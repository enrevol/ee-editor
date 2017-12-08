#include <sstream>

#include "rulerline.hpp"

#include <2d/CCLayer.h>
#include <ui/UIText.h>

namespace ee {
using Self = RulerLine;

Self* Self::create() {
    auto result = new Self();
    result->init();
    result->autorelease();
    return result;
}

bool Self::init() {
    if (not Super::init()) {
        return false;
    }
    coordLabel_ = cocos2d::ui::Text::create();
    coordLabel_->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    coordLabel_->setPosition(cocos2d::Point(5, 5));
    addChild(coordLabel_);
    hideCoordinate();

    layerColor_ =
        cocos2d::LayerColor::create(cocos2d::Color4B(100, 100, 100, 255));
    layerColor_->setContentSize(cocos2d::Size::ZERO);
    addChild(layerColor_);

    vertical_ = true;
    return true;
}

void Self::onEnter() {
    Super::onEnter();
}

void Self::onExit() {
    Super::onExit();
}

Self* Self::setCoordinate(float value) {
    std::stringstream ss; // Remove trailing zeroes.
    ss << value;
    coordLabel_->setString(ss.str());
    coordLabel_->setVisible(true);
    return this;
}

Self* Self::hideCoordinate() {
    coordLabel_->setVisible(false);
    return this;
}

Self* Self::setLineOpacity(int opacity) {
    layerColor_->setOpacity(static_cast<GLubyte>(opacity));
    return this;
}

Self* Self::setLineWidth(float width) {
    lineWidth_ = width;
    updateLine();
    return this;
}

Self* Self::alignHorizontal(float length) {
    lineLength_ = length;
    vertical_ = false;
    updateLine();
    return this;
}

Self* Self::alignVertical(float length) {
    lineLength_ = length;
    vertical_ = true;
    updateLine();
    return this;
}

void Self::updateLine() {
    if (vertical_) {
        layerColor_->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
        layerColor_->setContentSize(cocos2d::Size(lineWidth_, lineLength_));
    } else {
        layerColor_->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
        layerColor_->setContentSize(cocos2d::Size(lineLength_, lineWidth_));
    }
}
} // namespace ee
