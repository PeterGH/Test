#pragma once
namespace Test {
	class _declspec(dllexport) Search {
	public:
		// Assume the input array is already sorted.
		// The return value is the index of the element to search in the sorted input array if found, otherwise -1.
		// The return value may be the first index or the last index as the input array may contain duplicate elements.
		template<class T> static int BinarySearch(const T & element, const T * input, int length, bool firstIndex = true);
		template<class T> static int BinarySearchRecursively(const T & element, const T * input, int low, int high, bool firstIndex = true);
	};

	template<class T> int Search::BinarySearch(const T & element, const T * input, int length, bool firstIndex)
	{
		if (input == nullptr || length <= 0) return -1;
		int low = 0;
		int high = length - 1;
		while (low <= high) {
			// (1) If low < high - 1, then low < middle < high
			// (2) If low = high - 1, then low = middle < high
			// (3) If low = high, then low = middle = high
			int middle = low + ((high - low) >> 1);
			if (element < input[middle]) high = middle - 1;
			else if (element > input[middle]) low = middle + 1;
			else {
				// The input array may contain duplicate elements.
				if (firstIndex) {
					if (low == middle) return middle;
					else high = middle;
				} else {
					if (middle == high) return middle;
					else if (low < middle) low = middle;
					else {
						if (element == input[middle + 1]) low = middle + 1;
						else return middle;
					}
				}
			}
		}
		return -1;
	}

	template<class T> int Search::BinarySearchRecursively(const T & element, const T * input, int low, int high, bool firstIndex)
	{
		if (input == nullptr || low < 0 || high < 0 || high < low) return -1;
		int middle = low +  ((high - low) >> 1);
		if (element < input[middle]) return BinarySearchRecursively(element, input, low, middle - 1, firstIndex);
		else if (element > input[middle]) return BinarySearchRecursively(element, input, middle + 1, high, firstIndex);
		else {
			// The input array may contain duplicate elements.
			if (firstIndex) {
				if (low == middle) return middle;
				else return BinarySearchRecursively(element, input, low, middle, firstIndex);
			} else {
				if (middle == high) return middle;
				else if (low < middle) return BinarySearchRecursively(element, input, middle, high, firstIndex);
				else {
					if (element == input[middle + 1]) return BinarySearchRecursively(element, input, middle + 1, high, firstIndex);
					else return middle;
				}
			}
		}
	}
}
