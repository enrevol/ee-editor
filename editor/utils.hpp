#ifndef EE_EDITOR_UTILS_HPP
#define EE_EDITOR_UTILS_HPP

#include <base/CCValue.h>

#include <QJsonValue>

namespace cocos2d {
class GLView;
} // namespace cocos2d

namespace ee {
void makeCocosContext();

void makeCocosContext(cocos2d::GLView* view);

QJsonValue convertToJson(const cocos2d::Value& value);
cocos2d::Value convertToValue(const QJsonValue& json);
} // namespace ee

#endif // EE_EDITOR_UTILS_HPP
