#ifndef EE_PARSER_LAYOUT_LOADER_HPP
#define EE_PARSER_LAYOUT_LOADER_HPP

#include "widgetloader.hpp"

#include <ui/UILayout.h>

namespace cocos2d {
namespace ui {
class Layout;
} // namespace ui
} // namespace cocos2d

namespace ee {
class LayoutLoader : public WidgetLoader {
private:
    using Self = LayoutLoader;
    using Super = WidgetLoader;
    using Target = cocos2d::ui::Layout;

public:
    struct Property {
        static const PropertyColor3B BackgroundColor;
        static const PropertyInt BackgroundColorOpacity;
        static const PropertyEnum<cocos2d::ui::Layout::BackGroundColorType>
            BackgroundColorType;
        static const PropertyPoint BackgroundColorVector;
        // static const PropertyColor3B<Target> BackgroundStartColor;
        // static const PropertyColor3B<Target> BackgroundEndColor;
        static const PropertyRect BackgroundImageCapInsets;
        static const PropertyColor3B BackgroundImageColor;
        static const PropertyInt BackgroundImageOpacity;
        // static const PropertyString<Target> BackgroundImageName;
        // static const PropertyInt<Target> BackgroundImageTexType;
        // static const PropertyBool<Target> BackgroundImageScale9Enabled;
        static const PropertyBool ClippingEnabled;
        static const PropertyEnum<cocos2d::ui::Layout::ClippingType>
            ClippingType;
        static const PropertyEnum<cocos2d::ui::Layout::Type> LayoutType;
    };

    static const std::string ClassName;

    LayoutLoader();

    virtual ~LayoutLoader() override;

    virtual std::string getClassName() const override;

    virtual cocos2d::Node* createNode() const override;

protected:
    virtual Self* cloneRaw() const override;
};
} // namespace ee

#endif // EE_PARSER_LAYOUT_LOADER_HPP
