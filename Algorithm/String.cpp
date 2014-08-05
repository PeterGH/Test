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

	// http://leetcode.com/2010/11/microsoft-string-replacement-problem.html
	// Replace a pattern with a shorter string in place.
	// Continous occurrences of the pattern should be replaced with one shorter string.
	void String::ReplaceWithShorterString(char * input, const char * pattern, const char * shorter)
	{
		if (input == nullptr || pattern == nullptr || shorter == nullptr
			|| *input == '\0' || pattern == '\0' || shorter == '\0')
			return;

		char * i = input; // Next insert position
		char * j = input; // Next check position

		const char * s = shorter;
		const char * p = pattern;

		while (*j != '\0') {
			bool found = false;
			while (*j == *p) {
				char * k = j;
				while (*k != '\0' && *p != '\0' && *k == *p) {
					// Do not use *k++ == *p++ in the while condition statement,
					// because k and p will advance even if *k and *p are different.
					k++;
					p++;
				}
				if (*p == '\0') {
					// Found one pattern, skip it and
					// check for next continous pattern
					found = true;
					j = k;
					p = pattern;
				} else {
					// Input is done or not match
					p = pattern;
					break;
				}
			}

			if (found) {
				while (*s != '\0') *i++ = *s++;
				s = shorter;
			}

			if (*j != '\0') {
				// j may reach the end if the input ends with the pattern
				*i++ = *j++;
			}
		}

		*i = '\0';
	}

	const char * String::StrStr(const char * input1, const char * input2)
	{
		if (input1 == nullptr || input2 == nullptr || *input1 == '\0' || * input2 == '\0') return nullptr;

		const char * q = input1;
		const char * p = input2;
		while (*(q+1) != '\0' && *(p+1) != '\0') {
			q++;
			p++;
		}
		if (*(q+1) == '\0' && *(p+1) != '\0') {
			// input2 is longer than input1
			return nullptr;
		}

		// now input1 is not shorter than input2
		// set p to the beginning of input1
		p = input1;
		const char * s = input2;

		// Hop p and q at same step until q reaches the end of input1
		while (*q != '\0') {
			if (*p == *s) {
				const char * r = p;
				while (*s != '\0' && *r == *s) {
					r++;
					s++;
				}
				if (*s == '\0') {
					// match;
					return p;
				} else {
					// reset s for next match
					s = input2;
				}
			}
			p++;
			q++;
		}
		return nullptr;
	}
}