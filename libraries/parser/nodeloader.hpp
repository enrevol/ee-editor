#ifndef EE_PARSER_NODE_LOADER_HPP
#define EE_PARSER_NODE_LOADER_HPP

#include "parserfwd.hpp"
#include "property.hpp"

namespace ee {
/// Parses cocos2d::Node.
class NodeLoader {
private:
    using Self = NodeLoader;
    using Target = cocos2d::Node;

public:
    struct Property {
        static const PropertyPoint AnchorPoint;
        static const PropertyBool CascadeColorEnabled;
        static const PropertyBool CascadeOpacityEnabled;
        static const PropertyColor3B Color;
        static const PropertySize ContentSize;
        static const PropertyBool IgnoreAnchorPointForPosition;
        static const PropertyInt LocalZOrder;
        static const PropertyString Name;
        static const PropertyInt Opacity;
        static const PropertyBool OpacityModifyRGB;
        static const PropertyPoint Position;
        static const PropertyFloat Rotation;
        static const PropertyFloat ScaleX;
        static const PropertyFloat ScaleY;
        static const PropertyFloat SkewX;
        static const PropertyFloat SkewY;
        static const PropertyInt Tag;
        static const PropertyBool Visible;
    };

    /// Unique name of this node loader.
    static const std::string Name;

    /// Constructs a node loader.
    NodeLoader();

    virtual ~NodeLoader();

    /// Gets the unique name of this node loader.
    virtual std::string getName() const;

    /// Creates a default node.
    virtual cocos2d::Node* createNode() const;

    /// Loads properties from the specified handler to the specified node.
    void loadProperties(cocos2d::Node* node,
                        const PropertyHandler& handler) const;

    /// Stores properties from the specified node to the specified loader.
    void storeProperties(const cocos2d::Node* node,
                         PropertyHandler& handler) const;

    /// Clones this node loader.
    NodeLoaderPtr clone() const;

protected:
    Self& addProperty(const ee::Property& property);
    const std::vector<const ee::Property*>& getProperties() const;

    /// Raw clones this node.
    virtual Self* cloneRaw() const;

private:
    std::vector<const ee::Property*> properties_;
};
} // namespace ee

#endif // EE_PARSER_NODE_LOADER_HPP
