#ifndef EE_EDITOR_OPTIONAL_HPP
#define EE_EDITOR_OPTIONAL_HPP

#if __has_include(<optional>)
#include <optional>
#else
#include <optional/optional.hpp>
namespace std {
using std::experimental::optional;
using std::experimental::nullopt;
} // namespace std
#endif

#endif // EE_EDITOR_OPTIONAL_HPP
