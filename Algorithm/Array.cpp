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
		long long c = 0;
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
}