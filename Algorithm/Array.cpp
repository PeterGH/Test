#include "Array.h"

namespace Test {

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

	// http://leetcode.com/2011/01/sliding-window-maximum.html
	// Implement using a heap
	void Array::MaxSlidingWindow(const int * input, int length, int window, vector<int> & output)
	{
		if (input == nullptr) throw invalid_argument("input is a nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));
		if (window <= 0 || window > length) throw invalid_argument(String::Format("window %d is out of range (0, %d]", window, length));

		priority_queue<pair<int, int>> heap;

		for (int i = 0; i < window; i++) {
			heap.push(make_pair(input[i], i));
		}

		output.push_back(heap.top().first);

		for (int i = window; i < length; i++) {
			while (!heap.empty() && heap.top().second <= i - window) {
				heap.pop();
			}

			heap.push(make_pair(input[i], i));
			output.push_back(heap.top().first);
		}
	}

	// http://leetcode.com/2011/01/sliding-window-maximum.html
	// Implement using a deque
	void Array::MaxSlidingWindow2(const int * input, int length, int window, vector<int> & output)
	{
		if (input == nullptr) throw invalid_argument("input is a nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));
		if (window <= 0 || window > length) throw invalid_argument(String::Format("window %d is out of range (0, %d]", window, length));

		deque<int> queue;

		// Establish the baseline:
		// 1. queue contains the latest k elements where k <= window
		// 2. queue is sorted and the maximum is queue.front()
		// 3. queue.back() is the latest element
		// 4. queue.front() is the oldest element
		for (int i = 0; i < window; i++) {
			while (!queue.empty() && input[i] >= input[queue.back()]) {
				queue.pop_back();
			}
			queue.push_back(i);
		}

		output.push_back(input[queue.front()]);

		for (int i = window; i < length; i++) {
			while (!queue.empty() && input[i] >= input[queue.back()]) {
				queue.pop_back();
			}

			while (!queue.empty() && queue.front() <= i - window) {
				queue.pop_front();
			}

			queue.push_back(i);

			output.push_back(input[queue.front()]);
		}
	}
}