#ifndef EE_PARSER_NODE_INFO_HPP
#define EE_PARSER_NODE_INFO_HPP

#include <base/CCRef.h>
#include <base/CCValue.h>

namespace ee {
class NodeInfoReader;
class NodeInfoWriter;

class NodeInfo final : public cocos2d::Ref {
private:
    using Self = NodeInfo;

public:
    static Self* create();

private:
    friend NodeInfoReader;
    friend NodeInfoWriter;

    NodeInfo();

    cocos2d::ValueMap dict_;
};
} // namespace ee

#endif // NODEINFO_HPP
