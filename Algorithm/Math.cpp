#include "Math.h"
namespace Test {
	// Convert Excel column number to integer:
	//     A, B, ..., Z,  AA, AB, ..., AZ, BA, BB, ..., ZZ,  AAA, AAB, ...
	//     0, 1, ..., 25, 26, 27, ..., 51, 52, 53, ..., 701, 702, 703, ...
	// If we encode [A-Z] to [1 - 26], then
	//     A, B, ..., Z,  AA, AB, ..., AZ, BA, BB, ..., ZZ,  AAA, AAB, ...
	//     1, 2, ..., 26, 27, 28, ..., 52, 53, 54, ..., 702, 701, 702, ...
	// The output is merely one less.
	// input  I[0..n-1]
	// output I[0] * 26^(n-1) + I[1] * 26^(n-2) + ... + I[i] * 26^(n-1-i) + ... + I[n-2] * 26^1 + I[n-1]
	unsigned long long Math::ExcelDecode(const string & input)
	{
		unsigned long long s = 0;
		for (unsigned int i = 0; i < input.length(); i++) {
			s = s * 26 + (input[i] - 'A' + 1);
		}
		return s - 1;
	}

	// Convert integer tp Excel column number:
	//     0, 1, ..., 25, 26, 27, ..., 51, 52, 53, ..., 701, 702, 703, ...
	//     A, B, ..., Z,  AA, AB, ..., AZ, BA, BB, ..., ZZ,  AAA, AAB, ...
	// If we encode [A-Z] to [1 - 26], then
	//     A, B, ..., Z,  AA, AB, ..., AZ, BA, BB, ..., ZZ,  AAA, AAB, ...
	//     1, 2, ..., 26, 27, 28, ..., 52, 53, 54, ..., 702, 701, 702, ...
	string Math::ExcelEncode(unsigned long long input)
	{
		string code;
		unsigned int r;
		input++;
		while (input > 0) {
			r = input % 26;
			input /= 26;
			if (r == 0) {
				// make sure r is in [1, 26]
				// so if r = 0, then borrow one from next higher position
				input--;
				r = 26;
			}
			char c = r - 1 + 'A';
			code.insert(0, 1, c);
		}
		return code;
	}

	// http://leetcode.com/2010/04/multiplication-of-numbers.html
	// There is an array A[N] of N numbers. You have to compose an array Output[N] such that Output[i]
	// will be equal to multiplication of all the elements of A[N] except A[i]. Solve it without division operator and in O(n).
	// For example Output[0] will be multiplication of A[1] to A[N-1]
	// and Output[1] will be multiplication of A[0] and from A[2] to A[N-1].
	// Example:
	// A: {4, 3, 2, 1, 2}
	// OUTPUT: {12, 16, 24, 48, 24}
	// Let M[i..j] = I[i] * I[i+1] * ... * I[j]
	// I[i]  I[0]      I[1]      I[2]      ...... I[i]        ...... I[n-1]
	// L[i]  1         M[0..0]   M[0..1]   ...... M[0..i-1]   ...... M[0..n-2]
	// R[i]  M[1..n-1] M[2..n-1] M[3..n-1] ...... M[i+1..n-1] ...... 1
	// O[i] = L[i] * R[i]
	void Math::ExclusiveMultiplication(const int * input, int length, long long * output)
	{
		for (int i = 0; i < length; i++) {
			output[i] = 1;
		}
		long long left = 1;
		long long right = 1;
		for (int i = 0; i < length; i++) {
			// At loop i, output[i] = left = multiplication of input[0..i-1]
			// At loop length - 1 - i, output[i] *= right = multiplication of input[i+1..length-1]
			output[i] *= left;
			output[length - 1 - i] *= right;
			left *= input[i];
			right *= input[length - 1 - i];
		}
	}

