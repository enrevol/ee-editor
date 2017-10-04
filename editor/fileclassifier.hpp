#ifndef EE_EDITOR_FILE_CLASSIFIER_HPP
#define EE_EDITOR_FILE_CLASSIFIER_HPP

#include <QFileInfo>
#include <QString>

namespace ee {
class FileClassifier {
private:
    using Self = FileClassifier;

public:
    explicit FileClassifier(const QString& path);
    explicit FileClassifier(const QFileInfo& info);

    bool isImage() const;
    bool isSpriteSheet() const;
    bool isInterface() const;

private:
    QFileInfo info_;
};
} // namespace ee

#endif // EE_EDITOR_FILE_CLASSIFIER_HPP
