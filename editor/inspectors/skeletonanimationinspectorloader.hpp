#ifndef EE_EDITOR_SKELETON_ANIMATION_INSPECTOR_LOADER_HPP
#define EE_EDITOR_SKELETON_ANIMATION_INSPECTOR_LOADER_HPP

#include "inspectorloader.hpp"

namespace ee {
class SkeletonAnimationInspectorLoader : public InspectorLoader {
private:
    using Self = SkeletonAnimationInspectorLoader;
    using Super = InspectorLoader;

public:
    static InspectorLoaderPtr create();

    virtual ~SkeletonAnimationInspectorLoader() override;

    virtual Inspector* createInspector() const override;

    virtual bool isRoot() const override;

    virtual QString getParent() const override;

    virtual QString getName() const override;

protected:
    SkeletonAnimationInspectorLoader();
};
} // namespace ee

#endif // EE_EDITOR_SKELETON_ANIMATION_INSPECTOR_LOADER_HPP
