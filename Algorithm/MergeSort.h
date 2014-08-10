#pragma once

#include <ppl.h>
#include "Heap.h"
#include "SingleNode.h"

using namespace concurrency;

namespace Test {
	class _declspec(dllexport) MergeSort {
	public:
		// Assuming input[head..(middle-1)] and input[middle..tail] are already sorted,
		// rearrange input so that input[head..tail] is sorted.
		// In-place and stable.
		template<class T> static void Merge(T * input, int head, int middle, int tail);

		// Assuming input[head..(middle-1)] and input[middle..tail] are already sorted,
		// rearrange elements every step so that input[head..tail] is sorted.
		// In-place and stable.
		template<class T> static void Merge(T * input, int head, int middle, int tail, int step);

		template<class T> static void Merge(SingleNode<T> * & first, SingleNode<T> * second);

		// An inversion is a pair {input[i], input[j]} such that input[i] > input[j] when i < j.
		// We can extend the concept to two sub arrays of input, and the set of inversions
		// contains every inversion whose elements each falls into different sub arrays, e.g.,
		// input[i] is in the first sub array while input[j] is in the second.
		// Sorting the two sub arrays separately does not change the count of inversions
		// between the two sub arrays.
		// Assuming input[head..(middle-1)] and input[middle..tail] are already sorted,
		// count inversions between input[head..(middle-1)] and input[middle..tail] by merging 
		// them into a sorted array input[head..tail].
		template<class T> static int CountInversions(T * input, int head, int middle, int tail);

		// Sort input[head..tail] using merge
		template<class T> static void Sort(T * input, int head, int tail);
		template<class T> static void Sort(T * input, int length) { Sort(input, 0, length - 1); }

		template<class T> static void Sort(T * input, int head, int tail, int step);

		template<class T> static void Sort(SingleNode<T> * & list);

		template<class T> static void ParallelSort(T * input, int head, int tail);
		template<class T> static void ParallelSort(T * input, int length) { ParallelSort(input, 0, length - 1); }

		// Count inversions in input[head..tail]
		template<class T> static int CountInversions(T * input, int head, int tail);
		template<class T> static int CountInversions(T * input, int length) { return CountInversions(input, 0, length - 1); }

		// Merg sort multiple sorted sets
		// Each element of inputs points to a sorted array, whose length is in array sizes.
		// The length of inputs is size.
		// The final merged array is output.
		template<class T> static void Sort(T * inputs[], size_t * sizes, size_t size, vector<T> & output);
	};

	template<class T> void MergeSort::Merge(T * input, int head, int middle, int tail)
	{
		if (input == nullptr || head < 0 || middle <= 0 || tail < middle || tail <= head) return;
		// head and middle point to the heads of two sub sorted arrays.
		while (head < middle && middle <= tail) {
			if (input[head] <= input[middle]) {
				head++;
			} else {
				// Should move input[middle] to position head
				T t = input[middle];

				// Shift input[head..(middle-1)] to input[(head+1)..middle]
				for (int i = middle; i > head; i--) {
					input[i] = input[i - 1];
				}

				input[head] = t;

				// Move to the next pair of elements
				head++;
				middle++;
			}
		}
	}

