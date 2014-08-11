#pragma once

#include "BinarySearch.h"
#include "SingleNode.h"

namespace Test {
	class __declspec(dllexport) InsertionSort {
	public:
		template<class T> static void Sort(T * input, int length);
		template<class T> static void Sort(SingleNode<T> * & list);
		template<class T> static void RecursiveSort(T * input, int length);
	};

	// Insertion sort is in-place, stable.
	template<class T> void InsertionSort::Sort(T * input, int length)
	{
		if (input == nullptr || length <= 0) return;
		for (int i = 1; i < length; i++) {
			// Record the current value to insert into input[0..(i-1)]
			T key = input[i];

			// Shift any values in input[0..(i-1)] greater than the current value,
			// so that the right position for the current value is vacant.
			int j = i - 1;

			// Note the comparison is strict,
			// so the multiple instances of the same value preserve their
			// orignial orders, i.e., the sorting is stable.
			while (j >= 0 && input[j] > key) {
				// Right shift input[j] to input[j+1],
				// so that input[j] is vacant for insertion
				input[j + 1] = input[j];
				j--;
			}

			// Insert the current value
			input[j + 1] = key;
		}
	}

	// Sort a single link list or a circular list
	template<class T> void InsertionSort::Sort(SingleNode<T> * & list)
	{
		if (list == nullptr || list->Next() == nullptr || list->Next() == list) return;

		bool circular = false;
		SingleNode<T> * e = list;
		while (e->Next() != nullptr && e->Next() != list) {
			e = e->Next();
		}
		if (e->Next() == list) circular = true;

		SingleNode<T> * q = list;
		while (q->Next() != nullptr && q->Next() != list) {
			if (q->Next()->Value() < list->Value()) {
				SingleNode<T> * t = q->Next();
				if (circular) {
					if (t->Next() != list) {
						q->Next() = t->Next();
						t->Next() = list;
						e->Next() = t;
					}
				} else {
					q->Next() = t->Next();
					t->Next() = list;
				}
				list = t;
			} else {
				SingleNode<T> * p = list;
				while (p != q && q->Next()->Value() >= p->Next()->Value()) {
					p = p->Next();
				}
				if (p == q) {
					q = q->Next();
				} else {
					SingleNode<T> * t = q->Next();
					q->Next() = t->Next();
					t->Next() = p->Next();
					p->Next() = t;
				}
			}
		}
	}

	// Recursively sort input[0..(length-1)] by insertion
	// Use binary search to find the position to insert an element
	template<class T> void InsertionSort::RecursiveSort(T * input, int length)
	{
		// Invalid input
		if (input == nullptr || length <= 0) return;

		// Only one element. no need to recurse
		if (length == 1) return;

		// Recursively sort input[0..(length-2)]
		RecursiveSort(input, length - 1);

		// Record the current value to insert into input[0..(length-2)]
		T key = input[length - 1];

		// Find the last position after which the current value should be inserted.
		// -1 <= i <= (length-2)
		int i = BinarySearch::FindPositionToInsert<T>(key, input, length - 1, false);

		// Shift input[(i+1)..(length-2)] so that the position (i+1) for the current value is vacant.
		for (int j = length - 2; j > i; j--) {
			input[j + 1] = input[j];
		}

		// Insert the current value
		input[i + 1] = key;
	}
}