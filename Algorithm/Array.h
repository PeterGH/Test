#pragma once
#include <deque>
#include <functional>
#include <queue>
#include <vector>
#include "BinarySearch.h"
#include "BitSet.h"
#include "String.h"

using namespace std;

namespace Test {
	class __declspec(dllexport) Array {
	public:

		// For each element input[i] compute multiplication of the other elements in input.
		static void ExclusiveMultiplication(const int * input, int length, long long * output);

		// Find a subarray of contiguous elements whose sum is maximized
		// If array contains both positive and negative numbers, return the maximum subarray
		// If array contains positive numbers, return entire array A
		// If array contains non-positive numbers, return the maximum number
		// Parameter sum is the summation of the returned subarray
		// Parameters start and end are the start and end indices of the returned subarray
		static void MaxSubArray(const int * input, int length, int & start, int & end, long & sum);

		// An inversion is a pair (i, j) such that i < j and I[i] > I[j].
		// Find an inversion such that j - i is maximized.
		// Use parameter first to return value i and distance to return value j - i
		static void MaxInversionDistance(const int * input, int length, int & first, int & distance);
		static void MaxInversionDistance2(const int * input, int length, int & first, int & distance);

		// Slide a window across an input, output the maximum on every move.
		static void MaxSlidingWindow(const int * input, int length, int window, vector<int> & output);
		static void MaxSlidingWindow2(const int * input, int length, int window, vector<int> & output);

		// Find the indices of min and max elements.
		// minIndex will be the index of the minimum value (first index if there are more than on minimum value).
		// maxIndex will be the index of the maximum value (last index if there are more than on maximum value).
		template<class T> static void MinMax(const T * input, const int length, int & minIndex, int & maxIndex);

		// Permute a two dimensional matrix in place. 
		// The permute function takes three parameters: index of the element to permute, number of rows and number of columns,
		// and output the index of the new position of the element.
		template<class T> static void Permute(T * input, const int length, const int columns, function<int(int, int, int)> & permute);

		template<class T> static void Print(Log & log, const T * input, const int length, const int columns);

		// Rotate an input array to the left by a distance. The elements rotated out are shifted into the right.
		template<class T> static void RotateLeft(T * input, const int length, int distance);

		// Rotate an input array to the right by a distance. The elements rotated out are shifted into the left.
		template<class T> static void RotateRight(T * input, const int length, int distance);

		// Swap contiguous elements between the first and the second positions.
		template<class T> static void Swap(T * first, T * second, const int count);

		// Swap elements at two positions
		template<class T> static void Swap(T * buffer, unsigned int position1, unsigned int position2);

		// Transpose a two dimensional matrix in place
		template<class T> static void Transpose(T * input, const int length, const int columns);

		// Transpose rows to columns for a two dimensional matrix in place. Not change the dimensions.
		template<class T> static void TransposeRowsToColumns(T * input, const int length, const int columns);
		
		// Transpose columns to rows for a two dimensional matrix in place. Not change the dimensions.
		template<class T> static void TransposeColumnsToRows(T * input, const int length, const int columns);
	};

	template<class T> void Array::MinMax(const T * input, const int length, int & minIndex, int & maxIndex)
	{
		minIndex = -1;
		maxIndex = -1;
		if (input == nullptr || length <= 0) return;

		int startIndex = 0;
		if (length % 2 == 1) {
			minIndex = 0;
			maxIndex = 0;
			startIndex = 1;
		} else {
			if (input[0] <= input[1]) {
				minIndex = 0;
				maxIndex = 1;
			} else {
				minIndex = 1;
				maxIndex = 0;
			}

			startIndex = 2;
		}

		for (int i = startIndex; i < length; i += 2) {
			if (input[i] <= input[i + 1]) {
				if (input[i] < input[minIndex]) minIndex = i;
				if (input[i + 1] >= input[maxIndex]) maxIndex = i + 1;
			} else {
				if (input[i + 1] < input[minIndex]) minIndex = i + 1;
				if (input[i] >= input[maxIndex]) maxIndex = i;
			}
		}
	}

	template<class T> void Array::Swap(T * first, T * second, const int count)
	{
		if (first == nullptr) throw invalid_argument("first is nullptr");
		if (second == nullptr) throw invalid_argument("second is nullptr");

		T t;
		for (int i = 0; i < count; i++) {
			t = first[i];
			first[i] = second[i];
			second[i] = t;
		}
	}

