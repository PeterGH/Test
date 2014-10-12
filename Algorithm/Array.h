#pragma once
#include <deque>
#include <functional>
#include <queue>
#include <stack>
#include <vector>
#include "BinarySearch.h"
#include "BitSet.h"
#include "String.h"

using namespace std;

namespace Test {
	class __declspec(dllexport) Array {
	public:

		// Given an array of stock prices. Buy on one day and sell later. Maximize the profit.
		// Return the indices of buy day and sell day and the profit.
		template<class T> static void BuySellStock(const T * input, int length, int & buy, int & sell, T & profit);
		template<class T> static void BuySellStock2(const T * input, int length, int & buy, int & sell, T & profit);
		// Multiple transactions. But two transactions cannot overlap, i.e., must sell before buy again.
		template<class T> static void BuySellStock(const T * input, int length, vector<int> & buy, vector<int> & sell, vector<T> & profit);
		template<class T> static void BuySellStock2(const T * input, int length, vector<int> & buy, vector<int> & sell, vector<T> & profit);
		// At most two transactions. But two transactions cannot overlap, i.e., must sell before buy again.
		template<class T> static void BuySellStock2Transactions(const T * input, int length, vector<int> & buy, vector<int> & sell, vector<T> & profit);
		template<class T> static void BuySellStock2Transactions2(const T * input, int length, vector<int> & buy, vector<int> & sell, vector<T> & profit);

		// An inversion is a pair (i, j) such that i < j and I[i] > I[j].
		// Find an inversion such that j - i is maximized.
		// Use parameter first to return value i and distance to return value j - i
		template<class T> static void MaxInversionDistance(const T * input, int length, int & first, int & distance);
		template<class T> static void MaxInversionDistance2(const T * input, int length, int & first, int & distance);

		// Slide a window across an input, output the maximum on every move.
		template<class T> static void MaxSlidingWindow(const T * input, int length, int window, vector<T> & output);
		template<class T> static void MaxSlidingWindow2(const T * input, int length, int window, vector<T> & output);

		// Find a subarray of contiguous elements whose sum is maximized
		// If array contains both positive and negative numbers, return the maximum subarray
		// If array contains positive numbers, return entire array A
		// If array contains non-positive numbers, return the maximum number
		// Parameter sum is the summation of the returned subarray
		// Parameters start and end are the start and end indices of the returned subarray
		template<class T> static void MaxSubArray(const T * input, int length, int & start, int & end, T & sum);
		template<class T> static void MaxSubArray2(const T * input, int length, int & start, int & end, T & sum);

		// Find the indices of min and max elements.
		// minIndex will be the index of the minimum value (first index if there are more than on minimum value).
		// maxIndex will be the index of the maximum value (last index if there are more than on maximum value).
		template<class T> static void MinMax(const T * input, const int length, int & minIndex, int & maxIndex);

		// Permute a two dimensional matrix in place. 
		// The permute function takes three parameters: index of the element to permute, number of rows and number of columns,
		// and output the index of the new position of the element.
		template<class T> static void Permute(T * input, const int length, const int columns, function<int(int, int, int)> & permute);

		// Rotate an input array to the left by a distance. The elements rotated out are shifted into the right.
		template<class T> static void RotateLeft(T * input, const int length, int distance);

		// Rotate an input array to the right by a distance. The elements rotated out are shifted into the left.
		template<class T> static void RotateRight(T * input, const int length, int distance);

		// Swap contiguous elements between the first and the second positions.
		template<class T> static void Swap(T * first, T * second, const int count);

		// Swap elements at two positions
		template<class T> static void Swap(T * buffer, unsigned int position1, unsigned int position2);

		// Transpose a two dimensional matrix in place
		template<class T> static void Transpose(T * input, const int length, const int columns);

		// Transpose rows to columns for a two dimensional matrix in place. Not change the dimensions.
		template<class T> static void TransposeRowsToColumns(T * input, const int length, const int columns);
		
		// Transpose columns to rows for a two dimensional matrix in place. Not change the dimensions.
		template<class T> static void TransposeColumnsToRows(T * input, const int length, const int columns);
	};

