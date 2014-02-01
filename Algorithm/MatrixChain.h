#pragma once

#include <functional>
#include <iostream>
#include <memory>
using namespace std;

namespace Test {
	class __declspec(dllexport) MatrixChain {
	public:
		MatrixChain(void) {}
		~MatrixChain(void) {}
		static void ComputeCostTable(int * dimension, int count, int * cost, int * split);
		static void PrintSolution(int * dimension, int count);
	};
}

