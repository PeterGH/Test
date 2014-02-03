#pragma once
#include <algorithm>
#include <memory>
#include <string>
#include "Array2D.h"
using namespace std;
namespace Test {
	class __declspec(dllexport) Palindrome {
	public:
		Palindrome(void) {}
		~Palindrome(void) {}
		static void LengthTable(string & input, Array2D<size_t> & length);
		static void LongestSubsequenceByTable(string & input, string & output);
		static void LengthArray(string & input, size_t length[]);	
		static void LongestSubsequenceByArray(string & input, string & output);
	};
}

