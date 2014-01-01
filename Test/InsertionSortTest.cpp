#include "InsertionSortTest.h"

void InsertionSortTest::Init(void)
{
	Add("Sort 1", [&](){
		int I[] = { 1 };
		Test::InsertionSort::Sort<int>(I, 1);
		ASSERT1(I[0] == 1);
	});

	Add("Sort 2", [&](){
		int I[] = { 2, 1 };

		Test::InsertionSort::Sort<int>(I, 2);
		ASSERT1(I[0] == 1);
		ASSERT1(I[1] == 2);

		Test::InsertionSort::Sort<int>(I, 2);
		ASSERT1(I[0] == 1);
		ASSERT1(I[1] == 2);

		I[1] = I[0];
		Test::InsertionSort::Sort<int>(I, 2);
		ASSERT1(I[0] == 1);
		ASSERT1(I[1] == 1);
	});

	Add("Sort 3", [&](){
		int I[] = { 3, 2, 1 };

		Test::InsertionSort::Sort<int>(I, 3);
		ASSERT1(I[0] == 1);
		ASSERT1(I[1] == 2);
		ASSERT1(I[2] == 3);

		Test::InsertionSort::Sort<int>(I, 3);
		ASSERT1(I[0] == 1);
		ASSERT1(I[1] == 2);
		ASSERT1(I[2] == 3);

		I[1] = I[0];
		I[2] = I[0];
		Test::InsertionSort::Sort<int>(I, 3);
		ASSERT1(I[0] == 1);
		ASSERT1(I[1] == 1);
		ASSERT1(I[2] == 1);
	});

	Add("Sort 4", [&](){
		int I[] = { 3, 43, 42, 1, 3, 3556, 7, 34, 8, 8769, 96656532, 1, 445, 35, 64 };
		int L = sizeof(I) / sizeof(I[0]);

		std::vector<int> V;
		for (int i = 0; i < L; i++) {
			V.push_back(I[i]);
		}

		Test::InsertionSort::Sort<int>(I, L);

		std::sort(V.begin(), V.end());

		for (int i = 0; i < L; i++) {
			ASSERT1(V[i] == I[i]);
		}
	});

	Add("Sort 5", [&](){
		int I[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
		int L = sizeof(I) / sizeof(I[0]);

		std::vector<int> V;
		for (int i = 0; i < L; i++) {
			V.push_back(I[i]);
		}

		Test::InsertionSort::Sort<int>(I, L);

		std::sort(V.begin(), V.end());

		for (int i = 0; i < L; i++) {
			ASSERT1(V[i] == I[i]);
		}
	});

	Add("Sort 6", [&](){
		int I[] = { 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2 };
		int L = sizeof(I) / sizeof(I[0]);

		std::vector<int> V;
		for (int i = 0; i < L; i++) {
			V.push_back(I[i]);
		}

		Test::InsertionSort::Sort<int>(I, L);

		std::sort(V.begin(), V.end());

		for (int i = 0; i < L; i++) {
			ASSERT1(V[i] == I[i]);
		}
	});
}