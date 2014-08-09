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
}