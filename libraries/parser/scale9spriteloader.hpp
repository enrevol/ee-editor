#ifndef EE_PARSER_SCALE_9_SPRITE_LOADER_HPP
#define EE_PARSER_SCALE_9_SPRITE_LOADER_HPP

#include "spriteloader.hpp"

#include <ui/UIScale9Sprite.h>

namespace ee {
class Scale9SpriteLoader : public SpriteLoader {
private:
    using Self = Scale9SpriteLoader;
    using Super = SpriteLoader;
    using Target = cocos2d::ui::Scale9Sprite;

public:
    struct Property {
        static const PropertyEnum<Target::State> State;
        static const PropertyEnum<Target::RenderingType> RenderingType;
    };

    static const std::string Name;

    /// Constructs a sprite loader.
    Scale9SpriteLoader();

    virtual ~Scale9SpriteLoader() override;

    /// @see Super.
    virtual std::string getName() const override;

    /// @see Super.
    virtual cocos2d::Node* createNode() const override;

protected:
    /// @see Super.
    virtual Self* cloneRaw() const override;
};
} // namespace ee

#endif // EE_PARSER_SCALE_9_SPRITE_LOADER_HPP
