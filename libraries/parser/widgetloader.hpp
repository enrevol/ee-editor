#ifndef EE_PARSER_WIDGET_LOADER_HPP
#define EE_PARSER_WIDGET_LOADER_HPP

#include "nodeloader.hpp"

#include <ui/UIWidget.h>

namespace ee {
class WidgetLoader : public NodeLoader {
private:
    using Self = WidgetLoader;
    using Super = NodeLoader;
    using Target = cocos2d::ui::Widget;

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
        static const PropertyEnum<Target::PositionType> PositionType;
        static const PropertyBool PropagateTouchEvents;
        static const PropertyPoint SizePercent;
        static const PropertyEnum<Target::SizeType> SizeType;
        static const PropertyBool SwallowTouches;
        static const PropertyBool TouchEnabled;
        static const PropertyBool UnifySizeEnabled;
    };

    static const std::string Name;

    WidgetLoader();

    virtual ~WidgetLoader() override;

    /// @see Super.
    virtual std::string getName() const override;

    /// @see Super.
    virtual cocos2d::Node* createNode() const override;

protected:
    /// @see Super.
    virtual Self* cloneRaw() const override;
};
} // namespace ee

#endif // EE_PARSER_WIDGET_LOADER_HPP
