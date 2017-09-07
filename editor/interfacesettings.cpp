#include <ciso646>

#include "interfacesettings.hpp"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace ee {
namespace key {
constexpr auto resource_paths = "resource_paths";
constexpr auto publish_directory = "publish_directory";
} // namespace key

namespace defaults {
constexpr auto publish_directory = "generated";
} // namespace defaults

using Self = InterfaceSettings;

Self::InterfaceSettings(const QFileInfo& interfacePath)
    : interfacePath_(interfacePath) {}

Self::~InterfaceSettings() {}

const QFileInfo& Self::getInterfacePath() const {
    return interfacePath_;
}

bool Self::read() {
    QFile file(getInterfacePath().absoluteFilePath());
    if (not file.open(QIODevice::OpenModeFlag::ReadOnly)) {
        qWarning() << "Could't open project file to read";
        return false;
    }

    auto obj = QJsonDocument().fromJson(file.readAll()).object();
    return deserialize(obj);
}

bool Self::write() const {
    QFile file(getInterfacePath().absoluteFilePath());
    if (not file.open(QIODevice::OpenModeFlag::WriteOnly)) {
        qWarning() << "Could't open project file to write";
        return false;
    }

    QJsonObject json;
    serialize(json);
    QJsonDocument doc(json);
    file.write(doc.toJson());
    return true;
}

bool Self::deserialize(const QJsonObject& json) {
    // FIXME.
    return true;
}

void Self::serialize(QJsonObject& json) const {
    // FIXME.
}
} // namespace ee
