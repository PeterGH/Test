#include "CountTest.h"

void CountTest::Init()
{
	Add("Inversions", [&](){
		auto check = [&](int * A, int L, int expected) -> void {
			int count = Test::Count::Inversions<int>(A, L);
			ASSERT1(expected == count);
		};

		int I1[] = { 0 };
		check(I1, 1, 0);

		int I2[] = { 0, 1 };
		check(I2, 2, 0);

		int I3[] = { 1, 0 };
		check(I3, 2, 1);

		int I4[] = { 0, 1, 2 };
		check(I4, 3, 0);

		int I5[] = { 1, 0, 2 };
		check(I5, 3, 1);

		int I6[] = { 2, 0, 1 };
		check(I6, 3, 2);

		int I7[] = { 2, 1, 0 };
		check(I7, 3, 3);

		int I8[] = { 0, 2, 1 };
		check(I8, 3, 1);

		int I9[] = { 1, 2, 0 };
		check(I9, 3, 2);

		int I10[] = { 3, 2, 1, 0 };
		check(I10, 4, 6);

		int I11[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
		int L = sizeof(I11) / sizeof(I11[0]);
		check(I11, L, 45);
	});
}