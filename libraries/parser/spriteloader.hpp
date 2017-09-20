#ifndef EE_PARSER_SPRITE_LOADER_HPP
#define EE_PARSER_SPRITE_LOADER_HPP

#include "nodeloader.hpp"

namespace ee {
class SpriteLoader : public NodeLoader {
private:
    using Self = SpriteLoader;

public:
    /// Constructs a sprite loader.
    SpriteLoader();

    virtual ~SpriteLoader() override;

    virtual cocos2d::Node* createNode() const override;

protected:
    virtual Self* cloneRaw() const override;
};
} // namespace ee

#endif // SPRITELOADER_HPP
