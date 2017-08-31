#include "utils.hpp"

#include <base/CCDirector.h>
#include <platform/CCGLView.h>

namespace ee {
void makeCocosContext() {
    auto director = cocos2d::Director::getInstance();
    auto glView = director->getOpenGLView();
    makeCocosContext(glView);
}

void makeCocosContext(cocos2d::GLView* view) {
    auto context = view->getOpenGLContext();
    context->makeCurrent(context->surface());
}
} // namespace ee
