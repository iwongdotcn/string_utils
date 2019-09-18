#ifndef BASIC_STRING_UTILS_HELPER_HPP
#define BASIC_STRING_UTILS_HELPER_HPP

#include "config.hpp"
#include "detail.hpp"

NAMESPACE_BEGIN

template <typename char_t,
    typename traits_t = std::char_traits<char_t>,
    typename allocator_t = std::allocator<char_t>>
    std::basic_string<char_t, traits_t, allocator_t>
    make_string(char_t const* __unsafe) {
    return detail::make_safe_string(__unsafe);
}

NAMESPACE_END

#endif // BASIC_STRING_UTILS_HELPER_HPP
