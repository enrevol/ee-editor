#include "propertywriter.hpp"
#include "propertyreader.hpp"

namespace ee {
using Self = PropertyWriter;

Self::PropertyWriter(cocos2d::ValueMap& properties)
    : properties_(properties) {}

cocos2d::ValueMap& Self::getProperties() {
    return properties_;
}

const cocos2d::ValueMap& Self::getProperties() const {
    return properties_;
}

void Self::setProperty(const std::string& name, const cocos2d::Value& value) {
    getProperties()[name] = value;
}

void Self::setProperty(const std::string& name, bool value) {
    setProperty(name, cocos2d::Value(value));
}

void Self::setProperty(const std::string& name, int value) {
    setProperty(name, cocos2d::Value(value));
}

void Self::setProperty(const std::string& name, float value) {
    setProperty(name, cocos2d::Value(value));
}

void Self::setProperty(const std::string& name, const std::string& value) {
    setProperty(name, cocos2d::Value(value));
}

bool Self::addProperty(const std::string& name, const cocos2d::Value& value) {
    if (PropertyReader(getProperties()).hasProperty(name)) {
        return false;
    }
    setProperty(name, value);
    return true;
}

bool Self::addProperty(const std::string& name, bool value) {
    return addProperty(name, cocos2d::Value(value));
}

bool Self::addProperty(const std::string& name, int value) {
    return addProperty(name, cocos2d::Value(value));
}

bool Self::addProperty(const std::string& name, float value) {
    return addProperty(name, cocos2d::Value(value));
}

bool Self::addProperty(const std::string& name, const std::string& value) {
    return addProperty(name, cocos2d::Value(value));
}
} // namespace ee
