#include "MazeTest.h"

void MazeTest::Init()
{
	Add("UniquePaths", [&](){
		auto check = [&](int rows, int cols){
			Logger().WriteInformation("Maze %d x %d:", rows, cols);
			Matrix<double> count(rows, cols);
			Matrix<double> count2(rows, cols);
			Maze::CountUniquePaths(rows, cols, count);
			Maze::CountUniquePaths2(rows, cols, count2);
			Logger().WriteInformation(" unique paths (%f, %f)\n", count(0, 0), count2(0, 0));
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					ASSERT1(count(i, j) == count2(i, j));
				}
			}
		};

		// overflow may happen if the maze is too large
		for (int i = 1; i <= 15; i++) {
			for (int j = 1; j <= 15; j++) {
				check(i, j);
			}
		}
	});
}