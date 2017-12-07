#ifndef EE_PARSER_SCALE_9_SPRITE_LOADER_HPP
#define EE_PARSER_SCALE_9_SPRITE_LOADER_HPP

#include "spriteloader.hpp"

#include <ui/UIScale9Sprite.h>

namespace cocos2d {
namespace ui {
class Scale9Sprite;
} // namespace ui
} // namespace cocos2d

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

    static const std::string ClassName;

    /// Constructs a sprite loader.
    Scale9SpriteLoader();

    virtual ~Scale9SpriteLoader() override;

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

#endif // EE_PARSER_SCALE_9_SPRITE_LOADER_HPP
