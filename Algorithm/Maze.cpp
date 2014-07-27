#include "Maze.h"

namespace Test {
	// http://leetcode.com/2010/11/unique-paths.html
	// Given a MxN maze, count the unique paths to travel
	// from the top-left cell to the bottom-right cell.
	double Maze::CountUniquePaths(int rows, int cols, Array2D<double> & count)
	{
		if (rows <= 0) throw invalid_argument(String::Format("rows %d is invalid", rows));
		if (cols <= 0) throw invalid_argument(String::Format("cols %d is invalid", cols));
		if ((int)count.Rows() < rows) throw invalid_argument(String::Format("count rows %d is less than %d", count.Rows(), rows));
		if ((int)count.Cols() < cols) throw invalid_argument(String::Format("count cols %d is less than %d", count.Cols(), cols));

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				count(i, j) = -1;
			}
		}

		function<double(int,int)> countPaths = [&](int i, int j) -> double {
			if (i >= rows || j >= cols) {
				return 0;
			} else if (i == rows - 1 && j == cols - 1) {
				count(i, j) = 1;
			} else if (i == rows - 1) {
				if (count(i, j+1) == -1) {
					count(i, j+1) = countPaths(i, j+1);
				}
				count(i, j) = count(i, j+1);
			} else if (j == cols - 1) {
				if (count(i+1, j) == -1) {
					count(i+1, j) = countPaths(i+1, j);
				}
				count(i, j) = count(i+1, j);
			} else {
				if (count(i+1, j) == -1) {
					count(i+1, j) = countPaths(i+1, j);
				}
				if (count(i, j+1) == -1) {
					count(i, j+1) = countPaths(i, j+1);
				}
				count(i, j) = count(i+1, j) + count(i, j+1);
			}
			return count(i, j);
		};

		return countPaths(0, 0);
	}

	double Maze::CountUniquePaths2(int rows, int cols, Array2D<double> & count)
	{
		if (rows <= 0) throw invalid_argument(String::Format("rows %d is invalid", rows));
		if (cols <= 0) throw invalid_argument(String::Format("cols %d is invalid", cols));
		if ((int)count.Rows() < rows) throw invalid_argument(String::Format("count rows %d is less than %d", count.Rows(), rows));
		if ((int)count.Cols() < cols) throw invalid_argument(String::Format("count cols %d is less than %d", count.Cols(), cols));

		for (int i = 0; i < rows; i++) {
			count(i, cols - 1) = 1;
		}

		for (int j = 0; j < cols; j++) {
			count(rows - 1, j) = 1;
		}

		for (int i = rows - 2; i >= 0; i--) {
			for (int j = cols - 2; j >= 0; j--) {
				count(i, j) = count(i + 1, j) + count(i, j + 1);
			}
		}

		return count(0, 0);
	}
}