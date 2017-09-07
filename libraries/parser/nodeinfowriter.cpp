#include "nodeinfowriter.hpp"
#include "nodeinfo.hpp"

#include <2d/CCNode.h>

namespace ee {
using Self = NodeInfoWriter;

Self::NodeInfoWriter(cocos2d::Node* node)
    : node_(node) {}

NodeInfo* Self::getInfo() {
    auto obj = node_->getUserObject();
    return dynamic_cast<NodeInfo*>(obj);
}

cocos2d::ValueMap& Self::getDict() {
    auto info = getInfo();
    return info->dict_;
}

void Self::writeBool(const std::string& name, bool value) {
    auto&& dict = getDict();
    dict[name] = value;
}

void Self::writeInt(const std::string& name, int value) {
    auto&& dict = getDict();
    dict[name] = value;
}

void Self::writeFloat(const std::string& name, float value) {
    auto&& dict = getDict();
    dict[name] = value;
}

void Self::writeString(const std::string& name, const std::string& value) {
    auto&& dict = getDict();
    dict[name] = value;
}
} // namespace ee
