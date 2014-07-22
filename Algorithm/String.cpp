#include "String.h"

namespace Test {

	string String::Format(const char * format, ...)
	{
		char buffer[MaxLength];
		va_list args;
		va_start(args, format);
		vsprintf_s(buffer, format, args);
		va_end(args);
		return string(buffer);
	}

	wstring String::Format(const wchar_t * format, ...)
	{
		wchar_t buffer[MaxLength];
		va_list args;
		va_start(args, format);
		vswprintf_s(buffer, format, args);
		va_end(args);
		return wstring(buffer);
	}

	int String::RemoveDuplicateChars(char * input, int length)
	{
		if (input == nullptr) return -1;
		if (length <= 0) return length;
		bitset<256> mask;

		// Using i to point to the last position of a non-dup char that has been checked.
		// Next non-dup char should be copied to the position i+1.
		// 0 | 1 | ... | i | ... | j | ... | n-1
		// ~~~~~~~~~~~~~~~~      ~~~~~~~~~~~~~~
		// Non-dup chars         chars to check

		int i = -1;
		for (int j = 0; j < length; j++) {
			if ('\0' == input[j]) break;
			// Should look at bit input[j] of mark			
			if (!mask.test(input[j])) {
				// The bit is zero, and it means input[j] is not a dup.
				// Set the bit.
				mask.set(input[j]);
				if (1 < (j - i)) {
					// Have skipped some dups
					// Move current non-dup char to the front.
					input[++i] = input[j];
				} else {
					// Have not skipped any dups.
					// Hop i with j.
					i++;
				}
			}
		}

		input[++i] = '\0';
		// Now i equals to the new length.
		return i;
	}

	// http://leetcode.com/2011/09/regular-expression-matching.html
	bool String::IsMatch(char * input, char * pattern)
	{
		if (input == nullptr || pattern == nullptr) return false;

		while (*pattern == '*') pattern++;

		if (*input == '\0' && *pattern == '\0') return true;

		if (*input == '\0' || *pattern == '\0') return false;

		if (*input != *pattern && *pattern != '.') {
			// input    a#######
			// pattern  b####
			if (*(pattern+1) != '*') return false;

			// input    a#######
			// pattern  b***####
			return IsMatch(input, pattern + 2);
		} else {
			// input    a#######
			// pattern  a####
			//          .####
			if (*(pattern+1) != '*') return IsMatch(++input, ++pattern);

			// input    a#######
			// pattern  a***###
			//          .***###
			while (*input == *pattern || (*pattern == '.' && *input != '\0')) {
				if (IsMatch(input++, pattern+2)) return true;
			}

			return IsMatch(input, pattern+2);
		}
	}

	bool String::IsMatch2(char * input, char * pattern)
	{
		if (input == nullptr || pattern == nullptr) return false;

		while (*pattern == '*') {
			// Ignore leading '*'
			pattern++;
		}

		while ((*input == *pattern || *pattern == '.') && *input != '\0' && *pattern != '\0' && *(pattern+1) != '*') {
			// input    a#######
			// pattern  a####
			//          .####
			input++;
			pattern++;
		}

		if (*input == '\0' && *pattern == '\0') {
			// input and pattern match
			return true;
		}

		if (*pattern == '\0') {
			// input has more characters unmatched
			return false;
		}

		if (*input == '\0') {
			// pattern has more characters. Need to check if they are '*'
			while (*pattern == '*') pattern++;
			if (*pattern != '\0') return false;
			else return true;
		}

		if (*(pattern+1) != '*') {
			// input    a#######
			// pattern  b####
			return false;
		}

		// Now *(pattern+1) == '*'

		if (*input != *pattern && *pattern != '.') {
			// input    a#######
			// pattern  b*###
			return IsMatch2(input, pattern+2);
		}

		// input    a#######
		// pattern  a*###
		//          .*###
		while (*input != '\0' && (*input == *pattern || *pattern == '.')) {
			if (IsMatch2(input, pattern+2)) return true;
			input++;
		}

		// input	'\0'
		// input    b#######
		// pattern  a*###
		return IsMatch2(input, pattern+2);
	}

	void String::LongestSubStringWithUniqueChars(const string & input, int & index, int & length)
	{
		index = 0;
		length = 0;

		bitset<256> visited;
		int i = 0;
		int j = 0;

		while ((unsigned int)j < input.length()) {
			if (visited[input[j]] == true) {
				if (j - i > length) {
					index = i;
					length = j - i;
				}

				while (input[i] != input[j]) {
					visited[input[i]] = false;
					i++;
				}

				i++;
			} else {
				visited[input[j]] = true;
			}

			j++;
		}

		if (j - i > length) {
			index = i;
			length = j - i;
		}
	}
}