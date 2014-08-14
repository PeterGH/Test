#pragma once
#include <algorithm>
#include <memory>
#include <stack>
#include <string>
#include <vector>
using namespace std;
namespace Test {
	class Math {
	public:
		Math();
		~Math();

		__declspec(dllexport) static unsigned long long ExcelDecode(const string & input);
		__declspec(dllexport) static string ExcelEncode(unsigned long long input);

		__declspec(dllexport) static int EvalRPNExpression(vector<string> & tokens);

		__declspec(dllexport) static int FindSingleNumber(int input[], int lenth);
		__declspec(dllexport) static int FindSingleNumber2(int input[], int lenth);

		__declspec(dllexport) static int AllocateCandy(int ratings[], int length, int amount[]);
		__declspec(dllexport) static int AllocateCandy2(int ratings[], int length, int amount[]);

		template<class T> __declspec(dllexport) static T GreatestCommonDivisor(T n0, T n1);
	};

	template<class T> T Math::GreatestCommonDivisor(T n0, T n1)
	{
		if (n0 == 0 && n1 == 0) throw invalid_argument("(0, 0) has no greatest common divisor");
		if (n0 < 0) n0 = -n0;
		if (n1 < 0) n1 = -n1;
		if (n0 == 0) return n1;
		if (n1 == 0) return n0;
		if (n1 > n0) swap(n0, n1);
		T r = n0 % n1;
		while (r != 0) {
			n0 = n1;
			n1 = r;
			r = n0 % n1;
		}
		return n1;
	}
}

