#ifndef EE_EDITOR_SETTINGS_HPP
#define EE_EDITOR_SETTINGS_HPP

#include <QDir>
#include <QSettings>

namespace ee {
class Settings {
public:
    Settings();

    QDir getLastBrowsingPath() const;
    void setLastBrowsingPath(const QDir& dir);

private:
    QSettings settings_;
};
} // namespace ee

#endif // EE_EDITOR_SETTINGS_HPP
