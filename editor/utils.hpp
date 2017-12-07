#ifndef EE_EDITOR_UTILS_HPP
#define EE_EDITOR_UTILS_HPP

#include <QJsonValue>

namespace cocos2d {
class GLView;
} // namespace cocos2d

namespace ee {
class Value;

void makeCocosContext();
void doneCocosContext();

void makeCocosContext(cocos2d::GLView* view);
void doneCocosContext(cocos2d::GLView* view);

bool isCurrentContextCocos();

/// Converts from cocos2d::Value to QJsonValue.
QJsonValue convertToJson(const Value& value);

/// Converts from QJsonValue to cocos2d::Value.
Value convertToValue(const QJsonValue& json);
} // namespace ee

#endif // EE_EDITOR_UTILS_HPP
