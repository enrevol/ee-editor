#include "nodeinfo.hpp"

namespace ee {
using Self = NodeInfo;

Self* Self::create() {
    auto result = new Self();
    result->autorelease();
    return result;
}

Self::NodeInfo() {}
} // namespace ee