	// Buy on one day and sell later. Maximize the profit.
	template<class T> void Array::BuySellStock(const T * input, int length, int & buy, int & sell, T & profit)
	{
		int min = 0;
		buy = 0;
		sell = 0;
		profit = 0;
		for (int i = 1; i < length; i++) {
			if (input[i] < input[min]) {
				min = i;
			} else {
				T diff = input[i] - input[min];
				if (diff > profit) {
					buy = min;
					sell = i;
					profit = diff;
				}
			}
		}
	}

	// Buy on one day and sell later. Maximize the profit.
	template<class T> void Array::BuySellStock2(const T * input, int length, int & buy, int & sell, T & profit)
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
				T diff = input[sellCandidates.top()] - input[min];
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
	template<class T> void Array::BuySellStock(const T * input, int length, vector<int> & buy, vector<int> & sell, vector<T> & profit)
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

	// Multiple transactions. But two transactions cannot overlap, i.e., must sell before buy again.
	// However, sell and buy can happen on the same day.
	// Use as less transactions as possible.
	template<class T> void Array::BuySellStock2(const T * input, int length, vector<int> & buy, vector<int> & sell, vector<T> & profit)
	{
		if (input == nullptr || length < 2) return;
		int i = 0;
		int j = 0;
		while (j < length) {
			while (j + 1 < length && input[j+1] >= input[j]) j++;
			if (i < j) {
				// input[i..j] is increasing
				buy.push_back(i);
				sell.push_back(j);
				profit.push_back(input[j] - input[i]);
			}
			i = j + 1;
			j++;
		}
	}

