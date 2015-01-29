#pragma once

#include <ppl.h>
#include "Heap.h"
#include "SingleNode.h"

using namespace concurrency;

namespace Test {
	class _declspec(dllexport) MergeSort {
	public:
		template<class T> static void Merge(SingleNode<T> * & first, SingleNode<T> * second);

		template<class T> static void Sort(SingleNode<T> * & list);

		// Merg sort multiple sorted sets
		// Each element of inputs points to a sorted array, whose length is in array sizes.
		// The length of inputs is size.
		// The final merged array is output.
		template<class T> static void Sort(T * inputs[], size_t * sizes, size_t size, vector<T> & output);
	};

	// Merge two sorted single link lists
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

	// Sort a single link list or a circular list
	template<class T> void MergeSort::Sort(SingleNode<T> * & list)
	{
		if (list == nullptr || list->Next() == nullptr || list->Next() == list) return;

		SingleNode<T> * m = list;
		SingleNode<T> * p = list;

		while (p->Next() != nullptr && p->Next() != list
			&& p->Next()->Next() != nullptr && p->Next()->Next() != list) {
			// p visits the (2n-1)-th node.
			p = p->Next()->Next();
			// middle visits the n-th node.
			m = m->Next();
		}

		bool circular = false;
		if (p->Next() == list) {
			circular = true;
			p->Next() = nullptr;
		} else if (p->Next() != nullptr && p->Next()->Next() == list) {
			circular = true;
			p->Next()->Next() = nullptr;
		}

		SingleNode<T> * second = m->Next();
		m->Next() = nullptr;
		Sort(list);
		Sort(second);
		Merge(list, second);

		if (circular) {
			p = list;
			while (p->Next() != nullptr) {
				p = p->Next();
			}
			p->Next() = list;
		}
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