	// Evaluate the value of an arithmetic expression in Reverse Polish Notation.
	int Math::EvalRPNExpression(vector<string> & tokens)
	{
		if (tokens.size() == 0) throw runtime_error("No token is provided");
		stack<int> args;
		int first;
		int second;
		int s;
		for_each(tokens.begin(), tokens.end(), [&](string & t){
			if (t != "+" && t != "-" && t != "*" && t != "/") {
				if (t.length() == 0) throw runtime_error("Token is empty");
				s = 0;
				bool negative = false;
				if (t[0] == '-') {
					negative = true;
				}
				for (unsigned int i = negative ? 1 : 0; i < t.length(); i++) {
					if (t[i] < '0' || t[i] > '9') throw runtime_error("Token is not an integer");
					s = s * 10 + t[i] - '0';
				}
				if (negative) s = -s;
				args.push(s);
			} else {
				if (args.empty()) throw runtime_error("Not enough tokens");
				second = args.top();
				args.pop();
				if (args.empty()) throw runtime_error("Not enough tokens");
				first = args.top();
				args.pop();
				if (t == "+") {
					s = first + second;
				} else if (t == "-") {
					s = first - second;
				} else if (t == "*") {
					s = first * second;
				} else if (t == "/") {
					if (second == 0) throw runtime_error("Divided by zero");
					s = first / second;
				}
				args.push(s);
			}
		});
		return args.top();
	}

	// An array contain numbers duplicated by three times, except one single number.
	// Find the single number.
	// Count number of bit 1 per position and modulo 3.
	int Math::FindSingleNumber(int input[], int length)
	{
		if (length % 3 != 1) throw invalid_argument("The count of numbers is not 3n+1");

		int n = 0;
		int bits = 8 * sizeof(int);
		for (int i = 0; i < bits; i++) {
			int count = 0;
			for (int j = 0; j < length; j++) {
				count += ((input[j] >> i) & 0x1);
			}
			n |= ((count % 3) << i);
		}

		return n;
	}

	// An array contain numbers duplicated by three times, except one single number.
	// Find the single number.
	// For each position, track the occurrences of bit 1.
	int Math::FindSingleNumber2(int input[], int length)
	{
		if (length % 3 != 1) throw invalid_argument("The count of numbers is not 3n+1");

		int o0 = ~0; // positions that bit 1 occurred 0 or 3 times
		int o1 = 0;  // positions that bit 1 occurred 1 time
		int o2 = 0;  // positions that bit 1 occurred 2 times
		int t = 0;
		for (int i = 0; i < length; i++) {
			t = o2; // keep o2 temporarily to calculate o0 later
			o2 = (o1 & input[i]) | (o2 & ~input[i]); // Update the positions that bit 1 occurred the second time due to input[i], and
			                                         // keep the positions that bit 1 already occurred two times and not affected by input[i]
			o1 = (o0 & input[i]) | (o1 & ~input[i]); // Update the positions that bit 1 occurred the first time due to input[i], and
			                                         // keep the positions that bit 1 already occurred one time and not affected by input[i]
			o0 = (t & input[i]) | (o0 & ~input[i]);  // Update the positions that bit 1 occurred the third time due to input[i], and
			                                         // keep the positions that bit 1 already occurred zero or three times and not affected by input[i]
		}

		return o1;
	}

	// Allocate candies to children with ratings.
	// Each child gets at least one candy.
	// The children with higher rating get more candies than their neighbors.
	int Math::AllocateCandy(int ratings[], int length, int amount[])
	{
		amount[0] = 1;
		for (int i = 1; i < length; i++) {
			if (ratings[i] > ratings[i-1]) {
				if (amount[i-1] <= 1) {
					amount[i] = 2;
				} else {
					amount[i] = amount[i-1] + 1;
				}
			} else if (ratings[i] == ratings[i-1]) {
				amount[i] = amount[i-1];
			} else {
				if (amount[i-1] > 1) {
					amount[i] = 1;
				} else {
					amount[i] = amount[i-1] - 1;
				}
			}
		}

		int delta = 0;

		for (int i = length - 1; i >= 0; i--) {
			if (amount[i] > 1) {
				if (i < length - 1) {
					if (ratings[i] == ratings[i+1]) {
						amount[i] = amount[i+1];
					}
				}
				if (amount[i] <= 1 + delta) {
					amount[i] = 2 + delta;
				}
				delta = 0;
			} else {
				if (delta == 0) {
					delta = 1 - amount[i];
				}
				amount[i] += delta;
			}
		}

		int s = 0;
		for (int i = 0; i < length; i++) {
			s += amount[i];
		}

		return s;
	}

