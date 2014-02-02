#pragma once
#include <iostream>
#include <memory>
#include <stack>
using namespace std;
namespace Test {
	class __declspec(dllexport) LongestIncreasingSubsequence {
	public:
		LongestIncreasingSubsequence(void) {}
		~LongestIncreasingSubsequence(void) {}
		static void PrintSolution(int * input, int length);
	};
}