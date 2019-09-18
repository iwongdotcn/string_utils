#ifndef BASIC_STRING_CODEC_CONV_HPP_HEADER
#define BASIC_STRING_CODEC_CONV_HPP_HEADER
#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER
#include "config.hpp"
#include <string>

NAMESPACE_BEGIN

inline bool base64_decode(std::string const& input, std::string& output)
{
	static const char nop = -1;
	static const char decoding_data[] = {
		nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop,nop,
		nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop,nop,
		nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop, 62, nop,nop,nop, 63,
		52, 53, 54,  55,  56, 57, 58, 59,  60, 61,nop,nop, nop,nop,nop,nop,
		nop, 0,  1,   2,   3,  4,  5,  6,   7,  8,  9, 10,  11, 12, 13, 14,
		15, 16, 17,  18,  19, 20, 21, 22,  23, 24, 25,nop, nop,nop,nop,nop,
		nop,26, 27,  28,  29, 30, 31, 32,  33, 34, 35, 36,  37, 38, 39, 40,
		41, 42, 43,  44,  45, 46, 47, 48,  49, 50, 51,nop, nop,nop,nop,nop,
		nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop,nop,
		nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop,nop,
		nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop,nop,
		nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop,nop,
		nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop,nop,
		nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop,nop,
		nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop,nop,
		nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop,nop, nop,nop,nop,nop
	};

	unsigned int input_length = static_cast<unsigned int>(input.size());
	const char* input_ptr = input.data();

	// allocate space for output string
	output.clear();
	output.reserve(((input_length + 2) / 3) * 4);

	// for each 4-bytes sequence from the input, extract 4 6-bits sequences by droping first two bits
	// and regenerate into 3 8-bits sequence

	for (unsigned int i = 0; i < input_length; i++) {
		char base64code0;
		char base64code1;
		char base64code2 = 0;   // initialized to 0 to suppress warnings
		char base64code3;

		base64code0 = decoding_data[static_cast<int>(input_ptr[i])];
		if (base64code0 == nop)            // non base64 character
			return false;
		if (!(++i < input_length)) // we need at least two input bytes for first byte output
			return false;
		base64code1 = decoding_data[static_cast<int>(input_ptr[i])];
		if (base64code1 == nop)            // non base64 character
			return false;

		output += ((base64code0 << 2) | ((base64code1 >> 4) & 0x3));

		if (++i < input_length) {
			char c = input_ptr[i];
			if (c == '=') { // padding , end of input
//                    BOOST_ASSERT( (base64code1 & 0x0f)==0);
				return true;
			}
			base64code2 = decoding_data[static_cast<int>(input_ptr[i])];
			if (base64code2 == nop)            // non base64 character
				return false;

			output += ((base64code1 << 4) & 0xf0) | ((base64code2 >> 2) & 0x0f);
		}

		if (++i < input_length) {
			char c = input_ptr[i];
			if (c == '=') { // padding , end of input
//                    BOOST_ASSERT( (base64code2 & 0x03)==0);
				return true;
			}
			base64code3 = decoding_data[static_cast<int>(input_ptr[i])];
			if (base64code3 == nop)            // non base64 character
				return false;

			output += (((base64code2 << 6) & 0xc0) | base64code3);
		}

	}

	return true;
}

