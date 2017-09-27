#include "appdelegate.hpp"
#include "rootscene.hpp"
#include "utils.hpp"

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
    qDebug() << Q_FUNC_INFO;
}

Self::~AppDelegate() {
    qDebug() << Q_FUNC_INFO;
}

void Self::setOpenGLView(cocos2d::OpenGLWidget* view) {
    openGLView_ = view;
}

bool Self::applicationDidFinishLaunching() {
    qDebug() << Q_FUNC_INFO;

    auto glView = cocos2d::GLViewImpl::create(openGLView_);
    makeCocosContext(glView);

    auto director = cocos2d::Director::getInstance();
    director->setOpenGLView(glView);
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0f / 30);

    auto&& frameSize = director->getOpenGLView()->getFrameSize();
    qDebug() << "frameSize = " << frameSize.width << " " << frameSize.height;

    auto&& winSize = director->getWinSize();
    qDebug() << "winSize = " << winSize.width << " " << winSize.height;

    auto scene = RootScene::create();
    director->runWithScene(scene);

    return true;
}

void Self::applicationDidEnterBackground() {
    qDebug() << Q_FUNC_INFO;
    cocos2d::Director::getInstance()->stopAnimation();
}

void Self::applicationWillEnterForeground() {
    qDebug() << Q_FUNC_INFO;
    cocos2d::Director::getInstance()->startAnimation();
}
} // namespace ee
