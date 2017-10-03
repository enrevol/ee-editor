#ifndef EE_EDITOR_RESOURCE_TREE_HPP
#define EE_EDITOR_RESOURCE_TREE_HPP

#include <QFileInfo>
#include <QTreeWidget>

namespace ee {
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
    void fileSelected(const QString& path);

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

    bool listened_;
};
} // namespace ee

#endif // EE_EDITOR_RESOURCE_TREE_HPP
