#include "propertypoint.hpp"
#include "propertyhandler.hpp"
#include "propertyreader.hpp"
#include "propertystring.hpp"
#include "propertywriter.hpp"

#include <math/Vec2.h>

namespace ee {
using Self = PropertyPoint;

cocos2d::Point Self::get(const PropertyReader& reader,
                         const cocos2d::Point& defaultValue) const {
    if (not reader.hasProperty(nameX())) {
        return defaultValue;
    }
    if (not reader.hasProperty(nameY())) {
        return defaultValue;
    }
    auto x = reader.getFloatProperty(nameX());
    auto y = reader.getFloatProperty(nameY());
    return cocos2d::Point(x, y);
}

void Self::set(PropertyWriter& writer, const cocos2d::Point& value) const {
    writer.setProperty(nameX(), value.x);
    writer.setProperty(nameY(), value.y);
}

bool Self::add(PropertyWriter& writer, const cocos2d::Point& value) const {
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
    auto xHandler = [handler](const cocos2d::Node* node) {
        return handler(node).x;
    };
    auto yHandler = [handler](const cocos2d::Node* node) {
        return handler(node).y;
    };
    if (not propertyHandler.addReadFloatHandler(nameX(), xHandler)) {
        return false;
    }
    if (not propertyHandler.addReadFloatHandler(nameY(), yHandler)) {
        return false;
    }
    return true;
}

bool Self::addWriteHandler(PropertyHandler& propertyHandler,
                           const WriteHandler& handler) const {
    auto xName = nameX();
    auto yName = nameY();
    auto xHandler = [&propertyHandler, handler, yName](cocos2d::Node* node,
                                                       float value) {
        auto y = propertyHandler.readFloatProperty(node, yName);
        return handler(node, cocos2d::Point(value, y));
    };
    auto yHandler = [&propertyHandler, handler, xName](cocos2d::Node* node,
                                                       float value) {
        auto x = propertyHandler.readFloatProperty(node, xName);
        return handler(node, cocos2d::Point(x, value));
    };
    if (not propertyHandler.addWriteFloatHandler(nameX(), xHandler)) {
        return false;
    }
    if (not propertyHandler.addWriteFloatHandler(nameY(), yHandler)) {
        return false;
    }
    return true;
}
} // namespace ee
