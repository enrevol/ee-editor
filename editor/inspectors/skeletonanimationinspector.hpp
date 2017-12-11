#ifndef EE_EDITOR_SKELETON_ANIMATION_INSEPCTOR_HPP
#define EE_EDITOR_SKELETON_ANIMATION_INSEPCTOR_HPP

#include "inspectorgroup.hpp"

namespace ee {
class SkeletonAnimationInspector : public InspectorGroup {
private:
    using Self = SkeletonAnimationInspector;
    using Super = InspectorGroup;

public:
    explicit SkeletonAnimationInspector(QWidget* parent = nullptr);
};
} // namespace ee

#endif // EE_EDITOR_SKELETON_ANIMATION_INSEPCTOR_HPP
