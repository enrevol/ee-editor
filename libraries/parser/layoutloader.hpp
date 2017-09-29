#ifndef EE_PARSER_LAYOUT_LOADER_HPP
#define EE_PARSER_LAYOUT_LOADER_HPP

#include "widgetloader.hpp"

namespace ee {
class LayoutLoader : public WidgetLoader {
private:
    using Self = LayoutLoader;
    using Super = WidgetLoader;

public:
    struct Property {
        static const std::string BackgroundColorR;
        static const std::string BackgroundColorG;
        static const std::string BackgroundColorB;
        static const std::string BackgroundColorOpacity;
        static const std::string BackgroundColorType;
        static const std::string BackgroundColorVectorX;
        static const std::string BackgroundColorVectorY;
        static const std::string BackgroundEndColorR;
        static const std::string BackgroundEndColorG;
        static const std::string BackgroundEndColorB;
        static const std::string BackgroundImageCapInsetsX;
        static const std::string BackgroundImageCapInsetsY;
        static const std::string BackgroundImageCapInsetsW;
        static const std::string BackgroundImageCapInsetsH;
        static const std::string BackgroundImageColorR;
        static const std::string BackgroundImageColorG;
        static const std::string BackgroundImageColorB;
        static const std::string BackgroundImageOpacity;
        static const std::string BackgroundImageName;
        static const std::string BackgroundImageTexType;
        static const std::string BackgroundImageScale9Enabled;
        static const std::string BackgroundStartColorR;
        static const std::string BackgroundStartColorG;
        static const std::string BackgroundStartColorB;
        static const std::string ClippingEnabled;
        static const std::string ClippingType;
        static const std::string LayoutType;
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
