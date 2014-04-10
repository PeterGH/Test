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
}