#pragma once
#pragma once
#include <algorithm>
#include <vector>
#include "Array2D.h"
using namespace std;
namespace Test {
	class __declspec(dllexport) CoinSelect {
		static void GetIndices(Array2D<int> & v, int length, vector<int> & indices);
	public:
		CoinSelect();
		~CoinSelect();
		static int MaxSelection(const int * input, int length, vector<int> & indices);
		static int MaxSelection2(const int * input, int length, vector<int> & indices);
	};
}