	// Allocate candies to children with ratings.
	// Each child gets at least one candy.
	// The children with higher rating get more candies than their neighbors.
	int Math::AllocateCandy2(int ratings[], int length, int amount[])
	{
		amount[0] = 1;
		for (int i = 1; i < length; i++) {
			if (ratings[i] > ratings[i-1]) {
				if (amount[i-1] == 0)
					amount[i] = 2;
				else
					amount[i] = amount[i-1] + 1;
			} else if (ratings[i] == ratings[i-1])
				amount[i] = amount[i-1];
			else
				amount[i] = 0;
		}

		if (amount[length - 1] == 0)
			amount[length - 1] = 1;

		for (int i = length - 2; i >= 0; i--) {
			if (amount[i] == 0) {
				if (ratings[i] < ratings[i+1])
					amount[i] = 1;
				else if (ratings[i] == ratings[i+1])
					amount[i] = amount[i+1];
				else
					amount[i] = amount[i+1] + 1;
			} else {
				if (ratings[i] > ratings[i+1] && amount[i] <= amount[i+1])
					amount[i] = amount[i+1] + 1;
				else if (ratings[i] == ratings[i+1])
					amount[i] = amount[i+1];
			}
		}

		int s = 0;
		for (int i = 0; i < length; i++) {
			s += amount[i];
		}

		return s;
	}

	// Binary tree branch (root-to-leaf path) represents a number with each node as a digit.
	// Sum all branch numbers.
	// 1____2
	//  |___8
	// 12 + 18 = 30
	unsigned long long Math::BinaryTreeSumBranches(BinaryNode<unsigned int> * node)
	{
		if (node == nullptr) return 0;
		stack<BinaryNode<unsigned int> *> path;
		map<BinaryNode<unsigned int> *, unsigned long long> number;
		unsigned long long sum = 0;
		number[node] = node->Value();
		path.push(node);
		while (!path.empty()) {
			node = path.top();
			path.pop();
			if (node->Left() == nullptr && node->Right() == nullptr) {
				sum += number[node];
			}
			if (node->Right() != nullptr) {
				number[node->Right()] = 10 * number[node] + node->Right()->Value();
				path.push(node->Right());
			}
			if (node->Left() != nullptr) {
				number[node->Left()] = 10 * number[node] + node->Left()->Value();
				path.push(node->Left());
			}
		}
		return sum;
	}

