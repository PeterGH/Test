#pragma once
#include <string>
#include <vector>
#include "Matrix.h"
using namespace std;
namespace Test {
	class __declspec(dllexport) BreakString {
	public:
		BreakString(void) {}
		~BreakString(void) {}
		static void ComputeCostTable(int * positions, int length, Matrix<pair<int, int>> & cost);
		static int ComputeBreaks(int * positions, int length, vector<int> & breaks);
	};
}

