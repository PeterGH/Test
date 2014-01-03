#pragma once
#pragma once

#include <memory>
#include "MRInteger.h"

namespace Test {
	class Permutation {

	private:
		// Keep the permutation state
		MRInteger * _counter;
		template<class T> static void Swap(T * buffer, unsigned int position1, unsigned int position2);
	public:
		__declspec(dllexport) Permutation(unsigned int length);
		__declspec(dllexport) ~Permutation(void);

		// Permutation the buffer.
		template<class T> void Next(T * buffer, int length);
		template<class T> void Next(T * input, T * output, int length);
		template<class T> static void Random(T * buffer, int length);
		template<class T> static void Random(T * input, T * output, int length);
		__declspec(dllexport) const unsigned int operator[](unsigned int index) const { return (*_counter)[index]; }
		// maximum number of permutations
		__declspec(dllexport) const unsigned long Max(void) const { return _counter->Max(); }
	};

	template<class T> void Permutation::Swap(T * buffer, unsigned int position1, unsigned int position2)
	{
		if (position1 != position2) {
			T t = buffer[position1];
			buffer[position1] = buffer[position2];
			buffer[position2] = t;
		}
	}
	
	template<class T> void Permutation::Next(T * buffer, int length)
	{
		int len = min(length, (int)_counter->Length());
		for (int i = len - 1; i >= 0; i--) {
			Swap(buffer, i, i - (*_counter)[i]);
		}

		// Prepare for the next permutation
		(*_counter)++;
	}

	template<class T> void Permutation::Next(T * input, T * output, int length)
	{
		memcpy(output, input, length * sizeof(T));
		Next(output, length);
	}

	template<class T> void Permutation::Random(T * buffer, int length)
	{
		for (int i = length - 1; i >= 0; i--) {
			// The rand function returns a pseudorandom integer in the range 0 (inclusive) to RAND_MAX (32767). 
			// We need r in [0, i]
			int r = Random::Next(i);
			Swap(buffer, i, i - r);
		}
	}

	template<class T> void Permutation::Random(T * input, T * output, int length)
	{
		memcpy(output, input, length * sizeof(T));
		Random(output, length);
	}
}

