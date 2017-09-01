#ifndef EE_EDITOR_GLSL_COMPONENT_HPP
#define EE_EDITOR_GLSL_COMPONENT_HPP

namespace ee {
enum class GLSLComponent {
    Background,
    Normal,
    Comment,
    Number,
    String,
    Operator,
    Identifier,
    Keyword,
    BuiltIn,
    Sidebar,
    LineNumber,
    Cursor,
    Marker
};
} // namespace ee

#endif // EE_EDITOR_GLSL_COMPONENT_HPP
