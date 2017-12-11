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

    virtual Inspector* createInspector() const override;

    virtual bool isRoot() const override;

    virtual QString getParent() const override;

    virtual QString getName() const override;

protected:
    NodeInspectorLoader();
};
} // namespace ee

#endif // EE_EDITOR_NODE_INSPECTOR_LOADER_HPP
