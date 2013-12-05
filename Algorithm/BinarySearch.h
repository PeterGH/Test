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
}