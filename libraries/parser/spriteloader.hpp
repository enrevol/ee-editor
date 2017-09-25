#ifndef EE_PARSER_SPRITE_LOADER_HPP
#define EE_PARSER_SPRITE_LOADER_HPP

#include "nodeloader.hpp"

namespace ee {
class SpriteLoader : public NodeLoader {
private:
    using Self = SpriteLoader;
    using Super = NodeLoader;

public:
    struct Property {
        static const std::string BlendFuncDst;
        static const std::string BlendFuncSrc;
        static const std::string FlippedX;
        static const std::string FlippedY;
        static const std::string SpriteFrame;
        static const std::string StretchEnabled;
        static const std::string Texture;
    };

    static NodeLoaderPtr create();

    virtual ~SpriteLoader() override;

    virtual cocos2d::Node* createNode() const override;

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
