#include "appdelegate.hpp"
#include "rootscene.hpp"

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

    auto context = glView->getOpenGLContext();
    context->makeCurrent(context->surface());

    director->setOpenGLView(glView);

    director->setDisplayStats(true);
    director->setAnimationInterval(1.0f / 30);

    auto&& frameSize = director->getOpenGLView()->getFrameSize();
    qDebug() << "frameSize = " << frameSize.width << " " << frameSize.height;

    auto&& winSize = director->getWinSize();
    qDebug() << "winSize = " << winSize.width << " " << winSize.height;

    auto scene = RootScene::getInstance();
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
