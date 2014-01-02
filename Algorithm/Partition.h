#pragma once

#include <functional>
#include "BinarySearch.h"
#include "Random.h"

using namespace std;

namespace Test {
	class _declspec(dllexport) Partition {
	public:
		// Reorder input[low..i], input[(i+1)..(j-1)], input[j..high] using value,
		// such that transform(input[low..i]) <= transform(value) < transform(input[(i+1)..j]).
		// Return the index i, i.e. the last element less than or equal to value
		// If all elements are less than value, then return index high
		// If all elements are greater than value, then return low-1
		template<class T, class C> static int PartitionArrayByValue(T * input, int low, int high, const T & value, function<C(T)> transform);

		// Reorder input[low..i], input[(i+1)..(j-1)], input[j..high] using value,
		// such that input[low..i] <= value < input[(i+1)..j].
		// Return the index i, i.e. the last element less than or equal to value
		// If all elements are less than value, then return index high
		// If all elements are greater than value, then return low-1
		template<class T> static int PartitionArrayByValue(T * input, int low, int high, const T & value);

		// Reorder input[low..i], input[(i+1)..(j-1)], input[j..high] using input[high],
		// such that transform(input[low..i]) < transform(input[high]) <= transform(input[(i+1)..(j-1)]).
		// Return the new index of element input[high]
		// If all elements are equal, then return index low
		template<class T, class C> static int PartitionArray(T * input, int low, int high, function<C(T)> transform);

		// Reorder input[low..i], input[(i+1)..(j-1)], input[j..high] using input[high],
		// such that input[low..i] < input[high] <= input[(i+1)..(j-1)].
		// Return the new index of element input[high]
		// If all elements are equal, then return index low
		template<class T> static int PartitionArray(T * input, int low, int high);

		// Randomly select an element to partition the input.
		// Return the new index of selected element
		template<class T, class C> static int PartitionArrayRandomly(T * input, int low, int high, function<C(T)> transform);

		// Randomly select an element to partition the input.
		// Return the new index of selected element
		template<class T> static int PartitionArrayRandomly(T * input, int low, int high);

		// Reorder input[low..high] such that it is partioned by the i-th order element, 
		// i.e., input[low..(low+i-1)] <= input[low+i] <= input[low+i+1..high]
		template<class T, class C> static T & PartitionArrayByOrder(T * input, int low, int high, int i, function<C(T)> transform);

		// Reorder input[low..high] such that it is partioned by the i-th order element, 
		// i.e., input[low..(low+i-1)] <= input[low+i] <= input[low+i+1..high]
		template<class T> static T & PartitionArrayByOrder(T * input, int low, int high, int i);

		// Reorder input[low..high] such that it is partioned at the indices provided through an array.
		// Parameter low and high give the range of elements in input.
		// Parameter first and last give the range of indices used to partion input.
		// The elements of indices are sorted and are valid indices of input array.
		template<class T> static void PartitionArrayByOrders(T * input, int low, int high, int * indices, int first, int last);

		// The k-th quantiles of an array with length are k-1 elements evenly dividing the array so that
		// the set of subarrays is sorted, i.e., each element of a subarray is not less than each element of its preceeding subarray,
		// and not greater than each element of its succeeding subarray.
		// This method partition the input array and return the indices of the k-1 elements forming the quantiles.
		// Parameter order defines the order of quantiles, i.e., array indices will be used to return order-1 indices.
		template<class T> static void PartitionArrayByQuantiles(T * input, int length, int * indices, int order);

		// Find k closest neighbors to the i-th order element.
		// Parameter pivotIndex is the order of the input element.
		// When the method finishes, the first 1 + countNeighbors elements are the pivot element and its closest neighbors.
		template<class T> static T SelectClosestNeighbors(T * input, int length, int pivotIndex, int countNeighbors);
	};

	template<class T, class C> int Partition::PartitionArrayByValue(T * input, int low, int high, const T & value, function<C(T)> transform)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (low < 0) throw invalid_argument(String::Format("low %d is less than zero", low));
		if (high < low) throw invalid_argument(String::Format("low %d is greater than high %d", low, high));
		int i = low - 1;
		C v = transform(value);
		for (int j = low; j <= high; j++) {
			if (transform(input[j]) <= v) {
				// The check can be <.
				// The difference is:
				// 1. <= incurs more swaps, but it is stable because all elements equal to value 
				//    are still in their original order. The return value is the last index of elements equal to value.
				// 2. < incurs less swaps, but it is unstable. The return value is the first index of elements equal to value.
				i++;
				swap(input[i], input[j]);
			}
		}

