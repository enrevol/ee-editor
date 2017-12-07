#ifndef EE_PARSER_SPRITE_LOADER_HPP
#define EE_PARSER_SPRITE_LOADER_HPP

#include "nodeloader.hpp"

namespace cocos2d {
class Sprite;
} // namespace cocos2d

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
        static const PropertyString SpriteFrame;
    };

    static const std::string ClassName;

    /// Constructs a sprite loader.
    SpriteLoader();

    virtual ~SpriteLoader() override;

    virtual cocos2d::Node* createNode() const override;

    virtual void loadProperties(cocos2d::Node* node,
                                const PropertyHandler& handler) const override;

    virtual void storeProperties(const cocos2d::Node* node,
                                 PropertyHandler& handler) const override;

    virtual std::string getClassName() const override;

protected:
    virtual Self* cloneRaw() const override;
};
} // namespace ee

#endif // SPRITELOADER_HPP
