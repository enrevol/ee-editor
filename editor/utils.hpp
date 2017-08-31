#ifndef EE_EDITOR_UTILS_HPP
#define EE_EDITOR_UTILS_HPP

namespace cocos2d {
class GLView;
} // namespace cocos2d

namespace ee {
void makeCocosContext();

void makeCocosContext(cocos2d::GLView* view);
} // namespace ee

#endif // EE_EDITOR_UTILS_HPP
