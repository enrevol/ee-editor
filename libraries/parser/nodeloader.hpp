#ifndef EE_PARSER_NODE_LOADER_HPP
#define EE_PARSER_NODE_LOADER_HPP

#include "parserfwd.hpp"
#include "property.hpp"
#include "propertyhandler.hpp"

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class PropertyReader;
class PropertyWriter;

/// Parses cocos2d::Node.
class NodeLoader {
private:
    using Self = NodeLoader;
    using Target = cocos2d::Node;

public:
    struct Property {
        static const PropertyPoint<Target> AnchorPoint;
        static const PropertyBool<Target> CascadeColorEnabled;
        static const PropertyBool<Target> CascadeOpacityEnabled;
        static const PropertyColor3B<Target> Color;
        static const PropertySize<Target> ContentSize;
        static const PropertyBool<Target> IgnoreAnchorPointForPosition;
        static const PropertyInt<Target> LocalZOrder;
        static const PropertyString<Target> Name;
        static const PropertyInt<Target> Opacity;
        static const PropertyBool<Target> OpacityModifyRGB;
        static const PropertyPoint<Target> Position;
        static const PropertyFloat<Target> Rotation;
        static const PropertyFloat<Target> ScaleX;
        static const PropertyFloat<Target> ScaleY;
        static const PropertyFloat<Target> SkewX;
        static const PropertyFloat<Target> SkewY;
        static const PropertyInt<Target> Tag;
        static const PropertyBool<Target> Visible;
    };

    static const std::string ClassName;

    /// Constructs a node loader.
    NodeLoader();

    virtual ~NodeLoader();

    /// Creates a default node.
    virtual cocos2d::Node* createNode() const;

    /// Loads properties from the specified handler to the specified node.
    virtual void loadProperties(cocos2d::Node* node,
                                const PropertyHandler& handler) const;

    virtual std::string getClassName() const;

    PropertyReader getDefaultPropertyReader() const;

    NodeLoaderPtr clone() const;

protected:
    virtual Self* cloneRaw() const;

private:
    // cocos2d::ValueMap defaultProperties_;
};
} // namespace ee

#endif // EE_PARSER_NODE_LOADER_HPP
