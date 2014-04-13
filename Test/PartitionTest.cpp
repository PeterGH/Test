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

		int i = Test::Partition::PartitionArrayByOrder(I, 0, 0, 0);
		ASSERT1(i == 3);

		i = Test::Partition::PartitionArrayByOrder(I, L - 1, L - 1, 0);
		ASSERT1(i == 64);

		i = Test::Partition::PartitionArrayByOrder(I, 0, 1, 0);
		ASSERT1(i == 3);
		ASSERT1(I[0] == 3);
		ASSERT1(I[1] == 43);

		i = Test::Partition::PartitionArrayByOrder(I, 0, 1, 1);
		ASSERT1(i == 43);
		ASSERT1(I[0] == 3);
		ASSERT1(I[1] == 43);
		
		i = Test::Partition::PartitionArrayByOrder(I, 2, 3, 0);
		ASSERT1(i == 1);
		ASSERT1(I[2] == 1);
		ASSERT1(I[3] == 42);

		i = Test::Partition::PartitionArrayByOrder(I, 2, 3, 1);
		ASSERT1(i == 42);
		ASSERT1(I[2] == 1);
		ASSERT1(I[3] == 42);
		
		for (int j = 0; j < L; j++) {
			i = Test::Partition::PartitionArrayByOrder(I, 0, L - 1, j);
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
		Test::Partition::PartitionArrayByOrders(A, 0, 0, I, 0, 0);
		ASSERT1(A[0] == 1);
	});

	Add("Partition Array 2", [&](){
		int A[] = { 1, 2 };
		int I1[] = { 0 };
		Test::Partition::PartitionArrayByOrders(A, 0, 1, I1, 0, 0);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);

		int I2[] = { 1 };
		Test::Partition::PartitionArrayByOrders(A, 0, 1, I2, 0, 0);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);

		int I3[] = { 0, 1 };
		Test::Partition::PartitionArrayByOrders(A, 0, 1, I3, 0, 1);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);

		int B1[] = { 2, 1 };
		Test::Partition::PartitionArrayByOrders(B1, 0, 1, I1, 0, 0);
		ASSERT1(B1[0] == 1);
		ASSERT1(B1[1] == 2);

		int B2[] = { 2, 1 };
		Test::Partition::PartitionArrayByOrders(B2, 0, 1, I2, 0, 0);
		ASSERT1(B2[0] == 1);
		ASSERT1(B2[1] == 2);

		int B3[] = { 2, 1 };
		Test::Partition::PartitionArrayByOrders(B3, 0, 1, I3, 0, 1);
		ASSERT1(B3[0] == 1);
		ASSERT1(B3[1] == 2);
	});

	Add("Partition Array 3", [&](){
		int A[] = { 1, 2, 3 };
		int I1[] = { 0 };
		Test::Partition::PartitionArrayByOrders(A, 0, 2, I1, 0, 0);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);
		ASSERT1(A[2] == 3);

		int I2[] = { 1 };
		Test::Partition::PartitionArrayByOrders(A, 0, 2, I2, 0, 0);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);
		ASSERT1(A[2] == 3);

		int I3[] = { 2 };
		Test::Partition::PartitionArrayByOrders(A, 0, 2, I3, 0, 0);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);
		ASSERT1(A[2] == 3);

		int I4[] = { 0, 1 };
		Test::Partition::PartitionArrayByOrders(A, 0, 2, I4, 0, 1);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);
		ASSERT1(A[2] == 3);

		int I5[] = { 0, 2 };
		Test::Partition::PartitionArrayByOrders(A, 0, 2, I5, 0, 1);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);
		ASSERT1(A[2] == 3);

		int I6[] = { 1, 2 };
		Test::Partition::PartitionArrayByOrders(A, 0, 2, I6, 0, 1);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);
		ASSERT1(A[2] == 3);

		int I7[] = { 0, 1, 2 };
		Test::Partition::PartitionArrayByOrders(A, 0, 2, I7, 0, 2);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);
		ASSERT1(A[2] == 3);

		int B1[] = { 2, 1, 3 };
		Test::Partition::PartitionArrayByOrders(B1, 0, 2, I1, 0, 0);
		ASSERT1(B1[0] == 1);
		ASSERT1(B1[1] > B1[0]);
		ASSERT1(B1[2] > B1[0]);

		int B2[] = { 2, 3, 1 };
		Test::Partition::PartitionArrayByOrders(B2, 0, 2, I1, 0, 0);
		ASSERT1(B2[0] == 1);
		ASSERT1(B2[1] > B2[0]);
		ASSERT1(B2[2] > B2[0]);

		int B3[] = { 3, 1, 2 };
		Test::Partition::PartitionArrayByOrders(B3, 0, 2, I1, 0, 0);
		ASSERT1(B3[0] == 1);
		ASSERT1(B3[1] > B3[0]);
		ASSERT1(B3[2] > B3[0]);

		int B4[] = { 3, 2, 1 };
		Test::Partition::PartitionArrayByOrders(B4, 0, 2, I1, 0, 0);
		ASSERT1(B4[0] == 1);
		ASSERT1(B4[1] > B4[0]);
		ASSERT1(B4[2] > B4[0]);

		int B5[] = { 2, 1, 3 };
		Test::Partition::PartitionArrayByOrders(B5, 0, 2, I2, 0, 0);
		ASSERT1(B5[0] == 1);
		ASSERT1(B5[1] == 2);
		ASSERT1(B5[2] == 3);

		int B6[] = { 2, 3, 1 };
		Test::Partition::PartitionArrayByOrders(B6, 0, 2, I2, 0, 0);
		ASSERT1(B6[0] == 1);
		ASSERT1(B6[1] == 2);
		ASSERT1(B6[2] == 3);

		int B7[] = { 3, 1, 2 };
		Test::Partition::PartitionArrayByOrders(B7, 0, 2, I2, 0, 0);
		ASSERT1(B7[0] == 1);
		ASSERT1(B7[1] == 2);
		ASSERT1(B7[2] == 3);

		int B8[] = { 3, 2, 1 };
		Test::Partition::PartitionArrayByOrders(B8, 0, 2, I2, 0, 0);
		ASSERT1(B8[0] == 1);
		ASSERT1(B8[1] == 2);
		ASSERT1(B8[2] == 3);

		int B9[] = { 2, 1, 3 };
		Test::Partition::PartitionArrayByOrders(B9, 0, 2, I3, 0, 0);
		ASSERT1(B9[0] < B9[2]);
		ASSERT1(B9[1] < B9[2]);
		ASSERT1(B9[2] == 3);

		int B10[] = { 2, 3, 1 };
		Test::Partition::PartitionArrayByOrders(B10, 0, 2, I3, 0, 0);
		ASSERT1(B10[0] < B10[2]);
		ASSERT1(B10[1] < B10[2]);
		ASSERT1(B10[2] == 3);

		int B11[] = { 3, 1, 2 };
		Test::Partition::PartitionArrayByOrders(B11, 0, 2, I3, 0, 0);
		ASSERT1(B11[0] < B11[2]);
		ASSERT1(B11[1] < B11[2]);
		ASSERT1(B11[2] == 3);

		int B12[] = { 3, 2, 1 };
		Test::Partition::PartitionArrayByOrders(B12, 0, 2, I3, 0, 0);
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
			Test::Partition::PartitionArrayByOrders(B13[i], 0, 2, I4, 0, 1);
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
			Test::Partition::PartitionArrayByOrders(B14[i], 0, 2, I5, 0, 1);
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
			Test::Partition::PartitionArrayByOrders(B15[i], 0, 2, I6, 0, 1);
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
			Test::Partition::PartitionArrayByOrders(B16[i], 0, 2, I7, 0, 2);
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

			Test::Partition::PartitionArrayByOrders((int *)input.get(), 0, length - 1, (int *)indices.get(), 0, len - 1);

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

	Add("Partition Quantiles 1", [&](){
		int A[] = { 1 };
		int I[1];
		Test::Partition::PartitionArrayByQuantiles(A, 1, I, 1);
		ASSERT1(A[0] == 1);
	});

	Add("Partition Quantiles 2", [&](){
		int A1[] = { 1, 2 };
		int I1[1];
		Test::Partition::PartitionArrayByQuantiles(A1, 2, I1, 2);
		ASSERT1(A1[0] == 1);
		ASSERT1(A1[1] == 2);
		ASSERT1(I1[0] == 1);

		int A2[] = { 2, 1 };
		int I2[1];
		Test::Partition::PartitionArrayByQuantiles(A2, 2, I2, 2);
		ASSERT1(A2[0] == 1);
		ASSERT1(A2[1] == 2);
		ASSERT1(I2[0] == 1);
	});

	Add("Partition Quantiles 3", [&](){
		int A1[6][3] = {
			{ 1, 2, 3 },
			{ 1, 3, 2 },
			{ 2, 1, 3 },
			{ 2, 3, 1 },
			{ 3, 1, 2 },
			{ 3, 2, 1 }
		};

		for (int i = 0; i < 6; i++) {
			int I[1];
			Test::Partition::PartitionArrayByQuantiles(A1[i], 3, I, 2);
			ASSERT1(A1[i][0] == 1);
			ASSERT1(A1[i][1] == 2);
			ASSERT1(A1[i][2] == 3);
			ASSERT1(I[0] == 1);
		}

		int A2[6][3] = {
			{ 1, 2, 3 },
			{ 1, 3, 2 },
			{ 2, 1, 3 },
			{ 2, 3, 1 },
			{ 3, 1, 2 },
			{ 3, 2, 1 }
		};

		for (int i = 0; i < 6; i++) {
			int I[2];
			Test::Partition::PartitionArrayByQuantiles(A2[i], 3, I, 3);
			ASSERT1(A2[i][0] == 1);
			ASSERT1(A2[i][1] == 2);
			ASSERT1(A2[i][2] == 3);
			ASSERT1(I[0] == 1);
			ASSERT1(I[1] == 2);
		}
	});

	Add("Partition Quantiles Random", [&](){
		for (int i = 0; i < 100; i++) {
			int length = 1 + Test::Random::Next();
			int len = 1 + Test::Random::Next(length - 1);

			Logger().WriteInformation("Run %d: %d elements %d indices\n", i, length, len - 1);

			unique_ptr<int[]> input(new int[length]);
			for (int j = 0; j < length; j++) {
				input[j] = Test::Random::Next();
			}

			unique_ptr<int[]> indices(new int[len - 1]);

			Test::Partition::PartitionArrayByQuantiles((int *)input.get(), length, (int *)indices.get(), len);

			for (int i = 0; i < len - 3; i++) {
				int d1 = indices[i + 1] - indices[i];
				int d2 = indices[i + 2] - indices[i + 1];
				ASSERT1(abs(d1 - d2) <= 1);
			}

			int index = 0;
			for (int j = 0; j < length; j++) {
				if (j == indices[index]) {
					index++;
				}

				if (index < len - 1)
					ASSERT1(input[j] <= input[indices[index]]);

				if (index > 0)
					ASSERT1(input[j] >= input[indices[index - 1]]);
			}
		}
	});

	Add("Select Neighbors 2", [&](){
		int A1[] = { 1, 2 };
		Test::Partition::SelectClosestNeighbors(A1, 2, 0, 1);
		ASSERT1(A1[0] == 1);
		ASSERT1(A1[1] == 2);

		Test::Partition::SelectClosestNeighbors(A1, 2, 1, 1);
		ASSERT1(A1[0] == 2);
		ASSERT1(A1[1] == 1);

		Test::Partition::SelectClosestNeighbors(A1, 2, 0, 1);
		ASSERT1(A1[0] == 1);
		ASSERT1(A1[1] == 2);

		Test::Partition::SelectClosestNeighbors(A1, 2, 1, 1);
		ASSERT1(A1[0] == 2);
		ASSERT1(A1[1] == 1);

		Test::Partition::SelectClosestNeighbors(A1, 2, 0, 0);
		ASSERT1(A1[0] == 1);
		ASSERT1(A1[1] == 2);

		Test::Partition::SelectClosestNeighbors(A1, 2, 1, 0);
		ASSERT1(A1[0] == 2);
		ASSERT1(A1[1] == 1);
	});

	Add("Select Neighbors 3", [&](){
		int A1[6][3] = {
			{ 1, 2, 3 },
			{ 1, 3, 2 },
			{ 2, 1, 3 },
			{ 2, 3, 1 },
			{ 3, 1, 2 },
			{ 3, 2, 1 }
		};

		for (int i = 0; i < 6; i++) {
			Test::Partition::SelectClosestNeighbors(A1[i], 3, 0, 0);
			ASSERT1(A1[i][0] == 1);
		}

		int A2[6][3] = {
			{ 1, 2, 3 },
			{ 1, 3, 2 },
			{ 2, 1, 3 },
			{ 2, 3, 1 },
			{ 3, 1, 2 },
			{ 3, 2, 1 }
		};

		for (int i = 0; i < 6; i++) {
			Test::Partition::SelectClosestNeighbors(A2[i], 3, 0, 1);
			ASSERT1(A2[i][0] == 1);
			ASSERT1(A2[i][1] == 2);
		}

		int A3[6][3] = {
			{ 1, 2, 3 },
			{ 1, 3, 2 },
			{ 2, 1, 3 },
			{ 2, 3, 1 },
			{ 3, 1, 2 },
			{ 3, 2, 1 }
		};

		for (int i = 0; i < 6; i++) {
			Test::Partition::SelectClosestNeighbors(A3[i], 3, 1, 0);
			ASSERT1(A3[i][0] == 2);
		}

		int A4[6][3] = {
			{ 1, 2, 3 },
			{ 1, 3, 2 },
			{ 2, 1, 3 },
			{ 2, 3, 1 },
			{ 3, 1, 2 },
			{ 3, 2, 1 }
		};

		for (int i = 0; i < 6; i++) {
			Test::Partition::SelectClosestNeighbors(A4[i], 3, 2, 0);
			ASSERT1(A4[i][0] == 3);
		}

		int A5[6][3] = {
			{ 1, 2, 3 },
			{ 1, 3, 2 },
			{ 2, 1, 3 },
			{ 2, 3, 1 },
			{ 3, 1, 2 },
			{ 3, 2, 1 }
		};

		for (int i = 0; i < 6; i++) {
			Test::Partition::SelectClosestNeighbors(A5[i], 3, 2, 1);
			ASSERT1(A5[i][0] == 3);
			ASSERT1(A5[i][1] == 2);
		}
	});

	Add("Select Neighbors Random", [&](){
		for (int i = 0; i < 100; i++) {
			int length = 1 + Test::Random::Next();
			int pivotIndex = Test::Random::Next(length - 1);
			int countNeighbors = Test::Random::Next(length - 1);

			Logger().WriteInformation("Run %d: %d elements, select %d elements closest to pivotIndex %d\n", i, length, countNeighbors, pivotIndex);

			unique_ptr<int[]> input(new int[length]);
			for (int j = 0; j < length; j++) {
				input[j] = Test::Random::Next();
			}

			int pivot = Test::Partition::SelectClosestNeighbors((int *)input.get(), length, pivotIndex, countNeighbors);
			
			int maxDistance = 0;
			for (int i = 0; i <= countNeighbors ; i++) {
				int d = abs(input[i] - pivot);
				if (d > maxDistance) maxDistance = d;
			}

			for (int i = countNeighbors + 1; i < length; i++) {
				int d = abs(input[i] - pivot);
				ASSERT1(d >= maxDistance);
			}
		}
	});

	Add("MinMaxPartitionSum", [&](){
		auto check = [&](int * input, int length, int partitions, int expectedSum){
			Logger().WriteInformation("\nInput:");
			for (int i = 0; i < length; i++) {
				Logger().WriteInformation(" %d", input[i]);
			}
			Logger().WriteInformation("\n%d partitions\n", partitions);

			unique_ptr<int[]> indices(new int[partitions]);
			int sum = Test::Partition::MinMaxPartitionSum<int>(input, length, indices.get(), partitions);

			for (int j = 0; j < partitions; j++) {
				int b = indices[j];
				int e = j == partitions - 1 ? length - 1 : indices[j+1] - 1;
				int s = 0;
				for (int i = b; i <= e; i++) {
					s += input[i];
				}
				Logger().WriteInformation("  %d = sum{A[%d..%d]} = ", s, b, e);
				for (int i = b; i <= e; i++) {
					Logger().WriteInformation("%s%d", i == b ? "" : " + ", input[i]);
				}
				Logger().WriteInformation("\n");
			}

			ASSERT1(sum == expectedSum);
		};

		int A1[] = { 100, 200, 300, 400, 500, 600, 700, 800, 900 };
		check(A1, 9, 3, 1700);

		int A2[] = { 100, 200, 300, 400, 500, 600, 700, 800, 900 };
		check(A2, 9, 9, 900);

		int A3[] = { 900, 800, 700, 600, 500, 400, 300, 200, 100 };
		check(A3, 9, 3, 1700);

		int A4[] = { 100, 100, 100, 100, 100, 100, 100, 100, 100 };
		check(A4, 9, 3, 300);

		int A5[] = { 100, 100, 100, 100, 100, 100, 100, 100, 100 };
		check(A5, 9, 2, 500);

		int A7[] = { 100, 100, 100, 100, 100, 100, 100, 100, 100 };
		check(A7, 9, 9, 100);

		int A6[] = { 100, 100, 100, 100, 100, 100, 100, 100, 100 };
		check(A6, 9, 4, 300);
	});
}