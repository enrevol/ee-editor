#include <ciso646>

#include "nodegraph.hpp"
#include "propertyhandler.hpp"
#include "propertyreader.hpp"
#include "propertywriter.hpp"

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

const cocos2d::ValueMap& Self::getProperties() const {
    return properties_;
}

PropertyReader Self::getPropertyReader() const {
    return PropertyReader(properties_);
}

PropertyWriter Self::getPropertyWriter() {
    return PropertyWriter(properties_);
}

std::string Self::getBaseClass() const {
    return getPropertyReader().getStringProperty(key::base_class);
}

std::string Self::getCustomClass() const {
    return getPropertyReader().getStringProperty(key::custom_class, "");
}

std::string Self::getDisplayName() const {
    auto value = getPropertyReader().getStringProperty(key::display_name, "");
    if (not value.empty()) {
        return value;
    }
    return getBaseClass();
}

void Self::setBaseClass(const std::string& name) {
    getPropertyWriter().setProperty(key::base_class, name);
}

void Self::setCustomClass(const std::string& name) {
    getPropertyWriter().setProperty(key::custom_class, name);
}

void Self::setDisplayName(const std::string& name) {
    getPropertyWriter().setProperty(key::display_name, name);
}

Self& Self::getChild(std::size_t index) {
    return children_.at(index);
}

const Self& Self::getChild(std::size_t index) const {
    return children_.at(index);
}

std::vector<Self>& Self::getChildren() {
    return children_;
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
