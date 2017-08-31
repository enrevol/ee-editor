#include "appdelegate.hpp"

#include <2d/CCActionInterval.h>
#include <2d/CCLabel.h>
#include <2d/CCLayer.h>
#include <base/CCDirector.h>
#include <platform/CCGLView.h>
#include <platform/qt/CCGLView_Qt.hpp>

namespace ee {
using Self = AppDelegate;

Self::AppDelegate(int argc, char* argv[])
    : Super(argc, argv)
    , openGLView_(nullptr) {
    qDebug() << __PRETTY_FUNCTION__;
}

Self::~AppDelegate() {
    qDebug() << __PRETTY_FUNCTION__;
}

void Self::setOpenGLView(cocos2d::OpenGLWidget* view) {
    openGLView_ = view;
}

bool Self::applicationDidFinishLaunching() {
    qDebug() << __PRETTY_FUNCTION__;

    auto director = cocos2d::Director::getInstance();

    auto glView = cocos2d::GLViewImpl::create(openGLView_);
    glView->setDesignResolutionSize(480, 320, ResolutionPolicy::NO_BORDER);
    director->setOpenGLView(glView);

    director->setDisplayStats(true);
    director->setAnimationInterval(1.0f / 30);

    auto&& frameSize = director->getOpenGLView()->getFrameSize();
    qDebug() << "frameSize = " << frameSize.width << " " << frameSize.height;

    auto&& winSize = director->getWinSize();
    qDebug() << "winSize = " << winSize.width << " " << winSize.height;

    // director->setContentScaleFactor(4.0f);

    auto scene = cocos2d::Scene::create();

    auto action = cocos2d::RepeatForever::create(cocos2d::Sequence::create(
        cocos2d::ScaleTo::create(1.0f, 2.0f),
        cocos2d::ScaleTo::create(1.0f, 1.0f), nullptr));

    auto label =
        cocos2d::Label::createWithSystemFont("Hello world!", "Verdana", 50);
    label->setPositionNormalized(cocos2d::Vec2::ANCHOR_MIDDLE);
    label->runAction(action->clone());

    auto layer0 = cocos2d::LayerColor::create(cocos2d::Color4B::BLUE);
    layer0->setContentSize(cocos2d::Size(100, 100));
    layer0->setIgnoreAnchorPointForPosition(false);
    layer0->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    layer0->setPositionNormalized(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    layer0->runAction(action->clone());

    auto layer1 = cocos2d::LayerColor::create(cocos2d::Color4B::RED);
    layer1->setContentSize(cocos2d::Size(100, 100));
    layer1->setIgnoreAnchorPointForPosition(false);
    layer1->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_RIGHT);
    layer1->setPositionNormalized(cocos2d::Vec2::ANCHOR_BOTTOM_RIGHT);
    layer1->runAction(action->clone());
    layer1->setPosition(cocos2d::Point(winSize.width, 0));

    auto layer2 = cocos2d::LayerColor::create(cocos2d::Color4B::YELLOW);
    layer2->setContentSize(cocos2d::Size(100, 100));
    layer2->setIgnoreAnchorPointForPosition(false);
    layer2->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    layer2->setPositionNormalized(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    layer2->runAction(action->clone());

    auto layer3 = cocos2d::LayerColor::create(cocos2d::Color4B::GREEN);
    layer3->setContentSize(cocos2d::Size(100, 100));
    layer3->setIgnoreAnchorPointForPosition(false);
    layer3->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_RIGHT);
    layer3->setPositionNormalized(cocos2d::Vec2::ANCHOR_TOP_RIGHT);
    layer3->runAction(action->clone());

    scene->addChild(label);
    scene->addChild(layer0);
    scene->addChild(layer1);
    scene->addChild(layer2);
    scene->addChild(layer3);

    director->runWithScene(scene);
    return true;
}

void Self::applicationDidEnterBackground() {
    qDebug() << __PRETTY_FUNCTION__;
    cocos2d::Director::getInstance()->stopAnimation();
}

void Self::applicationWillEnterForeground() {
    qDebug() << __PRETTY_FUNCTION__;
    cocos2d::Director::getInstance()->startAnimation();
}
} // namespace ee
