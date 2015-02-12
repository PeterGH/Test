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
		// Current counter value at position index
		__declspec(dllexport) const unsigned int operator[](unsigned int index) const { return (*_counter)[index]; }
		// maximum number of permutations
		__declspec(dllexport) const unsigned long Max(void) const { return _counter->Max(); }

		// Given a collection of numbers, return all possible permutations. For example,
		// [1,2,3] have the following permutations:
		// [1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].
		template<class T> static vector<vector<T>> All(vector<T> & input);
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

	template<class T> vector<vector<T>> Permutation::All(vector<T> & input)
	{
		if (input.size() == 0) return vector<vector<T>> { };

		// Compute all permutations starting at index i
		function<void(vector<T> &, size_t, vector<vector<T>> &)>
		permute = [&](vector<T> & n, size_t i, vector<vector<T>> & o) {
			if (i == n.size() - 1) {
				o.push_back(n);
				return;
			}
			for (size_t j = i; j < n.size(); j++) {
				vector<T> m(n);
				if (j != i) {
					// Should just swap m[i] and m[j]
					// But we erase and insert, which effectively push m[i] one more positin to the right.
					// This way keeps the lexicographical order
					T t = m[j];
					m.erase(m.begin() + j);
					m.insert(m.begin() + i, t);
				}
				permute(m, i + 1, o);
			}
		};

		vector<vector<T>> output;
		permute(input, 0, output);
		return output;
	}
}

