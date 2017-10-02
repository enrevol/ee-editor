#ifndef EE_EDITOR_SPRITE_INSPECTOR_LOADER_HPP
#define EE_EDITOR_SPRITE_INSPECTOR_LOADER_HPP

#include "nodeinspectorloader.hpp"

namespace ee {
class SpriteInspectorLoader : public NodeInspectorLoader {
private:
    using Self = SpriteInspectorLoader;
    using Super = NodeInspectorLoader;

public:
    static InspectorLoaderPtr create();

    virtual ~SpriteInspectorLoader() override;

    virtual QVector<InspectorGroup*> createInspectors() const override;

    virtual QString getClassName() const override;

protected:
    SpriteInspectorLoader();
};
} // namespace ee

#endif // EE_EDITOR_SPRITE_INSPECTOR_LOADER_HPP
