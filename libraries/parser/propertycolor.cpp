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
                           const cocos2d::Color3B& defaultValue) const {
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

void Self::set(PropertyWriter& writer, const cocos2d::Color3B& value) const {
    writer.setProperty(nameR(), value.r);
    writer.setProperty(nameG(), value.g);
    writer.setProperty(nameB(), value.b);
}

bool Self::add(PropertyWriter& writer, const cocos2d::Color3B& value) const {
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
    auto rHandler = [handler](const cocos2d::Node* node) {
        return static_cast<int>(handler(node).r);
    };
    auto gHandler = [handler](const cocos2d::Node* node) {
        return static_cast<int>(handler(node).g);
    };
    auto bHandler = [handler](const cocos2d::Node* node) {
        return static_cast<int>(handler(node).b);
    };
    if (not propertyHandler.addReadIntHandler(nameR(), rHandler)) {
        return false;
    }
    if (not propertyHandler.addReadIntHandler(nameG(), gHandler)) {
        return false;
    }
    if (not propertyHandler.addReadIntHandler(nameB(), bHandler)) {
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
    auto rHandler = [handler](cocos2d::Node* node, int value) {
        CC_ASSERT(isInColorRange(value));
        auto&& color = node->getColor();
        return handler(node, cocos2d::Color3B(static_cast<GLubyte>(value),
                                              color.g, color.b));
    };
    auto gHandler = [handler](cocos2d::Node* node, int value) {
        CC_ASSERT(isInColorRange(value));
        auto&& color = node->getColor();
        return handler(
            node,
            cocos2d::Color3B(color.r, static_cast<GLubyte>(value), color.b));
    };
    auto bHandler = [handler](cocos2d::Node* node, int value) {
        CC_ASSERT(isInColorRange(value));
        auto&& color = node->getColor();
        return handler(node, cocos2d::Color3B(color.r, color.g,
                                              static_cast<GLubyte>(value)));
    };
    if (not propertyHandler.addWriteIntHandler(nameR(), rHandler)) {
        return false;
    }
    if (not propertyHandler.addWriteIntHandler(nameG(), gHandler)) {
        return false;
    }
    if (not propertyHandler.addWriteIntHandler(nameB(), bHandler)) {
        return false;
    }
    return true;
}
} // namespace ee
