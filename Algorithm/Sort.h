#pragma once
#include <cmath>
#include <functional>
#include <ppl.h>
#include "Array.h"
#include "Math.h"
#include "Search.h"
using namespace concurrency;
using namespace std;
namespace Test {
	class Sort {
	public:
		class Insert {
		public:
			template<class T> static void Sort(T * input, size_t length, function<bool(T &, T &)> compare);
			template<class T> static void Sort(T * input, size_t length);
			template<class T> static void SortRecursively(T * input, size_t length);
		};

		class Select {
		public:
			template<class T> static void Sort(T * input, size_t length, function<bool(T &, T &)> compare);
			template<class T> static void Sort(T * input, size_t length);
		};

		class Merge {
		public:
			template<class T> static void Sort(T * input, size_t length);
			template<class T> static void Sort(T * input, size_t head, size_t tail);
			template<class T> static void Sort(T * input, size_t head, size_t tail, size_t step);
		};

		class Heap {
		public:
			// Rearrange [i, length - 1] so that it is a heap. 0 <= i < length
			// The assumption is the subtrees rooted at i are already heapified.
			template<class T> static void HeapifyElement(T * input, unsigned int i, unsigned int length);
			// Construct the array into a max heap from bottom up
			template<class T> static void Heapify(T * input, unsigned int length);
			template<class T> static void ParallelHeapify(T * input, unsigned int length);
			template<class T> static void Sort(T * input, unsigned int length);

			// Rearrange [i, length - 1] so that it is a heap. 0 <= i < length
			// The assumption is the subtrees rooted at i are already heapified.
			template<class T> static void HeapifyElement(T * input, unsigned int i, unsigned int length, unsigned int d);
			// Construct the array into a max d-ary heap from bottom up
			template<class T> static void Heapify(T * input, unsigned int length, unsigned int d);
			template<class T> static void ParallelHeapify(T * input, unsigned int length, unsigned int d);
			template<class T> static void Sort(T * input, unsigned int length, unsigned int d);
		};

		class Util {
		public:
			// Assuming input[head..(middle-1)] and input[middle..tail] are already sorted,
			// rearrange elements every step so that input[head..tail] is sorted.
			// In-place and stable.
			template<class T> static void Merge(T * input, int head, int middle, int tail, int step = 1);
		};
	};

	template<class T> void Sort::Insert::Sort(T * input, size_t length, function<bool(T &, T &)> compare)
	{
		if (input == nullptr || length <= 1) return;
		for (size_t i = 1; i < length; i++) {
			// Record the current key value to insert into input[0..(i-1)]
			T key = input[i];
			int j = i - 1;
			// Shift any values in input[0..(i-1)] greater than the current key to the right,
			// so that the insert position for the current key is vacant.
			while (j >= 0 && compare(input[j], key)) {
				input[j + 1] = input[j];
				j--;
			}
			input[j + 1] = key;
		}
	}

	template<class T> void Sort::Insert::Sort(T * input, size_t length)
	{
		// Note the comparison is strict,
		// so the multiple instances of the same value preserve their
		// orignial orders, i.e., the sorting is stable.
		Sort<T>(input, length, [](T & x, T & y)->bool{ return x > y; });
	}

	// Recursively sort input[0..(length-1)] by insertion
	// Use binary search to find the position to insert an element
	template<class T> void Sort::Insert::SortRecursively(T * input, size_t length)
	{
		if (input == nullptr || length <= 1) return;

		// Recursively sort input[0..(length-2)]
		SortRecursively(input, length - 1);

		// Record the current value to insert into input[0..(length-2)]
		T key = input[length - 1];

		// Find the last position after which the current value should be inserted.
		// -1 <= i <= (length-2)
		int i = Search::FindPositionToInsert<T>(key, input, length - 1, false);

		// Shift input[(i+1)..(length-2)] so that the position (i+1) for the current value is vacant.
		for (int j = length - 2; j > i; j--) {
			input[j + 1] = input[j];
		}

		// Insert the current value
		input[i + 1] = key;
	}

	template<class T> void Sort::Select::Sort(T * input, size_t length, function<bool(T &, T &)> compare)
	{
		if (input == nullptr || length <= 1) return;
		for (size_t i = 0; i < length - 1; i++) {
			T min = i;
			for (size_t j = i + 1; j < length; j++) {
				if (compare(input[min], input[j])) {
					min = j;
				}
			}
			swap(input[i], input[min]);
		}
	}

	template<class T> void Sort::Select::Sort(T * input, size_t length)
	{
		// Note the comparison is strict,
		// so the multiple instances of the same value preserve their
		// orignial orders, i.e., the sorting is stable.
		Sort<T>(input, length, [](T & x, T & y)->bool{ return x > y; });
	}

	template<class T> void Sort::Merge::Sort(T * input, size_t length)
	{
		if (input == nullptr || length <= 1) return;

		function<void(T *, size_t, size_t)> sort = [&](T * a, size_t h, size_t t){
			if (h < t) {
				size_t m = h + ((t - h) >> 1) + 1;
				// parallel_invoke returns only when two actions finish
				parallel_invoke(
					[&sort, &a, h, m]{ sort(a, h, m - 1); },
					[&sort, &a, m, t]{ sort(a, m, t); }
				);
				Util::Merge(a, h, m, t);
			}
		};

		sort(input, 0, length - 1);
	}

	template<class T> void Sort::Merge::Sort(T * input, size_t head, size_t tail)
	{
		if (input == nullptr || head >= tail) return;

		Sort(input + head, tail - head + 1);
	}

