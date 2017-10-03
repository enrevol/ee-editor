#ifndef EE_EDITOR_SCALE_9_SPRITE_INSPECTOR_HPP
#define EE_EDITOR_SCALE_9_SPRITE_INSPECTOR_HPP

#include "inspectorgroup.hpp"

namespace ee {
class Scale9SpriteInspector : public InspectorGroup {
private:
    using Self = Scale9SpriteInspector;
    using Super = InspectorGroup;

public:
    explicit Scale9SpriteInspector(QWidget* parent = nullptr);

private:
};
} // namespace ee

#endif // EE_EDITOR_SCALE_9_SPRITE_INSPECTOR_HPP
