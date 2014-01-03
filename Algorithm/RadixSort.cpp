#include "RadixSort.h"

namespace Test {

	// Assume all the MRInteger instances in the vector have the same bases.
	void RadixSort::Sort(std::vector<MRInteger> & numbers)
	{
		std::function<std::function<bool(const MRInteger &, const MRInteger &)>(int)> compare = [](int radix) {
			std::function<bool(const MRInteger &, const MRInteger &)> c = [=](const MRInteger & left, const MRInteger & right) -> bool {
				return left[radix] < right[radix];
			};

			return c;
		};

		for (unsigned int i = 0; i < numbers.front().Length(); i++) {
			std::function<bool(const MRInteger &, const MRInteger &)> c = compare(i);
			std::stable_sort(numbers.begin(), numbers.end(), c);
		}
	}
}
