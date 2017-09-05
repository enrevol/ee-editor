#ifndef EE_PARSER_NODE_LOADER_HPP
#define EE_PARSER_NODE_LOADER_HPP

#include "parserfwd.hpp"

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class NodeLoader {
public:
    explicit NodeLoader(cocos2d::Node* node);

    virtual ~NodeLoader();

    const PropertyHandlerPtr& getPropertyHandler() const;

    virtual cocos2d::Node* getNode();

private:
    PropertyHandlerPtr propertyHandler_;
    cocos2d::Node* node_;
};
} // namespace ee

#endif // EE_PARSER_NODE_LOADER_HPP
