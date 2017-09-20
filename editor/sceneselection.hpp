#ifndef EE_EDITOR_SCENE_SELECTION_HPP
#define EE_EDITOR_SCENE_SELECTION_HPP

#include <QVector>

namespace ee {
class SceneSelection {
private:
    using Self = SceneSelection;

public:
    static Self emptySelection();
    static Self rootSelection();
    static Self singleSelection(const QVector<int>& ancestors, int child);
    static Self multipleSelection(const QVector<int>& ancestors,
                                  const QVector<int>& children);

protected:
    explicit SceneSelection(const QVector<int>& ancestors,
                            const QVector<int>& children);

    bool isEmpty() const;
    const QVector<int>& getAncestorIndices() const;
    const QVector<int>& getChildrenIndices() const;

private:
    QVector<int> ancestorIndices_;
    QVector<int> childrenIndices_;
};
} // namespace ee

#endif // EE_EDITOR_SCENE_SELECTION_HPP
