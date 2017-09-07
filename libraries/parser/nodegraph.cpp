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

Self::NodeGraph(const cocos2d::ValueMap& dict) {
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

Self::~NodeGraph() {}

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

const std::vector<NodeGraph>& Self::getChildren() const {
    return children_;
}
} // namespace ee