	// At most two transactions. But two transactions cannot overlap, i.e., must sell before buy again.
	// However, sell and buy can happen on the same day.
	template<class T> void Array::BuySellStock2Transactions(const T * input, int length, vector<int> & buy, vector<int> & sell, vector<T> & profit)
	{
		if (input == nullptr || length < 2) return;
		// Find one transaction during input[begin..end]
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
			// Increase i so that [0..i] contains one more increasing subarray
			while (i < length - 1 && input[i+1] <= input[i]) i++;
			if (i == length - 1) break;
			while (i < length - 1 && input[i+1] > input[i]) i++;

			// Find the max transaction before i
			maxProfit(b1, i, b1, s1, p1);

			// Find the max transaction after i
			if (i > b2)	{
				// If i <= b2, then no need to reevaluate because b2/s2 is already maximum after i
				maxProfit(i, length - 1, b2, s2, p2);
			}

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

	template<class T> void Array::BuySellStock2Transactions2(const T * input, int length, vector<int> & buy, vector<int> & sell, vector<T> & profit)
	{
		if (input == nullptr || length < 2) return;
		int buy1 = 0;
		int sell1 = 0;
		int buy2 = 0;
		int sell2 = 0;
		int buym = 0;
		int sellm = 0;
		int i = 0;
		int j = 0;
		while (j < length) {
			while (j + 1 < length && input[j] >= input[j+1]) j++;
			if (i < sell2 || input[i] >= input[j]) {
				// i is the minimal between sell2 and j
				i = j;
			}
			while (j + 1 < length && input[j] < input[j+1]) j++;
			if (i == j) {
				j++;
				continue;
			}
			// now input[i..j] is increasing
			if (buy1 == sell1) {
				// Get the first two increasing ranges
				buy1 = buy2;
				sell1 = sell2;
				buy2 = i;
				sell2 = j;
			} else {
				// Given [buy1, sell1], [buy2, sell2] and [i, j]
				// Compute new [buy1, sell1] and [buy2, sell2]
				// Need to compare following cases:
				// 1. [buy1, sell1], [buy2, sell2]
				// 2. [buy1, sell1], [buy2, j]
				// 3. [buy1, sell1], [i, j]
				// 4. [buy2, sell2], [i, j]
				// 5. [buy1, sell2], [i, j]
				int b1 = buy1;
				int s1 = sell1;
				int b2 = buy2;
				int s2 = sell2;
				if (input[j] > input[s2]) {
					// Covered case 1 and 2
					s2 = j;
				}
				if (input[j] - input[i] + input[sellm] - input[buym] >
					input[s2] - input[b2] + input[s1] - input[b1]) {
					// Covered case 3, 4 and 5
					b1 = buym;
					s1 = sellm;
					b2 = i;
					s2 = j;
				}
				buy1 = b1;
				sell1 = s1;
				buy2 = b2;
				sell2 = s2;
			}
			if (input[sell1] - input[buy1] > input[sellm] - input[buym]) {
				buym = buy1;
				sellm = sell1;
			}
			if (input[sell2] - input[buy2] > input[sellm] - input[buym]) {
				buym = buy2;
				sellm = sell2;
			}
			if (input[sell2] - input[buy1] > input[sellm] - input[buym]) {
				buym = buy1;
				sellm = sell2;
			}
			j++;
		}
		if (input[sellm] - input[buym] >= input[sell2] - input[buy2] + input[sell1] - input[buy1]) {
			buy.push_back(buym);
			sell.push_back(sellm);
			profit.push_back(input[sellm] - input[buym]);
		} else {
			buy.push_back(buy1);
			sell.push_back(sell1);
			profit.push_back(input[sell1] - input[buy1]);
			buy.push_back(buy2);
			sell.push_back(sell2);
			profit.push_back(input[sell2] - input[buy2]);
		}
	}

	// An inversion is a pair (i, j) such that i < j and I[i] > I[j].
	// Find an inversion such that j - i is maximized.
	// Use parameter first to return value i and distance to return value j - i
	// This is the same as http://leetcode.com/2011/05/a-distance-maximizing-problem.html
	// with only difference is to find an inversion.
	template<class T> void Array::MaxInversionDistance(const T * input, int length, int & first, int & distance)
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

		int prev;
		// Ignore input[0]
		for (int i = length - 1; i > 0; i--) {
			if (i < length - 1 && input[i] >= prev) {
				// if there is an inversion ending at i, then
				// prev would extend it by one more position.
				// So input[i] should be ignored.
				continue;
			}

			prev = input[i];

			while (i <= firstIndices[index]) index--;

			int f =	BinarySearch::FindPositionToInsert<int,int>(
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
	template<class T> void Array::MaxInversionDistance2(const T * input, int length, int & first, int & distance)
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

		int prev;
		// Ignore input[0]
		for (int i = length - 1; i > 0; i--) {
			if (i < length - 1 && input[i] >= prev) {
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
	template<class T> void Array::MaxSlidingWindow(const T * input, int length, int window, vector<T> & output)
	{
		if (input == nullptr) throw invalid_argument("input is a nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));
		if (window <= 0 || window > length) throw invalid_argument(String::Format("window %d is out of range (0, %d]", window, length));

		priority_queue<pair<T, int>> heap;

		for (int i = 0; i < window; i++) {
			heap.push(make_pair(input[i], i));
		}

		output.push_back(heap.top().first);

		for (int i = window; i < length; i++) {
			// The size of heap may be more than the window size.
			// Consider one case where the input contains increasing numbers.
			// But the top of heap is always the max within the current window.

			while (!heap.empty() && heap.top().second <= i - window) {
				heap.pop();
			}

			heap.push(make_pair(input[i], i));
			output.push_back(heap.top().first);
		}
	}

	// http://leetcode.com/2011/01/sliding-window-maximum.html
	// Implement using a deque
	template<class T> void Array::MaxSlidingWindow2(const T * input, int length, int window, vector<T> & output)
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
		// so effectively the queue contains a decreasing sequence between [max, i]
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

	// This is a solution to the buy-sell-stock problem in Introduction to Algorithms
	template<class T> void Array::MaxSubArray(const T * input, int length, int & start, int & end, T & sum)
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
		T c = 0;
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
			if (input[i] >= input[max]) max = i;
		}

		if (sum <= 0) {
			// All elements are zero or negative
			// Return the maximum element
			start = max;
			end = max;
			sum = input[max];
		}
	}

	template<class T> void Array::MaxSubArray2(const T * input, int length, int & start, int & end, T & sum)
	{
		start = -1;
		end = -1;
		sum = INT_MIN;
		if (input == nullptr || length <= 0) return;

		int minIndex = -1;
		int minSum = 0; // sum[0..minIndex]
		int s = 0; // sum[0..i]
		for (int i = 0; i < length; i++) {
			s += input[i];
			if (s - minSum >= sum) {
				start = minIndex + 1;
				end = i;
				sum = s - minSum;
			}
			if (s <= minSum) {
				minSum = s;
				minIndex = i;
			}
		}
	}

	template<class T> void Array::MinMax(const T * input, const int length, int & minIndex, int & maxIndex)
	{
		minIndex = -1;
		maxIndex = -1;
		if (input == nullptr || length <= 0) return;

		int startIndex = 0;
		if (length % 2 == 1) {
			minIndex = 0;
			maxIndex = 0;
			startIndex = 1;
		} else {
			if (input[0] <= input[1]) {
				minIndex = 0;
				maxIndex = 1;
			} else {
				minIndex = 1;
				maxIndex = 0;
			}

			startIndex = 2;
		}

		for (int i = startIndex; i < length; i += 2) {
			if (input[i] <= input[i + 1]) {
				if (input[i] < input[minIndex]) minIndex = i;
				if (input[i + 1] >= input[maxIndex]) maxIndex = i + 1;
			} else {
				if (input[i + 1] < input[minIndex]) minIndex = i + 1;
				if (input[i] >= input[maxIndex]) maxIndex = i;
			}
		}
	}

	template<class T> void Array::Permute(T * input, const int length, const int columns, function<int(int, int, int)> & permute)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is not positive.", length));
		if (columns <= 0) throw invalid_argument(String::Format("columns %d is not positive.", columns));
		if (length % columns > 0) throw invalid_argument(String::Format("length %d is not multiple of columns %d.", length, columns));

		int rows = length / columns;

		BitSet updated(length);

		// ------+------------+--------------
		//       j            k
		//       s            t
		for (int i = 0; i < length; i++) {
			if (updated.Test(i)) continue;
			int j = i;
			T s = input[j];
			int k = permute(j, rows, columns);
			while (k != i) {
				T t = input[k];
				input[k] = s;
				updated.Set(k);
				j = k;
				s = t;
				k = permute(j, rows, columns);
			}

			input[i] = s;
			updated.Set(i);
		}
	}

	template<class T> void Array::RotateLeft(T * input, const int length, int distance)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is not positive", length));
		if (distance < 0) throw invalid_argument(String::Format("distance %d is negative", distance));
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
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is not positive", length));
		if (distance < 0) throw invalid_argument(String::Format("distance %d is negative", distance));
		distance = distance % length;
		if (distance == 0) return;
		int i = 0;
		int j = length - 1;
		int k = j - distance + 1;
		// input[i..k-1] and input[k..j];
		while (i < k && k <= j) {
			if (k - i < j - k + 1) {
				// Left range is shorter
				// input[i..k-1], input[k..j-(k-i)], input[j-(k-i)+1..j]
				Swap(&input[i], &input[j - (k - i) + 1], k - i);
				j = j - (k - i);
			} else if (k - i > j - k + 1) {
				// Right range is shorter
				// input[i..i+(j-k)], input(i+(j-k)+1..k-1], input[k..j]
				Swap(&input[i], &input[k], j - k + 1);
				i = i + (j - k) + 1;
			} else {
				// Both ranges have the same length
				Swap(&input[i], &input[k], k - i);
				break;
			}
		}
	}

	// Swap two ranges. Expect the two ranges are not overlapping.
	// If the two ranges overlap, swap whatever the values are
	// in the overlapping range without any special treatment.
	template<class T> void Array::Swap(T * first, T * second, const int count)
	{
		if (first == nullptr) throw invalid_argument("first is nullptr");
		if (second == nullptr) throw invalid_argument("second is nullptr");

		T t;
		for (int i = 0; i < count; i++) {
			t = first[i];
			first[i] = second[i];
			second[i] = t;
		}
	}

	template<class T> void Array::Swap(T * buffer, unsigned int position1, unsigned int position2)
	{
		if (position1 != position2) {
			T t = buffer[position1];
			buffer[position1] = buffer[position2];
			buffer[position2] = t;
		}
	}

	// Given an MxN array
	//     (0,0)   (0,1)   (0,2)   ...... (0,M-2)   (0,M-1)   (0,M)   (0,M+1)   ...... (0,N-2)   (0,N-1)
	//     (1,0)   (1,1)   (1,2)   ...... (1,M-2)   (1,M-1)   (1,M)   (1,M+1)   ...... (1,N-2)   (1,N-1)
	//     (2,0)   (2,1)   (2,2)   ...... (2,M-2)   (2,M-1)   (2,M)   (2,M+1)   ...... (2,N-2)   (2,N-1)
	//                             ......
	//                             ......
	//     (M-2,0) (M-2,1) (M-2,2) ...... (M-2,M-2) (M-2,M-1) (M-2,M) (M-2,M+1) ...... (M-2,N-2) (M-2,N-1)
	//     (M-1,0) (M-1,1) (M-1,2) ...... (M-1,M-2) (M-1,M-1) (M-1,M) (M-1,M+1) ...... (M-1,N-2) (M-1,N-1)
	// 
	// Transpose
	//     (0,0)   (1,0)   (2,0)   ...... (M-2,0)   (M-1,0)
	//     (0,1)   (1,1)   (2,1)   ...... (M-2,1)   (M-1,1)
	//     (0,2)   (1,2)   (2,2)   ...... (M-2,2)   (M-1,2)
	//                             ......
	//                             ......
	//     (0,M-2) (1,M-2) (2,M-2) ...... (M-2,M-2) (M-1,M-2)
	//     (0,M-1) (1,M-1) (2,M-1) ...... (M-2,M-1) (M-1,M-1)
	//     (0,M)   (1,M)   (2,M)   ...... (M-2,M)   (M-1,M)
	//     (0,M+1) (1,M+1) (2,M+1) ...... (M-2,M+1) (M-1,M+1)
	//                             ......
	//                             ......
	//     (0,N-2) (1,N-2) (2,N-2) ...... (M-2,N-2) (M-1,N-2)
	//     (0,N-1) (1,N-1) (2,N-1) ...... (M-2,N-1) (M-1,N-1)
	//
	// In-place matrix transposition (http://en.wikipedia.org/wiki/In-place_matrix_transposition)
	// Transpose element (m,n) to (n,m) means the index i = Nm + n is mapped to j = Mn + m. The mapping is
	// actually a permutation:
	// P(i) = MN - 1            if i = MN - 1, or
	//        Mi mod (MN - 1)   if 0 <= i < MN - 1
	// The reason is 
	// P(i) = P(Nm + n) = M(Nm + n) mod (MN - 1) = MNm + Mn mod (MN - 1) = (MN-1)m + m + Mn mod (MN - 1) = Mn + m
	template<class T> void Array::Transpose(T * input, const int length, const int columns)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is not positive.", length));
		if (columns <= 0) throw invalid_argument(String::Format("columns %d is not positive.", columns));
		if (length % columns > 0) throw invalid_argument(String::Format("length %d is not multiple of columns %d.", length, columns));

		int rows = length / columns;

		function<int(int, int, int)> permute = [=](int i, int r, int c)->int {
			int l = r * c;
			if (i == (l - 1)) return i;
			int j = (r * i) % (l - 1);
			return j;
		};

		Permute(input, length, columns, permute);
	}

	// Given an MxN array, where N = kM
	//     (0,0)   (0,1)   (0,2)   ...... (0,M-2)   (0,M-1)   (0,M)   (0,M+1)   ...... (0,N-2)   (0,N-1)
	//     (1,0)   (1,1)   (1,2)   ...... (1,M-2)   (1,M-1)   (1,M)   (1,M+1)   ...... (1,N-2)   (1,N-1)
	//     (2,0)   (2,1)   (2,2)   ...... (2,M-2)   (2,M-1)   (2,M)   (2,M+1)   ...... (2,N-2)   (2,N-1)
	//                             ......
	//                             ......
	//     (M-2,0) (M-2,1) (M-2,2) ...... (M-2,M-2) (M-2,M-1) (M-2,M) (M-2,M+1) ...... (M-2,N-2) (M-2,N-1)
	//     (M-1,0) (M-1,1) (M-1,2) ...... (M-1,M-2) (M-1,M-1) (M-1,M) (M-1,M+1) ...... (M-1,N-2) (M-1,N-1)
	// 
	// Transpose rows to columns
	//     (0,0)   (0,M)    ...... (0,(k-1)M)   (1,0)   (1,M)    ...... (1,(k-1)M)   ...... (M-1,0)   (M-1,M)    ...... (M-1,(k-1)M) 
	//     (0,1)   (0,M+1)  ...... (0,(k-1)M+1) (1,1)   (1,M+1)  ...... (1,(k-1)M+1) ...... (M-1,1)   (M-1,M+1)  ...... (M-1,(k-1)M+1)
	//     (0,2)   (0,M+2)  ...... (0,(k-1)M+2) (1,2)   (1,M+2)  ...... (1,(k-1)M+2) ...... (M-1,2)   (M-1,M+2)  ...... (M-1,(k-1)M+2)
	//                      ......                               ......              ......                      ......
	//                      ......                               ......              ......                      ......
	//     (0,M-2) (0,2M-2) ...... (0,kM-2)     (1,M-2) (1,2M-2) ...... (1,kM-2)     ...... (M-1,M-2) (M-1,2M-2) ...... (M-1,kM-2)
	//     (0,M-1) (0,2M-1) ...... (0,kM-1)     (1,M-1) (1,2M-1) ...... (1,kM-1)     ...... (M-1,M-1) (M-1,2M-1) ...... (M-1,kM-1)
	//
	// Transpose element (m,n) to ((n % M), (km + n/M)) means the index i = Nm + n is mapped to j = (n % M)N + km + n/M
	// The mapping is actually a permutation:
	// 1. It is easy to see 0<= j <= MN-1
	// 2. From i to j is a one-to-one mapping
	//
	// Given an MxN array, where M = kN
	//     (0,0)   (0,1)   (0,2)   ...... (0,N-2)   (0,N-1)
	//     (1,0)   (1,1)   (1,2)   ...... (1,N-2)   (1,N-1)
	//     (2,0)   (2,1)   (2,2)   ...... (2,N-2)   (2,N-1)
	//                             ......
	//                             ......
	//     (N-2,0) (N-2,1) (N-2,2) ...... (N-2,N-2) (N-2,N-1)
	//     (N-1,0) (N-1,1) (N-1,2) ...... (N-1,N-2) (N-1,N-1)
	//                             ......
	//                             ......
	//     (M-2,0) (M-2,1) (M-2,2) ...... (M-2,N-2) (M-2,N-1)
	//     (M-1,0) (M-1,1) (M-1,2) ...... (M-1,N-2) (M-1,N-1)
	// 
	// Transpose rows to columns
	//     (0,0)     (k,0)      ...... ((N-1)k,0)
	//     (0,1)     (k,1)      ...... ((N-1)k,1)
	//     (0,2)     (k,2)      ...... ((N-1)k,2)
	//                          ......
	//     (0,N-2)   (k,N-2)    ...... ((N-1)k,N-2)
	//     (0,N-1)   (k,N-1)    ...... ((N-1)k,N-1)
	//     (1,0)     (k+1,0)    ...... ((N-1)k+1,0)
	//     (1,1)     (k+1,1)    ...... ((N-1)k+1,1)
	//     (1,2)     (k+1,2)    ...... ((N-1)k+1,2)
	//                          ......
	//     (1,N-2)   (k+1,N-2)  ...... ((N-1)k+1,N-2)
	//     (1,N-1)   (k+1,N-1)  ...... ((N-1)k+1,N-1)
	//                          ......
	//                          ......
	//     (k-1,0)   (2k-1,0)   ...... (kN-1,0)
	//     (k-1,1)   (2k-1,1)   ...... (kN-1,1)
	//     (k-1,2)   (2k-1,2)   ...... (kN-1,2)
	//                          ......
	//     (k-1,N-2) (2k-1,N-2) ...... (kN-1,N-2)
	//     (k-1,N-1) (2k-1,N-1) ...... (kN-1,N-1)
	//
	// Transpose element (m,n) to ((m%k)N + n, m/k)) means the index i = Nm + n is mapped to j = (m%k)NN + nN + m/k
	// The mapping is actually a permutation:
	// 1. It is easy to see 0<= j <= MN-1
	// 2. From i to j is a one-to-one mapping
	template<class T> void Array::TransposeRowsToColumns(T * input, const int length, const int columns)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is not positive.", length));
		if (columns <= 0) throw invalid_argument(String::Format("columns %d is not positive.", columns));
		if (length % columns > 0) throw invalid_argument(String::Format("length %d is not multiple of columns %d.", length, columns));

		int rows = length / columns;

		if (columns >= rows && (columns % rows > 0))
			throw invalid_argument(String::Format("columns %d is not multiple of rows %d.", columns, rows));

		if (rows >= columns && (rows % columns > 0))
			throw invalid_argument(String::Format("rows %d is not multiple of columns %d.", rows, columns));

		if (columns > rows) {
			// Transpose element (m,n) to ((n % M), (km + n/M)) means the index i = Nm + n is mapped to j = (n % M)N + km + n/M
			function<int(int, int, int)> permute = [=](int i, int r, int c)->int {
				int m = i / c;
				int n = i % c;
				int j = (n % r) * c + (c / r) * m + n / r;
				return j;
			};

			Permute(input, length, columns, permute);
		} else if (rows > columns) {
			// Transpose element (m,n) to ((m%k)N + n, m/k)) means the index i = Nm + n is mapped to j = (m%k)NN + nN + m/k
			function<int(int, int, int)> permute = [=](int i, int r, int c)->int {
				int m = i / c;
				int n = i % c;
				int k = r / c;
				int j = (m % k) * c * c + n * c + m / k;
				return j;
			};

			Permute(input, length, columns, permute);
		} else {
			Transpose(input, length, columns);
		}
	}

