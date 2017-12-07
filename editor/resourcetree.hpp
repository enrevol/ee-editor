#ifndef EE_EDITOR_RESOURCE_TREE_HPP
#define EE_EDITOR_RESOURCE_TREE_HPP

#include <QFileInfo>
#include <QTreeWidget>

namespace ee {
/// Displays all resource files in the current project.
class ResourceTree : public QTreeWidget {
    Q_OBJECT

private:
    using Self = ResourceTree;
    using Super = QTreeWidget;

public:
    explicit ResourceTree(QWidget* parent = nullptr);

    void setListenToFileChangeEvents(bool enabled);
    void updateResourceDirectories();

Q_SIGNALS:
    /// Occurs when the user double-clicks an interface file.
    /// @param interfacePath The interface file's path, relative to the
    /// project's resource directories.
    void interfaceSelected(const QString& interfacePath);

    /// Occurs when the user clicks an image.
    /// @param imagePath The image file's path, relative to the project's
    /// resource directories.
    void imageSelected(const QString& imagePath);

    /// Occurs when the user clicks a sprite frame.
    /// @param spriteFrameName The sprite frame's name.
    void spriteFrameSelected(const QString& spriteFrameName);

    void noneSelected();

protected:
    void updateResourcePath(QTreeWidgetItem* item, const QFileInfo& info);

    virtual QMimeData*
    mimeData(const QList<QTreeWidgetItem*> items) const override;

    virtual QStringList mimeTypes() const override;

private:
    QSet<QString> saveExpandedItems();
    void restoreExpandedItems(const QSet<QString>& expandedItems);
    void reloadResources();
    QStack<QString> saveSelectedItem();
    void restoreSelectedItem(QStack<QString> names);
    QStringList getPathComponents(const QTreeWidgetItem* item) const;
    QString getPath(const QTreeWidgetItem* item) const;

    bool listened_;
};
} // namespace ee

#endif // EE_EDITOR_RESOURCE_TREE_HPP
