#include "HeapSort.h"

namespace Test {
	// 2^(H - 1) - 1 < length <= 2^H - 1
	// There are H bits and the pattern is between:
	// 10000 ... 000
	// 11111 ... 111
	unsigned int HeapSort::Height(unsigned int length)
	{
		unsigned int x = length;
		unsigned int h = 0;
		while (x > 0) {
			x = x >> 1;
			h++;
		}

		return h;
	}
}