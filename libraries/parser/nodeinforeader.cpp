#include "nodeinforeader.hpp"
#include "nodeinfo.hpp"

#include <2d/CCNode.h>

namespace ee {
using Self = NodeInfoReader;

Self::NodeInfoReader(const cocos2d::Node* node)
    : node_(node) {}

const NodeInfo* Self::getInfo() const {
    auto obj = node_->getUserObject();
    return dynamic_cast<const NodeInfo*>(obj);
}

const cocos2d::ValueMap& Self::getDict() const {
    auto info = getInfo();
    return info->dict_;
}

bool Self::readBool(const std::string& name, bool defaultValue) const {
    auto&& dict = getDict();
    if (dict.count(name) == 0) {
        return defaultValue;
    }
    auto&& elt = dict.at(name);
    if (elt.getType() != cocos2d::Value::Type::BOOLEAN) {
        CC_ASSERT(false);
        return defaultValue;
    }
    return elt.asBool();
}

int Self::readInt(const std::string& name, int defaultValue) const {
    auto&& dict = getDict();
    if (dict.count(name) == 0) {
        return defaultValue;
    }
    auto&& elt = dict.at(name);
    if (elt.getType() != cocos2d::Value::Type::INTEGER) {
        CC_ASSERT(false);
        return defaultValue;
    }
    return elt.asInt();
}

float Self::readFloat(const std::string& name, float defaultValue) const {
    auto&& dict = getDict();
    if (dict.count(name) == 0) {
        return defaultValue;
    }
    auto&& elt = dict.at(name);
    if (elt.getType() != cocos2d::Value::Type::FLOAT) {
        CC_ASSERT(false);
        return defaultValue;
    }
    return elt.asFloat();
}

std::string Self::readString(const std::string& name,
                             const std::string& defaultValue) const {
    auto&& dict = getDict();
    if (dict.count(name) == 0) {
        return defaultValue;
    }
    auto&& elt = dict.at(name);
    if (elt.getType() != cocos2d::Value::Type::STRING) {
        CC_ASSERT(false);
        return defaultValue;
    }
    return elt.asString();
}
} // namespace ee
