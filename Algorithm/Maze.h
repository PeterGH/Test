#pragma once
#pragma once
#include "Array2D.h"
namespace Test {
	class __declspec(dllexport) Maze {
	public:
		Maze();
		~Maze();

		static double CountUniquePaths(int rows, int cols, Array2D<double> & count);
		static double CountUniquePaths2(int rows, int cols, Array2D<double> & count);
	};
}

