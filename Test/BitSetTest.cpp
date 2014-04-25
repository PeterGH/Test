#include "BitSetTest.h"

void BitSetTest::Init(void)
{
	Add("1-bit", [&]() {
		Test::BitSet m(1);
		bitset<1> b;
		m.Set(0);
		(Logger() << m).WriteInformation("\n");
		b.set(0);
		ASSERT2(m.Test(0), "Bit 0 != 1");
		ASSERT1(m.Test(0) == b.test(0));
		ASSERT2(m.Count() == 1, Test::String::Format("Count = [%d]", m.Count()));
		m.Reset(0);
		(Logger() << m).WriteInformation("\n");
		b.reset(0);
		ASSERT2(!m.Test(0), "Bit 0 != 0");
		ASSERT1(m.Test(0) == b.test(0));
		ASSERT2(m.Count() == 0, Test::String::Format("Count = [%d]", m.Count()));
		m.Set();
		(Logger() << m).WriteInformation("\n");
		b.set();
		ASSERT2(m.Test(0), "Bit 0 != 1");
		ASSERT1(m.Test(0) == b.test(0));
		ASSERT2(m.Count() == 1, Test::String::Format("Count = [%d]", m.Count()));
		m.Reset();
		(Logger() << m).WriteInformation("\n");
		b.reset();
		ASSERT2(!m.Test(0), "Bit 0 != 0");
		ASSERT1(m.Test(0) == b.test(0));
		ASSERT2(m.Count() == 0, Test::String::Format("Count = [%d]", m.Count()));
		m.Flip();
		(Logger() << m).WriteInformation("\n");
		b.flip();
		ASSERT2(m.Test(0), "Bit 0 != 1");
		ASSERT1(m.Test(0) == b.test(0));
		ASSERT2(m.Count() == 1, Test::String::Format("Count = [%d]", m.Count()));
		m.Flip(0);
		(Logger() << m).WriteInformation("\n");
		b.flip(0);
		ASSERT2(!m.Test(0), "Bit 0 != 0");
		ASSERT1(m.Test(0) == b.test(0));
		ASSERT2(m.Count() == 0, Test::String::Format("Count = [%d]", m.Count()));
	});

	Add("32-bit", [&]() {
		Test::BitSet m(32);
		bitset<32> b;
		m.Set(0);
		(Logger() << m).WriteInformation("\n");
		b.set(0);
		ASSERT2(m.Test(0), "Bit 0 != 1");
		ASSERT1(m.Test(0) == b.test(0));
		ASSERT2(m.Count() == 1, Test::String::Format("Count = [%d]", m.Count()));
		m.Set(11);
		(Logger() << m).WriteInformation("\n");
		b.set(11);
		ASSERT2(m.Test(11), "Bit 11 != 1");
		ASSERT1(m.Test(11) == b.test(11));
		ASSERT2(m.Count() == 2, Test::String::Format("Count = [%d]", m.Count()));
		m.Flip(11);
		(Logger() << m).WriteInformation("\n");
		b.flip(11);
		ASSERT2(!m.Test(11), "Bit 11 != 0");
		ASSERT1(m.Test(11) == b.test(11));
		ASSERT2(m.Count() == 1, Test::String::Format("Count = [%d]", m.Count()));
		m.Set(23);
		(Logger() << m).WriteInformation("\n");
		b.set(23);
		ASSERT2(m.Test(23), "Bit 23 != 1");
		ASSERT1(m.Test(23) == b.test(23));
		ASSERT2(m.Count() == 2, Test::String::Format("Count = [%d]", m.Count()));
		m.Set(31);
		(Logger() << m).WriteInformation("\n");
		b.set(31);
		ASSERT2(m.Test(31), "Bit 31 != 1");
		ASSERT1(m.Test(31) == b.test(31));
		ASSERT2(m.Count() == 3, Test::String::Format("Count = [%d]", m.Count()));
		m.Flip(31);
		(Logger() << m).WriteInformation("\n");
		b.flip(31);
		ASSERT2(!m.Test(31), "Bit 31 != 0");
		ASSERT1(m.Test(31) == b.test(31));
		ASSERT2(m.Count() == 2, Test::String::Format("Count = [%d]", m.Count()));
		m.Flip(31);
		(Logger() << m).WriteInformation("\n");
		b.flip(31);
		ASSERT2(m.Test(31), "Bit 31 != 1");
		ASSERT1(m.Test(31) == b.test(31));
		ASSERT2(m.Count() == 3, Test::String::Format("Count = [%d]", m.Count()));
		m.Reset();
		(Logger() << m).WriteInformation("\n");
		b.reset();
		ASSERT2(!m.Any(), "Mask is set");
		ASSERT1(m.Any() == b.any());
		ASSERT2(m.Count() == 0, Test::String::Format("Count = [%d]", m.Count()));
		m.Set();
		(Logger() << m).WriteInformation("\n");
		b.set();
		ASSERT2(m.All(), "Mask is not set");
		ASSERT1(m.All() == b.all());
		ASSERT2(m.Count() == 32, Test::String::Format("Count = [%d]", m.Count()));
		m.Flip();
		(Logger() << m).WriteInformation("\n");
		b.flip();
		ASSERT2(!m.All(), "Mask is not set");
		ASSERT1(m.All() == b.all());
		ASSERT2(m.Count() == 0, Test::String::Format("Count = [%d]", m.Count()));
	});

	Add("40-bit", [&]() {
		Test::BitSet m(40);
		bitset<40> b;
		m.Set(0);
		(Logger() << m).WriteInformation("\n");
		b.set(0);
		ASSERT2(m.Test(0), "Bit 0 != 1");
		ASSERT1(m.Test(0) == b.test(0));
		ASSERT2(m.Count() == 1, Test::String::Format("Count = [%d]", m.Count()));
		m.Set(11);
		(Logger() << m).WriteInformation("\n");
		b.set(11);
		ASSERT2(m.Test(11), "Bit 11 != 1");
		ASSERT1(m.Test(11) == b.test(11));
		ASSERT2(m.Count() == 2, Test::String::Format("Count = [%d]", m.Count())); m.Set(23);
		(Logger() << m).WriteInformation("\n");
		b.set(23);
		ASSERT2(m.Test(23), "Bit 23 != 1");
		ASSERT1(m.Test(23) == b.test(23));
		ASSERT2(m.Count() == 3, Test::String::Format("Count = [%d]", m.Count()));
		m.Set(31);
		(Logger() << m).WriteInformation("\n");
		b.set(31);
		ASSERT2(m.Test(31), "Bit 31 != 1");
		ASSERT1(m.Test(31) == b.test(31));
		ASSERT2(m.Count() == 4, Test::String::Format("Count = [%d]", m.Count()));
		m.Set(32);
		(Logger() << m).WriteInformation("\n");
		b.set(32);
		ASSERT2(m.Test(32), "Bit 32 != 1");
		ASSERT1(m.Test(32) == b.test(32));
		ASSERT2(m.Count() == 5, Test::String::Format("Count = [%d]", m.Count()));
		m.Set(39);
		(Logger() << m).WriteInformation("\n");
		b.set(39);
		ASSERT2(m.Test(39), "Bit 39 != 1");
		ASSERT1(m.Test(39) == b.test(39));
		ASSERT2(m.Count() == 6, Test::String::Format("Count = [%d]", m.Count()));
		m.Flip(39);
		(Logger() << m).WriteInformation("\n");
		b.flip(39);
		ASSERT2(!m.Test(39), "Bit 39 != 0");
		ASSERT1(m.Test(39) == b.test(39));
		ASSERT2(m.Count() == 5, Test::String::Format("Count = [%d]", m.Count()));
		m.Flip();
		(Logger() << m).WriteInformation("\n");
		b.flip();
		ASSERT2(m.Test(39), "Bit 39 != 1");
		ASSERT1(m.Test(39) == b.test(39));
		ASSERT2(m.Count() == 35, Test::String::Format("Count = [%d]", m.Count()));
		m.Reset();
		(Logger() << m).WriteInformation("\n");
		b.reset();
		ASSERT2(!m.Any(), "Mask is set");
		ASSERT1(m.Any() == b.any());
		ASSERT2(m.Count() == 0, Test::String::Format("Count = [%d]", m.Count()));
		m.Set();
		(Logger() << m).WriteInformation("\n");
		b.set();
		ASSERT2(m.All(), "Mask is not set");
		ASSERT1(m.All() == b.all());
		ASSERT2(m.Count() == 40, Test::String::Format("Count = [%d]", m.Count()));
	});

	Add("41-bit", [&]() {
		Test::BitSet m(41);
		bitset<41> b;
		m.Set(0);
		(Logger() << m).WriteInformation("\n");
		b.set(0);
		ASSERT2(m.Test(0), "Bit 0 != 1");
		ASSERT1(m.Test(0) == b.test(0));
		ASSERT2(m.Count() == 1, Test::String::Format("Count = [%d]", m.Count()));
		m.Set(11);
		(Logger() << m).WriteInformation("\n");
		b.set(11);
		ASSERT2(m.Test(11), "Bit 11 != 1");
		ASSERT1(m.Test(11) == b.test(11));
		ASSERT2(m.Count() == 2, Test::String::Format("Count = [%d]", m.Count()));
		m.Set(23);
		(Logger() << m).WriteInformation("\n");
		b.set(23);
		ASSERT2(m.Test(23), "Bit 23 != 1");
		ASSERT1(m.Test(23) == b.test(23));
		ASSERT2(m.Count() == 3, Test::String::Format("Count = [%d]", m.Count()));
		m.Set(31);
		(Logger() << m).WriteInformation("\n");
		b.set(31);
		ASSERT2(m.Test(31), "Bit 31 != 1");
		ASSERT1(m.Test(31) == b.test(31));
		ASSERT2(m.Count() == 4, Test::String::Format("Count = [%d]", m.Count()));
		m.Set(32);
		(Logger() << m).WriteInformation("\n");
		b.set(32);
		ASSERT2(m.Test(32), "Bit 32 != 1");
		ASSERT1(m.Test(32) == b.test(32));
		ASSERT2(m.Count() == 5, Test::String::Format("Count = [%d]", m.Count()));
		m.Set(39);
		(Logger() << m).WriteInformation("\n");
		b.set(39);
		ASSERT2(m.Test(39), "Bit 39 != 1");
		ASSERT1(m.Test(39) == b.test(39));
		ASSERT2(m.Count() == 6, Test::String::Format("Count = [%d]", m.Count()));
		m.Set(40);
		(Logger() << m).WriteInformation("\n");
		b.set(40);
		ASSERT2(m.Test(40), "Bit 40 != 1");
		ASSERT1(m.Test(40) == b.test(40));
		ASSERT2(m.Count() == 7, Test::String::Format("Count = [%d]", m.Count()));
		m.Reset();
		(Logger() << m).WriteInformation("\n");
		b.reset();
		ASSERT2(!m.Any(), "Mask is set");
		ASSERT1(m.Any() == b.any());
		ASSERT2(m.Count() == 0, Test::String::Format("Count = [%d]", m.Count()));
		m.Set();
		(Logger() << m).WriteInformation("\n");
		b.set();
		ASSERT2(m.All(), "Mask is not set");
		ASSERT1(m.All() == b.all());
		ASSERT2(m.Count() == 41, Test::String::Format("Count = [%d]", m.Count()));
	});

	Add("LeftShift", [&](){
		{
			Logger().WriteInformation("\n");
			Test::BitSet m(2);
			m.Set(0);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(m.Test(0));
			ASSERT1(!m.Test(1));

			m.LeftShift(0);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(m.Test(0));
			ASSERT1(!m.Test(1));

			m.LeftShift(1);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(!m.Test(0));
			ASSERT1(m.Test(1));

			m.LeftShift(1);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(!m.Test(0));
			ASSERT1(!m.Test(1));
		}
		{
			Logger().WriteInformation("\n");
			Test::BitSet m(2);
			m.Set();
			(Logger() << m).WriteInformation("\n");
			ASSERT1(m.Test(0));
			ASSERT1(m.Test(1));

			m.LeftShift(0);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(m.Test(0));
			ASSERT1(m.Test(1));

			m.LeftShift(1);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(!m.Test(0));
			ASSERT1(m.Test(1));

			m.LeftShift(1);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(!m.Test(0));
			ASSERT1(!m.Test(1));
		}
		{
			Logger().WriteInformation("\n");
			Test::BitSet m(3);
			m.Set(0);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(m.Test(0));
			ASSERT1(!m.Test(1));
			ASSERT1(!m.Test(2));

			m.LeftShift(0);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(m.Test(0));
			ASSERT1(!m.Test(1));
			ASSERT1(!m.Test(2));

			m.LeftShift(1);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(!m.Test(0));
			ASSERT1(m.Test(1));
			ASSERT1(!m.Test(2));

			m.LeftShift(1);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(!m.Test(0));
			ASSERT1(!m.Test(1));
			ASSERT1(m.Test(2));

			m.LeftShift(1);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(!m.Test(0));
			ASSERT1(!m.Test(1));
			ASSERT1(!m.Test(2));
		}
		{
			Logger().WriteInformation("\n");
			Test::BitSet m(3);
			m.Set();
			(Logger() << m).WriteInformation("\n");
			ASSERT1(m.Test(0));
			ASSERT1(m.Test(1));
			ASSERT1(m.Test(2));

			m.LeftShift(1);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(!m.Test(0));
			ASSERT1(m.Test(1));
			ASSERT1(m.Test(2));

			m.LeftShift(1);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(!m.Test(0));
			ASSERT1(!m.Test(1));
			ASSERT1(m.Test(2));

			m.LeftShift(1);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(!m.Test(0));
			ASSERT1(!m.Test(1));
			ASSERT1(!m.Test(2));
		}
		{
			Logger().WriteInformation("\n");
			Test::BitSet m(3);
			m.Set(0);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(m.Test(0));
			ASSERT1(!m.Test(1));
			ASSERT1(!m.Test(2));

			m.LeftShift(2);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(!m.Test(0));
			ASSERT1(!m.Test(1));
			ASSERT1(m.Test(2));

			m.LeftShift(1);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(!m.Test(0));
			ASSERT1(!m.Test(1));
			ASSERT1(!m.Test(2));
		}
		{
			Logger().WriteInformation("\n");
			Test::BitSet m(3);
			m.Set();
			(Logger() << m).WriteInformation("\n");
			ASSERT1(m.Test(0));
			ASSERT1(m.Test(1));
			ASSERT1(m.Test(2));

			m.LeftShift(2);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(!m.Test(0));
			ASSERT1(!m.Test(1));
			ASSERT1(m.Test(2));

			m.LeftShift(1);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(!m.Test(0));
			ASSERT1(!m.Test(1));
			ASSERT1(!m.Test(2));
		}
		{
			Logger().WriteInformation("\n");
			Test::BitSet m(32);
			m.Set(0);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(m.Test(0));
			for (int i = 1; i < 32; i++) {
				ASSERT1(!m.Test(i));
			}

			m.LeftShift(31);
			(Logger() << m).WriteInformation("\n");
			for (int i = 0; i < 31; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(31));

			m.LeftShift(1);
			(Logger() << m).WriteInformation("\n");
			for (int i = 0; i < 32; i++) {
				ASSERT1(!m.Test(i));
			}
		}
		{
			Logger().WriteInformation("\n");
			Test::BitSet m(32);
			m.Set();
			(Logger() << m).WriteInformation("\n");
			for (int i = 0; i < 32; i++) {
				ASSERT1(m.Test(i));
			}

			m.LeftShift(3);
			ASSERT1(!m.Test(0));
			ASSERT1(!m.Test(1));
			ASSERT1(!m.Test(2));
			(Logger() << m).WriteInformation("\n");
			for (int i = 3; i < 32; i++) {
				ASSERT1(m.Test(i));
			}

			m.LeftShift(10);
			(Logger() << m).WriteInformation("\n");
			for (int i = 0; i < 13; i++) {
				ASSERT1(!m.Test(i));
			}
			for (int i = 13; i < 32; i++) {
				ASSERT1(m.Test(i));
			}
		}
		{
			Logger().WriteInformation("\n");
			Test::BitSet m(32);
			m.Set();
			(Logger() << m).WriteInformation("\n");
			for (int i = 0; i < 32; i++) {
				ASSERT1(m.Test(i));
			}

			m.LeftShift(31);
			(Logger() << m).WriteInformation("\n");
			for (int i = 0; i < 31; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(31));

			m.LeftShift(1);
			(Logger() << m).WriteInformation("\n");
			for (int i = 0; i < 32; i++) {
				ASSERT1(!m.Test(i));
			}
		}
		{
			Logger().WriteInformation("\n");
			Test::BitSet m(33);
			m.Set(0);
			(Logger() << m).WriteInformation("\n");
			ASSERT1(m.Test(0));
			for (int i = 1; i < 33; i++) {
				ASSERT1(!m.Test(i));
			}

			m.LeftShift(32);
			(Logger() << m).WriteInformation("\n");
			for (int i = 0; i < 32; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(32));

			m.LeftShift(1);
			(Logger() << m).WriteInformation("\n");
			for (int i = 0; i < 33; i++) {
				ASSERT1(!m.Test(i));
			}
		}
		{
			Logger().WriteInformation("\n");
			Test::BitSet m(33);
			m.Set();
			(Logger() << m).WriteInformation("\n");
			for (int i = 0; i < 33; i++) {
				ASSERT1(m.Test(i));
			}

			m.LeftShift(20);
			(Logger() << m).WriteInformation("\n");
			for (int i = 0; i < 20; i++) {
				ASSERT1(!m.Test(i));
			}
			for (int i = 20; i < 32; i++) {
				ASSERT1(m.Test(i));
			}

			m.LeftShift(10);
			(Logger() << m).WriteInformation("\n");
			for (int i = 0; i < 30; i++) {
				ASSERT1(!m.Test(i));
			}
			for (int i = 30; i < 32; i++) {
				ASSERT1(m.Test(i));
			}
		}
		{
			Logger().WriteInformation("\n");
			Test::BitSet m(33);
			m.Set();
			(Logger() << m).WriteInformation("\n");
			for (int i = 0; i < 33; i++) {
				ASSERT1(m.Test(i));
			}

			m.LeftShift(32);
			(Logger() << m).WriteInformation("\n");
			for (int i = 0; i < 32; i++) {
				ASSERT1(!m.Test(i));
			}
			ASSERT1(m.Test(32));

			m.LeftShift(1);
			(Logger() << m).WriteInformation("\n");
			for (int i = 0; i < 33; i++) {
				ASSERT1(!m.Test(i));
			}
		}
		{
			Logger().WriteInformation("\n");
			Test::BitSet m(66);
			m.Set();
			(Logger() << m).WriteInformation("\n");
			for (int i = 0; i < 66; i++) {
				ASSERT1(m.Test(i));
			}

			m.LeftShift(33);
			(Logger() << m).WriteInformation("\n");
			for (int i = 0; i < 33; i++) {
				ASSERT1(!m.Test(i));
			}
			for (int i = 33; i < 66; i++) {
				ASSERT1(m.Test(i));
			}

			m.LeftShift(33);
			(Logger() << m).WriteInformation("\n");
			for (int i = 0; i < 66; i++) {
				ASSERT1(!m.Test(i));
			}
		}
	});
}