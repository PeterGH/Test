#pragma once

#include "Random.h"

namespace Test {
	class _declspec(dllexport) QuickSort {
	private:
		// Partition input[low..i], input[(i+1)..(j-1)], input[j..high] using input[high],
		// such that input[low..i] < input[high] <= input[(i+1)..(j-1)].
		// If all elements are equal, then return index low
		template<class T> static int Partition(T * input, int low, int high);
		
		// Sort input[low..high] using partition
		template<class T> static void Sort(T * input, int low, int high);

		// Parallel sort input[low..high]
		template<class T> static void ParallelSort(T * input, int low, int high);
		
		// Randomly select an element to partition the input.
		template<class T> static int RandomPartition(T * input, int low, int high);		

		// Sort input[low..high] using random partition
		template<class T> static void RandomSort(T * input, int low, int high);

		// Return the element of the i-th (zero-based) order from input[low..high]
		template<class T> static T & RandomSelect(T * input, int low, int high, int i);
	public:

		// Quick sort input
		template<class T> static void Sort(T * input, int length);

		// Parallel quick sort input
		template<class T> static void ParallelSort(T * input, int length);
		
		// Random quick sort input
		template<class T> static void RandomSort(T * input, int length);
		
		// Return the element of the i-th (zero-based) order from input[low..high]
		// This will change the ordering of elements because RandomPartition re-order the elements.
		template<class T> static T & RandomSelect(T * input, int length, int i);
	};

	template<class T> int QuickSort::Partition(T * input, int low, int high)
	{
		if (low >= 0 && low < high) {
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

	template<class T> void QuickSort::Sort(T * input, int low, int high)
	{
		if (low >= 0 && low < high) {
			int middle = Partition(input, low, high);
			if (low <= middle && middle <= high) {
				Sort(input, low, middle - 1);
				Sort(input, middle + 1, high);
			}
		}
	}

	template<class T> void QuickSort::ParallelSort(T * input, int low, int high)
	{
		if (low >= 0 && low < high) {
			int middle = Partition(input, low, high);
			if (low <= middle && middle <= high) {
				parallel_invoke(
					[&input, low, middle]{ParallelSort(input, low, middle - 1); },
					[&input, middle, high]{ParallelSort(input, middle + 1, high); }
				);
			}
		}
	}
	
	template<class T> int QuickSort::RandomPartition(T * input, int low, int high)
	{		
		if (low >= 0 && low < high) {
			int i = low + Random::Next(high - low);
			swap(input[i], input[high]);
			i = Partition(input, low, high);
			return i;
		} else {
			return -1;
		}
	}

	template<class T> void QuickSort::RandomSort(T * input, int low, int high)
	{
		if (low >= 0 && low < high) {
			int middle = RandomPartition(input, low, high);
			if (low <= middle && middle <= high) {
				RandomSort(input, low, middle - 1);
				RandomSort(input, middle + 1, high);
			}
		}
	}

	template<class T> T & QuickSort::RandomSelect(T * input, int low, int high, int i)
	{
		if (low == high) return input[low];
		else {
			int m = RandomPartition(input, low, high);
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
				return RandomSelect(input, low, m - 1, i);
			} else {
				// low ...... m ............ high
				// 0   ...... k
				// 0   ............ i
				return RandomSelect(input, m + 1, high, i - k - 1);
			}
		}
	}

	template<class T> void QuickSort::Sort(T * input, int length)
	{
		if (length > 1) {
			Sort(input, 0, length - 1);
		}
	}

	template<class T> void QuickSort::ParallelSort(T * input, int length)
	{
		if (length > 1) {
			ParallelSort(input, 0, length - 1);
		}
	}

	template<class T> void QuickSort::RandomSort(T * input, int length)
	{
		if (length > 1) {
			RandomSort(input, 0, length - 1);
		}
	}

	template<class T> T & QuickSort::RandomSelect(T * input, int length, int i)
	{
		if (input == nullptr || length <= 0 || i < 0 || i > length)
			throw invalid_argument(String::Format("Invalid i %d", i));

		return RandomSelect(input, 0, length - 1, i);
	}
}