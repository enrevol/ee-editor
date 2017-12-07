#ifndef EE_EDITOR_LAYER_COLOR_INSPECTOR_LOADER_HPP
#define EE_EDITOR_LAYER_COLOR_INSPECTOR_LOADER_HPP

#include "nodeinspectorloader.hpp"

namespace ee {
class LayerColorInspectorLoader : public NodeInspectorLoader {
private:
    using Self = LayerColorInspectorLoader;
    using Super = NodeInspectorLoader;

public:
    static InspectorLoaderPtr create();

    virtual ~LayerColorInspectorLoader() override;

    virtual QVector<InspectorGroup*> createInspectors() const override;

    virtual QString getClassName() const override;

protected:
    LayerColorInspectorLoader();
};
} // namespace ee
#endif // EE_EDITOR_LAYER_COLOR_INSPECTOR_LOADER_HPP
