/******************************************************************************
 The MIT License

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

#ifndef BASIC_STRING_UTILS_PREDICATE_HPP
#define BASIC_STRING_UTILS_PREDICATE_HPP

#include "config.hpp"
#include "detail.hpp"
#include <string>
#include <algorithm>

NAMESPACE_BEGIN

template <class char_t, class traits_t, class allocator_t>
bool
starts_with(std::basic_string<char_t, traits_t, allocator_t> const& input,
            std::basic_string<char_t, traits_t, allocator_t> const& test)
{
  if (!detail::check_size(input, test))
    return false;

  return std::equal(test.begin(), test.end(),
                    input.begin(),
                    detail::traits_equal<char_t, traits_t>());
}

template <class char_t, class traits_t, class allocator_t>
bool
starts_with(std::basic_string<char_t, traits_t, allocator_t> const& input,
            char const* test)
{
  return starts_with(input, detail::make_safe_string(test));
}

template <class char_t, class traits_t, class allocator_t>
bool
starts_with(std::basic_string<char_t, traits_t, allocator_t> const& input,
            wchar_t const* test)
{
  return starts_with(input, detail::make_safe_string(test));
}

template <class allocator_t>
bool
istarts_with(std::basic_string<char, std::char_traits<char>, allocator_t> const& input,
             std::basic_string<char, std::char_traits<char>, allocator_t> const& test)
{
  if (!detail::check_size(input, test))
    return false;

  return std::equal(test.begin(), test.end(),
                    input.begin(),
                    detail::ascii_iequal);
}

template <class allocator_t>
bool
istarts_with(std::basic_string<char, std::char_traits<char>, allocator_t> const& input,
             char const* test)
{
  return istarts_with(input, detail::make_safe_string(test));
}

template <class char_t, class traits_t, class allocator_t>
bool
istarts_with(std::basic_string<char_t, traits_t, allocator_t> const& input,
             std::basic_string<char_t, traits_t, allocator_t> const& test,
             std::locale const& loc)
{
  if (!detail::check_size(input, test))
    return false;

  return std::equal(test.begin(), test.end(),
                    input.begin(),
                    detail::traits_iequal<char_t, traits_t>(loc));
}

template <class char_t, class traits_t, class allocator_t>
bool
istarts_with(std::basic_string<char_t, traits_t, allocator_t> const& input,
             char const* test,
             std::locale const& loc)
{
  return istarts_with(input, detail::make_safe_string(test), loc);
}

template <class char_t, class traits_t, class allocator_t>
bool
istarts_with(std::basic_string<char_t, traits_t, allocator_t> const& input,
             wchar_t const* test,
             std::locale const& loc)
{
  return istarts_with(input, detail::make_safe_string(test), loc);
}

template <class char_t, class traits_t, class allocator_t>
bool
ends_with(std::basic_string<char_t, traits_t, allocator_t> const& input,
          std::basic_string<char_t, traits_t, allocator_t> const& test)
{
  if (!detail::check_size(input, test))
    return false;

  return std::equal(test.rbegin(), test.rend(),
                    input.rbegin(),
                    detail::traits_equal<char_t, traits_t>());
}

template <class char_t, class traits_t, class allocator_t>
bool
ends_with(std::basic_string<char_t, traits_t, allocator_t> const& input,
          char const* test)
{
  return ends_with(input, detail::make_safe_string(test));
}

template <class char_t, class traits_t, class allocator_t>
bool
ends_with(std::basic_string<char_t, traits_t, allocator_t> const& input,
          wchar_t const* test)
{
  return ends_with(input, detail::make_safe_string(test));
}


template <class allocator_t>
bool
iends_with(std::basic_string<char, std::char_traits<char>, allocator_t> const& input,
           std::basic_string<char, std::char_traits<char>, allocator_t> const& test)
{
  if (!detail::check_size(input, test))
    return false;

  return std::equal(test.rbegin(), test.rend(),
                    input.rbegin(),
                    detail::ascii_iequal);
}

template <class allocator_t>
bool
iends_with(std::basic_string<char, std::char_traits<char>, allocator_t> const& input,
           char const* test)
{
  return iends_with(input, detail::make_safe_string(test));
}

template <class char_t, class traits_t, class allocator_t>
bool
iends_with(std::basic_string<char_t, traits_t, allocator_t> const& input,
           std::basic_string<char_t, traits_t, allocator_t> const& test,
           std::locale const& loc)
{
  if (!detail::check_size(input, test))
    return false;

  return std::equal(test.rbegin(), test.rend(),
                    input.rbegin(),
                    detail::traits_iequal<char_t, traits_t>(loc));
}

template <class char_t, class traits_t, class allocator_t>
bool
iends_with(std::basic_string<char_t, traits_t, allocator_t> const& input,
           char const* test,
           std::locale const& loc)
{
  return iends_with(input, detail::make_safe_string(test), loc);
}

template <class char_t, class traits_t, class allocator_t>
bool
iends_with(std::basic_string<char_t, traits_t, allocator_t> const& input,
           wchar_t const* test,
           std::locale const& loc)
{
  return iends_with(input, detail::make_safe_string(test), loc);
}

template <class char_t, class traits_t, class allocator_t>
bool
contains(std::basic_string<char_t, traits_t, allocator_t> const& input,
         std::basic_string<char_t, traits_t, allocator_t> const& test)
{
  if (std::search(input.begin(), input.end(), test.begin(), test.end(),
                  detail::traits_equal<char_t, traits_t>()) != input.end())
    return true;
  return false;
}

template <class char_t, class traits_t, class allocator_t>
bool
contains(std::basic_string<char_t, traits_t, allocator_t> const& input,
         char const* test)
{
  return contains(input, detail::make_safe_string(test));
}

template <class char_t, class traits_t, class allocator_t>
bool
contains(std::basic_string<char_t, traits_t, allocator_t> const& input,
         wchar_t const* test)
{
  return contains(input, detail::make_safe_string(test));
}

template <class allocator_t>
bool
icontains(std::basic_string<char, std::char_traits<char>, allocator_t> const& input,
          std::basic_string<char, std::char_traits<char>, allocator_t> const& test)
{
  if (std::search(input.begin(), input.end(), test.begin(), test.end(),
                  detail::ascii_iequal) != input.end())
    return true;
  return false;

}

template <class allocator_t>
bool
icontains(std::basic_string<char, std::char_traits<char>, allocator_t> const& input,
          char const* test)
{
  return icontains(input, detail::make_safe_string(test));
}

template <class char_t, class traits_t, class allocator_t>
bool
icontains(std::basic_string<char_t, traits_t, allocator_t> const& input,
          std::basic_string<char_t, traits_t, allocator_t> const& test,
          std::locale const& loc)
{
  if (std::search(input.begin(), input.end(), test.begin(), test.end(),
                  detail::traits_iequal<char_t, traits_t>(loc)) != input.end())
    return true;
  return false;
}

template <class char_t, class traits_t, class allocator_t>
bool
icontains(std::basic_string<char_t, traits_t, allocator_t> const& input,
          char const* test,
          std::locale const& loc)
{
  return icontains(input, detail::make_safe_string(test), loc);
}

template <class char_t, class traits_t, class allocator_t>
bool
icontains(std::basic_string<char_t, traits_t, allocator_t> const& input,
          wchar_t const* test,
          std::locale const& loc)
{
  return icontains(input, detail::make_safe_string(test), loc);
}

template <class char_t, class traits_t, class allocator_t>
bool
equal(std::basic_string<char_t, traits_t, allocator_t> const& input,
	  std::basic_string<char_t, traits_t, allocator_t> const& test)
{
  return (input == test);
}

template <class char_t, class traits_t, class allocator_t>
bool
equal(std::basic_string<char_t, traits_t, allocator_t> const& input,
	  char_t const* test)
{
  return equal(input, detail::make_safe_string(test));
}

template <class char_t, class traits_t, class allocator_t>
bool
equal(char_t const* input,
	  std::basic_string<char_t, traits_t, allocator_t> const& test)
{
  return equal(detail::make_safe_string(input), test);
}

template <class char_t>
bool
equal(char_t const* input, char_t const* test)
{
  return equal(detail::make_safe_string(input),
    detail::make_safe_string(test));
}

template <class char_t, class traits_t, class allocator_t>
bool
iequal(std::basic_string<char_t, traits_t, allocator_t> const& input,
	   std::basic_string<char_t, traits_t, allocator_t> const& test)
{
  if (input.size() != test.size())
    return false;

  return std::equal(test.begin(), test.end(), input.begin(),
    detail::traits_iequal<char_t, traits_t>(std::locale()));
}

template <class char_t, class traits_t, class allocator_t>
bool
iequal(std::basic_string<char_t, traits_t, allocator_t> const& input,
	   char_t const* test)
{
  return iequal(input,
    detail::make_safe_string(test));
}

template <class char_t, class traits_t, class allocator_t>
bool
iequal(char_t const* input,
	   std::basic_string<char_t, traits_t, allocator_t> const& test)
{
  return iequal(detail::make_safe_string(input),
    test);
}

template <class char_t>
bool
iequal(char_t const* input, char_t const* test)
{
  return iequal(detail::make_safe_string(input),
    detail::make_safe_string(test));
}

NAMESPACE_END

#endif
