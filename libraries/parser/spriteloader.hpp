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
        static const PropertyBlend<Target> BlendFunc;
        static const PropertyBool<Target> FlippedX;
        static const PropertyBool<Target> FlippedY;
        static const PropertyBool<Target> StretchEnabled;
        static const PropertyString<Target> Texture;
        static const PropertyString<Target> SpriteFrame;
    };

    static const std::string ClassName;

    /// Constructs a sprite loader.
    SpriteLoader();

    virtual ~SpriteLoader() override;

    virtual cocos2d::Node* createNode() const override;

    virtual void loadProperties(cocos2d::Node* node,
                                const PropertyHandler& handler) const override;

    virtual std::string getClassName() const override;

protected:
    virtual Self* cloneRaw() const override;
};
} // namespace ee

#endif // SPRITELOADER_HPP
