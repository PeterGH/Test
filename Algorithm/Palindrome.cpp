#include "Palindrome.h"

namespace Test {
	// input: c_0, c_1, c_2, ..., c_i, ..., c_j, ..., c_(n-1)
	// Let L_(i, j) be the length of the longest palindrome subsequence of input c[i..j]
	// L_(i, j) = 1,                             if i == j
	//            2,                             if i+1 == j, c_i == c_j
	//            1,                             if i+1 == j, c_i != c_j
	//            2 + L_(i+1, j-1),              if c_i == c_j, i+1 < j
	//            max(L_(i, j-1), L_(i+1, j),    if c_i != c_j, i+1 < j
	//
	//	       0(c)    1(h)    2(a)    3(r)    4(a)    5(c)    6(t)    7(e)    8(r)
	// 0(c)    1       1       1       1       3       5       5       5       5
	// 1(h)    0       1       1       1       3       3       3       3       3
	// 2(a)    0       0       1       1       3       3       3       3       3
	// 3(r)    0       0       0       1       1       1       1       1       3
	// 4(a)    0       0       0       0       1       1       1       1       1
	// 5(c)    0       0       0       0       0       1       1       1       1
	// 6(t)    0       0       0       0       0       0       1       1       1
	// 7(e)    0       0       0       0       0       0       0       1       1
	// 8(r)    0       0       0       0       0       0       0       0       1
	//	
	void Palindrome::LengthTable(string & input, Array2D<size_t> & length)
	{
		for (size_t i = 0; i < input.length(); i ++) {
			// Set L_(i, i)
			length(i, i) = 1;

			// Set L_(i, i+1)
			if (i + 1 < input.length()) {
				if (input[i] == input[i+1]) {
					length(i, i+1) = 2;
				} else {
					length(i, i+1) = 1;
				}
			}
		}

		for (size_t j = 2; j < input.length(); j ++) {
			for (size_t i = 0; i + j < input.length(); i ++) {
				// Set L_(i, i+j)
				if (input[i] == input[i+j]) {
					length(i, i+j) = 2 + length(i+1, i+j-1);					
				} else {
					length(i, i+j) = max(length(i, i+j-1), length(i+1, i+j));
				}			
			}
		}
	}

	void Palindrome::LongestSubsequenceByTable(string & input, string & output)
	{
		Array2D<size_t> length(input.length(), input.length());

		// Compute the length table
		LengthTable(input, length);

		size_t i = 0;
		size_t j = input.length() - 1;

		if (length(i, j) == 1) {
			// no Parlindrome found, return the last char
			output.append(&input[j], 1);
			return;
		}

		size_t k = 0;

		while ((j-i) > 1) {
			while (length(i, j-1) == length(i, j)) {
				j --;
			}
			
			// The while loop stop when L_(i, j-1) != L_(i, j)
			// Now input[j] must be in the palindrome
			char c = input[j];
			j --;

			// Output a pair of c.
			// k will be the next insertion place.
			output.insert(k++, 1, c);
			output.insert(k, 1, c);

			while (input[i] != c) {
				i ++;
			}

			i ++;
		}
		
		// j = i or j = i+1
		output.insert(k, 1, input[j]);
		if (i+1 == j && input[i] == input[j]) {
			// The palindrome is of form xxxccxxxx
			output.insert(k, 1, input[j]);		
		}
	}

	// k       0(c)    1(h)    2(a)    3(r)    4(a)    5(c)    6(t)    7(e)    8(r)
	// 0       1       1       1       1       1       1       1       1       1
	// 1       1       1       1       1       1       1       1       1       1
	// 2       1       1       1       1       3       1       1       1       1
	// 3       1       1       1       1       3       3       1       1       1
	// 4       1       1       1       1       3       3       3       1       1
	// 5       1       1       1       1       3       5       3       3       1
	// 6       1       1       1       1       3       5       5       3       3
	// 7       1       1       1       1       3       5       5       5       3
	// 8       1       1       1       1       3       5       5       5       5
	// At step k, length[i] is the length of the longest palindrome subsequence from input[i-k] to input[i]
	void Palindrome::LengthArray(string & input, size_t length[])
	{
		// Compute all length=1 substrings
		for (int i = input.length() - 1; i >= 0; i --) {
			length[i] = 1;
		}

		// Compute all length=2 substrings
		for (int i = input.length() - 1; i >= 1; i --) {
			if (input[i-1] == input[i]) {
				length[i] = 2;
			}
		}	

		// Compute all length=(k+1) substrings
		for (int k = 2; k < (int)input.length(); k ++) {
			for (int i = input.length() - 1; i >= k; i --) {
				if (input[i-k] == input[i]) {
					// Here is a bug: length[i-1] refer to range input[i-k..i-1], but actually we need input[i-k+1..i-1]
					length[i] = 2 + length[i-1];
				} else {
					length[i] = max(length[i-1], length[i]);
				}
			}
		}
	}

