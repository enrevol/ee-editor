#ifndef EE_PARSER_NODE_LOADER_HPP
#define EE_PARSER_NODE_LOADER_HPP

#include "parserfwd.hpp"
#include "propertyhandler.hpp"

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class NodeLoader {
private:
    using Self = NodeLoader;

public:
    struct Property {
        static const std::string PositionX;
        static const std::string PositionY;
        static const std::string ContentSizeWidth;
        static const std::string ContentSizeHeight;
    };

    /// Constructs a node loader.
    NodeLoader();

    virtual ~NodeLoader();

    /// Creates a node.
    virtual cocos2d::Node* createNode() const;

    /// Gets the property handler.
    PropertyHandler& getPropertyHandler();

    /// Gets the property handler.
    const PropertyHandler& getPropertyHandler() const;

    NodeLoaderPtr clone() const;

protected:
    virtual Self* cloneRaw() const;

private:
    PropertyHandler propertyHandler_;
};
} // namespace ee

#endif // EE_PARSER_NODE_LOADER_HPP
