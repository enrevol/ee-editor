#include "sceneselection.hpp"

namespace ee {
using Self = SceneSelection;

Self Self::emptySelection() {
    return Self(false, {}, {});
}

Self Self::rootSelection() {
    return Self(true, {}, {});
}

Self Self::singleSelection(const QVector<int>& ancestors, int child) {
    return Self(false, ancestors, {child});
}

Self Self::multipleSelection(const QVector<int>& ancestors,
                             const QVector<int>& children) {
    Q_ASSERT(not children.isEmpty());
    return Self(false, ancestors, children);
}

Self::SceneSelection(bool root, const QVector<int>& ancestors,
                     const QVector<int>& children)
    : root_(root)
    , ancestorIndices_(ancestors)
    , childrenIndices_(children) {}

bool Self::isEmpty() const {
    return not isRoot() && getAncestorIndices().isEmpty() &&
           getChildrenIndices().isEmpty();
}

bool Self::isRoot() const {
    return root_;
}

const QVector<int>& Self::getAncestorIndices() const {
    return ancestorIndices_;
}

const QVector<int>& Self::getChildrenIndices() const {
    return childrenIndices_;
}
} // namespace ee
