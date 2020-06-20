#ifndef BASIC_STRING_UTILS_REPLACE_HPP_HEADER
#define BASIC_STRING_UTILS_REPLACE_HPP_HEADER
#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER
#include "config.hpp"
#include "detail.hpp"
#include "find.hpp"
#include <string>
#include <algorithm>

NAMESPACE_BEGIN

// case-sensitive
template <typename char_t, typename traits_t, typename allocator_t>
void replace(std::basic_string<char_t, traits_t, allocator_t>& __input,
	char_t const& __search, char_t const& __format) {
	std::replace(__input.begin(), __input.end(),
		__search, __format);
}

template <typename char_t, typename traits_t, typename allocator_t>
void replace(std::basic_string<char_t, traits_t, allocator_t>& __input,
	std::basic_string<char_t, traits_t, allocator_t> const& __search,
	std::basic_string<char_t, traits_t, allocator_t> const& __format) {
	if (__input.empty() || __search.empty())
		return;
	const size_t __n = __search.size();
	const size_t __off = __format.size();
	for (size_t lastPos = 0, findPos = 0; ;
		lastPos = findPos + __off) {
		findPos = find(__input, __search, lastPos);
		if (findPos == __input.npos)
			break;
		auto replaceBegin = std::next(__input.begin(), findPos);
		auto replaceEnd = std::next(replaceBegin, __n);
		__input.replace(replaceBegin, replaceEnd, __format);
	}
}

template <typename char_t>
void replace(std::basic_string<char_t>& __input,
	char_t const* __search, char_t const* __format) {
	replace(__input, detail::make_safe_string(__search),
		detail::make_safe_string(__format));
}


// case-sensitive copy
template <typename char_t, typename traits_t, typename allocator_t>
std::basic_string<char_t, traits_t, allocator_t>
replace_copy(std::basic_string<char_t, traits_t, allocator_t> const& __input,
    char_t const& __search, char_t const& __format) {
    return std::replace_copy(__input.begin(),
		__input.end(), __search, __format);
}

template <typename char_t, typename traits_t, typename allocator_t>
std::basic_string<char_t, traits_t, allocator_t>
replace_copy(std::basic_string<char_t, traits_t, allocator_t> const& __input,
    std::basic_string<char_t, traits_t, allocator_t> const& __search,
    std::basic_string<char_t, traits_t, allocator_t> const& __format) {
    auto __copy = __input;
    replace(__copy, __search, __format);
    return __copy;
}

template <typename char_t>
std::basic_string<char_t>
replace_copy(std::basic_string<char_t> const& __input,
	std::basic_string<char_t> const& __search, char_t const* __format) {
    auto __copy = __input;
    replace(__copy, __search, detail::make_safe_string(__format));
    return __copy;
}

template <typename char_t>
std::basic_string<char_t>
replace_copy(std::basic_string<char_t> const& __input, char_t const* __search,
	std::basic_string<char_t> const& __format) {
    auto __copy = __input;
    replace(__copy, detail::make_safe_string(__search), __format);
    return __copy;
}

template <typename char_t>
std::basic_string<char_t>
replace_copy(std::basic_string<char_t> const& __input,
    char_t const* __search, char_t const* __format) {
    auto __copy = __input;
    replace(__copy, detail::make_safe_string(__search),
		detail::make_safe_string(__format));
    return __copy;
}

template <typename char_t>
std::basic_string<char_t>
replace_copy(char_t const* __input, std::basic_string<char_t> const& __search,
	std::basic_string<char_t> const& __format) {
    auto __copy = detail::make_safe_string(__input);
    replace(__copy, __search, __format);
    return __copy;
}

template <typename char_t>
std::basic_string<char_t>
replace_copy(char_t const* __input,
	std::basic_string<char_t> const& __search, char_t const* __format) {
    auto __copy = detail::make_safe_string(__input);
    replace(__copy, __search, detail::make_safe_string(__format));
    return __copy;
}

template <typename char_t>
std::basic_string<char_t>
replace_copy(char_t const* __input, char_t const* __search,
	std::basic_string<char_t> const& __format) {
    auto __copy = detail::make_safe_string(__input);
    replace(__copy, detail::make_safe_string(__search), __format);
    return __copy;
}

template <typename char_t>
std::basic_string<char_t>
replace_copy(char_t const* __input,
    char_t const* __search, char_t const* __format) {
    auto __copy = detail::make_safe_string(__input);
    replace(__copy, detail::make_safe_string(__search),
        detail::make_safe_string(__format));
    return __copy;
}


