#include "propertyreader.hpp"

namespace ee {
using Self = PropertyReader;

Self::PropertyReader(const cocos2d::ValueMap& properties)
    : properties_(properties) {}

bool Self::hasProperty(const std::string& name) const {
    return properties_.count(name) != 0;
}

cocos2d::Value Self::getProperty(const std::string& name) const {
    auto value = getProperty(name, cocos2d::Value::Null);
    CC_ASSERT(not value.isNull());
    return value;
}

cocos2d::Value Self::getProperty(const std::string& name,
                                 const cocos2d::Value& defaultValue) const {
    if (not hasProperty(name)) {
        return defaultValue;
    }
    return properties_.at(name);
}

bool Self::getBoolProperty(const std::string& name) const {
    auto value = getProperty(name);
    if (value.getType() != cocos2d::Value::Type::BOOLEAN) {
        CC_ASSERT(false);
        return false;
    }
    return value.asBool();
}

bool Self::getBoolProperty(const std::string& name, bool defaultValue) const {
    auto value = getProperty(name, cocos2d::Value(defaultValue));
    if (value.getType() != cocos2d::Value::Type::BOOLEAN) {
        return defaultValue;
    }
    return value.asBool();
}

int Self::getIntProperty(const std::string& name) const {
    auto value = getProperty(name);
    if (value.getType() != cocos2d::Value::Type::INTEGER) {
        CC_ASSERT(false);
        return 0;
    }
    return value.asInt();
}

int Self::getIntProperty(const std::string& name, int defaultValue) const {
    auto value = getProperty(name, cocos2d::Value(defaultValue));
    if (value.getType() != cocos2d::Value::Type::INTEGER) {
        return defaultValue;
    }
    return value.asInt();
}

float Self::getFloatProperty(const std::string& name) const {
    auto value = getProperty(name);
    if (value.getType() != cocos2d::Value::Type::FLOAT &&
        value.getType() != cocos2d::Value::Type::INTEGER) {
        CC_ASSERT(false);
        return 0.0f;
    }
    return value.asFloat();
}

float Self::getFloatProperty(const std::string& name,
                             float defaultValue) const {
    auto value = getProperty(name, cocos2d::Value(defaultValue));
    if (value.getType() != cocos2d::Value::Type::FLOAT &&
        value.getType() != cocos2d::Value::Type::INTEGER) {
        CC_ASSERT(false);
        return defaultValue;
    }
    return value.asFloat();
}

std::string Self::getStringProperty(const std::string& name) const {
    auto value = getProperty(name);
    if (value.getType() != cocos2d::Value::Type::STRING) {
        return std::string();
    }
    return value.asString();
}

std::string Self::getStringProperty(const std::string& name,
                                    const std::string& defaultValue) const {
    auto value = getProperty(name, cocos2d::Value(defaultValue));
    if (value.getType() != cocos2d::Value::Type::STRING) {
        return defaultValue;
    }
    return value.asString();
}
} // namespace ee