	void Palindrome::LongestSubsequenceByArray(string & input, string & output)
	{
		unique_ptr<size_t> length(new size_t[input.length()]);
		LengthArray(input, length.get());

		size_t i = 0;
		size_t j = input.length() - 1;

		if (length.get()[j] == 1) {
			// no Parlindrome found, return the last char
			output.append(&input[j], 1);
			return;
		}

		size_t k = 0;

		while ((j-i) > 1) {
			while (length.get()[j-1] == length.get()[j]) {
				j --;
			}
			
			char c = input[j];
			j --;
			output.insert(k++, 1, c);
			output.insert(k, 1, c);
			while (input[i] != c) {
				i ++;
			}
			
			i ++;
		}

		output.insert(k, 1, input[j]);
		if (i+1 == j && input[i] == input[j]) {
			// The palindrome is of form xxxccxxxx
			output.insert(k, 1, input[j]);
		}
	}

	bool Palindrome::IsPalindrom(unsigned int number)
	{
		if (number < 10) return true;

		unsigned int base = 1;
		while ((number / base) >= 10) {
			base *= 10;
		}

		// Compare the most significant digit (MSD) and the least significant digit (LSD)
		while (number >= 10) {
			if ((number / base) != (number % 10)) {
				// MSD is different from LSD
				return false;
			}

			// Peel off MSD and LSD
			number = (number % base) / 10;
			base /= 100;
		}

		return true;
	}

	// Manacher Algorithm
	// Discussed at http://leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
	// Find the longest substring (contiguous characters) which is a palindrome
	void Palindrome::LongestSubstring(string & input, string & output)
	{
		int length = 1 + 2 * input.size();
		unique_ptr<int[]> p(new int[length]);

		// #  b  #  a  #  b  #  c  #  b  #  a  #  b  #  c  #  b  #  a  #  c  #  c  #  b  #  a  #
		// Original characters are at the odd positions
		auto getChar = [&](int i) -> char {
			if (i % 2 == 1) {
				return input[i >> 1];
			} else {
				return '#';
			}
		};

		// Given current index c and its palindrome length p[c],
		// try to expand it as far as possible.
		auto expand = [&](int c) -> int {
			while (true) {
				int m = c - p[c] - 1;
				if (m < 0) break;
				int n = c + p[c] + 1;
				if (n >= length) break;
				if (getChar(m) != getChar(n)) break;
				p[c]++;
			}

			return p[c];
		};

		auto printi = [&](){
			printf("\t");
			for (int i = 0; i < length; i++) {
				printf("  %c", getChar(i));
			}
			printf("\n");
		};

		auto printp = [&](int i){
			printf("%d\t", i);
			for (int j = 0; j <= i; j++) {
				printf("  %d", p[j]);
			}
			printf("\n");
		};

		int maxLength = 0;
		int maxIndex = 0;
		p[0] = 0;
		int c = 0;	// The center of current range
		int r = 0;	// The right-most boundary of current range, i.e., c + p[c]
		for (int i = 1; i < length; i++) {
			if (i > r) {
				p[i] = 0;
			} else {
				int j = 2 * c - i;
				// p[i] should be the same of its mirror about the current center but also bounded by the current range
				p[i] = std::min(p[j], r - i);
			}

			expand(i);
			if (i + p[i] > r) {
				c = i;
				r = c + p[c];
			}

			if (p[i] > maxLength) {
				maxLength = p[i];
				maxIndex = i;
			}

			// printi();
			// printp(i);
		}

		int i = maxIndex - maxLength + 1;
		string::iterator b = output.begin();
		int j = 0;
		while (i < maxIndex) {
			char c = getChar(i);
			output.insert(b + j++, c);
			output.insert(b + j, c);
			i += 2;
		}

		if (i == maxIndex) {
			output.insert(b + j, getChar(i));
		}
	}
}