inline bool base64_encode(std::string const& input, std::string& output) {
	static const char encoding_data[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	unsigned int input_length = static_cast<unsigned int>(input.size());
	const char* input_ptr = input.data();

	// allocate space for output string
	output.clear();
	output.reserve(((input_length + 2) / 3) * 4);

	// for each 3-bytes sequence from the input, extract 4 6-bits sequences and encode using
	// encoding_data lookup table.
	// if input do not contains enough chars to complete 3-byte sequence,use pad char '='
	for (unsigned int i = 0; i < input_length; i++) {
		int base64code0 = 0;
		int base64code1 = 0;
		int base64code2 = 0;
		int base64code3 = 0;

		base64code0 = (input_ptr[i] >> 2) & 0x3f;  // 1-byte 6 bits
		output += encoding_data[base64code0];
		base64code1 = (input_ptr[i] << 4) & 0x3f;  // 1-byte 2 bits +

		if (++i < input_length) {
			base64code1 |= (input_ptr[i] >> 4) & 0x0f; // 2-byte 4 bits
			output += encoding_data[base64code1];
			base64code2 = (input_ptr[i] << 2) & 0x3f;  // 2-byte 4 bits +

			if (++i < input_length) {
				base64code2 |= (input_ptr[i] >> 6) & 0x03; // 3-byte 2 bits
				base64code3 = input_ptr[i] & 0x3f;       // 3-byte 6 bits
				output += encoding_data[base64code2];
				output += encoding_data[base64code3];
			}
			else {
				output += encoding_data[base64code2];
				output += '=';
			}
		}
		else {
			output += encoding_data[base64code1];
			output += '=';
			output += '=';
		}
	}

	return true;
}

inline std::string url_decode(const std::string& str) {
	char decode_buf[3];
	std::string result;
	result.reserve(str.size());

	for (std::string::size_type pos = 0; pos < str.size(); ++pos) {
		switch (str[pos]) {
		case '+':
			// convert to space character
			result += ' ';
			break;
		case '%':
			// decode hexadecimal value
			if (pos + 2 < str.size()) {
				decode_buf[0] = str[++pos];
				decode_buf[1] = str[++pos];
				decode_buf[2] = '\0';

				char decoded_char = static_cast<char>(strtol(decode_buf, 0, 16));

				// decoded_char will be '\0' if strtol can't parse decode_buf as hex
				// (or if decode_buf == "00", which is also not valid).
				// In this case, recover from error by not decoding.
				if (decoded_char == '\0') {
					result += '%';
					pos -= 2;
				}
				else
					result += decoded_char;
			}
			else {
				// recover from error by not decoding character
				result += '%';
			}
			break;
		default:
			// character does not need to be escaped
			result += str[pos];
		}
	};

	return result;
}

inline std::string url_encode(const std::string& str) {
	char encode_buf[4];
	std::string result;
	encode_buf[0] = '%';
	result.reserve(str.size());

	// character selection for this algorithm is based on the following url:
	// http://www.blooberry.com/indexdot/html/topics/urlencoding.htm

	for (std::string::size_type pos = 0; pos < str.size(); ++pos) {
		switch (str[pos]) {
		default:
			if (str[pos] > 32 && str[pos] < 127) {
				// character does not need to be escaped
				result += str[pos];
				break;
			}
			// else pass through to next case
		case ' ':
		case '$': case '&': case '+': case ',': case '/': case ':':
		case ';': case '=': case '?': case '@': case '"': case '<':
		case '>': case '#': case '%': case '{': case '}': case '|':
		case '\\': case '^': case '~': case '[': case ']': case '`':
			// the character needs to be encoded
#ifdef _WIN32
			sprintf_s(encode_buf + 1, _countof(encode_buf) - 1,
				"%.2X", (unsigned char)(str[pos]));
#else
			sprintf(encode_buf + 1, "%.2X", (unsigned char)(str[pos]));
#endif // _WIN32
			result += encode_buf;
			break;
		}
	};

	return result;
}

inline std::string xml_encode(const std::string& str) {
	std::string result;
	result.reserve(str.size() + 20);    // Assume ~5 characters converted (length increases)
	const unsigned char* ptr = reinterpret_cast<const unsigned char*>(str.c_str());
	const unsigned char* end_ptr = ptr + str.size();
	while (ptr < end_ptr) {
		// check byte ranges for valid UTF-8
		// see http://en.wikipedia.org/wiki/UTF-8
		// also, see http://www.w3.org/TR/REC-xml/#charsets
		// this implementation is the strictest subset of both
		if ((*ptr >= 0x20 && *ptr <= 0x7F) || *ptr == 0x9 || *ptr == 0xa || *ptr == 0xd) {
			// regular ASCII character
			switch (*ptr) {
				// Escape special XML characters.
			case '&':
				result += "&amp;";
				break;
			case '<':
				result += "&lt;";
				break;
			case '>':
				result += "&gt;";
				break;
			case '\"':
				result += "&quot;";
				break;
			case '\'':
				result += "&apos;";
				break;
			default:
				result += *ptr;
			}
		}
		else if (*ptr >= 0xC2 && *ptr <= 0xDF) {
			// two-byte sequence
			if (*(ptr + 1) >= 0x80 && *(ptr + 1) <= 0xBF) {
				result += *ptr;
				result += *(++ptr);
			}
			else {
				// insert replacement char
				result += std::char_traits<char>::to_char_type(0xef);
				result += std::char_traits<char>::to_char_type(0xbf);
				result += std::char_traits<char>::to_char_type(0xbd);
			}
		}
		else if (*ptr >= 0xE0 && *ptr <= 0xEF) {
			// three-byte sequence
			if (*(ptr + 1) >= 0x80 && *(ptr + 1) <= 0xBF
				&& *(ptr + 2) >= 0x80 && *(ptr + 2) <= 0xBF) {
				result += *ptr;
				result += *(++ptr);
				result += *(++ptr);
			}
			else {
				// insert replacement char
				result += std::char_traits<char>::to_char_type(0xef);
				result += std::char_traits<char>::to_char_type(0xbf);
				result += std::char_traits<char>::to_char_type(0xbd);
			}
		}
		else if (*ptr >= 0xF0 && *ptr <= 0xF4) {
			// four-byte sequence
			if (*(ptr + 1) >= 0x80 && *(ptr + 1) <= 0xBF
				&& *(ptr + 2) >= 0x80 && *(ptr + 2) <= 0xBF
				&& *(ptr + 3) >= 0x80 && *(ptr + 3) <= 0xBF) {
				result += *ptr;
				result += *(++ptr);
				result += *(++ptr);
				result += *(++ptr);
			}
			else {
				// insert replacement char
				result += std::char_traits<char>::to_char_type(0xef);
				result += std::char_traits<char>::to_char_type(0xbf);
				result += std::char_traits<char>::to_char_type(0xbd);
			}
		}
		else {
			// insert replacement char
			result += std::char_traits<char>::to_char_type(0xef);
			result += std::char_traits<char>::to_char_type(0xbf);
			result += std::char_traits<char>::to_char_type(0xbd);
		}
		++ptr;
	}

	return result;
}

NAMESPACE_END

#endif // BASIC_STRING_CODEC_CONV_HPP_HEADER
