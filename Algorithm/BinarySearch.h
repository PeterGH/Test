#pragma once

#include "String.h"

namespace Test {
	class _declspec(dllexport) BinarySearch {
	public:
		// Assume the input array is already sorted.
		// The return value is the index of the element to search in the sorted input array if found, otherwise -1.
		// The return value may be the first index or the last index as the input array may contain duplicate elements.
		template<class T> static int Search(const T & element, const T * input, int length, bool firstIndex = true);

		// Assume the input array is already sorted.
		// The return value is the index of the element to search in the sorted input array if found, otherwise -1.
		// The return value may be the first index or the last index as the input array may contain duplicate elements.
		template<class T> static int SearchRecursively(const T & element, const T * input, int low, int high, bool firstIndex = true);

		// Assume array input[0..(length-1)] is already sorted and it can contain duplicate elements.
		// Return -1 if element < input[0]
		// Return (length-1) if input[length-1] < e or input[length-1] = e and firstIndex is false
		// Return i if input[i] < e <= input[i+1] and firstIndex is true
		// Return i if input[i] <= e < input[i+1] and firstIndex is false
		template<class T> static int FindPositionToInsert(const T & element, const T * input, int length, bool firstIndex = true);

		// Find the median of a sorted array.
		// If the array length is odd, then the median is unique.
		// If the array length is even, then return the lower median.
		template<class T> static T FindMedian(const T * input, int length);

		// Find the median from two sorted arrays.
		// If the two arrays contain odd number of elements, then the median is unique.
		// If the two arrays contain even number of elements, then return the lower median.
		template<class T> static T FindMedian(const T * input1, int length1, const T * input2, int length2);
	};

	template<class T> int BinarySearch::Search(const T & element, const T * input, int length, bool firstIndex)
	{
		if (input == nullptr || length <= 0) return -1;
		int low = 0;
		int high = length - 1;
		while (low <= high) {
			int middle = (low + high) >> 1;
			if (element < input[middle]) high = middle - 1;
			else if (element > input[middle]) low = middle + 1;
			else {
				// The input array may contain duplicate elements.
				if (firstIndex) {
					while (middle > 0 && element == input[middle - 1]) {
						middle--;
					}
				} else {
					while (middle < length - 1 && element == input[middle + 1]) {
						middle++;
					}
				}

				return middle;
			}
		}

		return -1;
	}

	template<class T> int BinarySearch::SearchRecursively(const T & element, const T * input, int low, int high, bool firstIndex)
	{
		if (input == nullptr || low < 0 || high < 0 || high < low) return -1;
		int middle = (low + high) >> 1;
		if (element < input[middle]) return SearchRecursively(element, input, low, middle - 1, firstIndex);
		else if (element > input[middle]) return SearchRecursively(element, input, middle + 1, high, firstIndex);
		else {
			// The input array may contain duplicate elements.
			if (firstIndex) {
				while (middle > low && element == input[middle - 1]) {
					middle--;
				}
			} else {
				while (middle < high && element == input[middle + 1]) {
					middle++;
				}
			}

			return middle;
		}
	}

