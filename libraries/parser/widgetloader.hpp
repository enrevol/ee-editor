#ifndef EE_PARSER_WIDGET_LOADER_HPP
#define EE_PARSER_WIDGET_LOADER_HPP

#include "nodeloader.hpp"
#include "propertybool.hpp"
#include "propertypoint.hpp"

namespace ee {
class WidgetLoader : public NodeLoader {
private:
    using Self = WidgetLoader;
    using Super = NodeLoader;

public:
    struct Property {
        static const PropertyBool Bright;
        static const PropertyBool Enabled;
        static const PropertyBool FlippedX;
        static const PropertyBool FlippedY;
        static const PropertyBool Highlighted;
        static const PropertyBool IgnoreContentAdaptWithSize;
        static const PropertyBool LayoutComponentEnabled;
        static const PropertyPoint PositionPercent;
        static const PropertyInt PositionType;
        static const PropertyBool PropagateTouchEvents;
        static const PropertyPoint SizePercent;
        static const PropertyInt SizeType;
        static const PropertyBool SwallowTouches;
        static const PropertyBool TouchEnabled;
        static const PropertyBool UnifySizeEnabled;
    };

    static const std::string ClassName;

    static NodeLoaderPtr create();

    virtual ~WidgetLoader() override;

    virtual cocos2d::Node* createNode() const override;

    virtual std::string getClassName() const override;

protected:
    WidgetLoader();

    virtual void addReadHandlers(PropertyHandler& handler) override;
    virtual void addWriteHandlers(PropertyHandler& handler) override;
    virtual void addDefaultProperties(PropertyWriter& writer) override;

    virtual Self* cloneRaw() const override;
};
} // namespace ee

#endif // EE_PARSER_WIDGET_LOADER_HPP
