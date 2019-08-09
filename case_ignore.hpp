#ifndef BASIC_STRING_CASE_IGNORE_HPP_HEADER
#define BASIC_STRING_CASE_IGNORE_HPP_HEADER
#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER
#include "config.hpp"
#include <cstring>

NAMESPACE_BEGIN

namespace case_ignore {

template <typename char_t>
bool
eq(const char_t& __c1, const char_t& __c2) noexcept
{
	return std::toupper(static_cast<unsigned char>(__c1))
		== std::toupper(static_cast<unsigned char>(__c2));
}

template <typename char_t>
bool
lt(const char_t& __c1, const char_t& __c2) noexcept
{
	return std::toupper(static_cast<unsigned char>(__c1))
		< std::toupper(static_cast<unsigned char>(__c2));
}

template <typename char_t>
int
compare(const char_t* __s1, const char_t* __s2, size_t __n)
{
	for (size_t __i = 0; __i < __n; ++__i)
		if (lt(__s1[__i], __s2[__i]))
			return -1;
		else if (lt(__s2[__i], __s1[__i]))
			return 1;
	return 0;
}

}

NAMESPACE_END

#endif // BASIC_STRING_CASE_IGNORE_HPP_HEADER
