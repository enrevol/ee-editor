#ifndef EE_EDITOR_NODE_INSPECTOR_LOADER_HPP
#define EE_EDITOR_NODE_INSPECTOR_LOADER_HPP

#include "inspectorloader.hpp"

namespace ee {
class NodeInspectorLoader : public InspectorLoader {
private:
    using Self = NodeInspectorLoader;

public:
    static InspectorLoaderPtr create();

    virtual ~NodeInspectorLoader();

    virtual QVector<InspectorGroup*> createInspectors() const override;

    virtual QString getClassName() const override;

protected:
    NodeInspectorLoader();
};
} // namespace ee

#endif // EE_EDITOR_NODE_INSPECTOR_LOADER_HPP
