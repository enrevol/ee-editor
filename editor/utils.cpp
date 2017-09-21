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

QJsonValue convertToJson(const cocos2d::Value& value) {
    if (value.getType() == cocos2d::Value::Type::BOOLEAN) {
        return value.asBool();
    }
    if (value.getType() == cocos2d::Value::Type::INTEGER) {
        return value.asInt();
    }
    if (value.getType() == cocos2d::Value::Type::FLOAT) {
        return static_cast<double>(value.asFloat());
    }
    if (value.getType() == cocos2d::Value::Type::STRING) {
        return QString::fromStdString(value.asString());
    }
    if (value.getType() == cocos2d::Value::Type::VECTOR) {
        QJsonArray array;
        for (auto&& v : value.asValueVector()) {
            array.append(convertToJson(v));
        }
        return array;
    }
    if (value.getType() == cocos2d::Value::Type::MAP) {
        QJsonObject dict;
        for (auto&& v : value.asValueMap()) {
            dict.insert(QString::fromStdString(v.first),
                        convertToJson(v.second));
        }
        return dict;
    }
    Q_ASSERT(false);
    return QJsonValue::Null;
}

cocos2d::Value convertToValue(const QJsonValue& json) {
    if (json.isBool()) {
        return cocos2d::Value(json.toBool());
    }
    if (json.isDouble()) {
        auto v = json.toDouble();
        if (int(v) == v) {
            return cocos2d::Value(json.toInt());
        }
        return cocos2d::Value(json.toDouble());
    }
    if (json.isString()) {
        return cocos2d::Value(json.toString().toStdString());
    }
    if (json.isArray()) {
        cocos2d::ValueVector array;
        for (auto v : json.toArray()) {
            array.push_back(convertToValue(v));
        }
        return cocos2d::Value(array);
    }
    if (json.isObject()) {
        cocos2d::ValueMap dict;
        auto obj = json.toObject();
        for (auto iter = obj.begin(); iter != obj.end(); ++iter) {
            dict.emplace(iter.key().toStdString(),
                         convertToValue(iter.value()));
        }
        return cocos2d::Value(dict);
    }
    Q_ASSERT(false);
    return cocos2d::Value::Null;
}
} // namespace ee
