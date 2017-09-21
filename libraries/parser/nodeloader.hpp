#ifndef EE_PARSER_NODE_LOADER_HPP
#define EE_PARSER_NODE_LOADER_HPP

#include "parserfwd.hpp"
#include "propertyhandler.hpp"

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class PropertyWriter;

class NodeLoader {
private:
    using Self = NodeLoader;

public:
    struct Property {
        static const std::string AnchorPointX;
        static const std::string AnchorPointY;
        static const std::string CascadeColorEnabled;
        static const std::string CascadeOpacityEnabled;
        static const std::string ColorB;
        static const std::string ColorG;
        static const std::string ColorR;
        static const std::string ContentSizeHeight;
        static const std::string ContentSizeWidth;
        static const std::string IgnoreAnchorPointForPosition;
        static const std::string LocalZOrder;
        static const std::string Opacity;
        static const std::string PositionX;
        static const std::string PositionY;
        static const std::string Rotation;
        static const std::string ScaleX;
        static const std::string ScaleY;
        static const std::string SkewX;
        static const std::string SkewY;
        static const std::string Tag;
        static const std::string Visible;
    };

    static NodeLoaderPtr create();

    virtual ~NodeLoader();

    /// Creates a node.
    virtual cocos2d::Node* createNode() const;

    /// Gets the property handler.
    const PropertyHandler& getPropertyHandler() const;

    NodeLoaderPtr clone() const;

protected:
    /// Constructs a node loader.
    NodeLoader();

    void initialize();

    virtual void addReadHandlers(PropertyHandler& handler);
    virtual void addWriteHandlers(PropertyHandler& handler);
    virtual void addDefaultProperties(PropertyWriter& writer);

    virtual Self* cloneRaw() const;

private:
    PropertyHandler propertyHandler_;
    cocos2d::ValueMap defaultProperties_;
};
} // namespace ee

#endif // EE_PARSER_NODE_LOADER_HPP
