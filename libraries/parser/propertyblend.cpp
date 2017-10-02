#include "propertyblend.hpp"
#include "propertyhandler.hpp"
#include "propertyreader.hpp"
#include "propertystring.hpp"
#include "propertywriter.hpp"

#include <base/ccTypes.h>

namespace ee {
using Self = PropertyBlend;

cocos2d::BlendFunc Self::get(const PropertyReader& reader,
                             const Value& defaultValue) const {
    if (not reader.hasProperty(nameSrc())) {
        return defaultValue;
    }
    if (not reader.hasProperty(nameDst())) {
        return defaultValue;
    }
    auto src = reader.getIntProperty(nameSrc());
    auto dst = reader.getIntProperty(nameDst());
    return {static_cast<GLenum>(src), static_cast<GLenum>(dst)};
}

void Self::set(PropertyWriter& writer, const Value& value) const {
    writer.setProperty(nameSrc(), static_cast<int>(value.src));
    writer.setProperty(nameDst(), static_cast<int>(value.dst));
}

bool Self::add(PropertyWriter& writer, const Value& value) const {
    if (not writer.addProperty(nameSrc(), static_cast<int>(value.src))) {
        return false;
    }
    if (not writer.addProperty(nameDst(), static_cast<int>(value.dst))) {
        return false;
    }
    return true;
}

bool Self::addReadHandler(PropertyHandler& propertyHandler,
                          const ReadHandler& handler) const {
    auto handlerSrc = [handler](const cocos2d::Node* node) {
        return static_cast<int>(handler(node).src);
    };
    auto handlerDst = [handler](const cocos2d::Node* node) {
        return static_cast<int>(handler(node).dst);
    };
    if (not propertyHandler.addReadFloatHandler(nameSrc(), handlerSrc)) {
        return false;
    }
    if (not propertyHandler.addReadFloatHandler(nameDst(), handlerDst)) {
        return false;
    }
    return true;
}

bool Self::addWriteHandler(PropertyHandler& propertyHandler,
                           const WriteHandler& handler) const {
    auto handlerSrc = [thiz = *this, &propertyHandler,
                       handler](cocos2d::Node * node, int value) {
        auto dst = propertyHandler.readIntProperty(node, thiz.nameDst());
        return handler(node,
                       {static_cast<GLenum>(value), static_cast<GLenum>(dst)});
    };
    auto handlerDst = [thiz = *this, &propertyHandler,
                       handler](cocos2d::Node * node, int value) {
        auto src = propertyHandler.readIntProperty(node, thiz.nameSrc());
        return handler(node,
                       {static_cast<GLenum>(src), static_cast<GLenum>(value)});
    };
    if (not propertyHandler.addWriteFloatHandler(nameSrc(), handlerSrc)) {
        return false;
    }
    if (not propertyHandler.addWriteFloatHandler(nameDst(), handlerDst)) {
        return false;
    }
    return true;
}
} // namespace ee
