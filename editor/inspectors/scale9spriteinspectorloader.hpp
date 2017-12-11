#ifndef EE_EDITOR_SCALE_9_SPRITE_INSPECTOR_LOADER_HPP
#define EE_EDITOR_SCALE_9_SPRITE_INSPECTOR_LOADER_HPP

#include "inspectorloader.hpp"

namespace ee {
class Scale9SpriteInspectorLoader : public InspectorLoader {
private:
    using Self = Scale9SpriteInspectorLoader;
    using Super = InspectorLoader;

public:
    static InspectorLoaderPtr create();

    virtual ~Scale9SpriteInspectorLoader() override;

    virtual Inspector* createInspector() const override;

    virtual bool isRoot() const override;

    virtual QString getParent() const override;

    virtual QString getName() const override;

protected:
    Scale9SpriteInspectorLoader();
};
} // namespace ee

#endif // EE_EDITOR_SCALE_9_SPRITE_INSPECTOR_LOADER_HPP
