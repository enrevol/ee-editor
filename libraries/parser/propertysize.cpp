#include "propertysize.hpp"
#include "propertyhandler.hpp"
#include "propertyreader.hpp"
#include "propertystring.hpp"
#include "propertywriter.hpp"

#include <math/CCGeometry.h>

namespace ee {
using Self = PropertySize;

cocos2d::Size Self::get(const PropertyReader& reader,
                        const Value& defaultValue) const {
    if (not reader.hasProperty(nameW())) {
        return defaultValue;
    }
    if (not reader.hasProperty(nameH())) {
        return defaultValue;
    }
    auto w = reader.getFloatProperty(nameW());
    auto h = reader.getFloatProperty(nameH());
    return Value(w, h);
}

void Self::set(PropertyWriter& writer, const Value& value) const {
    writer.setProperty(nameW(), value.width);
    writer.setProperty(nameH(), value.height);
}

bool Self::add(PropertyWriter& writer, const Value& value) const {
    if (not writer.addProperty(nameW(), value.width)) {
        return false;
    }
    if (not writer.addProperty(nameH(), value.height)) {
        return false;
    }
    return true;
}

bool Self::addReadHandler(PropertyHandler& propertyHandler,
                          const ReadHandler& handler) const {
    auto handlerW = [handler](const cocos2d::Node* node) {
        return handler(node).width;
    };
    auto handlerH = [handler](const cocos2d::Node* node) {
        return handler(node).height;
    };
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
    auto handlerW = [thiz = *this, &propertyHandler,
                     handler](cocos2d::Node * node, float value) {
        auto h = propertyHandler.readFloatProperty(node, thiz.nameH());
        return handler(node, Value(value, h));
    };
    auto handlerH = [thiz = *this, &propertyHandler,
                     handler](cocos2d::Node * node, float value) {
        auto w = propertyHandler.readFloatProperty(node, thiz.nameW());
        return handler(node, Value(w, value));
    };
    if (not propertyHandler.addWriteFloatHandler(nameW(), handlerW)) {
        return false;
    }
    if (not propertyHandler.addWriteFloatHandler(nameH(), handlerH)) {
        return false;
    }
    return true;
}
} // namespace ee
