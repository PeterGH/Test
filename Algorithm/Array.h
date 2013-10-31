#pragma once

#include <functional>
#include "BitSet.h"
#include "String.h"

using namespace std;

namespace Test {
	class __declspec(dllexport) Array {
	public:

		// Rotate an input array to the left by a distance. The elements rotated out are shifted into the right.
		template<class T> static void RotateLeft(T * input, const int length, int distance);

		// Rotate an input array to the right by a distance. The elements rotated out are shifted into the left.
		template<class T> static void RotateRight(T * input, const int length, int distance);

		// Swap contiguous elements between the first and the second positions.
		template<class T> static void Swap(T * first, T * second, const int count);

		// Transpose a two dimensional matrix in place
		static void Transpose(int * input, const int length, const int columns);
	};

	template<class T> void Array::Swap(T * first, T * second, const int count)
	{
		T t;
		for (int i = 0; i < count; i++) {
			t = first[i];
			first[i] = second[i];
			second[i] = t;
		}
	}

	template<class T> void Array::RotateLeft(T * input, const int length, int distance)
	{
		if (input == nullptr) return;
		if (length <= 0) return;
		if (distance <= 0) return;
		distance = distance % length;
		if (distance == 0) return;

		int i = 0;
		int j = length - 1;
		int k = distance;
		// input[i..k-1] and input[k..j]
		while (i < k && k <= j) {
			if (k - i < j - k + 1) {
				// Left range is shorter
				// input[i..k-1], input[k..j-(k-i)], input[j-(k-i)+1..j]
				Swap(&input[i], &input[j - (k - i) + 1], k - i);
				j = j - (k - i);
			} else if (k - i > j - k + 1) {
				// Right range is shorter
				// input[i..i+(j-k)], input[i+(j-k)+1..k-1], input[k..j]
				Swap(&input[i], &input[k], j - k + 1);
				i = i + (j - k) + 1;
			} else {
				// Both ranges have the same length
				Swap(&input[i], &input[k], k - i);
				break;
			}
		}
	}

	template<class T> void Array::RotateRight(T * input, const int length, int distance)
	{
		if (input == nullptr) return;
		if (length <= 0) return;
		if (distance <= 0) return;
		distance = distance % length;
		if (distance == 0) return;
		RotateLeft(input, length, length - distance);
	}
}