	template<class T> int BinarySearch::FindPositionToInsert(const T & element, const T * input, int length, bool firstIndex)
	{
		if (input == nullptr) throw invalid_argument("input is a nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));

		int low = 0;
		int high = length - 1;
		// The loop ensures input[0..(low-1)] < e < input[(high+1)..(length-1)]
		while (low <= high) {
			// (1) If low < high - 1, then low < middle < high
			// (2) If low = high - 1, then low = middle < high
			// (3) If low = high, then low = middle = high
			int middle = (low + high) >> 1;
			if (element < input[middle]) {
				if (middle == low) {
					// Case (2) or (3)
					return low - 1;
				} else {
					// Case (1)
					high = middle - 1;
				}
			} else if (element > input[middle]) {
				if (middle == high) {
					// Case (3)
					return high;
				} else {
					// Case (1) or (2)
					low = middle + 1;
				}
			} else {
				// The input array may contain duplicate elements.
				if (firstIndex) {
					while (middle > 0 && element == input[middle - 1]) {
						middle--;
					}

					middle--;
				} else {
					while (middle < length - 1 && element == input[middle + 1]) {
						middle++;
					}
				}

				return middle;
			}
		}

		// We should not hit this line.
		throw runtime_error(String::Format("Cannot find insertion point. low = %d, high = %d", low, high));
	}

	template<class T> T BinarySearch::FindMedian(const T * input, int length)
	{
		if (input == nullptr) throw invalid_argument("input is a nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));

		// If l = 2m
		// +----------------+  +------------------+  
		// 0               m-1 m                 2m-1
		// The median index is m-1 = (l - 1) / 2, rounding to the lower boundary
		//
		// If l = 2m-1
		// +----------------+   +   +------------------+  
		// 0               m-2 m-1  m                 2m-2
		// The median index is m-1 = (l - 1) / 2

		int medianIndex = (length - 1) >> 1;
		return input[medianIndex];
	}

	template<class T> T BinarySearch::FindMedian(const T * input1, int length1, const T * input2, int length2)
	{
		if (input1 == nullptr) throw invalid_argument("input1 is a nullptr");
		if (length1 <= 0) throw invalid_argument(String::Format("length1 %d is invalid", length1));
		if (input2 == nullptr) throw invalid_argument("input2 is a nullptr");
		if (length2 <= 0) throw invalid_argument(String::Format("length2 %d is invalid", length2));

		const T * shortArray;
		int shortLength;
		const T * longArray;
		int longLength;

		if (length1 <= length2) {
			shortLength = length1;
			shortArray = input1;
			longLength = length2;
			longArray = input2;
		} else {
			shortLength = length2;
			shortArray = input2;
			longLength = length1;
			longArray = input1;
		}

		int medianIndex = (shortLength + longLength - 1) / 2;
		if (shortArray[shortLength - 1] <= longArray[0]) {
			if (medianIndex == shortLength - 1) {
				// +---------------------------------------+  +---------------------------------------+
				// 0                                      s-1 0                                      l-1
				// s = l
				// m = s - 1 = l - 1
				return shortArray[medianIndex];
			} else {
				// +---------------------------------------+  +-----+------------------------------------------+
				// 0                                      s-1 0    m-s                                        l-1
				// s < l
				// m = (s + l - 1) / 2
				//   = k - 1    if (s + l) = 2k
				//     k - 1    if (s + l) = 2k - 1
				// s - 1 < m < l - 1
				return longArray[medianIndex - shortLength];
			}
		} else if (longArray[longLength - 1] <= shortArray[0]) {
			// +---------------------------------------+---------+  +---------------------------------------+
			// 0                                       m        l-1 0                                      s-1
			// s <= l
			// m = (s + l - 1) / 2
			//   = k - 1    if (s + l) = 2k
			//     k - 1    if (s + l) = 2k - 1
			// s - 1 <= m <= l - 1
			return longArray[medianIndex];
		}

		// +---------------------------------------+  
		// 0               m m+1                  s-1
		// +-----------------------------------------------+
		// 0                n n+1                         l-1
		//
		// m + n = medianIndex - 1
		// Median = S[m] if L[n] < S[m] <= L[n+1]
		//          L[n] if S[m] < L[n] <= S[m+1]
		//          S[m] if S[m] == L[n]

		int low = 0;
		int high = shortLength - 1;
		while (true) {
			// (1) If low < high - 1, then low < m < high
			// (2) If low = high - 1, then low = m < high
			// (3) If low = high, then low = m = high
			int m = (low + high) >> 1;
			int n = medianIndex - m - 1;
			if (shortArray[m] > longArray[n]) {
				if (shortArray[m] <= longArray[n + 1]) {
					return shortArray[m];
				} else {
					if (m < high) {
						// Case (1) or (2)
						high = m;
					} else {
						// Case (3)
						// s[m] > l[n] and s[m] > l[n+1]
						// Compare s[m-1] and l[n+1]
						if (m - 1 >= 0 || shortArray[m - 1] > longArray[n + 1])
							return shortArray[m - 1];
						else return longArray[n + 1];
					}
				}
			} else if (longArray[n] > shortArray[m]) {
				if (longArray[n] <= shortArray[m + 1]) {
					return longArray[n];
				} else {
					if (low < m) {
						// Case (1)
						low = m;
					} else {
						// Case (2) or (3)
						// l[n] > s[m] and l[n] > s[m+1]
						// Compare l[n-1] and s[m+1]
						if (n - 1 >= 0 && longArray[n - 1] > shortArray[m + 1])
							return longArray[n - 1];
						else return shortArray[m + 1];
					}
				}
			} else {
				return shortArray[m];
			}
		}
	}
}