	template<class T> void Array::Swap(T * buffer, unsigned int position1, unsigned int position2)
	{
		if (position1 != position2) {
			T t = buffer[position1];
			buffer[position1] = buffer[position2];
			buffer[position2] = t;
		}
	}

	template<class T> void Array::RotateLeft(T * input, const int length, int distance)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is not positive", length));
		if (distance < 0) throw invalid_argument(String::Format("distance %d is negative", distance));
		distance = distance % length;
		if (distance == 0) return;

		int i = 0;
		int j = length - 1;
		int k = distance;
		// input[i..k-1] and input[k..j]
		while (i < k && k <= j) {
			if (k - i < j - k + 1) {
				// Left range is shorter
				// input[i..k-1], input[k..j-(k-i)], input[j-(k-i)+1..j]
				Swap(&input[i], &input[j - (k - i) + 1], k - i);
				j = j - (k - i);
			} else if (k - i > j - k + 1) {
				// Right range is shorter
				// input[i..i+(j-k)], input[i+(j-k)+1..k-1], input[k..j]
				Swap(&input[i], &input[k], j - k + 1);
				i = i + (j - k) + 1;
			} else {
				// Both ranges have the same length
				Swap(&input[i], &input[k], k - i);
				break;
			}
		}
	}

	template<class T> void Array::RotateRight(T * input, const int length, int distance)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is not positive", length));
		if (distance < 0) throw invalid_argument(String::Format("distance %d is negative", distance));
		distance = distance % length;
		if (distance == 0) return;
		RotateLeft(input, length, length - distance);
	}

	template<class T> void Array::Permute(T * input, const int length, const int columns, function<int(int, int, int)> & permute)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is not positive.", length));
		if (columns <= 0) throw invalid_argument(String::Format("columns %d is not positive.", columns));
		if (length % columns > 0) throw invalid_argument(String::Format("length %d is not multiple of columns %d.", length, columns));

		int rows = length / columns;
		
		BitSet updated(length);

		// ------+------------+--------------
		//       j            k
		//       s            t
		for (int i = 0; i < length; i++) {
			if (updated.Test(i)) continue;
			int j = i;
			T s = input[j];
			int k = permute(j, rows, columns);
			while (k != i) {
				T t = input[k];
				input[k] = s;
				updated.Set(k);
				j = k;
				s = t;
				k = permute(j, rows, columns);
			}

			input[i] = s;
			updated.Set(i);
		}
	}

	// Given an MxN array
	//     (0,0)   (0,1)   (0,2)   ...... (0,M-2)   (0,M-1)   (0,M)   (0,M+1)   ...... (0,N-2)   (0,N-1)
	//     (1,0)   (1,1)   (1,2)   ...... (1,M-2)   (1,M-1)   (1,M)   (1,M+1)   ...... (1,N-2)   (1,N-1)
	//     (2,0)   (2,1)   (2,2)   ...... (2,M-2)   (2,M-1)   (2,M)   (2,M+1)   ...... (2,N-2)   (2,N-1)
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
	template<class T> void Array::Transpose(T * input, const int length, const int columns)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is not positive.", length));
		if (columns <= 0) throw invalid_argument(String::Format("columns %d is not positive.", columns));
		if (length % columns > 0) throw invalid_argument(String::Format("length %d is not multiple of columns %d.", length, columns));

		int rows = length / columns;

		function<int(int, int, int)> permute = [=](int i, int r, int c)->int {
			int l = r * c;
			if (i == (l - 1)) return i;
			int j = (r * i) % (l - 1);
			return j;
		};

		Permute(input, length, columns, permute);
	}

	// Given an MxN array, where N = kM
	//     (0,0)   (0,1)   (0,2)   ...... (0,M-2)   (0,M-1)   (0,M)   (0,M+1)   ...... (0,N-2)   (0,N-1)
	//     (1,0)   (1,1)   (1,2)   ...... (1,M-2)   (1,M-1)   (1,M)   (1,M+1)   ...... (1,N-2)   (1,N-1)
	//     (2,0)   (2,1)   (2,2)   ...... (2,M-2)   (2,M-1)   (2,M)   (2,M+1)   ...... (2,N-2)   (2,N-1)
	//                             ......
	//                             ......
	//     (M-2,0) (M-2,1) (M-2,2) ...... (M-2,M-2) (M-2,M-1) (M-2,M) (M-2,M+1) ...... (M-2,N-2) (M-2,N-1)
	//     (M-1,0) (M-1,1) (M-1,2) ...... (M-1,M-2) (M-1,M-1) (M-1,M) (M-1,M+1) ...... (M-1,N-2) (M-1,N-1)
	// 
	// Transpose rows to columns
	//     (0,0)   (0,M)    ...... (0,(k-1)M)   (1,0)   (1,M)    ...... (1,(k-1)M)   ...... (M-1,0)   (M-1,M)    ...... (M-1,(k-1)M) 
	//     (0,1)   (0,M+1)  ...... (0,(k-1)M+1) (1,1)   (1,M+1)  ...... (1,(k-1)M+1) ...... (M-1,1)   (M-1,M+1)  ...... (M-1,(k-1)M+1)
	//     (0,2)   (0,M+2)  ...... (0,(k-1)M+2) (1,2)   (1,M+2)  ...... (1,(k-1)M+2) ...... (M-1,2)   (M-1,M+2)  ...... (M-1,(k-1)M+2)
	//                      ......                               ......              ......                      ......
	//                      ......                               ......              ......                      ......
	//     (0,M-2) (0,2M-2) ...... (0,kM-2)     (1,M-2) (1,2M-2) ...... (1,kM-2)     ...... (M-1,M-2) (M-1,2M-2) ...... (M-1,kM-2)
	//     (0,M-1) (0,2M-1) ...... (0,kM-1)     (1,M-1) (1,2M-1) ...... (1,kM-1)     ...... (M-1,M-1) (M-1,2M-1) ...... (M-1,kM-1)
	//
	// Transpose element (m,n) to ((n % M), (km + n/M)) means the index i = Nm + n is mapped to j = (n % M)N + km + n/M
	// The mapping is actually a permutation:
	// 1. It is easy to see 0<= j <= MN-1
	// 2. From i to j is a one-to-one mapping
	//
	// Given an MxN array, where M = kN
	//     (0,0)   (0,1)   (0,2)   ...... (0,N-2)   (0,N-1)
	//     (1,0)   (1,1)   (1,2)   ...... (1,N-2)   (1,N-1)
	//     (2,0)   (2,1)   (2,2)   ...... (2,N-2)   (2,N-1)
	//                             ......
	//                             ......
	//     (N-2,0) (N-2,1) (N-2,2) ...... (N-2,N-2) (N-2,N-1)
	//     (N-1,0) (N-1,1) (N-1,2) ...... (N-1,N-2) (N-1,N-1)
	//                             ......
	//                             ......
	//     (M-2,0) (M-2,1) (M-2,2) ...... (M-2,N-2) (M-2,N-1)
	//     (M-1,0) (M-1,1) (M-1,2) ...... (M-1,N-2) (M-1,N-1)
	// 
	// Transpose rows to columns
	//     (0,0)     (k,0)      ...... ((N-1)k,0)
	//     (0,1)     (k,1)      ...... ((N-1)k,1)
	//     (0,2)     (k,2)      ...... ((N-1)k,2)
	//                          ......
	//     (0,N-2)   (k,N-2)    ...... ((N-1)k,N-2)
	//     (0,N-1)   (k,N-1)    ...... ((N-1)k,N-1)
	//     (1,0)     (k+1,0)    ...... ((N-1)k+1,0)
	//     (1,1)     (k+1,1)    ...... ((N-1)k+1,1)
	//     (1,2)     (k+1,2)    ...... ((N-1)k+1,2)
	//                          ......
	//     (1,N-2)   (k+1,N-2)  ...... ((N-1)k+1,N-2)
	//     (1,N-1)   (k+1,N-1)  ...... ((N-1)k+1,N-1)
	//                          ......
	//                          ......
	//     (k-1,0)   (2k-1,0)   ...... (kN-1,0)
	//     (k-1,1)   (2k-1,1)   ...... (kN-1,1)
	//     (k-1,2)   (2k-1,2)   ...... (kN-1,2)
	//                          ......
	//     (k-1,N-2) (2k-1,N-2) ...... (kN-1,N-2)
	//     (k-1,N-1) (2k-1,N-1) ...... (kN-1,N-1)
	//
	// Transpose element (m,n) to ((m%k)N + n, m/k)) means the index i = Nm + n is mapped to j = (m%k)NN + nN + m/k
	// The mapping is actually a permutation:
	// 1. It is easy to see 0<= j <= MN-1
	// 2. From i to j is a one-to-one mapping
	template<class T> void Array::TransposeRowsToColumns(T * input, const int length, const int columns)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is not positive.", length));
		if (columns <= 0) throw invalid_argument(String::Format("columns %d is not positive.", columns));
		if (length % columns > 0) throw invalid_argument(String::Format("length %d is not multiple of columns %d.", length, columns));

		int rows = length / columns;

		if (columns >= rows && (columns % rows > 0))
			throw invalid_argument(String::Format("columns %d is not multiple of rows %d.", columns, rows));

		if (rows >= columns && (rows % columns > 0))
			throw invalid_argument(String::Format("rows %d is not multiple of columns %d.", rows, columns));

		if (columns > rows) {
			// Transpose element (m,n) to ((n % M), (km + n/M)) means the index i = Nm + n is mapped to j = (n % M)N + km + n/M
			function<int(int, int, int)> permute = [=](int i, int r, int c)->int {
				int m = i / c;
				int n = i % c;
				int j = (n % r) * c + (c / r) * m + n / r;
				return j;
			};

			Permute(input, length, columns, permute);
		} else if (rows > columns) {
			// Transpose element (m,n) to ((m%k)N + n, m/k)) means the index i = Nm + n is mapped to j = (m%k)NN + nN + m/k
			function<int(int, int, int)> permute = [=](int i, int r, int c)->int {
				int m = i / c;
				int n = i % c;
				int k = r / c;
				int j = (m % k) * c * c + n * c + m / k;
				return j;
			};

			Permute(input, length, columns, permute);
		} else {
			Transpose(input, length, columns);
		}
	}

	// Given an MxN array, where N = kM
	//     (0,0)   (0,1)   (0,2)   ...... (0,M-2)   (0,M-1)   (0,M)   (0,M+1)   ...... (0,N-2)   (0,N-1)
	//     (1,0)   (1,1)   (1,2)   ...... (1,M-2)   (1,M-1)   (1,M)   (1,M+1)   ...... (1,N-2)   (1,N-1)
	//     (2,0)   (2,1)   (2,2)   ...... (2,M-2)   (2,M-1)   (2,M)   (2,M+1)   ...... (2,N-2)   (2,N-1)
	//                             ......
	//                             ......
	//     (M-2,0) (M-2,1) (M-2,2) ...... (M-2,M-2) (M-2,M-1) (M-2,M) (M-2,M+1) ...... (M-2,N-2) (M-2,N-1)
	//     (M-1,0) (M-1,1) (M-1,2) ...... (M-1,M-2) (M-1,M-1) (M-1,M) (M-1,M+1) ...... (M-1,N-2) (M-1,N-1)
	// 
	// Transpose columns to rows
	//     (0,0)    (1,0)    ...... (M-1,0)    (0,1)     (1,1)       ...... (M-1,1)      ...... (0,k-1)  (1,k-1)  ...... (M-1,k-1)
	//     (0,k)    (1,k)    ...... (M-1,k)    (0,k+1)   (1,k+1)     ...... (M-1,k+1)    ...... (0,2k-1) (1,2k-1) ...... (M-1,2k-1)
	//                       ......                                  ......              ......                   ......
	//                       ......                                  ......              ......                   ......
	//     (0,kM-M) (1,kM-M) ...... (M-1,kM-M) (0,kM-M+1) (1,kM-M+1) ...... (M-1,kM-M+1) ...... (0,kM-1) (1,kM-1) ...... (M-1,kM-1)
	//
	// Transpose element (m,n) to (n/k, (n%k)M+m) means the index i = Nm + n is mapped to j = (n/k)N + (n%k)M + m
	// The mapping is actually a permutation:
	// 1. It is easy to see 0<= j <= MN-1
	// 2. From i to j is a one-to-one mapping
	//	
	// Given an MxN array, where M = kN
	//     (0,0)   (0,1)   (0,2)   ...... (0,N-2)   (0,N-1)
	//     (1,0)   (1,1)   (1,2)   ...... (1,N-2)   (1,N-1)
	//     (2,0)   (2,1)   (2,2)   ...... (2,N-2)   (2,N-1)
	//                             ......
	//                             ......
	//     (N-2,0) (N-2,1) (N-2,2) ...... (N-2,N-2) (N-2,N-1)
	//     (N-1,0) (N-1,1) (N-1,2) ...... (N-1,N-2) (N-1,N-1)
	//                             ......
	//                             ......
	//     (M-2,0) (M-2,1) (M-2,2) ...... (M-2,N-2) (M-2,N-1)
	//     (M-1,0) (M-1,1) (M-1,2) ...... (M-1,N-2) (M-1,N-1)
	// 
	// Transpose columns to rows
	//     (0,0)        (1,0)          (2,0)          ...... (N-2,0)    (N-1,0)
	//     (N,0)        (N+1,0)        (N+2,0)        ...... (2N-2,0)   (2N-1,0)
	//                                                ......
	//     ((k-1)N,0)   ((k-1)N+1,0)   ((k-1)N+2,0)   ...... (kN-2,0)   (kN-1,0)
	//     (0,1)        (1,1)          (2,1)          ...... (N-2,1)    (N-1,1)
	//     (N,1)        (N+1,1)        (N+2,1)        ...... (2N-2,1)   (2N-1,1)
	//                                                ......
	//     ((k-1)N,1)   ((k-1)N+1,1)   ((k-1)N+2,1)   ...... (kN-2,1)   (kN-1,1)
	//                                                ......
	//                                                ......
	//     (0,M-1)      (1,M-1)        (2,M-1)        ...... (N-2,M-1)  (N-1,M-1)
	//     (N,M-1)      (N+1,M-1)      (N+2,M-1)      ...... (2N-2,M-1) (2N-1,M-1)
	//                                                ......
	//     ((k-1)N,M-1) ((k-1)N+1,M-1) ((k-1)N+2,M-1) ...... (kN-2,M-1) (kN-1,M-1)
	//
	// Transpose element (m,n) to (kn + m/N, m % N)) means the index i = Nm + n is mapped to j = (kn+m/N)N + m%N
	// The mapping is actually a permutation:
	// 1. It is easy to see 0<= j <= MN-1
	// 2. From i to j is a one-to-one mapping
	template<class T> void Array::TransposeColumnsToRows(T * input, const int length, const int columns)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is not positive.", length));
		if (columns <= 0) throw invalid_argument(String::Format("columns %d is not positive.", columns));
		if (length % columns > 0) throw invalid_argument(String::Format("length %d is not multiple of columns %d.", length, columns));

		int rows = length / columns;

		if (columns >= rows && (columns % rows > 0))
			throw invalid_argument(String::Format("columns %d is not multiple of rows %d.", columns, rows));

		if (rows >= columns && (rows % columns > 0))
			throw invalid_argument(String::Format("rows %d is not multiple of columns %d.", rows, columns));

		if (columns > rows) {
			// Transpose element (m,n) to (n/k, (n%k)M+m) means the index i = Nm + n is mapped to j = (n/k)N + (n%k)M + m
			function<int(int, int, int)> permute = [=](int i, int r, int c)->int {
				int m = i / c;
				int n = i % c;
				int k = c / r;
				int j = (n / k) * c + (n % k) * r + m;
				return j;
			};

			Permute(input, length, columns, permute);
		} else if (rows > columns) {
			// Transpose element (m,n) to (kn + m/N, m % N)) means the index i = Nm + n is mapped to j = (kn+m/N)N + m%N
			function<int(int, int, int)> permute = [=](int i, int r, int c)->int {
				int m = i / c;
				int n = i % c;
				int k = r / c;
				int j = (k * n + m / c) * c + m % c;
				return j;
			};

			Permute(input, length, columns, permute);
		} else {
			Transpose(input, length, columns);
		}
	}

	template<class T> void Array::Print(Log & log, const T * input, const int length, const int columns)
	{
		if (input == nullptr || length <= 0) return;

		for (int i = 0; i < columns; i++) {
			log.WriteInformation("\t%d", i);
		}

		log.WriteInformation("\n");

		int rows = length / columns;
		for (int i = 0; i < rows; i++) {
			log.WriteInformation("%d", i);
			for (int j = 0; j < columns; j++) {
				log.WriteInformation("\t%d", *(input + i * columns + j));
			}

			log.WriteInformation("\n");
		}

		int remainders = length % columns;
		if (remainders > 0) {
			log.WriteInformation("%d", rows);
			for (int j = 0; j < remainders; j++) {
				log.WriteInformation("\t%d", *(input + rows * columns + j));
			}

			log.WriteInformation("\n");
		}
	}
}

