#pragma once
#include <functional>
#include <ppl.h>
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

		// Merge a[h..(m-1)] and a[m..t], assuming both subarrays are sorted
		function<void(T *, size_t, size_t, size_t)> merge = [&](T * a, size_t h, size_t m, size_t t){
			while (h < m && m <= t) {
				if (a[h] <= a[m]) {
					h++;
				}
				else {
					T e = a[m];
					for (size_t i = m; i > h; i--) {
						a[i] = a[i - 1];
					}
					a[h] = e;
					h++;
					m++;
				}
			}
		};

		function<void(T *, size_t, size_t)> sort = [&](T * a, size_t h, size_t t){
			if (h < t) {
				size_t m = h + ((t - h) >> 1) + 1;
				// parallel_invoke returns only when two actions finish
				parallel_invoke(
					[&sort, &a, h, m]{ sort(a, h, m - 1); },
					[&sort, &a, m, t]{ sort(a, m, t); }
				);
				merge(a, h, m, t);
			}
		};

		sort(input, 0, length - 1);
	}

	template<class T> void Sort::Merge::Sort(T * input, size_t head, size_t tail)
	{
		if (input == nullptr || head + 1 <= tail) return;

		Sort(input + head, tail - head + 1);
	}


}