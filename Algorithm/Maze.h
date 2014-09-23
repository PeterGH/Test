#pragma once
#include "Matrix.h"
namespace Test {
	class __declspec(dllexport) Maze {
	public:
		Maze();
		~Maze();

		static double CountUniquePaths(int rows, int cols, Matrix<double> & count);
		static double CountUniquePaths2(int rows, int cols, Matrix<double> & count);
	};
}

