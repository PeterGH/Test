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

	Add("Partition Array 1", [&](){
		int A[] = { 1 };
		int I[] = { 0 };
		Test::Partition::PartitionArray(A, 0, 0, I, 0, 0);
		ASSERT1(A[0] == 1);
	});

	Add("Partition Array 2", [&](){
		int A[] = { 1, 2 };
		int I1[] = { 0 };
		Test::Partition::PartitionArray(A, 0, 1, I1, 0, 0);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);

		int I2[] = { 1 };
		Test::Partition::PartitionArray(A, 0, 1, I2, 0, 0);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);

		int I3[] = { 0, 1 };
		Test::Partition::PartitionArray(A, 0, 1, I3, 0, 1);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);

		int B1[] = { 2, 1 };
		Test::Partition::PartitionArray(B1, 0, 1, I1, 0, 0);
		ASSERT1(B1[0] == 1);
		ASSERT1(B1[1] == 2);

		int B2[] = { 2, 1 };
		Test::Partition::PartitionArray(B2, 0, 1, I2, 0, 0);
		ASSERT1(B2[0] == 1);
		ASSERT1(B2[1] == 2);

		int B3[] = { 2, 1 };
		Test::Partition::PartitionArray(B3, 0, 1, I3, 0, 0);
		ASSERT1(B3[0] == 1);
		ASSERT1(B3[1] == 2);
	});

	Add("Partition Array 3", [&](){
		int A[] = { 1, 2, 3 };
		int I1[] = { 0 };
		Test::Partition::PartitionArray(A, 0, 2, I1, 0, 0);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);
		ASSERT1(A[2] == 3);

		int I2[] = { 1 };
		Test::Partition::PartitionArray(A, 0, 2, I2, 0, 0);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);
		ASSERT1(A[2] == 3);

		int I3[] = { 2 };
		Test::Partition::PartitionArray(A, 0, 2, I3, 0, 0);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);
		ASSERT1(A[2] == 3);

		int I4[] = { 0, 1 };
		Test::Partition::PartitionArray(A, 0, 2, I4, 0, 1);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);
		ASSERT1(A[2] == 3);

		int I5[] = { 0, 2 };
		Test::Partition::PartitionArray(A, 0, 2, I5, 0, 1);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);
		ASSERT1(A[2] == 3);

		int I6[] = { 1, 2 };
		Test::Partition::PartitionArray(A, 0, 2, I6, 0, 1);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);
		ASSERT1(A[2] == 3);

		int I7[] = { 0, 1, 2 };
		Test::Partition::PartitionArray(A, 0, 2, I7, 0, 2);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);
		ASSERT1(A[2] == 3);

		int B1[] = { 2, 1, 3 };
		Test::Partition::PartitionArray(B1, 0, 2, I1, 0, 0);
		ASSERT1(B1[0] == 1);
		ASSERT1(B1[1] > B1[0]);
		ASSERT1(B1[2] > B1[0]);

		int B2[] = { 2, 3, 1 };
		Test::Partition::PartitionArray(B2, 0, 2, I1, 0, 0);
		ASSERT1(B2[0] == 1);
		ASSERT1(B2[1] > B2[0]);
		ASSERT1(B2[2] > B2[0]);

		int B3[] = { 3, 1, 2 };
		Test::Partition::PartitionArray(B3, 0, 2, I1, 0, 0);
		ASSERT1(B3[0] == 1);
		ASSERT1(B3[1] > B3[0]);
		ASSERT1(B3[2] > B3[0]);

		int B4[] = { 3, 2, 1 };
		Test::Partition::PartitionArray(B4, 0, 2, I1, 0, 0);
		ASSERT1(B4[0] == 1);
		ASSERT1(B4[1] > B4[0]);
		ASSERT1(B4[2] > B4[0]);

		int B5[] = { 2, 1, 3 };
		Test::Partition::PartitionArray(B5, 0, 2, I2, 0, 0);
		ASSERT1(B5[0] == 1);
		ASSERT1(B5[1] == 2);
		ASSERT1(B5[2] == 3);

		int B6[] = { 2, 3, 1 };
		Test::Partition::PartitionArray(B6, 0, 2, I2, 0, 0);
		ASSERT1(B6[0] == 1);
		ASSERT1(B6[1] == 2);
		ASSERT1(B6[2] == 3);

		int B7[] = { 3, 1, 2 };
		Test::Partition::PartitionArray(B7, 0, 2, I2, 0, 0);
		ASSERT1(B7[0] == 1);
		ASSERT1(B7[1] == 2);
		ASSERT1(B7[2] == 3);

		int B8[] = { 3, 2, 1 };
		Test::Partition::PartitionArray(B8, 0, 2, I2, 0, 0);
		ASSERT1(B8[0] == 1);
		ASSERT1(B8[1] == 2);
		ASSERT1(B8[2] == 3);

		int B9[] = { 2, 1, 3 };
		Test::Partition::PartitionArray(B9, 0, 2, I3, 0, 0);
		ASSERT1(B9[0] < B9[2]);
		ASSERT1(B9[1] < B9[2]);
		ASSERT1(B9[2] == 3);

		int B10[] = { 2, 3, 1 };
		Test::Partition::PartitionArray(B10, 0, 2, I3, 0, 0);
		ASSERT1(B10[0] < B10[2]);
		ASSERT1(B10[1] < B10[2]);
		ASSERT1(B10[2] == 3);

		int B11[] = { 3, 1, 2 };
		Test::Partition::PartitionArray(B11, 0, 2, I3, 0, 0);
		ASSERT1(B11[0] < B11[2]);
		ASSERT1(B11[1] < B11[2]);
		ASSERT1(B11[2] == 3);

		int B12[] = { 3, 2, 1 };
		Test::Partition::PartitionArray(B12, 0, 2, I3, 0, 0);
		ASSERT1(B12[0] < B12[2]);
		ASSERT1(B12[1] < B12[2]);
		ASSERT1(B12[2] == 3);

		int B13[6][3] = {
			{ 1, 2, 3 },
			{ 1, 3, 2 },
			{ 2, 1, 3 },
			{ 2, 3, 1 },
			{ 3, 1, 2 },
			{ 3, 2, 1 }
		};

		for (int i = 0; i < 6; i++) {
			Test::Partition::PartitionArray(B13[i], 0, 2, I4, 0, 1);
			ASSERT1(B13[i][0] == 1);
			ASSERT1(B13[i][1] == 2);
			ASSERT1(B13[i][2] == 3);
		}

		int B14[6][3] = {
			{ 1, 2, 3 },
			{ 1, 3, 2 },
			{ 2, 1, 3 },
			{ 2, 3, 1 },
			{ 3, 1, 2 },
			{ 3, 2, 1 }
		};

		for (int i = 0; i < 6; i++) {
			Test::Partition::PartitionArray(B14[i], 0, 2, I5, 0, 1);
			ASSERT1(B14[i][0] == 1);
			ASSERT1(B14[i][1] == 2);
			ASSERT1(B14[i][2] == 3);
		}
		
		int B15[6][3] = {
			{ 1, 2, 3 },
			{ 1, 3, 2 },
			{ 2, 1, 3 },
			{ 2, 3, 1 },
			{ 3, 1, 2 },
			{ 3, 2, 1 }
		};

		for (int i = 0; i < 6; i++) {
			Test::Partition::PartitionArray(B15[i], 0, 2, I6, 0, 1);
			ASSERT1(B15[i][0] == 1);
			ASSERT1(B15[i][1] == 2);
			ASSERT1(B15[i][2] == 3);
		}

		int B16[6][3] = {
			{ 1, 2, 3 },
			{ 1, 3, 2 },
			{ 2, 1, 3 },
			{ 2, 3, 1 },
			{ 3, 1, 2 },
			{ 3, 2, 1 }
		};

		for (int i = 0; i < 6; i++) {
			Test::Partition::PartitionArray(B16[i], 0, 2, I7, 0, 2);
			ASSERT1(B16[i][0] == 1);
			ASSERT1(B16[i][1] == 2);
			ASSERT1(B16[i][2] == 3);
		}
	});

	Add("Partition Array Random", [&](){
		for (int i = 0; i < 100; i++) {
			int length = 1 + Test::Random::Next();
			int len = 1 + Test::Random::Next(length - 1);

			Logger().WriteInformation("Run %d: %d elements %d indices\n", i, length, len);

			unique_ptr<int[]> input(new int[length]);
			for (int j = 0; j < length; j++) {
				input[j] = Test::Random::Next();
			}

			int delta = length / len;
			unique_ptr<int[]> indices(new int[len]);
			indices[0] = Test::Random::Next(0, delta);
			for (int j = 1; j < len; j++) {
				indices[j] = Test::Random::Next(indices[j - 1] + 1, indices[j - 1] + delta);
			}

			ASSERT1(indices[len - 1] < length);

			Test::Partition::PartitionArray((int *)input.get(), 0, length - 1, (int *)indices.get(), 0, len - 1);

			int index = 0;
			for (int j = 0; j < length; j++) {
				if (j == indices[index]) {
					index++;
				}

				if (index < len)
					ASSERT1(input[j] <= input[indices[index]]);

				if (index > 0)
					ASSERT1(input[j] >= input[indices[index - 1]]);
			}
		}
	});
}