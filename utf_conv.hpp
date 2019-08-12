#ifndef BASIC_STRING_UTF_CONV_HPP_HEADER
#define BASIC_STRING_UTF_CONV_HPP_HEADER
#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER
#include "config.hpp"
#include <cstring>
#include <string>
#include <locale>
#include <codecvt>

#if defined(_WIN32) || defined(_WINDOWS)
#include <windows.h>
#endif

NAMESPACE_BEGIN

inline int locale_is_utf8() {
	static int ret = 2;
	if (ret == 2) {
#if defined(_WIN32) || defined(_WINDOWS)
		ret = GetACP() == CP_UTF8;
#else
		char* s;
		ret = 1; // assumme UTF-8 if no locale
		if (((s = getenv("LC_CTYPE")) && *s) || ((s = getenv("LC_ALL")) && *s)
			|| ((s = getenv("LANG")) && *s)) {
			ret = (strstr(s, "utf") || strstr(s, "UTF"));
		}
#endif
	}
	return ret;
}

inline std::wstring utf8_to_unicode(std::string const& str) {
	size_t src_len = str.size();
	if (src_len == 0) {
		return std::wstring();
	}
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	return conv.from_bytes(str);
}

inline std::string unicode_to_utf8(std::wstring const& str) {
	size_t src_len = str.size();
	if (src_len == 0) {
		return std::string();
	}
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	return conv.to_bytes(str);
}

inline std::wstring ansi_to_unicode(std::string const& str) {
	const char* source = str.c_str();
	size_t source_len = str.length();
	if (source_len == 0) {
		return std::wstring();
	}
	size_t dest_len = 0;
#if defined(_WIN32) || defined(_WINDOWS)
	UINT cp = ::GetACP();
	dest_len = ::MultiByteToWideChar(cp, 0, source, static_cast<int>(source_len), 0, 0);
#else
	setlocale(LC_ALL, "");
	dest_len = mbstowcs(nullptr, source, source_len);
#endif
	std::wstring dest(dest_len, L'\0');
#if defined(_WIN32) || defined(_WINDOWS)
	::MultiByteToWideChar(cp, 0, source, -1, &dest[0], static_cast<int>(dest_len));
#else
	mbstowcs(&dest[0], source, source_len);
#endif
	return dest;
}

inline std::string unicode_to_ansi(std::wstring const& str) {
	size_t source_len = str.size();
	if (source_len <= 0) {
		return std::string();
	}
	const wchar_t* source = str.c_str();
	size_t dest_len = 0;
#if defined(_WIN32) || defined(_WINDOWS)
	UINT cp = ::GetACP();
	dest_len = ::WideCharToMultiByte(cp, 0, source, static_cast<int>(source_len), 0, 0, 0, 0);
#else
	setlocale(LC_ALL, "");
	dest_len = wcstombs(nullptr, source, source_len);
#endif
	std::string dest(dest_len, '\0');
#if defined(_WIN32) || defined(_WINDOWS)
	::WideCharToMultiByte(cp, 0, source, -1, &dest[0], static_cast<int>(dest_len), 0, 0);
#else
	dest_len = wcstombs(&dest[0], source, dest_len);
#endif
	return dest;
}

inline std::string utf8_to_ansi(std::string const& str) {
	if (!locale_is_utf8()) {
		std::wstring temp = utf8_to_unicode(str);
		std::string dest = unicode_to_ansi(temp);
		return dest;
	}
	else {
		std::string dest(str);
		return dest;
	}
}

inline std::string ansi_to_utf8(std::string const& str) {
	if (!locale_is_utf8()) {
		std::wstring temp = ansi_to_unicode(str);
		std::string dest = unicode_to_utf8(temp);
		return dest;
	}
	else {
		std::string dest(str);
		return dest;
	}
}

#ifdef USE_UTFCPP
inline bool is_valid_utf8(std::string const& str) {
	return utf8::is_valid(str.begin(), str.end());
}

inline bool starts_with_bom(std::string const& str) {
	return utf8::starts_with_bom(str.begin(), str.end());
}
#endif

NAMESPACE_END

#endif // BASIC_STRING_UTF_CONV_HPP_HEADER
