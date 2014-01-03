#pragma once

#include <stdexcept>

using namespace std;

namespace Test {
	// Sort using max heap
	class HeapSort {
	private:
		//         0
		//    1          2
		//  3   4     5     6
		// 7 8 9 10 11 12 13 14
		// Given height H, the number of nodes are in [2^(H - 1), 2^H - 1]
		// The indices of nodes at height H are in [2^(H - 1) - 1, 2^H - 2]
		static unsigned int Parent(unsigned int i) { return (i - 1) >> 1; }
		static unsigned int Left(unsigned int i) { return (i << 1) + 1; }
		static unsigned int Right(unsigned int i) { return (i << 1) + 2; }
		__declspec(dllexport) static unsigned int Height(unsigned int length);
		template<class T> static void Swap(T * input, unsigned int i, unsigned int j);
		// Rearrange [i, length - 1] so that it is a heap. 0 <= i < length
		// The assumption is the subtrees rooted at i are already heapified.
		template<class T> static void Heapify(T * input, unsigned int i, unsigned int length);
	public:
		// Construct the array into a max heap from bottom up
		template<class T> static void Heapify(T * input, unsigned int length);
		template<class T> static void ParallelHeapify(T * input, unsigned int length);
		template<class T> static void Sort(T * input, unsigned int length);
	};

	template<class T> void HeapSort::Swap(T * input, unsigned int i, unsigned int j)
	{
		if (i == j) return;
		T temp = input[i];
		input[i] = input[j];
		input[j] = temp;
	}

	template<class T> void HeapSort::Heapify(T * input, unsigned int i, unsigned length)
	{
		if (i >= length) return;
		unsigned int max = i;
		unsigned int l = Left(i);
		if (l < length && input[l] > input[i]) {
			max = l;
		}

		unsigned int r = Right(i);
		if (r < length && input[r] > input[max]) {
			max = r;
		}

		if (max != i) {
			Swap(input, i, max);
			Heapify(input, max, length);
		}
	}

	template<class T> void HeapSort::Heapify(T * input, unsigned int length)
	{
		if (input == nullptr)  throw invalid_argument("input is nullptr");

		unsigned int height = Height(length);

		// The elements at bottom are indexed in [2^(height - 1) - 1, 2^height - 2]
		// We only need to heapify elements above them
		for (long i = ((1 << (height - 1)) - 2); i >= 0; i--) {
			Heapify(input, (unsigned int)i, length);
		}
	}

	template<class T> void HeapSort::ParallelHeapify(T * input, unsigned int length)
	{
		if (input == nullptr)  throw invalid_argument("input is nullptr");

		unsigned height = Height(length);

		for (long long h = (height - 1); h > 0; h--) {
			// For h, the index is in [((1 << (h-1)) - 1), ((1 << h) - 2)]
			parallel_for(
				unsigned int((1 << (h - 1)) - 1),
				unsigned int((1 << h) - 1),
				[&](unsigned int i) {
					Heapify(input, (unsigned int)i, length);
				}
			);
		}
	}

	template<class T> void HeapSort::Sort(T * input, unsigned int length)
	{
		if (input == nullptr)  throw invalid_argument("input is nullptr");

		// Make a heap
		Heapify(input, length);

		// Sort
		for (long long i = length - 1; i >= 0; i--) {
			// Swap the current maximum value, which is at position 0, to position i.
			// The range [i, length - 1] is sorted.
			Swap(input, 0, (unsigned int)i);
			// Rearrange [0, i - 1] so that it is a heap
			Heapify(input, 0, (unsigned int)i);
		}
	}
}