// not case-sensitive
template <typename char_t, typename traits_t, typename allocator_t>
void ireplace(std::basic_string<char_t, traits_t, allocator_t>& __input,
	char_t const& __search, char_t const& __format) {
	std::replace_if(__input.begin(), __input.end(),
		std::bind1st(detail::traits_iequal<char_t, traits_t>(), __search),
		__format);
}

template <typename char_t, typename traits_t, typename allocator_t>
void ireplace(std::basic_string<char_t, traits_t, allocator_t>& __input,
	std::basic_string<char_t, traits_t, allocator_t> const& __search,
	std::basic_string<char_t, traits_t, allocator_t> const& __format) {
	using string_type = std::basic_string<char_t, traits_t, allocator_t>;

	if (__input.empty() || __search.empty())
		return;
	const size_t __n = __search.size();
	const size_t __off = __format.size();

	for (size_t lastPos = 0, findPos = 0; ;
		lastPos = findPos + __off) {
		findPos = ifind(__input, __search, lastPos);
		if (findPos == string_type::npos)
			break;
		auto replaceBegin = std::next(__input.begin(), findPos);
		auto replaceEnd = std::next(replaceBegin, __n);
		__input.replace(replaceBegin, replaceEnd, __format);
	}
}

template <typename char_t>
void ireplace(std::basic_string<char_t>& __input,
	char_t const* __search, char_t const* __format) {
	ireplace(__input, detail::make_safe_string(__search),
		detail::make_safe_string(__format));
}


// not case-sensitive copy
template <typename char_t, typename traits_t, typename allocator_t>
std::basic_string<char_t, traits_t, allocator_t>
ireplace_copy(std::basic_string<char_t, traits_t, allocator_t> const& __input,
	char_t const& __search, char_t const& __format) {
	return std::replace_copy_if(__input.begin(), __input.end(),
		std::bind1st(detail::traits_iequal<char_t, traits_t>(), __search),
		__format);
}

template <typename char_t, typename traits_t, typename allocator_t>
std::basic_string<char_t, traits_t, allocator_t>
ireplace_copy(std::basic_string<char_t, traits_t, allocator_t> const& __input,
	std::basic_string<char_t, traits_t, allocator_t> const& __search,
	std::basic_string<char_t, traits_t, allocator_t> const& __format) {
	auto __copy = __input;
	ireplace(__copy, __search, __format);
	return __copy;
}

template <typename char_t>
std::basic_string<char_t>
ireplace_copy(std::basic_string<char_t> const& __input,
	std::basic_string<char_t> const& __search, char_t const* __format) {
    auto __copy = __input;
    ireplace(__copy, __search, detail::make_safe_string(__format));
    return __copy;
}

template <typename char_t>
std::basic_string<char_t>
ireplace_copy(std::basic_string<char_t> const& __input,
    char_t const* __search, std::basic_string<char_t> const& __format) {
    auto __copy = __input;
    ireplace(__copy, detail::make_safe_string(__search), __format);
    return __copy;
}

template <typename char_t>
std::basic_string<char_t>
ireplace_copy(std::basic_string<char_t> const& __input,
	char_t const* __search, char_t const* __format) {
    auto __copy = __input;
    ireplace(__copy, detail::make_safe_string(__search),
		detail::make_safe_string(__format));
    return __copy;
}

template <typename char_t>
std::basic_string<char_t>
ireplace_copy(char_t const* __input,
	std::basic_string<char_t> const& __search, std::basic_string<char_t> const& __format) {
    auto __copy = detail::make_safe_string(__input);
    ireplace(__copy, __search, __format);
    return __copy;
}

template <typename char_t>
std::basic_string<char_t>
ireplace_copy(char_t const* __input,
    char_t const* __search, std::basic_string<char_t> const& __format) {
    auto __copy = detail::make_safe_string(__input);
    ireplace(__copy, detail::make_safe_string(__search), __format);
    return __copy;
}

template <typename char_t>
std::basic_string<char_t>
ireplace_copy(char_t const* __input,
    std::basic_string<char_t> const& __search, char_t const* __format) {
    auto __copy = detail::make_safe_string(__input);
    ireplace(__copy, __search, detail::make_safe_string(__format));
    return __copy;
}

template <typename char_t>
std::basic_string<char_t>
ireplace_copy(char_t const* __input,
    char_t const* __search, char_t const* __format) {
    auto __copy = detail::make_safe_string(__input);
    ireplace(__copy, detail::make_safe_string(__search),
		detail::make_safe_string(__format));
    return __copy;
}

NAMESPACE_END

#endif // BASIC_STRING_UTILS_REPLACE_HPP_HEADER
