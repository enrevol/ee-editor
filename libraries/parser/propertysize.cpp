#include "propertysize.hpp"
#include "propertyhandler.hpp"
#include "propertyreader.hpp"
#include "propertystring.hpp"
#include "propertywriter.hpp"

#include <math/CCGeometry.h>

namespace ee {
using Self = PropertySize;

cocos2d::Size PropertySize::get(const PropertyReader& reader,
                                const cocos2d::Size& defaultValue) const {
    if (not reader.hasProperty(nameX())) {
        return defaultValue;
    }
    if (not reader.hasProperty(nameY())) {
        return defaultValue;
    }
    auto x = reader.getFloatProperty(nameX());
    auto y = reader.getFloatProperty(nameY());
    return cocos2d::Size(x, y);
}

void PropertySize::set(PropertyWriter& writer,
                       const cocos2d::Size& value) const {
    writer.setProperty(nameX(), value.width);
    writer.setProperty(nameY(), value.height);
}

bool PropertySize::add(PropertyWriter& writer,
                       const cocos2d::Size& value) const {
    if (not writer.addProperty(nameX(), value.width)) {
        return false;
    }
    if (not writer.addProperty(nameY(), value.height)) {
        return false;
    }
    return true;
}

bool PropertySize::addReadHandler(PropertyHandler& propertyHandler,
                                  const ReadHandler& handler) const {
    auto xHandler = [handler](const cocos2d::Node* node) {
        return handler(node).width;
    };
    auto yHandler = [handler](const cocos2d::Node* node) {
        return handler(node).height;
    };
    if (not propertyHandler.addReadFloatHandler(nameX(), xHandler)) {
        return false;
    }
    if (not propertyHandler.addReadFloatHandler(nameY(), yHandler)) {
        return false;
    }
    return true;
}

bool PropertySize::addWriteHandler(PropertyHandler& propertyHandler,
                                   const WriteHandler& handler) const {
    auto xName = nameX();
    auto yName = nameY();
    auto xHandler = [&propertyHandler, handler, yName](cocos2d::Node* node,
                                                       float value) {
        auto y = propertyHandler.readFloatProperty(node, yName);
        return handler(node, cocos2d::Size(value, y));
    };
    auto yHandler = [&propertyHandler, handler, xName](cocos2d::Node* node,
                                                       float value) {
        auto x = propertyHandler.readFloatProperty(node, xName);
        return handler(node, cocos2d::Size(x, value));
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
