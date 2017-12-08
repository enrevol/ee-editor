#ifndef EE_PARSER_OPTIONAL_HPP
#define EE_PARSER_OPTIONAL_HPP

#if __has_include(<optional>)
#include <optional>
#else
#include <optional/optional.hpp>
namespace std {
using std::experimental::optional;
using std::experimental::nullopt;
using std::experimental::make_optional;
} // namespace std
#endif

namespace ee {
template <class T, class F>
auto map(const std::optional<T>& opt, F&& f) -> std::result_of_t<F(T)> {
    if (opt.has_value()) {
        return std::forward<F>(f)(opt.value());
    }
    return std::nullopt;
}
} // namespace ee

#endif // EE_PARSER_OPTIONAL_HPP
