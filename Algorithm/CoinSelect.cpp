#include "CoinSelect.h"

namespace Test {
	// http://leetcode.com/2011/02/coins-in-line.html
	// Two players take turn to select a coin from one end of a line of coins.
	// Compute the maximum value of coins the first palyer can get.
	
	void CoinSelect::GetIndices(Array2D<int> & v, int length, vector<int> & indices)
	{
		int i = 0;
		int j = length - 1;
		while (i + 2 <= j) {
			if (v(i+1, j) <= v(i, j-1)) {
				// A select input[i] and leave B input[i+1..j]
				indices.push_back(i);
				if (v(i+2, j) <= v(i+1, j-1)) {
					// B select input[i+1] and leave A input[i+2..j]
					i = i+2;
				} else {
					// B select input[j] and leave A input[i+1..j-1]
					i++;
					j--;
				}
			} else {
				// A select input[j] and leave B input[i..j-1]
				indices.push_back(j);
				if (v(i+1, j-1) <= v(i, j-2)) {
					// B select input[i] and leave A input[i+1..j-1]
					i++;
					j--;
				} else {
					// B select input[j-1] and leave A input[i..j-2]
					j = j - 2;
				}
			};
		}

		if (i + 1 == j) {
			if (v(i, i) > v(j, j)) {
				indices.push_back(i);
			} else {
				indices.push_back(j);
			}
		} else if (i == j) {
			indices.push_back(i);
		}
	}

	// Let V[i,j] be the maximum value from input[i..j]
	// Let S[i,j] be the sum of input[i..j]
	// V[i,j] = S[i,j] - min { V[i+1,j], V[i,j-1] }
	int CoinSelect::MaxSelection(const int * input, int length, vector<int> & indices)
	{
		Array2D<int> v(length, length);
		Array2D<int> s(length, length);

		// S[i,i] = input[i]
		// V[i,i] = input[i]
		for (int i = 0; i < length; i++) {
			s(i, i) = input[i];
			v(i, i) = input[i];
		}

		// S[i,j] = S[i,j-1] + input[j]
		// V[i,j] = S[i,j] - min { V[i+1,j], V[i,j-1] }
		for (int l = 1; l < length; l++) {
			for (int i = 0; i < length - l; i++) {
				s(i, i+l) = s(i, i+l-1) + input[i+l];
				v(i, i+l) = s(i, i+l) - std::min(v(i+1, i+l), v(i, i+l-1));
			}
		}

		GetIndices(v, length, indices);
		return v(0, length-1);
	}

	// Let V[i,j] be the maximum value from input[i..j]
	// V[i,j] = max { input[i] + min { V[i+2,j], V[i+1,j-1] },
	//                input[j] + min { V[i+1,j-1], V[i,j-2] } }
	int CoinSelect::MaxSelection2(const int * input, int length, vector<int> & indices)
	{
		Array2D<int> v(length, length);
		
		// V[i,i] = input[i]
		for (int i = 0; i < length; i++) {
			v(i, i) = input[i];
		}

		// V[i,i+1] = max { V[i,i], V[i+1,i+1] }
		for (int i = 0; i < length-1; i++) {
			v(i, i+1) = std::max(v(i,i), v(i+1,i+1));
		}

		// V[i,j] = max { input[i] + min { V[i+2,j], V[i+1,j-1] },
		//                input[j] + min { V[i+1,j-1], V[i,j-2] } }
		for (int l = 2; l < length; l++) {
			for (int i = 0; i < length - l; i++) {
				v(i, i+l) = std::max(
					input[i] + std::min(v(i+2, i+l), v(i+1, i+l-1)),
					input[i+l] + std::min(v(i+1, i+l-1), v(i, i+l-2)));
			}
		}

		GetIndices(v, length, indices);
		return v(0, length-1);
	}
}