#include <ciso646>

#include "nodegraph.hpp"
#include "propertyhandler.hpp"

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

Self::NodeGraph(const ValueMap& dict) {
    setDictionary(dict);
}

Self::~NodeGraph() {}

void Self::setDictionary(const ValueMap& dict) {
    children_.clear();
    propertyHandler_.clearProperties();
    if (dict.count(key::children)) {
        auto&& children = dict.at(key::children).getList();
        for (auto&& child : children) {
            children_.emplace_back(child.getMap());
        }
    }
    if (dict.count(key::properties)) {
        auto&& properties = dict.at(key::properties).getMap();
        propertyHandler_.setProperties(properties);
    }
}

const PropertyHandler& Self::getPropertyHandler() const {
    return propertyHandler_;
}

std::string Self::getBaseClass() const {
    return getPropertyHandler().getProperty(key::base_class).getString();
}

std::string Self::getCustomClass() const {
    return getPropertyHandler().getProperty(key::custom_class).getString();
}

std::string Self::getDisplayName() const {
    auto value =
        getPropertyHandler().getProperty(key::display_name).getString();
    if (not value.empty()) {
        return value;
    }
    return getBaseClass();
}

/*
void Self::setBaseClass(const std::string& name) {
    getPropertyWriter().setProperty(key::base_class, name);
}

void Self::setCustomClass(const std::string& name) {
    getPropertyWriter().setProperty(key::custom_class, name);
}

void Self::setDisplayName(const std::string& name) {
    getPropertyWriter().setProperty(key::display_name, name);
}
*/

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

ValueMap Self::toDict() const {
    ValueMap dict;
    dict[key::properties] = propertyHandler_.getProperties();

    ValueList children;
    for (auto&& child : getChildren()) {
        children.emplace_back(child.toDict());
    }
    dict[key::children] = children;
    return dict;
}
} // namespace ee
