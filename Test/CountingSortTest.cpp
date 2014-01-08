#include "CountingSortTest.h"

void CountingSortTest::Init(void)
{
	Add("One", [&](){
		int A[] = { 2, 5, 3, 0, 2, 3, 0, 3 };
		int L = sizeof(A) / sizeof(A[0]);
		int B[8];
		Test::CountingSort::Sort(A, L, B);

		Logger().WriteInformation("A:\t%d", A[0]);
		for (int i = 1; i < L; i++) {
			Logger().WriteInformation("\t%d", A[i]);
		}

		Logger().WriteInformation("\n");

		Logger().WriteInformation("B:\t%d", B[0]);
		for (int i = 1; i < L; i++) {
			Logger().WriteInformation("\t%d", B[i]);
			ASSERT1(B[i] >= B[i - 1]);
		}

		Logger().WriteInformation("\n");

		Test::CountingSort::Sort(A, L);

		Logger().WriteInformation("A:\t%d", A[0]);
		for (int i = 1; i < L; i++) {
			Logger().WriteInformation("\t%d", A[i]);
			ASSERT1(A[i] >= A[i - 1]);
		}

		Logger().WriteInformation("\n");
	});

	Add("Two", [&](){
		const int size = 1000;
		int A[size];
		for (int i = 0; i < size; i++) {
			A[i] = Test::Random::Next(-50, 50);
		}

		Test::CountingSort::Sort(A, size);

		Logger().WriteInformation("A:\t%d", A[0]);
		for (int i = 1; i < size; i++) {
			Logger().WriteInformation("\t%d", A[i]);
			ASSERT1(A[i] >= A[i - 1]);
		}

		Logger().WriteInformation("\n");
	});
}