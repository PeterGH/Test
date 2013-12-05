#pragma once

#include "BinarySearch.h"
#include "Random.h"

namespace Test {
	class _declspec(dllexport) Partition {
	public:
		// Reorder input[low..i], input[(i+1)..(j-1)], input[j..high] using input[high],
		// such that input[low..i] < input[high] <= input[(i+1)..(j-1)].
		// Return the new index of element input[high]
		// If all elements are equal, then return index low
		template<class T> static int PartitionArray(T * input, int low, int high);

		// Randomly select an element to partition the input.
		// Return the new index of selected element
		template<class T> static int PartitionArrayRandomly(T * input, int low, int high);

		// Reorder input[low..high] such that it is partioned by the i-th order element, 
		// i.e., input[low..(low+i-1)] <= input[low+i] <= input[low+i+1..high]
		template<class T> static T & PartitionArray(T * input, int low, int high, int i);

		// Reorder input[low..high] such that it is partioned at the indices provided through an array.
		// Parameter low and high give the range of elements in input.
		// Parameter first and last give the range of indices used to partion input.
		// The elements of indices are sorted and are valid indices of input array.
		template<class T> static void PartitionArray(T * input, int low, int high, int * indices, int first, int last);
	};

	template<class T> int Partition::PartitionArray(T * input, int low, int high)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (low >= 0 && low <= high) {
			int i = low - 1;
			for (int j = low; j < high; j++) {
				if (input[j] < input[high]) {
					// The check can be <=.
					// The difference is:
					// 1. <= incurs more swaps, but it is stable because all elements equal to input[high] 
					//    are still in their original order
					// 2. < incurs less swaps, but it is unstable
					i++;
					swap(input[i], input[j]);
				}
			}

			// now input[low..i] < input[high], and input[(i+1)..(high-1)] >= input[high]
			i++;
			swap(input[i], input[high]);

			// now input[low..(i-1)] < input[i] <= input[(i+1)..high]
			return i;
		} else {
			return -1;
		}
	}

	template<class T> int Partition::PartitionArrayRandomly(T * input, int low, int high)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (low >= 0) {
			if (low == high) return low;
			else if (low < high) {
				int i = low + Random::Next(high - low);
				swap(input[i], input[high]);
				i = PartitionArray(input, low, high);
				return i;
			}
		}
		
		return -1;
	}

	template<class T> T & Partition::PartitionArray(T * input, int low, int high, int i)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (low < 0) throw invalid_argument(String::Format("low %d is less than zero", low));
		if (high < low) throw invalid_argument(String::Format("low %d is greater than high %d", low, high));
		if (i > high - low) throw invalid_argument(String::Format("i %d is greater than high %d - low %d", i, high, low));
		if (low == high) return input[low];
		else {
			int m = PartitionArrayRandomly(input, low, high);
			int k = m - low;
			if (i == k) {
				// low ......... m ......... high
				// 0   ......... k
				// 0   ......... i
				return input[m];
			} else if (i < k) {
				// low ............ m ...... high
				// 0   ............ k
				// 0   ...... i
				return PartitionArray(input, low, m - 1, i);
			} else {
				// low ...... m ............ high
				// 0   ...... k
				// 0   ............ i
				return PartitionArray(input, m + 1, high, i - k - 1);
			}
		}
	}

	template<class T> void Partition::PartitionArray(T * input, int low, int high, int * indices, int first, int last)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (low < 0) throw invalid_argument(String::Format("low %d is less than zero", low));
		if (high < low) throw invalid_argument(String::Format("low %d is greater than high %d", low, high));
		if (indices == nullptr) throw invalid_argument("indices is nullptr");
		if (first < 0) throw invalid_argument(String::Format("first %d is less than zero", first));
		if (last < first) throw invalid_argument(String::Format("first %d is greater than last %d", first, last));
		if (last - first > high - low) throw invalid_argument(String::Format("There are %d indices but only %d elements", last - first, high - low));
		if (low > indices[first]) throw invalid_argument(String::Format("low %d is greater than indices[%d] %d", low, first, indices[first]));
		if (high < indices[last]) throw invalid_argument(String::Format("high %d is less than indices[%d] %d", high, last, indices[last]));
		if (low == high) return;

		if (first == last) {
			if (low <= indices[first] && indices[first] <= high) {
				// low <= indices[first] <= high
				PartitionArray(input, low, high, indices[first] - low);
			}

			return;
		}

		int m = PartitionArrayRandomly(input, low, high);

		// Find the last element index in indices less than m
		int k = first + BinarySearch::FindPositionToInsert<int>(m, &indices[first], last - first + 1);

		// low ................................ m ............................... high
		//        indices[fist] .... indices[k]   indices[k+1] .... indices[last]
		// first <= k < last, if indices[first] < m < indices[last]
		//
		// low .. m ............................................................. high
		//      k   indices[fist] ................................. indices[last]
		// k < first, if m <= indices[first]
		//
		// low ............................................................... m .... high
		//       indices[fist] ................................. indices[last]   k
		// last <= k, if indices[last] < m

		if (first <= k && k < last) {
			// indices[k] < m <= indices[k+1]
			if (m == indices[k + 1]) {
				PartitionArray(input, low, m - 1, indices, first, k);
				if (k + 1 < last) PartitionArray(input, m + 1, high, indices, k + 2, last);
			} else {
				PartitionArray(input, low, m - 1, indices, first, k);
				PartitionArray(input, m + 1, high, indices, k + 1, last);
			}
		} else if (k < first) {
			// m <= indices[first]
			if (m == indices[first])
				PartitionArray(input, m + 1, high, indices, first + 1, last);
			else
				PartitionArray(input, m + 1, high, indices, first, last);
		} else if (last <= k) {
			PartitionArray(input, low, m - 1, indices, first, last);
		}
	}
}