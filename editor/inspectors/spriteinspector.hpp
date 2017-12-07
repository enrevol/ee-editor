#ifndef EE_EDITOR_SPRITE_LOADER_HPP
#define EE_EDITOR_SPRITE_LOADER_HPP

#include "inspectorgroup.hpp"

namespace ee {
class SpriteInspector : public InspectorGroup {
private:
    using Self = SpriteInspector;
    using Super = InspectorGroup;

public:
    explicit SpriteInspector(QWidget* parent = nullptr);

private:
};
} // namespace ee

#endif // EE_EDITOR_SPRITE_LOADER_HPP
