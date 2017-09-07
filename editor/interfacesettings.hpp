#ifndef EE_EDITOR_INTERFACE_SETTINGS_HPP
#define EE_EDITOR_INTERFACE_SETTINGS_HPP

#include "iserializable.hpp"
#include "optional.hpp"

#include <parser/nodegraph.hpp>

#include <QFileInfo>

namespace ee {
class InterfaceSettings : public ISerializable {
private:
    using Self = InterfaceSettings;

public:
    explicit InterfaceSettings(const QFileInfo& interfacePath);

    virtual ~InterfaceSettings() override;

    /// Gets the project's path.
    const QFileInfo& getInterfacePath() const;

    const std::optional<NodeGraph>& getNodeGraph() const;

    void setNodeGraph(const NodeGraph& graph);

    virtual bool deserialize(const QJsonObject& json) override;
    virtual void serialize(QJsonObject& json) const override;

    /// Attempts to read from file.
    bool read();

    /// Attempts to write to file.
    bool write() const;

private:
    QFileInfo interfacePath_;
    std::optional<NodeGraph> graph_;
};
} // namespace ee

#endif // EE_EDITOR_INTERFACE_SETTINGS_HPP