	template<class T> void MergeSort::Merge(T * input, int head, int middle, int tail, int step)
	{
		if (input == nullptr || head < 0 || middle <= 0 || tail < middle || tail <= head || step <= 0) return;
		// head and middle point to the heads of two sub sorted arrays.
		while (head < middle && middle <= tail) {
			if (input[head] <= input[middle]) {
				head += step;
			} else {
				// Should move input[middle] to position head
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
	
	template<class T> void MergeSort::Merge(SingleNode<T> * & first, SingleNode<T> * second)
	{
		if (second == nullptr) return;

		if (first == nullptr) {
			first = second;
			return;
		}

		SingleNode<T> * p;
		if (second->Value() < first->Value()) {
			p = second->Next();
			second->Next() = first;
			first = second;
			second = p;
		}

		// Now first->Value() <= second->Value()

		p = first;
		while (p != nullptr && second != nullptr) {
			while (p->Next() != nullptr && p->Next()->Value() <= second->Value()) {
				p = p->Next();
			}

			// Now p->Value() <= second->Value()

			if (p->Next() == nullptr) {
				// first list is done, append rest of second to first
				p->Next() = second;
				break;
			} else {
				// Insert second between p and p->Next()
				SingleNode<T> * q = second->Next();
				second->Next() = p->Next();
				p->Next() = second;
				p = second;
				second = q;
			}
		}
	}

	template<class T> int MergeSort::CountInversions(T * input, int head, int middle, int tail)
	{
		if (input == nullptr || head < 0 || middle <= 0 || tail < middle || tail <= head) return 0;
		int count = 0;
		// head and middle point to the heads of two sub sorted arrays.
		while (head < middle && middle <= tail) {
			if (input[head] <= input[middle]) {
				head++;
			} else {
				// Should move input[middle] to position head
				T t = input[middle];
				
				// Shift input[head..(middle-1)] to input[(head+1)..middle]
				for (int i = middle; i > head; i--) {
					input[i] = input[i - 1];
				}

				input[head] = t;
				
				// There (middle - head) elements moved.
				// Each of them paired with input[middle] is an inversion.
				count += (middle - head);

				// Move to the next pair of elements
				head++;
				middle++;
			}
		}

		return count;
	}

	template<class T> void MergeSort::Sort(T * input, int head, int tail)
	{
		if (input == nullptr || head < 0 || tail < 0 || tail < head) return;
		if (head < tail) {
			int middle = head + ((tail - head) >> 1) + 1;
			Sort(input, head, middle - 1);
			Sort(input, middle, tail);
			Merge(input, head, middle, tail);
		}
	}

	template<class T> void MergeSort::ParallelSort(T * input, int head, int tail)
	{
		if (input == nullptr || head < 0 || tail < 0 || tail < head) return;
		if (head < tail) {
			int middle = head + ((tail - head) >> 1) + 1;

			// parallel_invoke returns only when two actions finish
			parallel_invoke(
				[&input, head, middle]{ ParallelSort(input, head, middle - 1); },
				[&input, middle, tail]{ ParallelSort(input, middle, tail); }
			);

			// Now two sub arrays are sorted, it is safe to merge
			Merge(input, head, middle, tail);
		}
	}

	template<class T> void MergeSort::Sort(T * input, int head, int tail, int step)
	{
		if (input == nullptr || head < 0 || tail < 0 || tail < head || step <= 0) return;
		if (head < tail) {
			int middle = head + (((tail - head) / step) >> 1) * step + step;
			Sort(input, head, middle - step, step);
			Sort(input, middle, tail, step);
			Merge(input, head, middle, tail, step);			
		}
	}
	
	template<class T> int MergeSort::CountInversions(T * input, int head, int tail)
	{
		if (input == nullptr || head < 0 || tail < 0 || tail < head) return 0;
		int count = 0;
		if (head < tail) {
			int middle = head + ((tail - head) >> 1) + 1;

			// Sort and count inversions in each sub array
			count += CountInversions(input, head, middle - 1);
			count += CountInversions(input, middle, tail);

			// Sort and count inversions between two sub arrays
			count += CountInversions(input, head, middle, tail);
		}

		return count;
	}

	// Merge-sort multiple sorted arrays

	// Contain information to point to an element of a sorted array
	template<class T> class Element	{
	public:
		// Sorted array
		const T * _sorted;
		// Size of array
		const size_t _size;
		// The index of this element in the array
		size_t _index;
		Element(const T * sorted, const size_t size, size_t index) : _sorted(sorted), _size(size), _index(index) {}
	};

	// A comparator betweeb two Element<T> instances
	template<class T> struct Greater : public binary_function<const Element<T> *, const Element<T> *, bool>
	{
		bool operator() (const Element<T> * left, const Element<T> * right) const;
	};

	template<class T> bool Greater<T>::operator() (const Element<T> * left, const Element<T> * right) const
	{
		return left->_sorted[left->_index] > right->_sorted[right->_index];
	}

	// Implementation of merge-sort multiple sorted arrays
	template<class T> void MergeSort::Sort(T * inputs[], size_t * sizes, size_t size, vector<T> & output)
	{
		// A minimum heap
		Heap<Element<T> *, Greater<T>> heap(size);

		for (size_t i = 0; i < size; i++) {
			if (sizes[i] > 0) {
				// Initialize the heap with the first element in each sorted array
				heap.Push(new Element<T>(inputs[i], sizes[i], 0));
			}
		}

		while (heap.Size() > 0) {
			// Extract the minimum element from the heap
			Element<T> * min = heap.Pop();

			// append the minum element into the output vector
			output.push_back(min->_sorted[min->_index]);

			// Move to the next element in the same array
			min->_index++;

			if (min->_index < min->_size) {
				// The array still has elements.
				// Push the next element into the heap.
				heap.Push(min);
			} else {
				// The array has been processed. Discard it.
				delete min;
			}
		}
	}
}