#include "ColumnSortTest.h"

void ColumnSortTest::Init(void)
{
	Add("Sort", [&](){
		const int rows = 3;
		const int columns = 18;
		const int length = rows * columns;
		int A[length];
		for (int i = 0; i < length; i++) {
			A[i] = length - i;
		}

		Test::RowSort::Sort<int>(A, length, columns);
		ASSERT1(Test::RowSort::IsSorted(A, length, columns));
	});

	Add("Sort rand", [&](){
		srand((unsigned)time(NULL));		
		const int rows = rand() % 100 + 1;
		const int columns = 2 * rows * rows;
		const int length = rows * columns;

		Logger().WriteInformation("%d X %d\n", rows, columns);

		int * A = new int[length];
		
		for (int i = 0; i < length; i++) {
			A[i] = rand();
		}

		int * B = new int[length];
		memcpy_s(B, length * sizeof(int), A, length * sizeof(int));

		long tick = GetTickCount();
		bool sortedA = Test::RowSort::IsSorted(A, length, columns);
		Logger().WriteInformation("Serialized: %ssorted, %d ticks\n", sortedA ? "" : "not ", GetTickCount() - tick);
		tick = GetTickCount();
		Test::RowSort::Sort<int>(A, length, columns);
		Logger().WriteInformation("Serialized: sort took %d ticks\n", GetTickCount() - tick);
		tick = GetTickCount();
		sortedA = Test::RowSort::IsSorted(A, length, columns);	
		Logger().WriteInformation("Serialized: %ssorted, %d ticks\n", sortedA ? "" : "not ", GetTickCount() - tick);

		tick = GetTickCount();
		bool sortedB = Test::RowSort::IsSorted(B, length, columns);
		Logger().WriteInformation("Parallel: %ssorted, %d ticks\n", sortedB ? "" : "not ", GetTickCount() - tick);
		tick = GetTickCount();
		Test::RowSort::ParallelSort<int>(B, length, columns);
		Logger().WriteInformation("Parallel: sort took %d ticks\n", GetTickCount() - tick);
		tick = GetTickCount();
		sortedB = Test::RowSort::IsSorted(B, length, columns);
		Logger().WriteInformation("Parallel: %ssorted, %d ticks\n", sortedB ? "" : "not ", GetTickCount() - tick);

		bool equal = true;
		for (int i = 0; i < length; i++) {
			if (A[i] != B[i]) {
				equal = false;
				break;
			}
		}

		delete[] B;
		delete[] A;

		ASSERT1(sortedA == true);
		ASSERT1(sortedB == true);
		ASSERT1(equal == true);
	});
}