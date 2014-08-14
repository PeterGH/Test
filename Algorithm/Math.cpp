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
}