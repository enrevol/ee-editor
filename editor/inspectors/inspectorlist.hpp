#ifndef EE_EDITOR_INSPECTOR_LIST_HPP
#define EE_EDITOR_INSPECTOR_LIST_HPP

#include "inspectors/inspector.hpp"

namespace ee {
class InspectorList : public Inspector {
private:
    using Super = Inspector;
    using Self = InspectorList;

public:
    explicit InspectorList(QWidget* parent = nullptr);

    virtual ~InspectorList() override;

    /// Adds the specified inspector to this inspector list.
    /// @param inspector The desired inspector.
    virtual void addInspector(Inspector* inspector) = 0;

    /// Clears all inspectors from this inspector list.
    virtual void clearInspectors() = 0;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_LIST_HPP
