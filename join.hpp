#ifndef BASIC_STRING_JOIN_HPP_HEADER
#define BASIC_STRING_JOIN_HPP_HEADER
#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER
#include "config.hpp"
#include "detail.hpp"
#include <string>

NAMESPACE_BEGIN

template <typename char_t, typename traits_t, typename allocator_t, typename container_t>
std::basic_string<char_t, traits_t, allocator_t>
join(container_t const& __strings,
	 std::basic_string<char_t, traits_t, allocator_t> const& __delimiter) {
  using string_type = std::basic_string<char_t, traits_t, allocator_t>;
  string_type __joined;
  size_t ncount = __strings.size();
  for (const string_type& s : __strings) {
    __joined += s;
    if (--ncount > 0)
      __joined += __delimiter;
  }
  return __joined;
}

template <typename char_t, typename container_t>
std::basic_string<char_t>
join(container_t const& __strings,
     char_t const __delimiter) {
  using string_type = std::basic_string<char_t>;
  string_type __joined;
  size_t ncount = __strings.size();
  for (const string_type& s : __strings) {
    __joined += s;
    if (--ncount > 0)
      __joined.push_back(__delimiter);
  }
  return __joined;
}

template <typename char_t, typename container_t>
std::basic_string<char_t>
join(container_t const& _strings,
     char_t const *_delimiter) {
  return join(_strings, detail::make_safe_string(_delimiter));
}

template <typename char_t, typename traits_t, typename allocator_t, typename container_t>
std::basic_string<char_t, traits_t, allocator_t>
join_to_string(container_t const& __values,
               std::basic_string<char_t, traits_t, allocator_t> const& __delimiter) {
  using string_type = std::basic_string<char_t, traits_t, allocator_t>;
  string_type __joined, strval;
  size_t ncount = __values.size();
  for (auto const& val : __values) {
    detail::to_string(val, strval);
    __joined += strval;
    if (--ncount > 0)
      __joined += __delimiter;
  }
  return __joined;
}

template <typename char_t, typename container_t>
std::basic_string<char_t>
join_to_string(container_t const& __values,
               char_t const __delimiter) {
  using string_type = std::basic_string<char_t>;
  string_type __joined, strval;
  size_t ncount = __values.size();
  for (auto const& val : __values) {
    detail::to_string(val, strval);
    __joined += strval;
    if (--ncount > 0)
      __joined += __delimiter;
  }
  return __joined;
}

template <typename char_t, typename container_t>
std::basic_string<char_t>
join_to_string(container_t const& _values,
               char_t const *_delimiter) {
  return join_to_string(_values,
      detail::make_safe_string(_delimiter));
}

NAMESPACE_END

#endif // BASIC_STRING_JOIN_HPP_HEADER
