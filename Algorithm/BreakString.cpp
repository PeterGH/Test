#include "BreakString.h"
namespace Test {
	// Given a string of length n, we want to break it at some predetermined positions.
	// We can start at any one of the positions to break the string into two parts, 
	// and continue with each substring and the rest of positions.
	// For each position there is a cost of splitting depending on the length of 
	// substring to break.
	// We want to find a sequence of positions to break the string with minimum cost.
	//     0    1    2    3    ......    i    ......    n-2    n-1
	// p   p[0] p[1] p[2] p[3]           p[i]           p[n-2] p[n-1]
	//     0 = p[0] < p[1] < p[2] < ... < p[i] < ... < p[n-2] < p[n-1] = string length
	// Define c[i,j] as the cost of breaking a substring starting at position p[i] 
	// and ending at position p[j].
	// c[i,j] = 0,     if i == j || i+1 == j
	//          p[j] - p[i] + 1 + min {
	//                  c[i,i+1] + c[i+1,j],
	//                  c[i,i+2] + c[i+2,j],
	//                  ......
	//                  c[i,j-2] + c[j-2,j],
	//                  c[i,j-1] + c[j-1,j]},    if i+1 < j
	void BreakString::ComputeCostTable(int * positions, int length, Matrix<pair<int, int>> & cost)
	{
		if (positions == nullptr) throw invalid_argument("positions is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("Invalid length %d", length));
		int rows = cost.Rows();
		if (rows != length) throw invalid_argument(String::Format("rows %d != length %d", rows, length));
		int cols = cost.Cols();
		if (cols != length) throw invalid_argument(String::Format("cols %d != length %d", cols, length));

		for (int i = 0; i < length; i++) {
			cost(i, i).first = i;
			cost(i, i).second = 0;
			if (i < length - 1) {
				cost(i, i+1).first = i;
				cost(i, i+1).second = 0;
			}
		}

		for (int l = 2; l < length; l++) {
			for (int i = 0; i < length - l; i++) {
				// Compute cost(i, i+l)
				int c = 0x7FFFFFFF;
				int k = i;
				for (int j = i+1; j < i + l; j++) {
					int t = cost(i, j).second + cost(j, i+l).second;
					if (t < c) {
						c = t;
						k = j;
					}
				}

				cost(i, i+l).first = k;
				cost(i, i+l).second = c + positions[i+l] - positions[i];
			}
		}
	}

	int BreakString::ComputeBreaks(int * positions, int length, vector<int> & breaks)
	{
		if (positions == nullptr) throw invalid_argument("positions is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("Invalid length %d", length));
		Matrix<pair<int, int>> cost(length, length);
		ComputeCostTable(positions, length, cost);

		vector<pair<int, int>> range;
		range.push_back(make_pair(0, length - 1));
		while (!range.empty()) {
			pair<int, int> p = range.back();
			range.pop_back();
			
			int k = cost(p.first, p.second).first;
			breaks.push_back(positions[k]);

			if (k < p.second - 1) {
				range.push_back(make_pair(k, p.second));
			}

			if (p.first < k - 1) {
				range.push_back(make_pair(p.first, k));
			}
		}

		return cost(0, length-1).second;
	}
}