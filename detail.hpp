/******************************************************************************
 The MIT License

 Copyright (c) 2019-2019 Wang Jun
 Copyright (c) 2009-2015 Leandro T. C. Melo

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
******************************************************************************/

#ifndef BASIC_STRING_UTILS_DETAIL_HPP
#define BASIC_STRING_UTILS_DETAIL_HPP

#include "config.hpp"
#include <string>
#include <functional>
#include <locale>

NAMESPACE_BEGIN

DETAIL_NAMESPACE_BEGIN

//Constants imply internal linkage. No problem defining in this header.
char const* const space = "\x20\x09\x0A\x0B\x0C\x0D";

char const to_lower_table[128] =
  {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    0x40,
    //Begin characters converted to lower.
          0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A,
    //End.
                                                                      0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
    0X60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F
  };

char const to_upper_table[128] =
  {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
    0x60,
    //Begin characters converted to upper.
          0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A,
    //End.
                                                                      0x7B, 0x7C, 0x7D, 0x7E, 0x7F
  };


inline void ascii_to_lower(char & c)
{
  if (c > 0)
    c = *(to_lower_table + c);
}

inline void ascii_to_upper(char & c)
{
  if (c > 0)
    c = *(to_upper_table + c);
}

inline bool ascii_iequal(char c1, char c2)
{
  ascii_to_upper(c1);
  ascii_to_upper(c2);
  return (c1 == c2);
}

const std::locale default_locale;

template <class char_t>
class not_space //: public std::unary_function<bool, char_t>
{
public:
  not_space(std::locale const& loc)
      : facet_(std::use_facet<std::ctype<char_t> >(loc))
  {}

  bool operator()(char_t character)
  {
    if (!(facet_.is(std::ctype_base::space, character)))
      return true;
    return false;
  }

private:
  std::ctype<char_t> const& facet_;
};

template <class char_t>
class not_space_nor_any_of
//  : public std::unary_function<bool, char_t>
{
public:
  using ctype_t = std::ctype<char_t>;
  using string_t = std::basic_string<char_t>;

  not_space_nor_any_of(std::locale const& loc,
                       char_t const * test)
    : facet_(std::use_facet<ctype_t>(loc))
    , test_(test ? test : string_t())
  {}

  bool operator()(char_t character) const
  {
    return !facet_.is(std::ctype_base::space, character)
      && test_.find(character) == string_t::npos;
  }

private:
  ctype_t const& facet_;
  string_t const test_;
};

template <class char_t, class traits_t>
struct traits_equal //: public std::binary_function<bool, char_t, char_t>
{
  bool operator()(char_t c1, char_t c2)
  {
    return traits_t::eq(c1, c2);
  }
};

template <class char_t, class traits_t>
class traits_iequal //: public std::binary_function<bool, char_t, char_t>
{
public:
  traits_iequal(std::locale const& loc):facet_(std::use_facet<std::ctype<char_t> >(loc))
  {}

  bool operator()(char_t c1, char_t c2)
  {
    return traits_t::eq(facet_.tolower(c1), facet_.tolower(c2));
  }

private:
  std::ctype<char_t> const& facet_;
};

template <class basic_string_t>
bool
check_size(basic_string_t const& input, basic_string_t const& test)
{
  return input.size() >= test.size();
}


template <typename char_t,
          typename traits_t = std::char_traits<char_t>,
          typename allocator_t = std::allocator<char_t>>
std::basic_string<char_t, traits_t, allocator_t>
make_safe_string(char_t const *__unsafe) {
  using string_type = std::basic_string<char_t,
    traits_t, allocator_t>;
  return (__unsafe) ? string_type(__unsafe) : string_type();
}

template <typename value_t>
void
to_string(const value_t& _value, std::basic_string<char>& _string) {
  _string = std::to_string(_value);
}

template <typename value_t>
void
to_string(const value_t& _value, std::basic_string<wchar_t>& _string) {
  _string = std::to_wstring(_value);
}

NAMESPACE_END

NAMESPACE_END

#endif
