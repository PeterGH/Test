#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include "Partition.h"
#include "Sort.h"
using namespace std;
namespace Test {
	class _declspec(dllexport) Search {
	public:
		// Assume the input array is already sorted.
		// The return value is the index of the element to search in the sorted input array if found, otherwise -1.
		// The return value may be the first index or the last index as the input array may contain duplicate elements.
		template<class T> static int BinarySearch(const T & element, const T * input, int length, bool firstIndex = true);
		template<class T> static int BinarySearchRecursively(const T & element, const T * input, int low, int high, bool firstIndex = true);

		// Assume array input[0..(length-1)] is already sorted and it can contain duplicate elements.
		// Return -1 if transform(element) < transform(input[0])
		// Return (length-1) if transform(input[length-1]) < transform(element) or transform(input[length-1]) = transform(element) and firstIndex is false
		// Return i if transform(input[i]) < transform(element) <= transform(input[i+1]) and firstIndex is true
		// Return i if transform(input[i]) <= transform(element) < transform(input[i+1]) and firstIndex is false
		template<class T, class C> static int FindPositionToInsert(
			const T & element,
			const T * input,
			int length,
			bool firstIndex = true,
			function<C(T)> transform = [&](T v)->C{ return v; });

		// Assume array input[0..(length-1)] is already sorted and it can contain duplicate elements.
		// Return -1 if element < input[0]
		// Return (length-1) if input[length-1] < e or input[length-1] = e and firstIndex is false
		// Return i if input[i] < e <= input[i+1] and firstIndex is true
		// Return i if input[i] <= e < input[i+1] and firstIndex is false
		template<class T> static int FindPositionToInsert(const T & element, const T * input, int length, bool firstIndex = true);

		// Find all pairs of elements each of which is summed up to a given value
		// Return the indices using a vector
		// The elements of input will be rearranged so the indices returned are not the original ones
		template<class T> static void TwoSum(T * input, int length, const T sum, vector<pair<int, int>> & indices);
		template<class T> static void TwoSum2(T * input, int length, const T sum, vector<pair<int, int>> & indices);
		template<class T> static void TwoSum3(T * input, int length, const T sum, vector<pair<int, int>> & indices);
		template<class T> static void TwoSum4(T * input, int length, const T sum, vector<pair<int, int>> & indices);

		// Find a subarray of contiguous elements whose sum is maximized
		// If array contains both positive and negative numbers, return the maximum subarray
		// If array contains positive numbers, return entire array A
		// If array contains non-positive numbers, return the maximum number
		// Parameter sum is the summation of the returned subarray
		// Parameters start and end are the start and end indices of the returned subarray
		template<class T> static void MaxSum(const T * input, int length, int & start, int & end, T & sum);
		template<class T> static void MaxSum2(const T * input, int length, int & start, int & end, T & sum);
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

