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

    virtual Inspector* createInspector() const override;

    virtual bool isRoot() const override;

    virtual QString getParent() const override;

    virtual QString getName() const override;

protected:
    LayerColorInspectorLoader();
};
} // namespace ee
#endif // EE_EDITOR_LAYER_COLOR_INSPECTOR_LOADER_HPP
