#ifndef EE_PARSER_NODE_LOADER_HPP
#define EE_PARSER_NODE_LOADER_HPP

#include "parserfwd.hpp"
#include "propertyhandler.hpp"

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class NodeLoader {
public:
    /// Constructs a node loader.
    NodeLoader();

    virtual ~NodeLoader();

    virtual cocos2d::Node* createNode() const;

    PropertyHandler& getPropertyHandler();

    /// Gets the property handler.
    const PropertyHandler& getPropertyHandler() const;

private:
    PropertyHandler propertyHandler_;
};
} // namespace ee

#endif // EE_PARSER_NODE_LOADER_HPP
