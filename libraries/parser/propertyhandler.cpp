#include <ciso646>

#include "propertyhandler.hpp"

namespace ee {
using Self = PropertyHandler;

Self::PropertyHandler() {}

const ValueMap& Self::getProperties() const {
    return properties_;
}

void Self::setProperties(const ValueMap& properties) {
    properties_ = properties;
}

void Self::clearProperties() {
    properties_.clear();
}

const Value& Self::getProperty(const std::string& name) const {
    return properties_.at(name);
}

void Self::setProperty(const std::string& name, const Value& value) {
    properties_[name] = value;
}
} // namespace ee
