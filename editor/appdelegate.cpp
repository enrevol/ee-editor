#include "appdelegate.hpp"

#include <2d/CCLayer.h>
#include <base/CCDirector.h>
#include <platform/CCGLView.h>
#include <platform/qt/CCGLView_Qt.hpp>

namespace ee {
using Self = AppDelegate;

Self::AppDelegate(int argc, char* argv[])
    : Super(argc, argv)
    , openGLView_(nullptr) {}

Self::~AppDelegate() {}

void Self::setOpenGLView(cocos2d::OpenGLWidget* view) {
    openGLView_ = view;
}

bool Self::applicationDidFinishLaunching() {
    qDebug() << __PRETTY_FUNCTION__;

    auto director = cocos2d::Director::getInstance();
    auto glView = cocos2d::GLViewImpl::create(openGLView_);
    glView->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);
    director->setOpenGLView(glView);
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0f / 60);

    auto scene = cocos2d::Scene::create();
    auto layer = cocos2d::LayerColor::create(cocos2d::Color4B::BLUE);
    layer->setContentSize(cocos2d::Size(100, 100));
    scene->addChild(layer);

    director->runWithScene(scene);
    return true;
}

void Self::applicationDidEnterBackground() {
    cocos2d::Director::getInstance()->stopAnimation();
}

void Self::applicationWillEnterForeground() {
    cocos2d::Director::getInstance()->startAnimation();
}
} // namespace ee
