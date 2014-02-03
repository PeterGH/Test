#include "Array2DTest.h"

void Array2DTest::Init(void)
{
	Add("Array2D", [&]() {
		Test::Array2D<int> B(3, 4);
		B.Print();
		B(1, 2) = 101;
		B.Print();
		int v = B(1, 2);
		ASSERT1(101 == v);
		B(2, 3) = 202;
		B.Print();
		v = B(2, 3);
		ASSERT1(202 == v);
	});
}