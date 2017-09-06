#include <ciso646>

#include "propertyhandler.hpp"

namespace ee {
using Self = PropertyHandler;

bool Self::readBoolProperty(const std::string& name, bool defaultValue) const {
    if (readHandlers_.count(name) == 0) {
        CC_ASSERT(false);
        return defaultValue;
    }
    auto&& handler = readHandlers_.at(name);
    auto value = handler();
    CC_ASSERT(value.getType() == cocos2d::Value::Type::BOOLEAN);
    return value.asBool();
}

int Self::readIntProperty(const std::string& name, int defaultValue) const {
    if (readHandlers_.count(name) == 0) {
        CC_ASSERT(false);
        return defaultValue;
    }
    auto&& handler = readHandlers_.at(name);
    auto value = handler();
    CC_ASSERT(value.getType() == cocos2d::Value::Type::INTEGER);
    return value.asInt();
}

float Self::readFloatProperty(const std::string& name,
                              float defaultValue) const {
    if (readHandlers_.count(name) == 0) {
        CC_ASSERT(false);
        return defaultValue;
    }
    auto&& handler = readHandlers_.at(name);
    auto value = handler();
    CC_ASSERT(value.getType() == cocos2d::Value::Type::FLOAT);
    return value.asFloat();
}

std::string Self::readStringProperty(const std::string& name,
                                     std::string defaultValue) const {
    if (readHandlers_.count(name) == 0) {
        CC_ASSERT(false);
        return defaultValue;
    }
    auto&& handler = readHandlers_.at(name);
    auto value = handler();
    CC_ASSERT(value.getType() == cocos2d::Value::Type::STRING);
    return value.asString();
}

bool Self::writeProperty(const std::string& name,
                         const cocos2d::Value& value) const {
    if (writeHandlers_.count(name) == 0) {
        CC_ASSERT(false);
        return false;
    }
    auto&& handler = writeHandlers_.at(name);
    if (not handler(value)) {
        return false;
    }
    return true;
}

bool Self::addReadHandler(const std::string& name, const ReadHandler& handler) {
    if (readHandlers_.count(name) != 0) {
        CC_ASSERT(false);
        return false;
    }
    readHandlers_.emplace(name, handler);
    return true;
}

bool Self::addReadBoolHandler(const std::string name,
                              const ReadBoolHandler& handler) {
    return addReadHandler(name,
                          [handler] { return cocos2d::Value(handler()); });
}

bool Self::addReadIntHandler(const std::string name,
                             const ReadIntHandler& handler) {
    return addReadHandler(name,
                          [handler] { return cocos2d::Value(handler()); });
}

bool Self::addReadFloatHandler(const std::string name,
                               const ReadFloatHandler& handler) {
    return addReadHandler(name,
                          [handler] { return cocos2d::Value(handler()); });
}

bool Self::addReadStringHandler(const std::string name,
                                const ReadStringHandler& handler) {
    return addReadHandler(name,
                          [handler] { return cocos2d::Value(handler()); });
}

bool Self::addWriteHandler(const std::string& name,
                           const WriteHandler& handler) {
    if (writeHandlers_.count(name) != 0) {
        CC_ASSERT(false);
        return false;
    }
    writeHandlers_.emplace(name, handler);
    return true;
}

bool Self::addWriteBoolHandler(const std::string& name,
                               const WriteBoolHandler& handler) {
    return addWriteHandler(name, [handler](const cocos2d::Value& value) {
        if (value.getType() != cocos2d::Value::Type::BOOLEAN) {
            CC_ASSERT(false);
            return false;
        }
        handler(value.asBool());
        return true;
    });
}

bool Self::addWriteIntHandler(const std::string& name,
                              const WriteIntHandler& handler) {
    return addWriteHandler(name, [handler](const cocos2d::Value& value) {
        if (value.getType() != cocos2d::Value::Type::INTEGER) {
            CC_ASSERT(false);
            return false;
        }
        handler(value.asInt());
        return true;
    });
}

bool Self::addWriteFloatHandler(const std::string& name,
                                const WriteFloatHandler& handler) {
    return addWriteHandler(name, [handler](const cocos2d::Value& value) {
        if (value.getType() != cocos2d::Value::Type::FLOAT) {
            CC_ASSERT(false);
            return false;
        }
        handler(value.asFloat());
        return true;
    });
}

bool Self::addWriteStringHandler(const std::string& name,
                                 const WriteStringHandler& handler) {
    return addWriteHandler(name, [handler](const cocos2d::Value& value) {
        if (value.getType() != cocos2d::Value::Type::STRING) {
            CC_ASSERT(false);
            return false;
        }
        handler(value.asString());
        return true;
    });
}
} // namespace ee
