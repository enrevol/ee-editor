#include "propertycolor.hpp"
#include "propertyhandler.hpp"
#include "propertyreader.hpp"
#include "propertysize.hpp"
#include "propertystring.hpp"
#include "propertywriter.hpp"

#include <2d/CCNode.h>
#include <base/ccTypes.h>

namespace ee {
using Self = PropertyColor;

cocos2d::Color3B Self::get(const PropertyReader& reader,
                           const Value& defaultValue) const {
    if (not reader.hasProperty(nameR())) {
        return defaultValue;
    }
    if (not reader.hasProperty(nameG())) {
        return defaultValue;
    }
    if (not reader.hasProperty(nameB())) {
        return defaultValue;
    }
    auto r = static_cast<GLubyte>(reader.getIntProperty(nameR()));
    auto g = static_cast<GLubyte>(reader.getIntProperty(nameG()));
    auto b = static_cast<GLubyte>(reader.getIntProperty(nameB()));
    return cocos2d::Color3B(r, g, b);
}

void Self::set(PropertyWriter& writer, const Value& value) const {
    writer.setProperty(nameR(), value.r);
    writer.setProperty(nameG(), value.g);
    writer.setProperty(nameB(), value.b);
}

bool Self::add(PropertyWriter& writer, const Value& value) const {
    if (not writer.addProperty(nameR(), value.r)) {
        return false;
    }
    if (not writer.addProperty(nameG(), value.g)) {
        return false;
    }
    if (not writer.addProperty(nameB(), value.b)) {
        return false;
    }
    return true;
}

bool Self::addReadHandler(PropertyHandler& propertyHandler,
                          const ReadHandler& handler) const {
    auto handlerR = [handler](const cocos2d::Node* node) {
        return static_cast<int>(handler(node).r);
    };
    auto handlerG = [handler](const cocos2d::Node* node) {
        return static_cast<int>(handler(node).g);
    };
    auto handlerB = [handler](const cocos2d::Node* node) {
        return static_cast<int>(handler(node).b);
    };
    if (not propertyHandler.addReadIntHandler(nameR(), handlerR)) {
        return false;
    }
    if (not propertyHandler.addReadIntHandler(nameG(), handlerG)) {
        return false;
    }
    if (not propertyHandler.addReadIntHandler(nameB(), handlerB)) {
        return false;
    }
    return true;
}

namespace {
bool isInColorRange(int value) {
    auto min = std::numeric_limits<GLubyte>::min();
    auto max = std::numeric_limits<GLubyte>::max();
    if (value < static_cast<int>(min)) {
        return false;
    }
    if (value > static_cast<int>(max)) {
        return false;
    }
    return true;
}
} // namespace

bool Self::addWriteHandler(PropertyHandler& propertyHandler,
                           const WriteHandler& handler) const {
    auto handlerR = [thiz = *this, &propertyHandler,
                     handler](cocos2d::Node * node, int value) {
        CC_ASSERT(isInColorRange(value));
        auto g = propertyHandler.readIntProperty(node, thiz.nameG());
        auto b = propertyHandler.readIntProperty(node, thiz.nameB());
        return handler(node, cocos2d::Color3B(static_cast<GLubyte>(value),
                                              static_cast<GLubyte>(g),
                                              static_cast<GLubyte>(b)));
    };
    auto handlerG = [thiz = *this, &propertyHandler,
                     handler](cocos2d::Node * node, int value) {
        CC_ASSERT(isInColorRange(value));
        auto r = propertyHandler.readIntProperty(node, thiz.nameR());
        auto b = propertyHandler.readIntProperty(node, thiz.nameB());
        return handler(node, cocos2d::Color3B(static_cast<GLubyte>(r),
                                              static_cast<GLubyte>(value),
                                              static_cast<GLubyte>(b)));
    };
    auto handlerB = [thiz = *this, &propertyHandler,
                     handler](cocos2d::Node * node, int value) {
        CC_ASSERT(isInColorRange(value));
        auto r = propertyHandler.readIntProperty(node, thiz.nameR());
        auto g = propertyHandler.readIntProperty(node, thiz.nameG());
        return handler(node, cocos2d::Color3B(static_cast<GLubyte>(r),
                                              static_cast<GLubyte>(g),
                                              static_cast<GLubyte>(value)));
    };
    if (not propertyHandler.addWriteIntHandler(nameR(), handlerR)) {
        return false;
    }
    if (not propertyHandler.addWriteIntHandler(nameG(), handlerG)) {
        return false;
    }
    if (not propertyHandler.addWriteIntHandler(nameB(), handlerB)) {
        return false;
    }
    return true;
}
} // namespace ee
