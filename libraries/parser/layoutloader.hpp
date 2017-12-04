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
        static const PropertyColor3B<Target> BackgroundColor;
        static const PropertyInt<Target> BackgroundColorOpacity;
        static const PropertyEnum<Target,
                                  cocos2d::ui::Layout::BackGroundColorType>
            BackgroundColorType;
        static const PropertyPoint<Target> BackgroundColorVector;
        // static const PropertyColor3B<Target> BackgroundStartColor;
        // static const PropertyColor3B<Target> BackgroundEndColor;
        static const PropertyRect<Target> BackgroundImageCapInsets;
        static const PropertyColor3B<Target> BackgroundImageColor;
        static const PropertyInt<Target> BackgroundImageOpacity;
        // static const PropertyString<Target> BackgroundImageName;
        // static const PropertyInt<Target> BackgroundImageTexType;
        // static const PropertyBool<Target> BackgroundImageScale9Enabled;
        static const PropertyBool<Target> ClippingEnabled;
        static const PropertyEnum<Target, cocos2d::ui::Layout::ClippingType>
            ClippingType;
        static const PropertyEnum<Target, cocos2d::ui::Layout::Type> LayoutType;
    };

    static const std::string ClassName;

    virtual ~LayoutLoader() override;

    virtual cocos2d::Node* createNode() const override;

    virtual void loadProperties(cocos2d::Node* node,
                                const PropertyHandler& handler) const override;

    virtual std::string getClassName() const override;

protected:
    LayoutLoader();

    virtual Self* cloneRaw() const override;
};
} // namespace ee

#endif // EE_PARSER_LAYOUT_LOADER_HPP
