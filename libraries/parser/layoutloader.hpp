#ifndef EE_PARSER_LAYOUT_LOADER_HPP
#define EE_PARSER_LAYOUT_LOADER_HPP

#include "propertybool.hpp"
#include "propertycolor.hpp"
#include "propertyint.hpp"
#include "propertypoint.hpp"
#include "propertyrect.hpp"
#include "propertystring.hpp"
#include "widgetloader.hpp"

namespace ee {
class LayoutLoader : public WidgetLoader {
private:
    using Self = LayoutLoader;
    using Super = WidgetLoader;

public:
    struct Property {
        static const PropertyColor BackgroundColor;
        static const PropertyInt BackgroundColorOpacity;
        static const PropertyInt BackgroundColorType;
        static const PropertyPoint BackgroundColorVector;
        static const PropertyColor BackgroundEndColor;
        static const PropertyRect BackgroundImageCapInsets;
        static const PropertyColor BackgroundImageColor;
        static const PropertyInt BackgroundImageOpacity;
        static const PropertyString BackgroundImageName;
        static const PropertyInt BackgroundImageTexType;
        static const PropertyBool BackgroundImageScale9Enabled;
        static const PropertyColor BackgroundStartColor;
        static const PropertyBool ClippingEnabled;
        static const PropertyInt ClippingType;
        static const PropertyInt LayoutType;
    };

    static const std::string ClassName;

    static NodeLoaderPtr create();

    virtual ~LayoutLoader() override;

    virtual cocos2d::Node* createNode() const override;

    virtual std::string getClassName() const override;

protected:
    LayoutLoader();

    virtual void addReadHandlers(PropertyHandler& handler) override;
    virtual void addWriteHandlers(PropertyHandler& handler) override;
    virtual void addDefaultProperties(PropertyWriter& writer) override;

    virtual Self* cloneRaw() const override;
};
} // namespace ee

#endif // EE_PARSER_LAYOUT_LOADER_HPP
