#ifndef EE_EDITOR_SCALE_9_SPRITE_INSPECTOR_LOADER_HPP
#define EE_EDITOR_SCALE_9_SPRITE_INSPECTOR_LOADER_HPP

#include "spriteinspectorloader.hpp"

namespace ee {
class Scale9SpriteInspectorLoader : public SpriteInspectorLoader {
private:
    using Self = Scale9SpriteInspectorLoader;
    using Super = SpriteInspectorLoader;

public:
    static InspectorLoaderPtr create();

    virtual ~Scale9SpriteInspectorLoader() override;

    virtual QVector<InspectorGroup*> createInspectors() const override;

    virtual QString getClassName() const override;

protected:
    Scale9SpriteInspectorLoader();
};
} // namespace ee

#endif // EE_EDITOR_SCALE_9_SPRITE_INSPECTOR_LOADER_HPP
