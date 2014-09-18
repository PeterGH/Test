#include "Array.h"

namespace Test {

	// This is a solution to the buy-sell-stock problem in Introduction to Algorithms
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

	// http://leetcode.com/2010/11/best-time-to-buy-and-sell-stock.html
	// Buy on one day and sell later. Maximize the profit.
	void Array::BuySellStock(const int * input, int length, int & buy, int & sell, int & profit)
	{
		int min = 0;
		buy = 0;
		sell = 0;
		profit = 0;
		for (int i = 1; i < length; i++) {
			if (input[i] < input[min]) {
				min = i;
			} else {
				int diff = input[i] - input[min];
				if (diff > profit) {
					buy = min;
					sell = i;
					profit = diff;
				}
			}
		}
	}

	// http://leetcode.com/2010/11/best-time-to-buy-and-sell-stock.html
	// Buy on one day and sell later. Maximize the profit.
	void Array::BuySellStock2(const int * input, int length, int & buy, int & sell, int & profit)
	{
		buy = 0;
		sell = 0;
		profit = 0;
		stack<int> sellCandidates; // track the increasing values from end to beginning
		sellCandidates.push(length - 1);
		for (int i = length - 2; i > 0; i--) {
			if (input[i] >= input[sellCandidates.top()]) {
				// i is the possible sell date, because
				// other dates later than i have less stock values
				sellCandidates.push(i);
			}
		}
		int min = 0;
		for (int i = 0; i < length - 1; i++) {
			if (i == 0 || input[i] < input[min]) {
				min = i;
				while (min >= sellCandidates.top()) {
					// i may be way later than top candidates
					sellCandidates.pop();
				}
				int diff = input[sellCandidates.top()] - input[min];
				if (diff > profit) {
					buy = min;
					sell = sellCandidates.top();
					profit = diff;
				}
			}
		}
	}

	// Multiple transactions. But two transactions cannot overlap, i.e., must sell before buy again.
	// However, sell and buy can happen on the same day.
	void Array::BuySellStock(const int * input, int length, vector<int> & buy, vector<int> & sell, vector<int> & profit)
	{
		if (input == nullptr || length < 2) return;
		for (int i = 1; i < length; i++) {
			if (input[i] > input[i-1]) {
				buy.push_back(i-1);
				sell.push_back(i);
				profit.push_back(input[i] - input[i-1]);
			}
		}
	}

	// At most two transactions. But two transactions cannot overlap, i.e., must sell before buy again.
	// However, sell and buy can happen on the same day.
	void Array::BuySellStock2(const int * input, int length, vector<int> & buy, vector<int> & sell, vector<int> & profit)
	{
		if (input == nullptr || length < 2) return;
		auto maxProfit = [&](int begin, int end, int & buy, int & sell, int & profit){
			int min = begin;
			buy = begin;
			sell = begin;
			profit = 0;
			if (end == begin) return;
			for (int i = begin + 1; i <= end; i++) {
				if (input[i] < input[min]) {
					min = i;
				} else {
					if (input[i] - input[min] > profit) {
						buy = min;
						sell = i;
						profit = input[i] - input[min];
					}
				}
			}
		};

		int buy1 = 0;
		int sell1 = 0;
		int profit1 = 0;
		int buy2 = 0;
		int sell2 = 0;
		int profit2 = 0;

		int b1 = 0;
		int s1 = 0;
		int p1 = 0;
		int b2 = 0;
		int s2 = 0;
		int p2 = 0;
		int i = 0;
		while (i < length - 1) {
			while (i < length - 1 && input[i+1] <= input[i]) i++;
			if (i == length - 1) break;
			while (i < length - 1 && input[i+1] > input[i]) i++;

			maxProfit(b1, i, b1, s1, p1);

			if (i > b2)	maxProfit(i, length - 1, b2, s2, p2);

			if (p1 + p2 > profit1 + profit2) {
				buy1 = b1;
				sell1 = s1;
				profit1 = p1;
				buy2 = b2;
				sell2 = s2;
				profit2 = p2;
			}

			i++;
		}

		int b3;
		int s3;
		int p3;
		maxProfit(0, length - 1, b3, s3, p3);
		if (p3 > profit1 + profit2) {
			buy.push_back(b3);
			sell.push_back(s3);
			profit.push_back(p3);
		} else {
			buy.push_back(buy1);
			sell.push_back(sell1);
			profit.push_back(profit1);
			buy.push_back(buy2);
			sell.push_back(sell2);
			profit.push_back(profit2);
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