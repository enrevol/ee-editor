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

/// Converts from cocos2d::Value to QJsonValue.
QJsonValue convertToJson(const cocos2d::Value& value);

/// Converts from QJsonValue to cocos2d::Value.
cocos2d::Value convertToValue(const QJsonValue& json);
} // namespace ee

#endif // EE_EDITOR_UTILS_HPP
