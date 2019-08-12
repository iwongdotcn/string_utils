#ifndef BASIC_STRING_FIND_HPP_HEADER
#define BASIC_STRING_FIND_HPP_HEADER
#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER
#include "config.hpp"
#include "detail.hpp"
#include "case_ignore.hpp"
#include <string>

NAMESPACE_BEGIN

template <typename char_t, typename traits_t, typename allocator_t>
size_t find(std::basic_string<char_t, traits_t, allocator_t> const& __input,
	std::basic_string<char_t, traits_t, allocator_t> const& __search,
	size_t __pos = 0) {
	return __input.find(__search, __pos);
}

template <typename char_t>
size_t find(std::basic_string<char_t> const& __input,
	char_t const* __search, size_t __pos = 0) {
	return find(__input, detail::make_safe_string(__search), __pos);
}

template <typename char_t, typename traits_t, typename allocator_t>
size_t ifind(std::basic_string<char_t, traits_t, allocator_t> const& __input,
	std::basic_string<char_t, traits_t, allocator_t> const& __search,
	size_t __pos = 0) {
	const char_t* __data = __input.data();
	const size_t __size = __input.size();
	const size_t __n = __search.size();

	if (__n == 0) {
		if (__pos <= __size)
			return __pos;
	}
	else if (__n <= __size) {
		for (; __pos <= __size - __n; ++__pos)
			if (case_ignore::eq(__data[__pos], __search[0])
				&& case_ignore::compare(__data + __pos + 1,
					&__search[1], __n - 1) == 0)
				return __pos;
	}
	return __input.npos;
}

template <typename char_t>
size_t ifind(std::basic_string<char_t> const& __input,
	char_t const* __search, size_t __pos = 0) {
	return ifind(__input, detail::make_safe_string(__search), __pos);
}

NAMESPACE_END

#endif // BASIC_STRING_FIND_HPP_HEADER
