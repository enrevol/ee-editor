#ifndef EE_EDITOR_SPRITE_INSPECTOR_LOADER_HPP
#define EE_EDITOR_SPRITE_INSPECTOR_LOADER_HPP

#include "inspectorloader.hpp"

namespace ee {
class SpriteInspectorLoader : public InspectorLoader {
private:
    using Self = SpriteInspectorLoader;
    using Super = InspectorLoader;

public:
    static InspectorLoaderPtr create();

    virtual ~SpriteInspectorLoader() override;

    virtual Inspector* createInspector() const override;

    virtual bool isRoot() const override;

    virtual QString getParent() const override;

    virtual QString getName() const override;

protected:
    SpriteInspectorLoader();
};
} // namespace ee

#endif // EE_EDITOR_SPRITE_INSPECTOR_LOADER_HPP
