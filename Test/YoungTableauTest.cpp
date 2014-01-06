#include "YoungTableauTest.h"

void YoungTableauTest::Init(void)
{
	Add("Test 1", [&]() {
		int A[20];
		for (int i = 0; i < 20; i++) {
			A[i] = 20 - i;
		}

		Test::YoungTableau<int> yt(4, 5);
		yt.SortRows(A, 20);
		Test::Array::Print(Logger(), A, 20, yt.Columns());

		yt.SortColumns(A, 20);
		Test::Array::Print(Logger(), A, 20, yt.Columns());

		ASSERT1(yt.Verify(A, 20));
	});

	Add("Test 2", [&]() {
		int A[20];
		for (int i = 0; i < 20; i++) {
			A[i] = 20 - i;
		}

		Test::YoungTableau<int> yt1(4, 5, A, 20);
		Logger() << yt1;
		ASSERT1(yt1.Verify());

		Test::YoungTableau<int> yt2(4, 5);
		yt2.Init(A, 20);
		Logger() << yt2;
		ASSERT1(yt2.Verify());

		yt2.Create(A, 20);
		Test::Array::Print(Logger(), A, 20, yt2.Columns());
		ASSERT1(yt2.Verify(A, 20));
	});

	Add("Test 3", [&]() {
		int A[20];
		for (int i = 0; i < 20; i++) {
			A[i] = 20 - i;
		}

		Test::YoungTableau<int> yt(5, 4, A, 20);
		Logger() << yt;
		ASSERT1(yt.Verify());
	});

	Add("Test 4", [&]() {
		int A[20];
		for (int i = 0; i < 20; i++) {
			A[i] = 20 - i;
		}

		Test::YoungTableau<int> yt(3, 7);
		yt.Push(A, 20);
		Logger() << yt;
		ASSERT1(yt.Verify());
	});

	Add("Test 5", [&]() {
		int A[20];
		for (int i = 0; i < 20; i++) {
			A[i] = 20 - i;
		}

		Test::YoungTableau<int> yt(7, 3);
		yt.Init(A, 20);
		Logger() << yt;
		ASSERT1(yt.Verify());
	});

	Add("Test 6", [&]() {
		int A[20];
		for (int i = 0; i < 20; i++) {
			A[i] = 20 - i;
		}

		Test::YoungTableau<int> yt(2, 13);
		yt.Init(A, 20);
		Logger() << yt;
		ASSERT1(yt.Verify());
	});

	Add("Test 7", [&]() {
		int A[20];
		for (int i = 0; i < 20; i++) {
			A[i] = 20 - i;
		}

		Test::YoungTableau<int> yt(2, 19);
		yt.Push(A, 20);
		Logger() << yt;
		ASSERT1(yt.Verify());
	});

	Add("Test 8", [&]() {
		int A[20];
		for (int i = 0; i < 20; i++) {
			A[i] = 20 - i;
		}

		Test::YoungTableau<int> yt(1, 20);
		yt.Init(A, 20);
		Logger() << yt;
		ASSERT1(yt.Verify());
	});

	Add("Test 9", [&]() {
		int A[20];
		for (int i = 0; i < 20; i++) {
			A[i] = 20 - i;
		}

		Test::YoungTableau<int> yt(1, 21, A, 20);
		Logger() << yt;
		ASSERT1(yt.Verify());
	});

	Add("Test 10", [&]() {
		int A = 1;

		Test::YoungTableau<int> yt(1, 21);
		yt.Push(&A, 1);
		Logger() << yt;
		ASSERT1(yt.Verify());
	});

	Add("Test 11", [&]() {
		for (int i = 0; i < 100; i++) {
			int lenA = 1 + Test::Random::Next();
			unique_ptr<int[]> A(new int[lenA]);
			
			int lenB = 1 + Test::Random::Next();
			unique_ptr<int[]> B(new int[lenB]);
			
			for (int j = 0; j < lenA; j++) {
				A[j] = Test::Random::Next();
			}

			for (int j = 0; j < lenB; j++) {
				B[j] = Test::Random::Next();
			}
			
			int len = max(500, max(lenA, lenB) >> 3);
			int cols = Test::Random::Next(1, len);
			int rows = Test::Random::Next(1, (len / cols) << 3);

			Logger().WriteInformation("Run %d, tableau %d X %d, , %d elements and then push %d elements\n", i, rows, cols, lenA, lenB);
			Test::YoungTableau<int> yt(rows, cols);
			yt.Push(A.get(), lenA);
			ASSERT1(yt.Verify());
			yt.Push(B.get(), lenB);
			ASSERT1(yt.Verify());
		}
	});

	Add("Test 12", [&]() {
		for (int i = 0; i < 100; i++) {
			int lenA = 1 + Test::Random::Next();
			unique_ptr<int[]> A(new int[lenA]);

			int lenB = 1 + Test::Random::Next();
			unique_ptr<int[]> B(new int[lenB]);

			for (int j = 0; j < lenA; j++) {
				A[j] = Test::Random::Next();
			}

			for (int j = 0; j < lenB; j++) {
				B[j] = Test::Random::Next();
			}

			int len = max(500, max(lenA, lenB) >> 3);
			int cols = Test::Random::Next(1, len);
			int rows = Test::Random::Next(1, (len / cols) << 3);

			Logger().WriteInformation("Run %d, tableau %d X %d, , %d elements and then push %d elements\n", i, rows, cols, lenA, lenB);
			Test::YoungTableau<int> yt(rows, cols);
			yt.Push(A.get(), lenA, false);
			ASSERT1(yt.Verify());
			yt.Push(B.get(), lenB, false);
			ASSERT1(yt.Verify());
		}
	});
}