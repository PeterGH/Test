#include "Permutation.h"

namespace Test {
	Permutation::Permutation(unsigned int length)
	{
		std::unique_ptr<unsigned int[]> bases(new unsigned int[length]);
		for (unsigned int i = 0; i < length; i++) {
			bases[i] = i + 1;
		}

		_counter = new MRInteger(bases.get(), length);
	}

	Permutation::~Permutation(void)
	{
		delete _counter;
	}
}