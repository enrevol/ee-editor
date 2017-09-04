#include <ciso646>

#include "settings.hpp"

namespace ee {
namespace key {
constexpr auto last_browsing_path = "last_browsing_path";
} // namespace key

Settings::Settings()
    : settings_("ee", "editor") {}

QDir Settings::getLastBrowsingPath() const {
    if (not settings_.contains(key::last_browsing_path)) {
        return QDir::currentPath();
    }
    auto value = settings_.value(key::last_browsing_path);
    return QDir(value.toString());
}

void Settings::setLastBrowsingPath(const QDir& dir) {
    settings_.setValue(key::last_browsing_path, dir.absolutePath());
}
} // namespace ee
