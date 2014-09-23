#include "MatrixTest.h"

void MatrixTest::Init()
{
	Add("Matrix", [&]() {
		Matrix<int> B(3, 4);
		Logger().Print(B);
		B(1, 2) = 101;
		Logger().Print(B, "%d", "\t");
		int v = B(1, 2);
		ASSERT1(101 == v);
		B(2, 3) = 202;
		auto p = [&](Log & l, int & x) { l.WriteInformation("%d", x); };
		Logger().Print<int>(B, p, "\t");
		v = B(2, 3);
		ASSERT1(202 == v);
	});
}