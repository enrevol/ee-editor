#include <ciso646>

#include "gizmo.hpp"

#include <2d/CCSprite.h>
#include <base/CCDirector.h>
#include <base/CCEventDispatcher.h>
#include <base/CCEventListenerMouse.h>
#include <base/CCEventListenerTouch.h>
#include <renderer/CCTextureCache.h>

namespace ee {
using Self = Gizmo;

namespace images {
constexpr auto box = "gizmo_box.png";
constexpr auto box_hovered = "gizmo_box_hovered.png";
constexpr auto box_locked = "gizmo_box_locked.png";
constexpr auto x_axis = "gizmo_x_axis.png";
constexpr auto x_axis_hovered = "gizmo_x_axis_hovered.png";
constexpr auto x_axis_locked = "gizmo_x_axis_locked.png";
constexpr auto y_axis = "gizmo_y_axis.png";
constexpr auto y_axis_hovered = "gizmo_y_axis_hovered.png";
constexpr auto y_axis_locked = "gizmo_y_axis_locked.png";
} // namespace images

struct Capture {
    static constexpr int None = 0;
    static constexpr int X = 1 << 0;
    static constexpr int Y = 1 << 1;
    static constexpr int Box = X | Y;
};

namespace {
void addImages() {
    auto cache = cocos2d::Director::getInstance()->getTextureCache();
    cache->addImage(images::box)->setAliasTexParameters();
    cache->addImage(images::box_hovered)->setAliasTexParameters();
    cache->addImage(images::box_locked)->setAliasTexParameters();
    cache->addImage(images::x_axis)->setAliasTexParameters();
    cache->addImage(images::x_axis_hovered)->setAliasTexParameters();
    cache->addImage(images::x_axis_locked)->setAliasTexParameters();
    cache->addImage(images::y_axis)->setAliasTexParameters();
    cache->addImage(images::y_axis_hovered)->setAliasTexParameters();
    cache->addImage(images::y_axis_locked)->setAliasTexParameters();
}

cocos2d::Sprite* createBox() {
    auto sprite = cocos2d::Sprite::create(images::box);
    sprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    return sprite;
}

cocos2d::Sprite* createAxisX() {
    auto sprite = cocos2d::Sprite::create(images::x_axis);
    sprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
    return sprite;
}

cocos2d::Sprite* createAxisY() {
    auto sprite = cocos2d::Sprite::create(images::y_axis);
    sprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
    return sprite;
}
} // namespace

bool Self::init() {
    if (not Super::init()) {
        return false;
    }

    capturedMask_ = Capture::None;

    addImages();

    axisX_ = createAxisX();
    addChild(axisX_);

    axisY_ = createAxisY();
    addChild(axisY_);

    box_ = createBox();
    box_->setPosition(cocos2d::Point(-0.5f, -0.5f)); // Half width of the line.
    addChild(box_);

    mouseListener_ = cocos2d::EventListenerMouse::create();
    mouseListener_->onMouseDown =
        std::bind(&Self::mousePressed, this, std::placeholders::_1);
    mouseListener_->onMouseMove =
        std::bind(&Self::mouseMoved, this, std::placeholders::_1);
    mouseListener_->onMouseUp =
        std::bind(&Self::mouseReleased, this, std::placeholders::_1);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener_,
                                                                 this);

    return true;
}

void Self::onEnter() {
    Super::onEnter();
}

void Self::onExit() {
    Super::onExit();
}

void Self::resetImages() {
    box_->setTexture(images::box);
    axisX_->setTexture(images::x_axis);
    axisY_->setTexture(images::y_axis);
}

void Self::mousePressed(cocos2d::EventMouse* event) {
    auto position = convertToNodeSpace(event->getLocation());
    capturedMask_ = Capture::None;
    if (box_->getBoundingBox().containsPoint(position)) {
        capturedMask_ |= Capture::Box;
        box_->setTexture(images::box_locked);
    } else if (axisX_->getBoundingBox().containsPoint(position)) {
        capturedMask_ |= Capture::X;
        axisX_->setTexture(images::x_axis_locked);
    } else if (axisY_->getBoundingBox().containsPoint(position)) {
        capturedMask_ |= Capture::Y;
        axisY_->setTexture(images::y_axis_locked);
    }
}

void Self::mouseMoved(cocos2d::EventMouse* event) {
    if (capturedMask_ != Capture::None) {
        auto delta = event->getDelta();
        if ((capturedMask_ | Capture::X) != capturedMask_) {
            delta.x = 0;
        }
        if ((capturedMask_ | Capture::Y) != capturedMask_) {
            delta.y = 0;
        }
        Q_EMIT moveBy(delta);
    } else {
        resetImages();
        auto position = convertToNodeSpace(event->getLocation());
        if (box_->getBoundingBox().containsPoint(position)) {
            box_->setTexture(images::box_hovered);
        } else if (axisX_->getBoundingBox().containsPoint(position)) {
            axisX_->setTexture(images::x_axis_hovered);
        } else if (axisY_->getBoundingBox().containsPoint(position)) {
            axisY_->setTexture(images::y_axis_hovered);
        }
    }
}

void Self::mouseReleased(cocos2d::EventMouse* event) {
    Q_UNUSED(event);
    resetImages();
    capturedMask_ = Capture::None;
}
} // namespace ee
