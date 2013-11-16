#include "PartitionTest.h"

void PartitionTest::Init(void)
{
	Add("Partition Random", [&](){
		int I[] = { 3, 43, 42, 1, 3, 3556, 7, 34, 8, 8769, 96656532, 1, 445, 35, 64 };
		int L = sizeof(I) / sizeof(I[0]);

		int i = Test::Partition::PartitionArray(I, 0, 0);
		ASSERT1(i == 0);

		i = Test::Partition::PartitionArray(I, L - 1, L - 1);
		ASSERT1(i == L - 1);

		i = Test::Partition::PartitionArray(I, 0, 1);
		ASSERT1(i == 1);
		ASSERT1(I[0] == 3);
		ASSERT1(I[1] == 43);

		i = Test::Partition::PartitionArray(I, 2, 3);
		ASSERT1(i == 2);
		ASSERT1(I[2] == 1);
		ASSERT1(I[3] == 42);

		i = Test::Partition::PartitionArray(I, 0, L - 1);
		ASSERT1(i >= 0);
		ASSERT1(i <= L - 1);
		for (int j = 0; j < L - 1; j++) {
			if (j < i) ASSERT1(I[j] <= I[i]);
			else if (j > i) ASSERT1(I[j] >= I[i]);
		}

		i = Test::Partition::PartitionArrayRandomly(I, 0, L - 1);
		ASSERT1(i >= 0);
		ASSERT1(i <= L - 1);
		for (int j = 0; j < L - 1; j++) {
			if (j < i) ASSERT1(I[j] <= I[i]);
			else if (j > i) ASSERT1(I[j] >= I[i]);
		}
	});

	Add("Partition Select", [&](){
		int I[] = { 3, 43, 42, 1, 3, 3556, 7, 34, 8, 8769, 96656532, 1, 445, 35, 64 };
		int L = sizeof(I) / sizeof(I[0]);

		int i = Test::Partition::PartitionArray(I, 0, 0, 0);
		ASSERT1(i == 3);

		i = Test::Partition::PartitionArray(I, L - 1, L - 1, 0);
		ASSERT1(i == 64);

		i = Test::Partition::PartitionArray(I, 0, 1, 0);
		ASSERT1(i == 3);
		ASSERT1(I[0] == 3);
		ASSERT1(I[1] == 43);

		i = Test::Partition::PartitionArray(I, 0, 1, 1);
		ASSERT1(i == 43);
		ASSERT1(I[0] == 3);
		ASSERT1(I[1] == 43);
		
		i = Test::Partition::PartitionArray(I, 2, 3, 0);
		ASSERT1(i == 1);
		ASSERT1(I[2] == 1);
		ASSERT1(I[3] == 42);

		i = Test::Partition::PartitionArray(I, 2, 3, 1);
		ASSERT1(i == 42);
		ASSERT1(I[2] == 1);
		ASSERT1(I[3] == 42);
		
		for (int j = 0; j < L; j++) {
			i = Test::Partition::PartitionArray(I, 0, L - 1, j);
			ASSERT1(i == I[j]);
			for (int k = 0; k < L - 1; k++) {
				if (k < j) ASSERT1(I[k] <= I[j]);
				else if (k > j) ASSERT1(I[k] >= I[j]);
			}
		}
	});
}