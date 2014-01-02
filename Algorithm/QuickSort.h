#pragma once

#include "Partition.h"

namespace Test {
	class _declspec(dllexport) QuickSort {
	private:
		// Sort input[low..high] using partition
		template<class T> static void Sort(T * input, int low, int high);

		// Parallel sort input[low..high]
		template<class T> static void ParallelSort(T * input, int low, int high);
		
		// Sort input[low..high] using random partition
		template<class T> static void RandomSort(T * input, int low, int high);
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

	template<class T> void QuickSort::Sort(T * input, int low, int high)
	{
		if (input != nullptr && low >= 0 && low < high) {
			int middle = Partition::PartitionArray(input, low, high);
			if (low <= middle && middle <= high) {
				Sort(input, low, middle - 1);
				Sort(input, middle + 1, high);
			}
		}
	}

	template<class T> void QuickSort::ParallelSort(T * input, int low, int high)
	{
		if (input != nullptr && low >= 0 && low < high) {
			int middle = Partition::PartitionArray(input, low, high);
			if (low <= middle && middle <= high) {
				parallel_invoke(
					[&input, low, middle]{ParallelSort(input, low, middle - 1); },
					[&input, middle, high]{ParallelSort(input, middle + 1, high); }
				);
			}
		}
	}
	
	template<class T> void QuickSort::RandomSort(T * input, int low, int high)
	{
		if (input != nullptr && low >= 0 && low < high) {
			int middle = Partition::PartitionArrayRandomly(input, low, high);
			if (low <= middle && middle <= high) {
				RandomSort(input, low, middle - 1);
				RandomSort(input, middle + 1, high);
			}
		}
	}

	template<class T> void QuickSort::Sort(T * input, int length)
	{
		if (input != nullptr && length > 1) {
			Sort(input, 0, length - 1);
		}
	}

	template<class T> void QuickSort::ParallelSort(T * input, int length)
	{
		if (input != nullptr && length > 1) {
			ParallelSort(input, 0, length - 1);
		}
	}

	template<class T> void QuickSort::RandomSort(T * input, int length)
	{
		if (input != nullptr && length > 1) {
			RandomSort(input, 0, length - 1);
		}
	}

	template<class T> T & QuickSort::RandomSelect(T * input, int length, int i)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("Invalid length %d", length));
		if (i < 0 || i >= length) throw invalid_argument(String::Format("Invalid i %d", i));
		return Partition::PartitionArrayByOrder(input, 0, length - 1, i);
	}
}