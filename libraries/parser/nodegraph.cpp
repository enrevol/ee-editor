#include <ciso646>

#include "nodegraph.hpp"

namespace ee {
namespace key {
constexpr auto base_class = "base_class";
constexpr auto custom_class = "custom_class";
constexpr auto display_name = "display_name";
constexpr auto children = "children";
constexpr auto properties = "properties";
} // namespace key

using Self = NodeGraph;

Self::NodeGraph() {}

Self::NodeGraph(const cocos2d::ValueMap& dict) {
    setDictionary(dict);
}

Self::~NodeGraph() {}

void Self::setDictionary(const cocos2d::ValueMap& dict) {
    children_.clear();
    properties_.clear();
    if (dict.count(key::children)) {
        auto&& children = dict.at(key::children).asValueVector();
        for (auto&& child : children) {
            children_.emplace_back(child.asValueMap());
        }
    }
    if (dict.count(key::properties)) {
        auto&& properties = dict.at(key::properties).asValueMap();
        properties_ = properties;
    }
}

cocos2d::Value Self::getProperty(const std::string& name) const {
    auto value = getProperty(name, cocos2d::Value::Null);
    CC_ASSERT(not value.isNull());
    return value;
}

cocos2d::Value Self::getProperty(const std::string& name,
                                 const cocos2d::Value& defaultValue) const {
    if (not properties_.count(name)) {
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
    if (value.getType() != cocos2d::Value::Type::FLOAT) {
        CC_ASSERT(false);
        return 0.0f;
    }
    return value.asFloat();
}

float Self::getFloatProperty(const std::string& name,
                             float defaultValue) const {
    auto value = getProperty(name, cocos2d::Value(defaultValue));
    if (value.getType() != cocos2d::Value::Type::FLOAT) {
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

void Self::setProperty(const std::string& name, const cocos2d::Value& value) {
    properties_[name] = value;
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

std::string Self::getBaseClass() const {
    return getStringProperty(key::base_class);
}

std::string Self::getCustomClass() const {
    return getStringProperty(key::custom_class, "");
}

std::string Self::getDisplayName() const {
    auto value = getStringProperty(key::display_name, "");
    if (not value.empty()) {
        return value;
    }
    return getBaseClass();
}

void Self::setBaseClass(const std::string& name) {
    setProperty(key::base_class, name);
}

void Self::setCustomClass(const std::string& name) {
    setProperty(key::custom_class, name);
}

void Self::setDisplayName(const std::string& name) {
    setProperty(key::display_name, name);
}

Self& Self::getChild(std::size_t index) {
    return children_.at(index);
}

const Self& Self::getChild(std::size_t index) const {
    return children_.at(index);
}

const std::vector<Self>& Self::getChildren() const {
    return children_;
}

void Self::addChild(const Self& child) {
    children_.push_back(child);
}

cocos2d::ValueMap Self::toDict() const {
    cocos2d::ValueMap dict;
    dict[key::properties] = properties_;

    cocos2d::ValueVector children;
    for (auto&& child : getChildren()) {
        children.emplace_back(child.toDict());
    }
    dict[key::children] = children;
    return dict;
}
} // namespace ee
