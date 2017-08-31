#include "rootscene.hpp"
#include "utils.hpp"

#include <2d/CCLayer.h>
#include <2d/CCSprite.h>
#include <base/CCRefPtr.h>
#include <renderer/CCGLProgram.h>

namespace ee {
using Self = RootScene;

Self* Self::getInstance() {
    static cocos2d::RefPtr<Self> sharedInstance = create();
    return sharedInstance;
}

bool Self::init() {
    if (not Super::init()) {
        return false;
    }

    sprite_ = cocos2d::Sprite::create();
    sprite_->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
    sprite_->setPositionNormalized(cocos2d::Vec2::ANCHOR_MIDDLE);
    addChild(sprite_);

    return true;
}

void Self::onEnter() {
    Super::onEnter();
}

void Self::onEnterTransitionDidFinish() {
    Super::onEnterTransitionDidFinish();
}

void Self::onExitTransitionDidStart() {
    Super::onExitTransitionDidStart();
}

void Self::onExit() {
    Super::onExit();
}

bool Self::setTexturePath(const QString& path) {
    makeCocosContext();
    auto oldTexture = sprite_->getTexture();
    sprite_->setTexture(path.toStdString());
    if (sprite_->getTexture() == nullptr) {
        sprite_->setTexture(oldTexture);
        return false;
    }
    return true;
}

bool Self::setShader(const QString& vertexShader,
                     const QString& fragmentShader) {
    makeCocosContext();
    auto program = cocos2d::GLProgram::createWithByteArrays(
        vertexShader.toStdString().c_str(),
        fragmentShader.toStdString().c_str());
    if (program != nullptr) {
        sprite_->setGLProgram(program);
        return true;
    }
    return false;
}
} // namespace ee
