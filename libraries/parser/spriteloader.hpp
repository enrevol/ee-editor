#ifndef EE_PARSER_SPRITE_LOADER_HPP
#define EE_PARSER_SPRITE_LOADER_HPP

#include "nodeloader.hpp"
#include "propertyblend.hpp"
#include "propertybool.hpp"
#include "propertyint.hpp"
#include "propertystring.hpp"

namespace ee {
class SpriteLoader : public NodeLoader {
private:
    using Self = SpriteLoader;
    using Super = NodeLoader;

public:
    struct Property {
        static const PropertyBlend BlendFunc;
        static const PropertyBool FlippedX;
        static const PropertyBool FlippedY;
        static const PropertyBool StretchEnabled;
        static const PropertyString Texture;
    };

    static const std::string ClassName;

    static NodeLoaderPtr create();

    virtual ~SpriteLoader() override;

    virtual cocos2d::Node* createNode() const override;

    virtual std::string getClassName() const override;

protected:
    /// Constructs a sprite loader.
    SpriteLoader();

    virtual void addReadHandlers(PropertyHandler& handler) override;
    virtual void addWriteHandlers(PropertyHandler& handler) override;
    virtual void addDefaultProperties(PropertyWriter& writer) override;

    virtual Self* cloneRaw() const override;
};
} // namespace ee

#endif // SPRITELOADER_HPP
