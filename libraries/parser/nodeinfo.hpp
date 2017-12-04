#ifndef EE_PARSER_NODE_INFO_HPP
#define EE_PARSER_NODE_INFO_HPP

#include <propertyhandler.hpp>

#include <base/CCRef.h>

namespace ee {
class NodeInfoReader;
class NodeInfoWriter;

/// Stores additional properties for a node.
class NodeInfo final : public cocos2d::Ref {
private:
    using Self = NodeInfo;

public:
    static const PropertyHandler& getPropertyHandler(const cocos2d::Node* node);
    static PropertyHandler& getPropertyHandler(cocos2d::Node* node);

    static Self* create();

    const PropertyHandler& getPropertyHandler() const;
    PropertyHandler& getPropertyHandler();

protected:
    friend NodeInfoReader;
    friend NodeInfoWriter;

    NodeInfo();

private:
    PropertyHandler propertyHandler_;
};
} // namespace ee

#endif // NODEINFO_HPP
