#include "propertypoint.hpp"
#include "propertyhandler.hpp"
#include "propertyreader.hpp"
#include "propertystring.hpp"
#include "propertywriter.hpp"

#include <math/Vec2.h>

namespace ee {
using Self = PropertyPoint;

cocos2d::Point Self::get(const PropertyReader& reader,
                         const Value& defaultValue) const {
    if (not reader.hasProperty(nameX())) {
        return defaultValue;
    }
    if (not reader.hasProperty(nameY())) {
        return defaultValue;
    }
    auto x = reader.getFloatProperty(nameX());
    auto y = reader.getFloatProperty(nameY());
    return Value(x, y);
}

void Self::set(PropertyWriter& writer, const Value& value) const {
    writer.setProperty(nameX(), value.x);
    writer.setProperty(nameY(), value.y);
}

bool Self::add(PropertyWriter& writer, const Value& value) const {
    if (not writer.addProperty(nameX(), value.x)) {
        return false;
    }
    if (not writer.addProperty(nameY(), value.y)) {
        return false;
    }
    return true;
}

bool Self::addReadHandler(PropertyHandler& propertyHandler,
                          const ReadHandler& handler) const {
    auto handlerX = [handler](const cocos2d::Node* node) {
        return handler(node).x;
    };
    auto handlerY = [handler](const cocos2d::Node* node) {
        return handler(node).y;
    };
    if (not propertyHandler.addReadFloatHandler(nameX(), handlerX)) {
        return false;
    }
    if (not propertyHandler.addReadFloatHandler(nameY(), handlerY)) {
        return false;
    }
    return true;
}

bool Self::addWriteHandler(PropertyHandler& propertyHandler,
                           const WriteHandler& handler) const {
    auto handlerX = [thiz = *this, &propertyHandler,
                     handler](cocos2d::Node * node, float value) {
        auto y = propertyHandler.readFloatProperty(node, thiz.nameX());
        return handler(node, cocos2d::Point(value, y));
    };
    auto handlerY = [thiz = *this, &propertyHandler,
                     handler](cocos2d::Node * node, float value) {
        auto x = propertyHandler.readFloatProperty(node, thiz.nameY());
        return handler(node, cocos2d::Point(x, value));
    };
    if (not propertyHandler.addWriteFloatHandler(nameX(), handlerX)) {
        return false;
    }
    if (not propertyHandler.addWriteFloatHandler(nameY(), handlerY)) {
        return false;
    }
    return true;
}
} // namespace ee
