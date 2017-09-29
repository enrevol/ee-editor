#ifndef EE_PARSER_WIDGET_LOADER_HPP
#define EE_PARSER_WIDGET_LOADER_HPP

#include "nodeloader.hpp"

namespace ee {
class WidgetLoader : public NodeLoader {
private:
    using Self = WidgetLoader;
    using Super = NodeLoader;

public:
    struct Property {
        static const std::string Bright;
        static const std::string Enabled;
        static const std::string FlippedX;
        static const std::string FlippedY;
        static const std::string Highlighted;
        static const std::string IgnoreContentAdaptWithSize;
        static const std::string LayoutComponentEnabled;
        static const std::string PositionPercentX;
        static const std::string PositionPercentY;
        static const std::string PositionType;
        static const std::string PropagateTouchEvents;
        static const std::string SizePercentX;
        static const std::string SizePercentY;
        static const std::string SizeType;
        static const std::string SwallowTouches;
        static const std::string TouchEnabled;
        static const std::string UnifySizeEnabled;
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
