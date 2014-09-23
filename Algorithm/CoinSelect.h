#pragma once
#include <algorithm>
#include <vector>
#include "Matrix.h"
using namespace std;
namespace Test {
	class __declspec(dllexport) CoinSelect {
		static void GetIndices(Matrix<int> & v, int length, vector<int> & indices);
	public:
		CoinSelect();
		~CoinSelect();
		static int MaxSelection(const int * input, int length, vector<int> & indices);
		static int MaxSelection2(const int * input, int length, vector<int> & indices);
	};
}