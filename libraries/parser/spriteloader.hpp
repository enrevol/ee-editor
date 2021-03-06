#ifndef EE_PARSER_SPRITE_LOADER_HPP
#define EE_PARSER_SPRITE_LOADER_HPP

#include "nodeloader.hpp"

namespace ee {
class SpriteLoader : public NodeLoader {
private:
    using Self = SpriteLoader;
    using Super = NodeLoader;
    using Target = cocos2d::Sprite;

public:
    struct Property {
        static const PropertyBlend BlendFunc;
        static const PropertyBool FlippedX;
        static const PropertyBool FlippedY;
        static const PropertyBool StretchEnabled;
        static const PropertyString Texture;
        // static const PropertyString SpriteFrame;
    };

    static const std::string Name;

    /// Constructs a sprite loader.
    SpriteLoader();

    virtual ~SpriteLoader() override;

    /// @see Super.
    virtual std::string getName() const override;

    /// @see Super.
    virtual cocos2d::Node* createNode() const override;

protected:
    /// @see Super.
    virtual Self* cloneRaw() const override;
};
} // namespace ee

#endif // SPRITELOADER_HPP
