#ifndef EE_EDITOR_SPRITE_SHEET_HPP
#define EE_EDITOR_SPRITE_SHEET_HPP

#include <QString>
#include <QVector>

namespace ee {
class SpriteSheet {
private:
    using Self = SpriteSheet;

public:
    explicit SpriteSheet(const QString& content);

    const QVector<QString>& getFrames() const;

private:
    QVector<QString> frames_;
};
} // namespace ee

#endif // EE_EDITOR_SPRITE_SHEET_HPP
