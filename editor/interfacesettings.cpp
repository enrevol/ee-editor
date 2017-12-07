#include <ciso646>

#include "interfacesettings.hpp"
#include "utils.hpp"

#include <parser/graphreader.hpp>
#include <parser/nodeloaderlibrary.hpp>

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace ee {
namespace key {
constexpr auto node_graph = "node_graph";
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

const std::optional<NodeGraph>& Self::getNodeGraph() const {
    return graph_;
}

void Self::setNodeGraph(const NodeGraph& graph) {
    graph_ = graph;

    NodeLoaderLibrary library;
    library.addDefaultLoaders();
    GraphReader reader(library);
    reader.addDefaultProperties(graph_.value());
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
    auto obj = json.value(key::node_graph).toObject();
    auto dict = convertToValue(obj).getMap();
    NodeGraph graph(dict);
    setNodeGraph(graph);
    return true;
}

void Self::serialize(QJsonObject& json) const {
    auto dict = getNodeGraph()->toDict();
    auto obj = convertToJson(Value(dict)).toObject();
    json[key::node_graph] = obj;
}
} // namespace ee
