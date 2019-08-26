#ifndef BASIC_STRING_UTILS_SPLIT_HPP_HEADER
#define BASIC_STRING_UTILS_SPLIT_HPP_HEADER
#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER
#include "config.hpp"
#include "detail.hpp"
#include <string>
#include <vector>

NAMESPACE_BEGIN

DETAIL_NAMESPACE_BEGIN

template <typename string_t>
struct tokenizer
{
  tokenizer(string_t const& _str)
    : offset_(0), string_(_str) {
  }
  tokenizer(string_t const& _str,
    string_t const& _delimiters)
    : offset_(0), string_(_str), delimiters_(_delimiters) {
  }
  tokenizer(string_t const& _str,
    typename string_t::value_type const* _delimiters)
    : tokenizer(_str, detail::make_safe_string(_delimiters)) {
  }

  bool next_token() {
    return next_token(delimiters_);
  }

  bool next_token(string_t const& delimiters) {
    size_t i = string_.find_first_not_of(delimiters, offset_);
    if (i == string_t::npos) {
      offset_ = string_.length();
      return false;
    }

    size_t j = string_.find_first_of(delimiters, i);
    if (j == string_t::npos) {
      token_ = string_.substr(i);
      offset_ = string_.length();
      return true;
    }

    token_ = string_.substr(i, j - i);
    offset_ = j;
    return true;
  }

  const string_t& get_token() const {
    return token_;
  }

  void reset() {
    offset_ = 0;
  }

  size_t offset_;
  const string_t string_;
  string_t token_;
  string_t delimiters_;
};

NAMESPACE_END

template <typename char_t, typename traits_t, typename allocator_t>
std::vector<std::basic_string<char_t, traits_t, allocator_t>>
split(std::basic_string<char_t, traits_t, allocator_t> const& __string,
      std::basic_string<char_t, traits_t, allocator_t> const& __delimiters) {
  using string_type = std::basic_string<char_t, traits_t, allocator_t>;

  std::vector<string_type> ss;
  detail::tokenizer<string_type> token(__string,
    __delimiters);
  for (; token.next_token(); ) {
    ss.push_back(token.get_token());
  }
  return ss;
}

template <typename char_t>
std::vector<std::basic_string<char_t>>
split(std::basic_string<char_t> const& __string,
      char_t const* __delimiters) {
  return split(__string,
    detail::make_safe_string(__delimiters));
}

template <typename char_t>
std::vector<std::basic_string<char_t>>
split(char_t const* __string,
      std::basic_string<char_t> const& __delimiters) {
  return split(detail::make_safe_string(__string),
    __delimiters);
}

template <typename char_t>
std::vector<std::basic_string<char_t>>
split(char_t const* __string,
      char_t const* __delimiters) {
  return split(detail::make_safe_string(__string),
    detail::make_safe_string(__delimiters));
}

NAMESPACE_END

#endif // BASIC_STRING_UTILS_SPLIT_HPP_HEADER
