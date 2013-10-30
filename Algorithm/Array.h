#pragma once
#pragma once

#include <functional>
#include "BitSet.h"
#include "String.h"

using namespace std;

namespace Test {
	class __declspec(dllexport) Array {
	public:
		// Transpose a two dimensional matrix in place
		static void Transpose(int * input, const int length, const int columns);
	};
}

