#include "BitSet.h"

namespace Test {

	ostream & operator<<(ostream & os, const BitSet & bitset)
	{
		if (nullptr != bitset._ints) {
			for (int i = bitset._lenInt - 1; i >= 0; i--) {
				for (int j = 28; j >= 0; j -= 4) {
					os << hex << (0xF & (bitset._ints[i] >> j));
				}
			}
		}

		return os;
	}

	Log & operator<<(Log & log, const BitSet & bitset)
	{
		if (nullptr != bitset._ints) {
			for (int i = bitset._lenInt - 1; i >= 0; i--) {
				for (int j = 28; j >= 0; j -= 4) {
					log.WriteInformation("%X", (0xF & (bitset._ints[i] >> j)));
				}
			}
		}

		return log;
	}
	
	// Assume n = sizeof(int), then the int array represents a bit map like:
	//     | 0 1 ... (n-1) | n (n+1) ... (2n-1) | 2n  ... (3n-1) | 3n ...
	// x = | 0             | 1                  | 2              | 3  ...
	// y = | 0 1 ... (n-1) | 0 1     ... (n-1)  | 0 1 ... (n-1)  | 0  ...
	// position = x*n + y
	void BitSet::Position(int position, int * x, int * y) const
	{
		if (position < 0 || position >= _lenBit) throw invalid_argument(String::Format("Invalid bit position [%d]", position));
		*x = position / IntBits;
		*y = position % IntBits;
	}

	BitSet::BitSet(int maxBits)
	{
		if (maxBits <= 0) throw invalid_argument(String::Format("Invalid argument [%d]", maxBits));
		_lenBit = maxBits;
		_lenInt = _lenBit / IntBits;
		int y = _lenBit % IntBits;
		if (y > 0) _lenInt++;
		_ints = new int[_lenInt];
		memset(_ints, 0, _lenInt * sizeof(int));
	}

	BitSet::BitSet(const BitSet & bitset)
	{
		_lenBit = bitset._lenBit;
		_lenInt = bitset._lenInt;
		_ints = new int[bitset._lenInt];
		memcpy(_ints, bitset._ints, bitset._lenInt * sizeof(int));
	}

	BitSet::~BitSet(void)
	{
		if (nullptr != _ints) {
			delete[] _ints;
			_ints = nullptr;
		}
	}

	bool BitSet::All(void) const
	{
		int y = _lenBit % IntBits;

		for (int i = 0; i < (y == 0 ? _lenInt : _lenInt - 1); i++) {
			if (_ints[i] != 0xFFFFFFFF) return false;
		}

		// Test if the lower y bits of the last integer are all ones
		if (y > 0 && (((0x1 << y) - 1) ^ _ints[_lenInt - 1]) != 0) return false;

		return true;
	}

	bool BitSet::Any(void) const
	{
		int y = _lenBit % IntBits;

		for (int i = 0; i < (y == 0 ? _lenInt : _lenInt - 1); i++) {
			if (_ints[i] != 0) return true;
		}

		// Test if the lower y bits of the last integer are all zeros
		if (y > 0 && ((((0x1 << y) - 1) & _ints[_lenInt - 1]) != 0)) return true;

		return false;
	}

	size_t BitSet::Count(void) const
	{
		size_t count = 0;
		int y = _lenBit % IntBits;
		for (int i = 0; i < (y == 0 ? _lenInt : _lenInt - 1); i++) {
			for (int j = 0; j < IntBits; j++) {
				count += 0x1 & (_ints[i] >> j);
			}
		}

		if (y > 0) {
			for (int i = 0; i < y; i++) {
				count += 0x1 & (_ints[_lenInt - 1] >> i);
			}
		}
		return count;
	}

	void BitSet::Flip(void)
	{
		for (int i = 0; i < _lenInt; i++) {
			_ints[i] ^= 0xFFFFFFFF;
		}

		int y = _lenBit % IntBits;

		// The bits of the last integer have already been flipped.
		// Just reset its higher non-used bits to zero.
		if (y > 0) _ints[_lenInt - 1] &= (0x1 << y) - 1;
	}

	void BitSet::Flip(size_t position)
	{
		int x, y;
		Position(position, &x, &y);
		_ints[x] ^= 0x1 << y;
	}

	void BitSet::Reset(void)
	{
		memset(_ints, 0, _lenInt * sizeof(int));
	}

	void BitSet::Reset(size_t position)
	{
		int x, y;
		Position(position, &x, &y);
		_ints[x] &= ~(0x1 << y);
	}

	void BitSet::Set(void)
	{
		memset(_ints, 0xFF, _lenInt * sizeof(int));
		int y = _lenBit % IntBits;
		
		// The bits of the last integer have already been flipped.
		// Just reset its higher non-used bits to zero.
		if (y > 0) _ints[_lenInt - 1] &= (0x1 << y) - 1;
	}

	void BitSet::Set(size_t position)
	{
		int x, y;
		Position(position, &x, &y);
		_ints[x] |= 0x1 << y;
	}

	bool BitSet::Test(size_t position) const
	{
		int x, y;
		Position(position, &x, &y);
		return 0x1 & (_ints[x] >> y);
	}

	string BitSet::ToString(void)
	{
		ostringstream oss;
		oss << *this;
		return oss.str();
	}
}
