#include "utils.hpp"

#include <parser/value.hpp>

#include <base/CCDirector.h>
#include <platform/CCGLView.h>

namespace ee {
void makeCocosContext() {
    auto director = cocos2d::Director::getInstance();
    auto glView = director->getOpenGLView();
    makeCocosContext(glView);
}

void doneCocosContext() {
    auto director = cocos2d::Director::getInstance();
    auto glView = director->getOpenGLView();
    doneCocosContext(glView);
}

void makeCocosContext(cocos2d::GLView* view) {
    auto oldContext = QOpenGLContext::currentContext();
    auto context = view->getOpenGLContext();
    context->makeCurrent(context->surface());
    auto newContext = QOpenGLContext::currentContext();
    qDebug() << QString::asprintf("Make cocos context: from %p to %p",
                                  static_cast<void*>(oldContext),
                                  static_cast<void*>(newContext));
}

void doneCocosContext(cocos2d::GLView* view) {
    auto oldContext = QOpenGLContext::currentContext();
    auto context = view->getOpenGLContext();
    context->doneCurrent();
    auto newContext = QOpenGLContext::currentContext();
    qDebug() << QString::asprintf("Done cocos context: from %p to %p",
                                  static_cast<void*>(oldContext),
                                  static_cast<void*>(newContext));
}

bool isCurrentContextCocos() {
    auto director = cocos2d::Director::getInstance();
    auto glView = director->getOpenGLView();
    auto context = glView->getOpenGLContext();
    auto currentContext = QOpenGLContext::currentContext();
    return context == currentContext;
}

QJsonValue convertToJson(const Value& value) {
    if (value.isBool()) {
        return value.getBool();
    }
    if (value.isInt()) {
        return value.getInt();
    }
    if (value.isFloat()) {
        return static_cast<double>(value.getFloat());
    }
    if (value.isString()) {
        return QString::fromStdString(value.getString());
    }
    if (value.isList()) {
        QJsonArray array;
        for (auto&& v : value.getList()) {
            array.append(convertToJson(v));
        }
        return array;
    }
    if (value.isMap()) {
        QJsonObject dict;
        for (auto&& v : value.getMap()) {
            dict.insert(QString::fromStdString(v.first),
                        convertToJson(v.second));
        }
        return dict;
    }
    Q_ASSERT(false);
    return QJsonValue::Null;
}

Value convertToValue(const QJsonValue& json) {
    if (json.isBool()) {
        return Value(json.toBool());
    }
    if (json.isDouble()) {
        auto v = json.toDouble();
        constexpr auto eps = std::numeric_limits<double>::epsilon();
        if (std::abs(int(v) - v) < eps) {
            return Value(json.toInt());
        }
        return Value(static_cast<float>(json.toDouble()));
    }
    if (json.isString()) {
        return Value(json.toString().toStdString());
    }
    if (json.isArray()) {
        ValueList array;
        for (auto v : json.toArray()) {
            array.push_back(convertToValue(v));
        }
        return Value(array);
    }
    if (json.isObject()) {
        ValueMap dict;
        auto obj = json.toObject();
        for (auto iter = obj.begin(); iter != obj.end(); ++iter) {
            dict.emplace(iter.key().toStdString(),
                         convertToValue(iter.value()));
        }
        return Value(dict);
    }
    Q_ASSERT(false);
    return Value::Null;
}
} // namespace ee