	template<class T, class C> int Search::FindPositionToInsert(const T & element, const T * input, int length, bool firstIndex, function<C(T)> transform)
	{
		if (input == nullptr) throw invalid_argument("input is a nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));

		C v = transform(element);
		int low = 0;
		int high = length - 1;
		// The loop ensures input[0..(low-1)] < e < input[(high+1)..(length-1)]
		while (low <= high) {
			// (1) If low < high - 1, then low < middle < high
			// (2) If low = high - 1, then low = middle < high
			// (3) If low = high, then low = middle = high
			int middle = low + ((high - low) >> 1);
			if (v < transform(input[middle])) {
				if (low == middle) return low - 1; // Case (2) or (3)
				else high = middle - 1; // Case (1)
			} else if (v > transform(input[middle])) {
				if (middle == high) return high; // Case (3)
				else low = middle + 1; // Case (1) or (2)
			} else {
				// The input array may contain duplicate elements.
				if (firstIndex) {
					if (low == middle) return low - 1; // Case (2) or (3)
					else high = middle; // Case (1)
				} else {
					if (middle == high) return high; // Case (3)
					else if (low < middle) low = middle; // Case (1)
					else { // Case (2)
						if (v == transform(input[middle + 1])) low = middle + 1;
						else return middle;
					}
				}
			}
		}

		// We should not hit this line.
		throw runtime_error(String::Format("Cannot find insertion point. low = %d, high = %d", low, high));
	}

	template<class T> int Search::FindPositionToInsert(const T & element, const T * input, int length, bool firstIndex)
	{
		return FindPositionToInsert<T, T>(element, input, length, firstIndex, [&](T e)->T{return e; });
	}

	template<class T> void Search::TwoSum(T * input, int length, const T sum, vector<pair<int, int>> & indices)
	{
		if (input == nullptr) throw invalid_argument("input is a nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));

		if (length == 1) return;

		Sort::Merge::Sort<T>(input, length);

		for (int i = 0; i < length - 1; i++) {
			// Given input[i], try to find the other one in input[i+1..length-1]
			T v = sum - input[i];
			int j = BinarySearch<T>(v, &input[i + 1], length - 1 - i, true);
			if (j == -1) continue; // No element == sum - input[i]
			j = i + 1 + j;
			do {
				indices.push_back(make_pair(i, j));
				j++;
			} while (j < length && input[j] == v);
		}
	}

	template<class T> void Search::TwoSum2(T * input, int length, const T sum, vector<pair<int, int>> & indices)
	{
		if (input == nullptr) throw invalid_argument("input is a nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));

		if (length == 1) return;

		T half = sum >> 1;

		// input may contain positive and negative values

		int shortRangeBegin;
		int shortRangeEnd;
		int longRangeBegin;
		int longRangeEnd;

		if ((sum & 0x1) == 0) {
			//
			// sum is even
			// +--------------------------+---------------------+------------------------------+
			// 0                          i1                    i2                          length-1
			//           < sum/2                  = sum/2                > sum/2

			// Partition input so that input[0..i1] <= half - 1 < input[i1+1..length-1]
			int i1 = Partition::PartitionArrayByValue(input, 0, length - 1, half - 1);
			if (i1 == length - 1) {
				// All elements are less than sum/2 - 1, no matter whether sum is positive or negative.
				return;
			}

			// Partition input once more so that input[i1+1..i2] = half < input[i2+1..length-1]
			// Note it is possible that i2 == i1
			int i2 = Partition::PartitionArrayByValue(input, i1 + 1, length - 1, half);

			// Now input[i1+1..i2] == sum/2
			for (int i = i1 + 1; i < i2; i++) {
				for (int j = i + 1; j <= i2; j++) {
					indices.push_back(make_pair(i, j));
				}
			}

			if (i1 == -1 || i2 == length - 1) return; // All elements are equal to sum/2

			if (i1 + 1 >= length - 1 - i2) {
				shortRangeBegin = i2 + 1;
				shortRangeEnd = length - 1;
				longRangeBegin = 0;
				longRangeEnd = i1;
			} else {
				shortRangeBegin = 0;
				shortRangeEnd = i1;
				longRangeBegin = i2 + 1;
				longRangeEnd = length - 1;
			}
		} else {
			//
			// sum is odd
			// +-------------------------------------+-----------------------------------------+
			// 0                                     i1                                     length-1
			//                 <= sum/2                             >= sum/2 + 1

			// Partition input so that input[0..i1] <= half < input[i1+1..length-1]
			int i1 = Partition::PartitionArrayByValue(input, 0, length - 1, half);

			if (i1 == -1) {
				// All elements are greater than sum/2, no matter whether sum is positive or negative.
				return;
			}

			if (i1 == length - 1) {
				// All elements are less than or equal to sum/2, no matter whether sum is positive or negative.
				return;
			}

			if (i1 + 1 >= length - 1 - i1) {
				shortRangeBegin = i1 + 1;
				shortRangeEnd = length - 1;
				longRangeBegin = 0;
				longRangeEnd = i1;
			} else {
				shortRangeBegin = 0;
				shortRangeEnd = i1;
				longRangeBegin = i1 + 1;
				longRangeEnd = length - 1;
			}
		}

		Sort::Merge::Sort<T>(input, longRangeBegin, longRangeEnd);

		for (int i = shortRangeBegin; i <= shortRangeEnd; i++) {
			T v = sum - input[i];
			int j = BinarySearch<T>(v, &input[longRangeBegin], longRangeEnd - longRangeBegin + 1, true);
			if (j == -1) continue; // No element == sum - input[i]
			j = longRangeBegin + j;
			do {
				indices.push_back(make_pair(i, j));
				j++;
			} while (j <= longRangeEnd && input[j] == v);
		}
	}

	template<class T> void Search::TwoSum3(T * input, int length, const T sum, vector<pair<int, int>> & indices)
	{
		if (length < 2) return;
		vector<pair<T, int>> m;
		for (int i = 0; i < length; i++) {
			m.push_back(make_pair(input[i], i));
		}
		sort(m.begin(), m.end());
		int i = 0;
		int j = m.size() - 1;
		while (i < j) {
			T s = m[i].first + m[j].first;
			if (s < sum) {
				i++;
			} else if (s > sum) {
				j--;
			} else {
				int p = i;
				while (p + 1 <= j && m[p + 1].first == m[i].first) p++;
				int q = j;
				while (i <= q - 1 && m[q - 1].first == m[j].first) q--;
				if (p < q) {
					for (int r = i; r <= p; r++) {
						for (int s = q; s <= j; s++) {
							indices.push_back(make_pair(min(m[r].second, m[s].second), max(m[r].second, m[s].second)));
						}
					}
					i = p + 1;
					j = q - 1;
				} else { // p == j && q == i
					for (int r = i; r < j; r++) {
						for (int s = r + 1; s <= j; s++) {
							indices.push_back(make_pair(min(m[r].second, m[s].second), max(m[r].second, m[s].second)));
						}
					}
					break;
				}
			}
		}
	}

	template<class T> void Search::TwoSum4(T * input, int length, const T sum, vector<pair<int, int>> & indices)
	{
		if (length < 2) return;
		unordered_multimap<T, int> m;
		for (int i = 0; i < length; i++) {
			T d = sum - input[i];
			auto range = m.equal_range(d);
			for_each(range.first, range.second, [&](unordered_multimap<T, int>::value_type & v){
				indices.push_back(make_pair(v.second, i));
			});
			m.insert(make_pair(input[i], i));
		}
	}

	template<class T> void Search::MaxSum(const T * input, int length, int & start, int & end, T & sum)
	{
		start = -1;
		end = -1;
		sum = INT_MIN;

		if (input == nullptr || length <= 0) return;

		// Track the last maximum sum so far
		start = 0;
		end = 0;
		sum = 0;

		// Track the current streak
		int l = 0; // Beginning
		T c = 0; // Cumulative sum up to current element
		int max = 0; // The index of the maximum element seen so far

		for (int i = 0; i < length; i++) {
			c += input[i];

			if (c > sum) {
				// Current element is positive and the current sum is larger than the last one.
				// Update the last seen maximum sum
				start = l;
				end = i;
				sum = c;
			} else if (c <= 0) {
				// Current element is negative and everything cancel out
				// Reset and start from the next element
				l = i + 1;
				c = 0;
			}

			// Record the max element so far
			if (input[i] >= input[max]) max = i;
		}

		if (sum <= 0) {
			// All elements are zero or negative
			// Return the maximum element
			start = max;
			end = max;
			sum = input[max];
		}
	}

	template<class T> void Search::MaxSum2(const T * input, int length, int & start, int & end, T & sum)
	{
		start = -1;
		end = -1;
		sum = INT_MIN;

		if (input == nullptr || length <= 0) return;

		int minIndex = -1;
		int minSum = 0; // sum[0..minIndex]
		int s = 0; // sum[0..i]
		for (int i = 0; i < length; i++) {
			s += input[i];
			int d = s - minSum;
			if (d >= sum) {
				start = minIndex + 1;
				if (d != sum || input[i] != 0 || sum == 0) end = i;
				sum = d;
			}
			if (s <= minSum) {
				minSum = s;
				minIndex = i;
			}
		}
	}

}