	template<class T> void Sort::Merge::Sort(T * input, size_t head, size_t tail, size_t step)
	{
		if (input == nullptr || head < 0 || tail < 0 || tail < head || step <= 0) return;
		if (head < tail) {
			int middle = head + (((tail - head) / step) >> 1) * step + step;
			parallel_invoke(
				[&input, head, middle, step]{ Sort(input, head, middle - step, step); },
				[&input, middle, tail, step]{ Sort(input, middle, tail, step); }
			);
			Util::Merge(input, head, middle, tail, step);
		}
	}

	template<class T> void Sort::Heap::HeapifyElement(T * input, unsigned int i, unsigned length)
	{
		if (i >= length) return;
		unsigned int max = i;
		unsigned int l = Math::Tree::Left(i);
		if (l < length && input[l] > input[max]) {
			max = l;
		}

		unsigned int r = Math::Tree::Right(i);
		if (r < length && input[r] > input[max]) {
			max = r;
		}

		if (max != i) {
			Array::Swap(input, i, max);
			HeapifyElement(input, max, length);
		}
	}

	template<class T> void Sort::Heap::Heapify(T * input, unsigned int length)
	{
		if (input == nullptr)  throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));

		unsigned int height = Math::Tree::Height(length);

		// The elements at bottom are indexed in [2^(height - 1) - 1, 2^height - 2]
		// We only need to heapify elements above them
		for (long i = ((1 << (height - 1)) - 2); i >= 0; i--) {
			HeapifyElement(input, (unsigned int)i, length);
		}
	}

	template<class T> void Sort::Heap::ParallelHeapify(T * input, unsigned int length)
	{
		if (input == nullptr)  throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));

		unsigned height = Math::Tree::Height(length);

		for (long long h = (height - 1); h > 0; h--) {
			// For h, the index is in [((1 << (h-1)) - 1), ((1 << h) - 2)]
			parallel_for(
				unsigned int((1 << (h - 1)) - 1),
				unsigned int((1 << h) - 1),
				[&](unsigned int i) { HeapifyElement(input, (unsigned int)i, length); }
			);
		}
	}

	template<class T> void Sort::Heap::Sort(T * input, unsigned int length)
	{
		if (input == nullptr)  throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));

		// Make a heap
		Heapify(input, length);

		// Sort
		for (long long i = length - 1; i >= 0; i--) {
			// Swap the current maximum value, which is at position 0, to position i.
			// The range [i, length - 1] is sorted.
			Array::Swap(input, 0, (unsigned int)i);
			// Rearrange [0, i - 1] so that it is a heap
			HeapifyElement(input, 0, (unsigned int)i);
		}
	}

	// Rearrange [i, length - 1] so that it is a heap. 0 <= i < length
	// The assumption is the subtrees rooted at i are already heapified.
	template<class T> void Sort::Heap::HeapifyElement(T * input, unsigned int i, unsigned int length, unsigned int d)
	{
		if (i >= length) return;
		unsigned int max = i;

		for (unsigned int j = 0; j < d; j++) {
			unsigned int c = Math::Tree::Child(i, j, d);
			if (c < length && input[c] > input[max]) {
				max = c;
			}
		}

		if (max != i) {
			Array::Swap(input, i, max);
			HeapifyElement(input, max, length, d);
		}
	}

	template<class T> void Sort::Heap::Heapify(T * input, unsigned int length, unsigned int d)
	{
		if (input == nullptr)  throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));
		if (d <= 1) throw invalid_argument(String::Format("d %d is invalid", d));

		unsigned int height = Math::Tree::Height(length, d);
		long long index = ((long long)pow(d, height - 1) - 1) / (d - 1) - 1;
		for (long long i = index; i >= 0; i--) {
			HeapifyElement(input, (unsigned int)i, length, d);
		}
	}

	template<class T> void Sort::Heap::ParallelHeapify(T * input, unsigned int length, unsigned int d)
	{
		if (input == nullptr)  throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));
		if (d <= 1) throw invalid_argument(String::Format("d %d is invalid", d));

		unsigned int height = Math::Tree::Height(length, d);

		for (long long h = height - 1; h > 0; h--) {
			// For h, the index is in [(d ^ (h - 1) - 1) / (d - 1), (d^h - 1) / (d - 1) - 1]
			parallel_for(
				unsigned int((pow(d, h - 1) - 1) / (d - 1)),
				unsigned int((pow(d, h) - 1) / (d - 1)),
				[&](unsigned int i) { HeapifyElement(input, (unsigned int)i, length, d); }
			);
		}
	}

	template<class T> void Sort::Heap::Sort(T * input, unsigned int length, unsigned int d)
	{
		if (input == nullptr)  throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));
		if (d <= 1) throw invalid_argument(String::Format("d %d is invalid", d));

		// Make A a heap
		Heapify(input, length, d);

		// Sort
		for (long i = length - 1; i >= 0; i--) {
			// Swap the current maximum value, which is at position 0, to position i.
			// The range [i, length - 1] is sorted.
			Array::Swap(input, 0, (unsigned int)i);
			// Rearrange [0, i - 1] so that it is a heap
			HeapifyElement(input, 0, (unsigned int)i, d);
		}
	}

	template<class T> void Sort::Util::Merge(T * input, int head, int middle, int tail, int step)
	{
		if (input == nullptr || head < 0 || middle <= 0 || tail < middle || tail <= head || step <= 0) return;
		// head and middle point to the heads of two sub sorted arrays.
		while (head < middle && middle <= tail) {
			if (input[head] <= input[middle]) {
				head += step;
			} else {
				T t = input[middle];
				// Shift input[head..(middle-step)] to input[(head+step)..middle]
				for (int i = middle; i > head; i -= step) {
					input[i] = input[i - step];
				}
				input[head] = t;
				// Move to the next pair of elements
				head += step;
				middle += step;
			}
		}
	}

}