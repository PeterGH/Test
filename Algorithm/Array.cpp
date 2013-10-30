#include "Array.h"

namespace Test {
	// Given an MxN array
	//     (0,0)   (0,1)   (0,2)   ...... (0,M-2) (0,M-1)    (0,M)    (0,M+1)   ...... (0,N-2)   (0,N-1)
	//     (1,0)   (1,1)   (1,2)   ...... (1,M-2) (1,M-1)    (1,M)    (1,M+1)   ...... (1,N-2)   (1,N-1)
	//     (2,0)   (2,1)   (2,2)   ...... (2,M-2) (2,M-1)    (2,M)    (2,M+1)   ...... (2,N-2)   (2,N-1)
	//                             ......
	//                             ......
	//     (M-2,0) (M-2,1) (M-2,2) ...... (M-2,M-2) (M-2,M-1) (M-2,M) (M-2,M+1) ...... (M-2,N-2) (M-2,N-1)
	//     (M-1,0) (M-1,1) (M-1,2) ...... (M-1,M-2) (M-1,M-1) (M-1,M) (M-1,M+1) ...... (M-1,N-2) (M-1,N-1)
	// 
	// Transpose
	//     (0,0)   (1,0)   (2,0)   ...... (M-2,0)   (M-1,0)
	//     (0,1)   (1,1)   (2,1)   ...... (M-2,1)   (M-1,1)
	//     (0,2)   (1,2)   (2,2)   ...... (M-2,2)   (M-1,2)
	//                             ......
	//                             ......
	//     (0,M-2) (1,M-2) (2,M-2) ...... (M-2,M-2) (M-1,M-2)
	//     (0,M-1) (1,M-1) (2,M-1) ...... (M-2,M-1) (M-1,M-1)
	//     (0,M)   (1,M)   (2,M)   ...... (M-2,M)   (M-1,M)
	//     (0,M+1) (1,M+1) (2,M+1) ...... (M-2,M+1) (M-1,M+1)
	//                             ......
	//                             ......
	//     (0,N-2) (1,N-2) (2,N-2) ...... (M-2,N-2) (M-1,N-2)
	//     (0,N-1) (1,N-1) (2,N-1) ...... (M-2,N-1) (M-1,N-1)
	//
	// In-place matrix transposition (http://en.wikipedia.org/wiki/In-place_matrix_transposition)
	// Transpose element (m,n) to (n,m) means the index i = Nm + n is mapped to j = Mn + m. The mapping is
	// actually a permutation:
	// P(i) = MN - 1            if i = MN - 1, or
	//        Mi mod (MN - 1)   if 0 <= i < MN - 1
	// The reason is 
	// P(i) = P(Nm + n) = M(Nm + n) mod (MN - 1) = MNm + Mn mod (MN - 1) = (MN-1)m + m + Mn mod (MN - 1) = Mn + m
	void Array::Transpose(int * input, const int length, const int columns)
	{
		if (length <= 0)
			throw invalid_argument(String::Format("length %d is not positive.", length));
		
		if (columns <= 0)
			throw invalid_argument(String::Format("columns %d is not positive.", columns));
		
		if (length % columns > 0)
			throw invalid_argument(String::Format("length %d is not multiple of columns %d.", length, columns));

		int rows = length / columns;

		function<int(int)> permute = [=](int i)->int {
			if (i == (length - 1)) return i;
			int j = (rows * i) % (length - 1);
			return j;
		};

		BitSet updated(length);

		// ------+------------+--------------
		//       j            k
		//       s            t
		for (int i = 0; i < length; i++) {
			if (updated.Test(i)) continue;
			int j = i;
			int s = input[j];
			int k = permute(j);
			while (k != i) {
				int t = input[k];
				input[k] = s;
				updated.Set(k);
				j = k;
				s = t;
				k = permute(j);
			}

			input[i] = s;
			updated.Set(i);
		}
	}
}