		// now input[low..i] <= value < input[(i+1)..high]
		return i;
	}

	template<class T> int Partition::PartitionArrayByValue(T * input, int low, int high, const T & value)
	{
		return PartitionArrayByValue<T, T>(input, low, high, value, [](T v)->T{ return v; });
	}

	template<class T, class C> int Partition::PartitionArray(T * input, int low, int high, function<C(T)> transform)
	{
		T v = input[high];
		return PartitionArrayByValue<T, C>(input, low, high, v, transform);
	}
	
	template<class T> int Partition::PartitionArray(T * input, int low, int high)
	{
		return PartitionArray<T, T>(input, low, high, [](T v)->T{ return v; });
	}

	template<class T, class C> int Partition::PartitionArrayRandomly(T * input, int low, int high, function<C(T)> transform)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (low < 0) throw invalid_argument(String::Format("low %d is less than zero", low));
		if (high < low) throw invalid_argument(String::Format("low %d is greater than high %d", low, high));

		int i = Random::Next(low, high);
		swap(input[i], input[high]);
		return PartitionArray<T, C>(input, low, high, transform);
	}
	
	template<class T> int Partition::PartitionArrayRandomly(T * input, int low, int high)
	{
		return PartitionArrayRandomly<T, T>(input, low, high, [](T v)->T{ return v; });
	}

	template<class T, class C> T & Partition::PartitionArrayByOrder(T * input, int low, int high, int i, function<C(T)> transform)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (low < 0) throw invalid_argument(String::Format("low %d is less than zero", low));
		if (high < low) throw invalid_argument(String::Format("low %d is greater than high %d", low, high));
		if (i > high - low) throw invalid_argument(String::Format("i %d is greater than high %d - low %d", i, high, low));
		if (low == high) return input[low];
		else {
			int m = PartitionArrayRandomly(input, low, high, transform);
			int k = m - low;
			if (i == k) {
				// low ......... m ......... high
				// 0   ......... k
				// 0   ......... i
				return input[m];
			}
			else if (i < k) {
				// low ............ m ...... high
				// 0   ............ k
				// 0   ...... i
				return PartitionArrayByOrder(input, low, m - 1, i, transform);
			}
			else {
				// low ...... m ............ high
				// 0   ...... k
				// 0   ............ i
				return PartitionArrayByOrder(input, m + 1, high, i - k - 1, transform);
			}
		}
	}

	template<class T> T & Partition::PartitionArrayByOrder(T * input, int low, int high, int i)
	{
		return PartitionArrayByOrder<T, T>(input, low, high, i, [](T v)->T{ return v; });
	}

	template<class T> void Partition::PartitionArrayByOrders(T * input, int low, int high, int * indices, int first, int last)
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
				PartitionArrayByOrder(input, low, high, indices[first] - low);
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
				PartitionArrayByOrders(input, low, m - 1, indices, first, k);
				if (k + 1 < last) PartitionArrayByOrders(input, m + 1, high, indices, k + 2, last);
			} else {
				PartitionArrayByOrders(input, low, m - 1, indices, first, k);
				PartitionArrayByOrders(input, m + 1, high, indices, k + 1, last);
			}
		} else if (k < first) {
			// m <= indices[first]
			if (m == indices[first])
				PartitionArrayByOrders(input, m + 1, high, indices, first + 1, last);
			else
				PartitionArrayByOrders(input, m + 1, high, indices, first, last);
		} else if (last <= k) {
			PartitionArrayByOrders(input, low, m - 1, indices, first, last);
		}
	}

	template<class T> void Partition::PartitionArrayByQuantiles(T * input, int length, int * indices, int order)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is less than or equal to zero", length));
		if (indices == nullptr) throw invalid_argument("indices is nullptr");
		if (order < 1) throw invalid_argument(String::Format("order %d is less than 1", order));
		if (order > length) throw invalid_argument(String::Format("order %d is greater than length %d", order, length));

		if (order == 1) return;

		int step = length / order;
		int remainder = length % order;

		// 0                                                                                                         L-1
		// +----------+----------+----------+----------+----------+----------+----------+----------+----------+-------+
		// 0         step       2*step             (R-1)*step   R*step                         (O-1)*step   O*step  O*step+R-1
		//            0          1                    R-2        R-1         R                    O-2

		int s = 0;
		if (step > 1) {
			for (int i = 0; i < remainder; i++) {
				indices[i] = s + step;
				s = indices[i];
			}

			for (int i = remainder; i < order - 1; i++) {
				indices[i] = s + step - 1;
				s = indices[i];
			}
		} else {
			for (int i = 0; i < order - 1; i++) {
				indices[i] = s + step;
				s = indices[i];
			}
		}

		PartitionArrayByOrders(input, 0, length - 1, indices, 0, order - 2);
	}

	template<class T> T Partition::SelectClosestNeighbors(T * input, int length, int pivotIndex, int countNeighbors)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is less than or equal to zero", length));
		if (pivotIndex < 0 || pivotIndex >= length) throw invalid_argument(String::Format("pivotIndex %d is not in [0, %d]", pivotIndex, length - 1));
		if (countNeighbors < 0 || countNeighbors >= length) throw invalid_argument(String::Format("countNeighbors %d is not in [0, %d]", countNeighbors, length - 1));
		PartitionArrayByOrder(input, 0, length - 1, pivotIndex);
		T pivot = input[pivotIndex];
		PartitionArrayByOrder<T, int>(input, 0, length - 1, countNeighbors, [&pivot](T v)->int{ return abs(v - pivot); });
		return pivot;
	}
}