#ifndef EE_PARSER_SCALE_9_SPRITE_LOADER_HPP
#define EE_PARSER_SCALE_9_SPRITE_LOADER_HPP

#include "spriteloader.hpp"

namespace ee {
class Scale9SpriteLoader : public SpriteLoader {
private:
    using Self = Scale9SpriteLoader;
    using Super = SpriteLoader;

public:
    struct Property {
        static const PropertyInt State;
        static const PropertyInt RenderingType;
    };

    static const std::string ClassName;

    static NodeLoaderPtr create();

    virtual ~Scale9SpriteLoader() override;

    virtual cocos2d::Node* createNode() const override;

    virtual std::string getClassName() const override;

protected:
    /// Constructs a sprite loader.
    Scale9SpriteLoader();

    virtual void addReadHandlers(PropertyHandler& handler) override;
    virtual void addWriteHandlers(PropertyHandler& handler) override;
    virtual void addDefaultProperties(PropertyWriter& writer) override;

    virtual Self* cloneRaw() const override;
};
} // namespace ee

#endif // EE_PARSER_SCALE_9_SPRITE_LOADER_HPP
