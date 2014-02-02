#include "LongestIncreasingSubsequence.h"

namespace Test {
	//  i    0    1    2    3    ......    i    ......    n-2    n-1
	//  I    I[0] I[1] I[2] I[3]           I[i]           I[n-2] I[n-1]
	//  For each i, compute M[j]
	//  j    0    1    2    3    ......    i
	//  Compute the ending elements of all increasing subsequences of length j+1, 
	//  choose I[k] which is the smallest ending element, 
	//  and set M[j] with its position k.
	//  M[j] tracks the increasing subsequence of length j+1 that is most likely to be extended
	//  when scanning the rest of elements in I.
	//  If L is the length of longest increasing subsequence up to I[i] (0 <= L-1 <= i), then
	//  M[0] < M[1] < M[2] < ...... < M[L-1] <= i
	void LongestIncreasingSubsequence::PrintSolution(int * input, int length)
	{
		if (input == nullptr || length <= 0) return;

		cout << "Input:";
		for (int i = 0; i < length; i ++) {
			cout << " " << input[i];
		}

		cout << endl;

		unique_ptr<int[]> m(new int[length]);
		unique_ptr<int[]> p(new int[length]);

		m[0] = 0;
		p[0] = -1;
		int L = 1;
		for (int i = 1; i < length; i++) {
			// Should have used binary search.
			int j = L;
			while (j > 0 && input[i] <= input[m[j-1]]) j--;

			if (j > 0) p[i] = m[j-1];
			else p[i] = -1;

			if (j == L || input[i] < input[m[j]]) {
				m[j] = i;
				L = j + 1 > L ? j + 1 : L;
			}
		}

		stack<int> e;
		int i = m[L - 1];
		while (i >= 0) {
			e.push(input[i]);
			i = p[i];
		}
		
		cout << "Longest increasing subsequence:";
		while (!e.empty()) {
			cout << " " << e.top();
			e.pop();
		}

		cout << endl;
	}
}