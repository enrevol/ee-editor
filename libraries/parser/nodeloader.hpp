#ifndef EE_PARSER_NODE_LOADER_HPP
#define EE_PARSER_NODE_LOADER_HPP

#include "parserfwd.hpp"
#include "propertybool.hpp"
#include "propertycolor.hpp"
#include "propertyfloat.hpp"
#include "propertyhandler.hpp"
#include "propertyint.hpp"
#include "propertypoint.hpp"
#include "propertysize.hpp"
#include "propertystring.hpp"

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class PropertyReader;
class PropertyWriter;

class NodeLoader {
private:
    using Self = NodeLoader;

public:
    struct Property {
        static const PropertyPoint AnchorPoint;
        static const PropertyBool CascadeColorEnabled;
        static const PropertyBool CascadeOpacityEnabled;
        static const PropertyColor Color;
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

    static const std::string ClassName;

    static NodeLoaderPtr create();

    virtual ~NodeLoader();

    /// Creates a node.
    virtual cocos2d::Node* createNode() const;

    virtual std::string getClassName() const;

    /// Gets the property handler.
    const PropertyHandler& getPropertyHandler() const;

    PropertyReader getDefaultPropertyReader() const;

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
