#ifndef EE_PARSER_WIDGET_LOADER_HPP
#define EE_PARSER_WIDGET_LOADER_HPP

#include "nodeloader.hpp"

#include <ui/UIWidget.h>

namespace cocos2d {
namespace ui {
class Widget;
} // namespace ui
} // namespace cocos2d

namespace ee {
class WidgetLoader : public NodeLoader {
private:
    using Self = WidgetLoader;
    using Super = NodeLoader;
    using Target = cocos2d::ui::Widget;

public:
    struct Property {
        static const PropertyBool<Target> Bright;
        static const PropertyBool<Target> Enabled;
        static const PropertyBool<Target> FlippedX;
        static const PropertyBool<Target> FlippedY;
        static const PropertyBool<Target> Highlighted;
        static const PropertyBool<Target> IgnoreContentAdaptWithSize;
        static const PropertyBool<Target> LayoutComponentEnabled;
        static const PropertyPoint<Target> PositionPercent;
        static const PropertyEnum<Target, cocos2d::ui::Widget::PositionType>
            PositionType;
        static const PropertyBool<Target> PropagateTouchEvents;
        static const PropertyPoint<Target> SizePercent;
        static const PropertyEnum<Target, cocos2d::ui::Widget::SizeType>
            SizeType;
        static const PropertyBool<Target> SwallowTouches;
        static const PropertyBool<Target> TouchEnabled;
        static const PropertyBool<Target> UnifySizeEnabled;
    };

    static const std::string ClassName;

    WidgetLoader();

    virtual ~WidgetLoader() override;

    virtual cocos2d::Node* createNode() const override;

    virtual void loadProperties(cocos2d::Node* node,
                                const PropertyHandler& handler) const override;

    virtual std::string getClassName() const override;

protected:
    virtual Self* cloneRaw() const override;
};
} // namespace ee

#endif // EE_PARSER_WIDGET_LOADER_HPP
