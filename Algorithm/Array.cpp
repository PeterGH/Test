#include "Array.h"

namespace Test {

	void Array::MaxSubArray(const int * input, int length, int & start, int & end, long & sum)
	{
		start = -1;
		end = -1;
		sum = 0;

		if (input == nullptr || length <= 0) return;

		// Track the last maximum sum so far
		start = 0;
		end = 0;
		sum = 0;

		// Track the current streak
		// Beginning 
		int l = 0;
		// Cumulative sum up to current element
		long c = 0;
		// The index of the maximum element seen so far
		int max = 0;

		for (int i = 0; i < length; i++) {
			// Add current element
			c += input[i];

			if (c > sum) {
				// Current element is positive,
				// and the current sum is larger than the last one.
				// Update the last seen maximum sum
				start = l;
				end = i;
				sum = c;
			} else if (c <= 0) {
				// Current element is negative
				// and everything cancel out
				// Reset and start from the next element
				l = i + 1;
				c = 0;
			}

			// Record the max element so far
			if (input[i] > input[max]) max = i;
		}

		if (sum <= 0) {
			// All elements are zero or negative
			// Return the maximum element
			start = max;
			end = max;
			sum = input[max];
		}
	}

	// An inversion is a pair (i, j) such that i < j and I[i] > I[j].
	// Find an inversion such that j - i is maximized.
	// Use parameter first to return value i and distance to return value j - i
	// This is the same as http://leetcode.com/2011/05/a-distance-maximizing-problem.html
	// with only difference is to find an inversion.
	void Array::MaxInversionDistance(const int * input, int length, int & first, int & distance)
	{
		first = 0;
		distance = 0;
		if (input == nullptr || length <= 1) return;

		// Array firstIndices to contain the indices of a increasing subsequence of input
		// Each element of firstIndices is a candidate for the first index of maximum inversion
		//       firstIndices[0]  <       firstIndices[1]  <       firstIndices[2]  < ...
		// input[firstIndices[0]] < input[firstIndices[1]] < input[firstIndices[2]] < ...
		unique_ptr<int[]> firstIndices(new int[length]);
		int index = 0;
		firstIndices[index] = 0;
		// Ignore input[length - 1]
		for (int i = 1; i < length - 1; i++) {
			if (input[i] > input[firstIndices[index]]) {
				index++;
				firstIndices[index] = i;
			}
		}

		int prev = INT_MAX;
		// Ignore input[0]
		for (int i = length - 1; i > 0; i--) {
			if (input[i] >= prev) {
				// if there is an inversion ending at i, then
				// prev would extend it by one more position.
				// So input[i] should be ignored.
				continue;
			}

			prev = input[i];

			while (i <= firstIndices[index]) index--;

			int f =
				BinarySearch::FindPositionToInsert<int,int>(
				i,
				firstIndices.get(),
				index+1,
				false,
				[&](int i) -> int { return input[i]; });

			if (f == index) {
				// input[i] is equal or greater than all elements referenced by firstIndices
				continue;
			}

			// firstIndices[f] < firstIndices[f + 1] < i
			// input[firstIndices[f]] <= input[i] < input[firstIndices[f+1]]
			int d = i - firstIndices[f + 1];
			if (d > distance) {
				distance = d;
				first = firstIndices[f + 1];
			}
		}
	}

	// An inversion is a pair (i, j) such that i < j and I[i] > I[j].
	// Find an inversion such that j - i is maximized.
	// Use parameter first to return value i and distance to return value j - i
	// This is the same as http://leetcode.com/2011/05/a-distance-maximizing-problem.html
	// with only difference is to find an inversion.
	void Array::MaxInversionDistance2(const int * input, int length, int & first, int & distance)
	{
		first = 0;
		distance = 0;
		if (input == nullptr || length <= 1) return;

		// Array firstIndices to contain the indices of a increasing subsequence of input
		// Each element of firstIndices is a candidate for the first index of maximum inversion
		//       firstIndices[0]  <       firstIndices[1]  <       firstIndices[2]  < ...
		// input[firstIndices[0]] < input[firstIndices[1]] < input[firstIndices[2]] < ...
		unique_ptr<int[]> firstIndices(new int[length]);
		int index = 0;
		firstIndices[index] = 0;
		// Ignore input[length - 1]
		for (int i = 1; i < length - 1; i++) {
			if (input[i] > input[firstIndices[index]]) {
				index++;
				firstIndices[index] = i;
			}
		}

		int prev = INT_MAX;
		// Ignore input[0]
		for (int i = length - 1; i > 0; i--) {
			if (input[i] >= prev) {
				// if there is an inversion ending at i, then
				// prev would extend it by one more position.
				// So input[i] should be ignored.
				continue;
			}

			prev = input[i];

			while (i <= firstIndices[index]) index--;

			if (prev >= input[firstIndices[index]]) {
				// prev is greater than all possible first indices
				continue;
			}

			while (index > 0 && input[firstIndices[index-1]] > prev) {
				index--;
			}

			// Now firstIndices[index] is the first element greater than input[i]
			int d = i - firstIndices[index];
			if (d > distance) {
				first = firstIndices[index];
				distance = i - first;
			}

			if (index == 0) {
				// All elements of firstIndices are examined
				break;
			}
		}
	}
}