	// In a binary tree find a path where the sum of node values is maximized.
	long long Math::BinaryTreeMaxPathSum(BinaryNode<int> * root, vector<BinaryNode<int> *> & path)
	{
		if (root == nullptr) return 0;

		function<void(BinaryNode<int> *, long long &, vector<BinaryNode<int> *> &, long long &, vector<BinaryNode<int> *> &)>
		search = [&](
			BinaryNode<int> * node,
			long long & currentSum,
			vector<BinaryNode<int> *> & currentPath,
			long long & maxSum,
			vector<BinaryNode<int> *> & maxPath)
		{
			currentSum = 0;
			currentPath.clear();
			maxSum = 0;
			maxPath.clear();
			if (node == nullptr) return;

			if (node->Left() == nullptr && node->Right() == nullptr) {
				currentSum = node->Value();
				currentPath.push_back(node);
				maxSum = node->Value();
				maxPath.push_back(node);
				return;
			}

			long long leftSum;
			vector<BinaryNode<int> *> leftPath;
			long long leftMaxSum;
			vector<BinaryNode<int> *> leftMaxPath;
			search(node->Left(), leftSum, leftPath, leftMaxSum, leftMaxPath);

			long long rightSum;
			vector<BinaryNode<int> *> rightPath;
			long long rightMaxSum;
			vector<BinaryNode<int> *> rightMaxPath;
			search(node->Right(), rightSum, rightPath, rightMaxSum, rightMaxPath);

			if (node->Left() != nullptr && node->Right() == nullptr) {
				maxSum = leftMaxSum;
				maxPath.insert(maxPath.begin(), leftMaxPath.begin(), leftMaxPath.end());

				if (leftSum <= 0) {
					currentSum = node->Value();
					currentPath.push_back(node);

					if (node->Value() > maxSum) {
						maxSum = node->Value();
						maxPath.clear();
						maxPath.push_back(node);
					}
				} else {
					currentSum = leftSum + node->Value();
					currentPath.push_back(node);
					currentPath.insert(currentPath.end(), leftPath.begin(), leftPath.end());

					if (leftSum + node->Value() > maxSum) {
						maxSum = leftSum + node->Value();
						maxPath.clear();
						maxPath.insert(maxPath.end(), leftPath.rbegin(), leftPath.rend());
						maxPath.push_back(node);
					}
				}
			} else if (node->Left() == nullptr && node->Right() != nullptr) {
				maxSum = rightMaxSum;
				maxPath.insert(maxPath.begin(), rightMaxPath.begin(), rightMaxPath.end());

				if (rightSum <= 0) {
					currentSum = node->Value();
					currentPath.push_back(node);

					if (node->Value() > maxSum) {
						maxSum = node->Value();
						maxPath.clear();
						maxPath.push_back(node);
					}
				} else {
					currentSum = node->Value() + rightSum;
					currentPath.push_back(node);
					currentPath.insert(currentPath.end(), rightPath.begin(), rightPath.end());

					if (node->Value() + rightSum > maxSum) {
						maxSum = node->Value() + rightSum;
						maxPath.clear();
						maxPath.push_back(node);
						maxPath.insert(maxPath.end(), rightPath.begin(), rightPath.end());
					}
				}
			} else {
				if (leftMaxSum >= rightMaxSum) {
					maxSum = leftMaxSum;
					maxPath.insert(maxPath.begin(), leftMaxPath.begin(), leftMaxPath.end());
				} else {
					maxSum = rightMaxSum;
					maxPath.insert(maxPath.begin(), rightMaxPath.begin(), rightMaxPath.end());
				}

				if (leftSum <= 0 && rightSum <= 0) {
					currentSum = node->Value();
					currentPath.push_back(node);

					if (node->Value() > maxSum) {
						maxSum = node->Value();
						maxPath.clear();
						maxPath.push_back(node);
					}
				} else if (leftSum > 0 && rightSum <= 0) {
					currentSum = leftSum + node->Value();
					currentPath.push_back(node);
					currentPath.insert(currentPath.end(), leftPath.begin(), leftPath.end());

					if (leftSum + node->Value() > maxSum) {
						maxSum = leftSum + node->Value();
						maxPath.clear();
						maxPath.insert(maxPath.end(), leftPath.rbegin(), leftPath.rend());
						maxPath.push_back(node);
					}
				} else if (leftSum <= 0 && rightSum > 0) {
					currentSum = node->Value() + rightSum;
					currentPath.push_back(node);
					currentPath.insert(currentPath.end(), rightPath.begin(), rightPath.end());

					if (node->Value() + rightSum > maxSum) {
						maxSum = node->Value() + rightSum;
						maxPath.clear();
						maxPath.push_back(node);
						maxPath.insert(maxPath.end(), rightPath.begin(), rightPath.end());
					}
				} else {
					if (leftSum >= rightSum) {
						currentSum = leftSum + node->Value();
						currentPath.push_back(node);
						currentPath.insert(currentPath.end(), leftPath.begin(), leftPath.end());
					} else {
						currentSum = node->Value() + rightSum;
						currentPath.push_back(node);
						currentPath.insert(currentPath.end(), rightPath.begin(), rightPath.end());
					}

					if (leftSum + node->Value() + rightSum > maxSum) {
						maxSum = leftSum + node->Value() + rightSum;
						maxPath.clear();
						maxPath.insert(maxPath.end(), leftPath.rbegin(), leftPath.rend());
						maxPath.push_back(node);
						maxPath.insert(maxPath.end(), rightPath.begin(), rightPath.end());
					}
				}
			}
		};

		long long currentSum;
		vector<BinaryNode<int> *> currentPath;
		long long max;
		search(root, currentSum, currentPath, max, path);
		return max;
	}

