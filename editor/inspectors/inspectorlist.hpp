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
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_LIST_HPP