	// Given an MxN array, where N = kM
	//     (0,0)   (0,1)   (0,2)   ...... (0,M-2)   (0,M-1)   (0,M)   (0,M+1)   ...... (0,N-2)   (0,N-1)
	//     (1,0)   (1,1)   (1,2)   ...... (1,M-2)   (1,M-1)   (1,M)   (1,M+1)   ...... (1,N-2)   (1,N-1)
	//     (2,0)   (2,1)   (2,2)   ...... (2,M-2)   (2,M-1)   (2,M)   (2,M+1)   ...... (2,N-2)   (2,N-1)
	//                             ......
	//                             ......
	//     (M-2,0) (M-2,1) (M-2,2) ...... (M-2,M-2) (M-2,M-1) (M-2,M) (M-2,M+1) ...... (M-2,N-2) (M-2,N-1)
	//     (M-1,0) (M-1,1) (M-1,2) ...... (M-1,M-2) (M-1,M-1) (M-1,M) (M-1,M+1) ...... (M-1,N-2) (M-1,N-1)
	// 
	// Transpose columns to rows
	//     (0,0)    (1,0)    ...... (M-1,0)    (0,1)     (1,1)       ...... (M-1,1)      ...... (0,k-1)  (1,k-1)  ...... (M-1,k-1)
	//     (0,k)    (1,k)    ...... (M-1,k)    (0,k+1)   (1,k+1)     ...... (M-1,k+1)    ...... (0,2k-1) (1,2k-1) ...... (M-1,2k-1)
	//                       ......                                  ......              ......                   ......
	//                       ......                                  ......              ......                   ......
	//     (0,kM-M) (1,kM-M) ...... (M-1,kM-M) (0,kM-M+1) (1,kM-M+1) ...... (M-1,kM-M+1) ...... (0,kM-1) (1,kM-1) ...... (M-1,kM-1)
	//
	// Transpose element (m,n) to (n/k, (n%k)M+m) means the index i = Nm + n is mapped to j = (n/k)N + (n%k)M + m
	// The mapping is actually a permutation:
	// 1. It is easy to see 0<= j <= MN-1
	// 2. From i to j is a one-to-one mapping
	//	
	// Given an MxN array, where M = kN
	//     (0,0)   (0,1)   (0,2)   ...... (0,N-2)   (0,N-1)
	//     (1,0)   (1,1)   (1,2)   ...... (1,N-2)   (1,N-1)
	//     (2,0)   (2,1)   (2,2)   ...... (2,N-2)   (2,N-1)
	//                             ......
	//                             ......
	//     (N-2,0) (N-2,1) (N-2,2) ...... (N-2,N-2) (N-2,N-1)
	//     (N-1,0) (N-1,1) (N-1,2) ...... (N-1,N-2) (N-1,N-1)
	//                             ......
	//                             ......
	//     (M-2,0) (M-2,1) (M-2,2) ...... (M-2,N-2) (M-2,N-1)
	//     (M-1,0) (M-1,1) (M-1,2) ...... (M-1,N-2) (M-1,N-1)
	// 
	// Transpose columns to rows
	//     (0,0)        (1,0)          (2,0)          ...... (N-2,0)    (N-1,0)
	//     (N,0)        (N+1,0)        (N+2,0)        ...... (2N-2,0)   (2N-1,0)
	//                                                ......
	//     ((k-1)N,0)   ((k-1)N+1,0)   ((k-1)N+2,0)   ...... (kN-2,0)   (kN-1,0)
	//     (0,1)        (1,1)          (2,1)          ...... (N-2,1)    (N-1,1)
	//     (N,1)        (N+1,1)        (N+2,1)        ...... (2N-2,1)   (2N-1,1)
	//                                                ......
	//     ((k-1)N,1)   ((k-1)N+1,1)   ((k-1)N+2,1)   ...... (kN-2,1)   (kN-1,1)
	//                                                ......
	//                                                ......
	//     (0,M-1)      (1,M-1)        (2,M-1)        ...... (N-2,M-1)  (N-1,M-1)
	//     (N,M-1)      (N+1,M-1)      (N+2,M-1)      ...... (2N-2,M-1) (2N-1,M-1)
	//                                                ......
	//     ((k-1)N,M-1) ((k-1)N+1,M-1) ((k-1)N+2,M-1) ...... (kN-2,M-1) (kN-1,M-1)
	//
	// Transpose element (m,n) to (kn + m/N, m % N)) means the index i = Nm + n is mapped to j = (kn+m/N)N + m%N
	// The mapping is actually a permutation:
	// 1. It is easy to see 0<= j <= MN-1
	// 2. From i to j is a one-to-one mapping
	template<class T> void Array::TransposeColumnsToRows(T * input, const int length, const int columns)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is not positive.", length));
		if (columns <= 0) throw invalid_argument(String::Format("columns %d is not positive.", columns));
		if (length % columns > 0) throw invalid_argument(String::Format("length %d is not multiple of columns %d.", length, columns));

		int rows = length / columns;

		if (columns >= rows && (columns % rows > 0))
			throw invalid_argument(String::Format("columns %d is not multiple of rows %d.", columns, rows));

		if (rows >= columns && (rows % columns > 0))
			throw invalid_argument(String::Format("rows %d is not multiple of columns %d.", rows, columns));

		if (columns > rows) {
			// Transpose element (m,n) to (n/k, (n%k)M+m) means the index i = Nm + n is mapped to j = (n/k)N + (n%k)M + m
			function<int(int, int, int)> permute = [=](int i, int r, int c)->int {
				int m = i / c;
				int n = i % c;
				int k = c / r;
				int j = (n / k) * c + (n % k) * r + m;
				return j;
			};

			Permute(input, length, columns, permute);
		} else if (rows > columns) {
			// Transpose element (m,n) to (kn + m/N, m % N)) means the index i = Nm + n is mapped to j = (kn+m/N)N + m%N
			function<int(int, int, int)> permute = [=](int i, int r, int c)->int {
				int m = i / c;
				int n = i % c;
				int k = r / c;
				int j = (k * n + m / c) * c + m % c;
				return j;
			};

			Permute(input, length, columns, permute);
		} else {
			Transpose(input, length, columns);
		}
	}
}

