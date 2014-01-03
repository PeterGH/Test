#pragma once

#include <algorithm>
#include <functional>
#include "MRInteger.h"

namespace Test {
	class RadixSort {
	public:
		__declspec(dllexport) static void Sort(std::vector<MRInteger> & numbers);
	};
}
