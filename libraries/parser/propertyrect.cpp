#include "propertyrect.hpp"
#include "propertyhandler.hpp"
#include "propertyreader.hpp"
#include "propertystring.hpp"
#include "propertywriter.hpp"

#include <math/CCGeometry.h>

namespace ee {
using Self = PropertyRect;

cocos2d::Rect PropertyRect::get(const PropertyReader& reader,
                                const Value& defaultValue) const {
    if (not reader.hasProperty(nameX())) {
        return defaultValue;
    }
    if (not reader.hasProperty(nameY())) {
        return defaultValue;
    }
    if (not reader.hasProperty(nameW())) {
        return defaultValue;
    }
    if (not reader.hasProperty(nameW())) {
        return defaultValue;
    }
    auto x = reader.getFloatProperty(nameX());
    auto y = reader.getFloatProperty(nameY());
    auto w = reader.getFloatProperty(nameW());
    auto h = reader.getFloatProperty(nameH());
    return Value(x, y, w, h);
}

void Self::set(PropertyWriter& writer, const Value& value) const {
    writer.setProperty(nameX(), value.origin.x);
    writer.setProperty(nameY(), value.origin.y);
    writer.setProperty(nameW(), value.size.width);
    writer.setProperty(nameH(), value.size.height);
}

bool Self::add(PropertyWriter& writer, const Value& value) const {
    if (not writer.addProperty(nameX(), value.origin.x)) {
        return false;
    }
    if (not writer.addProperty(nameY(), value.origin.y)) {
        return false;
    }
    if (not writer.addProperty(nameW(), value.size.width)) {
        return false;
    }
    if (not writer.addProperty(nameH(), value.size.height)) {
        return false;
    }
    return true;
}

bool Self::addReadHandler(PropertyHandler& propertyHandler,
                          const ReadHandler& handler) const {
    auto handlerX = [handler](const cocos2d::Node* node) {
        return handler(node).origin.x;
    };
    auto handlerY = [handler](const cocos2d::Node* node) {
        return handler(node).origin.y;
    };
    auto handlerW = [handler](const cocos2d::Node* node) {
        return handler(node).size.width;
    };
    auto handlerH = [handler](const cocos2d::Node* node) {
        return handler(node).size.height;
    };
    if (not propertyHandler.addReadFloatHandler(nameX(), handlerX)) {
        return false;
    }
    if (not propertyHandler.addReadFloatHandler(nameY(), handlerY)) {
        return false;
    }
    if (not propertyHandler.addReadFloatHandler(nameW(), handlerW)) {
        return false;
    }
    if (not propertyHandler.addReadFloatHandler(nameH(), handlerH)) {
        return false;
    }
    return true;
}

bool Self::addWriteHandler(PropertyHandler& propertyHandler,
                           const WriteHandler& handler) const {
    auto handlerX = [&propertyHandler, handler,
                     thiz = *this](cocos2d::Node * node, float value) {
        auto y = propertyHandler.readFloatProperty(node, thiz.nameY());
        auto w = propertyHandler.readFloatProperty(node, thiz.nameW());
        auto h = propertyHandler.readFloatProperty(node, thiz.nameH());
        return handler(node, cocos2d::Rect(value, y, w, h));
    };
    auto handlerY = [&propertyHandler, handler,
                     thiz = *this](cocos2d::Node * node, float value) {
        auto x = propertyHandler.readFloatProperty(node, thiz.nameX());
        auto w = propertyHandler.readFloatProperty(node, thiz.nameW());
        auto h = propertyHandler.readFloatProperty(node, thiz.nameH());
        return handler(node, cocos2d::Rect(x, value, w, h));
    };
    auto handlerW = [&propertyHandler, handler,
                     thiz = *this](cocos2d::Node * node, float value) {
        auto x = propertyHandler.readFloatProperty(node, thiz.nameX());
        auto y = propertyHandler.readFloatProperty(node, thiz.nameY());
        auto h = propertyHandler.readFloatProperty(node, thiz.nameH());
        return handler(node, cocos2d::Rect(x, y, value, h));
    };
    auto handlerH = [&propertyHandler, handler,
                     thiz = *this](cocos2d::Node * node, float value) {
        auto x = propertyHandler.readFloatProperty(node, thiz.nameX());
        auto y = propertyHandler.readFloatProperty(node, thiz.nameY());
        auto w = propertyHandler.readFloatProperty(node, thiz.nameW());
        return handler(node, cocos2d::Rect(x, y, w, value));
    };
    if (not propertyHandler.addWriteFloatHandler(nameX(), handlerX)) {
        return false;
    }
    if (not propertyHandler.addWriteFloatHandler(nameY(), handlerY)) {
        return false;
    }
    if (not propertyHandler.addWriteFloatHandler(nameW(), handlerW)) {
        return false;
    }
    if (not propertyHandler.addWriteFloatHandler(nameH(), handlerH)) {
        return false;
    }
    return true;
}
} // namespace ee
