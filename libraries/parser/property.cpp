#include "property.hpp"

namespace ee {
using Self = Property;

Self::Property(const std::string& name)
    : name_(name) {}

Self::~Property() {}

const std::string& Self::getName() const {
    return name_;
}
} // namespace ee