	// Find the elements forming the longest contiguous sequence.
	// Given [100, 4, 200, 1, 3, 2], The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
	void Math::LongestConsecutiveSequence(vector<int> & input, int & begin, int & length)
	{
		if (input.size() == 0) {
			length = 0;
			return;
		}

		begin = input[0];
		length = 1;

		// Given a open range (begin, end), track the begin and end using two hash tables.
		unordered_map<int, int> rangeBegin; // (begin, end)
		unordered_map<int, int> rangeEnd;   // (end, begin)
		for_each (input.begin(), input.end(), [&](int i){
			bool foundBegin = rangeBegin.find(i) != rangeBegin.end();
			bool foundEnd = rangeEnd.find(i) != rangeEnd.end();
			if (foundBegin && foundEnd) {
				// merge (i, rangeBegin[i]) with (i, rangeEnd[i])
				if (rangeBegin[i] - rangeEnd[i] - 1 > length) {
					length = rangeBegin[i] - rangeEnd[i] - 1;
					begin = rangeEnd[i] + 1;
				}
				rangeBegin[rangeEnd[i]] = rangeBegin[i];
				rangeEnd[rangeBegin[i]] = rangeEnd[i];
				rangeBegin.erase(i);
				rangeEnd.erase(i);
			} else if (foundBegin) {
				// expand (i, rangeBegin[i]) and (rangeEnd[rangeBegin[i]], i)
				if (rangeBegin[i] - i > length) {
					length = rangeBegin[i] - i;
					begin = i;
				}
				if (rangeBegin.find(i-1) == rangeBegin.end()) {
					rangeBegin[i-1] = rangeBegin[i];
					rangeEnd[rangeBegin[i]] = i-1;
					rangeBegin.erase(i);
				}
			} else if (foundEnd) {
				// expand (rangeBegin[rangeEnd[i]], i) and (i, rangeEnd[i])
				if (i - rangeEnd[i] > length) {
					length = i - rangeEnd[i];
					begin = rangeEnd[i] + 1;
				}
				if (rangeEnd.find(i+1) == rangeEnd.end()) {
					rangeEnd[i+1] = rangeEnd[i];
					rangeBegin[rangeEnd[i]] = i+1;
					rangeEnd.erase(i);
				}
			} else {
				// add new range (i-1, i+1) and (i+1, i-1)
				// the new range may already be covered in existing range, e.g.
				// { 0, 1, 2, 1}, when the second 1 occurrs, a new range (0,2) is added,
				// but the first three numbers already generate range (-1, 3).
				if (1 > length) {
					length = 1;
					begin = i;
				}
				if (rangeBegin.find(i-1) == rangeBegin.end()
					&& rangeEnd.find(i+1) == rangeEnd.end()) {
					rangeBegin[i-1] = i+1;
					rangeEnd[i+1] = i-1;
				}
			}
		});
	}

	// Given a triangle, find the minimum path sum from top to bottom. Each step may move to only adjacent numbers on the row below.
	// For example, given the following triangle
	// [     [2],
	//      [3,4],
	//     [6,5,7],
	//    [4,1,8,3]]
	// The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
	//
	//          0
	//         0 1
	//        0 1 2
	//       0 1 2 3
	//      0 1 2 3 4
	//        ......
	// minSum[i] = e[i] + min { minSum[i-1], minSum[i] }
	int Math::TriangleMinPathSum(vector<vector<int>> & triangle)
	{
		if (triangle.size() == 0) return 0;
		vector<int> sum;
		sum.push_back(triangle[0][0]);
		for (size_t i = 1; i < triangle.size(); i++) {
			vector<int> & row = triangle[i];
			sum.push_back(row[i] + sum[i-1]);
			for (int j = i-1; j > 0; j--) {
				sum[j] = row[j] + std::min(sum[j-1], sum[j]);
			}
			sum[0] = row[0] + sum[0];
		}

		int min = sum[0];
		for (size_t i = 1; i < sum.size(); i++) {
			if (sum[i] < min) {
				min = sum[i];
			}
		}
		return min;
	}
}