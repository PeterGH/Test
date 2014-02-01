#include "MatrixChain.h"

namespace Test {
	// Matrices:    A_0,       A_1,       A_2,       ..., A_i,           ..., A_j,           ..., A_(n-2)
	// Dimensions:  d_0 x d_1, d_1 x d_2, d_2 x d_3, ..., d_i x d_(i+1), ..., d_j x d_(j+1), ..., d_(n-2) x d_(n-1)
	// count = n
	// Costs:
	//   cost[i][i] = 0, for i = 0, 1, 2, ..., (n-2)
	//   cost[i][j] = min { (cost[i][i] + cost[i+1][j] + d_i x d_(i+1) x d_(j+1)),
	//                      (cost[i][i+1] + cost[i+2][j] + d_i x d_(i+2) x d_(j+1)),
	//                      (cost[i][i+2] + cost[i+3][j] + d_i x d_(i+3) x d_(j+1)),
	//                      ...
	//                      (cost[i][j-1] + cost[j][j] + d_i x d_j x d_(j+1))
	//                    }, 
	//                 for i < j, 
	//                     i = 0, 1, 2, ..., n-3
	//                     j =    1, 2, ..., n-3, n-2
	void MatrixChain::ComputeCostTable(int * dimension, int count, int * cost, int * split)
	{
		if (dimension == nullptr || count <= 0 || cost == nullptr || split == nullptr) return;

		function<int &(int, int)> c = [&](int i, int j)->int &{
			return *(cost + i*(count-1) + j);
		};

		for (int i = 0; i < count - 1; i ++) {
			c(i, i) = 0;
		}

		// l = 1,   cost[0][1],   cost[1][2],   cost[2][3], ..., cost[i][i+1], ..., cost[n-4][n-3], cost[n-3][n-2]
		// l = 2,   cost[0][2],   cost[1][3],   cost[2][4], ..., cost[i][i+2], ..., cost[n-4][n-2]
		// ...
		// l = n-3, cost[0][n-3], cost[1][n-2]
		// l = n-2, cost[0][n-2]
		for (int l = 1; l < count - 1; l++) {
			for (int i = 0; i < count - 1 - l; i++) {
				int j = i + l;
				c(i, j) = 0x7FFFFFFF;
				for (int k = i; k < j; k++) {
					// split A_i..A_k, A_(k+1)..A_j
					int min = c(i, k) + c(k+1, j) + dimension[i] * dimension[k+1] * dimension[j+1];
					if (min < c(i, j)) {
						c(i, j) = min;
						*(split + i*(count-1)+ j) = k;
					}
				}
			}
		}
	}

	void MatrixChain::PrintSolution(int * dimension, int count)
	{
		if (dimension == nullptr || count <= 0) return;

		int length = (count - 1) * (count - 1);
		unique_ptr<int[]> cost(new int[length]);
		unique_ptr<int[]> split(new int[length]);

		memset(cost.get(), 0, length * sizeof(int));
		memset(split.get(), 0, length * sizeof(int));

		Test::MatrixChain::ComputeCostTable(dimension, count, cost.get(), split.get());

		for (int i = 0; i < count - 1; i++) {
			cout << "A_" << i << " : " << dimension[i] << " x " << dimension[i+1] << endl;
		}

		function<void(int, int)> print = [&](int i, int j){
			if (i == j) {
				cout << " A_" << i << " ";
			} else {
				int k = *(split.get() + i * (count - 1) + j);
				cout << "(";
				print(i, k);
				print(k + 1, j);
				cout << ")";
			}
		};
		
		cout << "Parenthesization : ";
		print(0, count - 2);
		cout << endl;
		cout << "Cost : " << *(cost.get() + count -2) << endl;
	}
}