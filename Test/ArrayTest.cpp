#include "ArrayTest.h"

void ArrayTest::Print(const int * input, const int length, const int columns)
{
	int rows = length / columns;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			int k = i * columns + j;
			Logger().WriteInformation("\t%d", input[k]);
		}

		Logger().WriteInformation("\n");
	}

	int r = length % columns;
	for (int i = 0; i < r; i++) {
		Logger().WriteInformation("\t%d", input[length - r + i]);
	}

	Logger().WriteInformation("\n");
}

void ArrayTest::Test(int * A, int * B, int length, int columns, int rows)
{
	for (int i = 0; i < length; i++) {
		A[i] = i;
		B[i] = i;
	}

	Print(A, length, columns);
	Test::Array::Transpose<int>(B, length, columns);
	Print(B, length, rows);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			int s = i * columns + j;
			int t = j * rows + i;
			ASSERT1(A[s] == B[t]);
		}
	}

	Test::Array::Transpose<int>(B, length, rows);
	Print(B, length, columns);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			int s = i * columns + j;
			ASSERT1(A[s] == B[s]);
		}
	}
}

void ArrayTest::Init(void)
{
	Add("MinMax 1", [&](){
		int A[] = { 1 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 1, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 0);
	});

	Add("MinMax 2 0", [&](){
		int A[] = { 2, 2 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 2, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 1);
	});

	Add("MinMax 2 1", [&](){
		int A[] = { 1, 2 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 2, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 1);
	});

	Add("MinMax 2 2", [&](){
		int A[] = { 2, 1 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 2, minIndex, maxIndex);
		ASSERT1(minIndex == 1);
		ASSERT1(maxIndex == 0);
	});

	Add("MinMax 3 0", [&](){
		int A[] = { 2, 2, 2 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 3, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 2);
	});

	Add("MinMax 3 1", [&](){
		int A[] = { 1, 2, 2 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 3, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 2);
	});

	Add("MinMax 3 2", [&](){
		int A[] = { 2, 1, 2 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 3, minIndex, maxIndex);
		ASSERT1(minIndex == 1);
		ASSERT1(maxIndex == 2);
	});

	Add("MinMax 3 3", [&](){
		int A[] = { 2, 2, 1 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 3, minIndex, maxIndex);
		ASSERT1(minIndex == 2);
		ASSERT1(maxIndex == 1);
	});

	Add("MinMax 3 4", [&](){
		int A[] = { 1, 1, 2 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 3, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 2);
	});

	Add("MinMax 3 5", [&](){
		int A[] = { 1, 2, 1 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 3, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 1);
	});

	Add("MinMax 3 6", [&](){
		int A[] = { 2, 1, 1 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 3, minIndex, maxIndex);
		ASSERT1(minIndex == 1);
		ASSERT1(maxIndex == 0);
	});

	Add("MinMax 3 7", [&](){
		int A[] = { 1, 2, 3 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 3, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 2);
	});

	Add("MinMax 3 8", [&](){
		int A[] = { 3, 2, 1 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 3, minIndex, maxIndex);
		ASSERT1(minIndex == 2);
		ASSERT1(maxIndex == 0);
	});

	Add("MinMax 4 0", [&](){
		int A[] = { 4, 4, 4, 4 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 3);
	});

	Add("MinMax 4 1", [&](){
		int A[] = { 1, 4, 4, 4 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 3);
	});

	Add("MinMax 4 2", [&](){
		int A[] = { 4, 1, 4, 4 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 1);
		ASSERT1(maxIndex == 3);
	});

	Add("MinMax 4 3", [&](){
		int A[] = { 4, 4, 1, 4 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 2);
		ASSERT1(maxIndex == 3);
	});

	Add("MinMax 4 4", [&](){
		int A[] = { 4, 4, 4, 1 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 3);
		ASSERT1(maxIndex == 2);
	});

	Add("MinMax 4 5", [&](){
		int A[] = { 1, 1, 4, 4 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 3);
	});

	Add("MinMax 4 6", [&](){
		int A[] = { 1, 4, 1, 4 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 3);
	});

	Add("MinMax 4 7", [&](){
		int A[] = { 4, 1, 4, 1 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 1);
		ASSERT1(maxIndex == 2);
	});

	Add("MinMax 4 8", [&](){
		int A[] = { 4, 4, 1, 1 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 2);
		ASSERT1(maxIndex == 1);
	});

	Add("MinMax 4 9", [&](){
		int A[] = { 4, 3, 2, 1 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 3);
		ASSERT1(maxIndex == 0);
	});

	Add("MinMax 4 10", [&](){
		int A[] = { 1, 3, 2, 4 };
		int minIndex;
		int maxIndex;
		Test::Array::MinMax<int>(A, 4, minIndex, maxIndex);
		ASSERT1(minIndex == 0);
		ASSERT1(maxIndex == 3);
	});

	Add("Transpose(1,1)", [&](){
		const int length = 1;
		const int columns = 1;
		const int rows = 1;
		int A[length];
		int B[length];

		Test(A, B, length, columns, rows);
	});

	Add("Transpose(1,5)", [&](){
		const int length = 5;
		const int columns = 5;
		const int rows = 1;		
		int A[length];
		int B[length];

		Test(A, B, length, columns, rows);
	});

	Add("Transpose(5,1)", [&](){
		const int length = 5;
		const int columns = 1;
		const int rows = 5;
		int A[length];
		int B[length];

		Test(A, B, length, columns, rows);
	});

	Add("Transpose(3,5)", [&](){
		const int length = 15;
		const int columns = 5;
		const int rows = 3;
		int A[length];
		int B[length];

		Test(A, B, length, columns, rows);
	});

	Add("Transpose(10,6)", [&](){
		const int length = 60;
		const int columns = 6;
		const int rows = 10;
		int A[length];
		int B[length];

		Test(A, B, length, columns, rows);
	});

	Add("Transpose(8,8)", [&](){
		const int length = 64;
		const int columns = 8;
		const int rows = 8;
		int A[length];
		int B[length];

		Test(A, B, length, columns, rows);
	});

	Add("RowsToColumns(8, 8)", [&](){
		const int length = 64;
		const int columns = 8;
		const int rows = 8;
		int A[length];
		int B[length];

		for (int i = 0; i < length; i++) {
			A[i] = i;
			B[i] = i;
		}

		Print(A, length, columns);
		Test::Array::TransposeRowsToColumns<int>(B, length, columns);
		Print(B, length, rows);

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				int s = i * columns + j;
				int t = j * rows + i;
				ASSERT1(A[s] == B[t]);
			}
		}

		Test::Array::TransposeColumnsToRows<int>(B, length, columns);
		Print(B, length, columns);

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				int s = i * columns + j;
				ASSERT1(A[s] == B[s]);
			}
		}
	});

	Add("RowsToColumns(2, 8)", [&](){
		const int length = 16;
		const int columns = 8;
		const int rows = 2;
		int A[length];
		int B[length];

		for (int i = 0; i < length; i++) {
			A[i] = i;
			B[i] = i;
		}

		Print(A, length, columns);
		Test::Array::TransposeRowsToColumns<int>(B, length, columns);
		Print(B, length, columns);

		// Transpose element (m,n) to ((n % M), (k(m-1) + n/M)) means the index i = Nm + n is mapped to j = (n % M)N + k(m-1) + n/M
		int k = columns / rows;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				int s = i * columns + j;
				int t = (j % rows) * columns + k * i + j / rows;
				ASSERT1(A[s] == B[t]);
			}
		}

		Test::Array::TransposeColumnsToRows<int>(B, length, columns);
		Print(B, length, columns);

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				int s = i * columns + j;
				ASSERT1(A[s] == B[s]);
			}
		}
	});
	
	Add("RowsToColumns(9, 3)", [&](){
		const int length = 27;
		const int columns = 3;
		const int rows = 9;
		int A[length];
		int B[length];

		for (int i = 0; i < length; i++) {
			A[i] = i;
			B[i] = i;
		}

		Print(A, length, columns);
		Test::Array::TransposeRowsToColumns<int>(B, length, columns);
		Print(B, length, columns);

		// Transpose element (m,n) to ((m%k)N + n, m/k)) means the index i = Nm + n is mapped to j = (m%k)NN + nN + m/k
		int k = rows / columns;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				int s = i * columns + j;
				int t = (i % k) * columns * columns + j * columns + i / k;
				ASSERT1(A[s] == B[t]);
			}
		}

		Test::Array::TransposeColumnsToRows<int>(B, length, columns);
		Print(B, length, columns);

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				int s = i * columns + j;
				ASSERT1(A[s] == B[s]);
			}
		}
	});

	Add("Rotate(1)", [&](){
		int A[1] = { 1 };

		Test::Array::RotateLeft<int>(A, 1, 0);
		ASSERT1(A[0] == 1);
		Test::Array::RotateLeft<int>(A, 1, 1);
		ASSERT1(A[0] == 1);
		Test::Array::RotateLeft<int>(A, 1, 2);
		ASSERT1(A[0] == 1);
		Test::Array::RotateLeft<int>(A, 1, 3);
		ASSERT1(A[0] == 1);
		Test::Array::RotateRight<int>(A, 1, 3);
		ASSERT1(A[0] == 1);
		Test::Array::RotateRight<int>(A, 1, 2);
		ASSERT1(A[0] == 1);
		Test::Array::RotateRight<int>(A, 1, 1);
		ASSERT1(A[0] == 1);
		Test::Array::RotateRight<int>(A, 1, 0);
		ASSERT1(A[0] == 1);
	});

	Add("Rotate(2)", [&](){
		int A[2] = { 0, 1 };

		Test::Array::RotateLeft<int>(A, 2, 0);
		ASSERT1(A[0] == 0);
		ASSERT1(A[1] == 1);
		Test::Array::RotateLeft<int>(A, 2, 1);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 0);
		Test::Array::RotateLeft<int>(A, 2, 1);
		ASSERT1(A[0] == 0);
		ASSERT1(A[1] == 1);
		Test::Array::RotateLeft<int>(A, 2, 2);
		ASSERT1(A[0] == 0);
		ASSERT1(A[1] == 1);
		Test::Array::RotateLeft<int>(A, 2, 3);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 0);
		Test::Array::RotateRight<int>(A, 2, 1);
		ASSERT1(A[0] == 0);
		ASSERT1(A[1] == 1);
		Test::Array::RotateRight<int>(A, 2, 1);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 0);
		Test::Array::RotateRight<int>(A, 2, 1);
		ASSERT1(A[0] == 0);
		ASSERT1(A[1] == 1);
		Test::Array::RotateRight<int>(A, 2, 2);
		ASSERT1(A[0] == 0);
		ASSERT1(A[1] == 1);
		Test::Array::RotateRight<int>(A, 2, 3);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 0);
	});

	Add("Rotate(3)", [&](){
		int A[3] = { 0, 1, 2 };

		Test::Array::RotateLeft<int>(A, 3, 0);
		ASSERT1(A[0] == 0);
		ASSERT1(A[1] == 1);
		ASSERT1(A[2] == 2);
		Test::Array::RotateLeft<int>(A, 3, 1);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);
		ASSERT1(A[2] == 0);
		Test::Array::RotateLeft<int>(A, 3, 1);
		ASSERT1(A[0] == 2);
		ASSERT1(A[1] == 0);
		ASSERT1(A[2] == 1);
		Test::Array::RotateLeft<int>(A, 3, 1);
		ASSERT1(A[0] == 0);
		ASSERT1(A[1] == 1);
		ASSERT1(A[2] == 2);
		Test::Array::RotateLeft<int>(A, 3, 2);
		ASSERT1(A[0] == 2);
		ASSERT1(A[1] == 0);
		ASSERT1(A[2] == 1);
		Test::Array::RotateLeft<int>(A, 3, 2);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);
		ASSERT1(A[2] == 0);
		Test::Array::RotateLeft<int>(A, 3, 2);
		ASSERT1(A[0] == 0);
		ASSERT1(A[1] == 1);
		ASSERT1(A[2] == 2);
		Test::Array::RotateLeft<int>(A, 3, 3);
		ASSERT1(A[0] == 0);
		ASSERT1(A[1] == 1);
		ASSERT1(A[2] == 2);
		Test::Array::RotateLeft<int>(A, 3, 4);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);
		ASSERT1(A[2] == 0);
		Test::Array::RotateLeft<int>(A, 3, 5);
		ASSERT1(A[0] == 0);
		ASSERT1(A[1] == 1);
		ASSERT1(A[2] == 2);
		Test::Array::RotateRight<int>(A, 3, 0);
		ASSERT1(A[0] == 0);
		ASSERT1(A[1] == 1);
		ASSERT1(A[2] == 2);
		Test::Array::RotateRight<int>(A, 3, 1);
		ASSERT1(A[0] == 2);
		ASSERT1(A[1] == 0);
		ASSERT1(A[2] == 1);
		Test::Array::RotateRight<int>(A, 3, 1);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);
		ASSERT1(A[2] == 0);
		Test::Array::RotateRight<int>(A, 3, 1);
		ASSERT1(A[0] == 0);
		ASSERT1(A[1] == 1);
		ASSERT1(A[2] == 2);
		Test::Array::RotateRight<int>(A, 3, 2);
		ASSERT1(A[0] == 1);
		ASSERT1(A[1] == 2);
		ASSERT1(A[2] == 0);
		Test::Array::RotateRight<int>(A, 3, 2);
		ASSERT1(A[0] == 2);
		ASSERT1(A[1] == 0);
		ASSERT1(A[2] == 1);
		Test::Array::RotateRight<int>(A, 3, 2);
		ASSERT1(A[0] == 0);
		ASSERT1(A[1] == 1);
		ASSERT1(A[2] == 2);
		Test::Array::RotateRight<int>(A, 3, 3);
		ASSERT1(A[0] == 0);
		ASSERT1(A[1] == 1);
		ASSERT1(A[2] == 2);
		Test::Array::RotateRight<int>(A, 3, 4);
		ASSERT1(A[0] == 2);
		ASSERT1(A[1] == 0);
		ASSERT1(A[2] == 1);
		Test::Array::RotateRight<int>(A, 3, 5);
		ASSERT1(A[0] == 0);
		ASSERT1(A[1] == 1);
		ASSERT1(A[2] == 2);
	});

	Add("Rotate(10)", [&](){
		int A[10];

		function<void(void)> init = [&](){
			for (int i = 0; i < 10; i++) {
				A[i] = i;
			}
		};

		function<void(int)> checkLeft = [&](int d){
			for (int i = 0; i < 10; i++) {
				ASSERT1(A[i] == (i + d) % 10);
			}
		};

		for (int i = 0; i < 20; i++) {
			init();
			Test::Array::RotateLeft<int>(A, 10, i);
			checkLeft(i);
		}

		function<void(int)> checkRight = [&](int d){
			d = d % 10;
			for (int i = 0; i < 10; i++) {
				ASSERT1(A[i] == (i - d + 10) % 10);
			}
		};

		for (int i = 0; i < 20; i++) {
			init();
			Test::Array::RotateRight<int>(A, 10, i);
			checkRight(i);
		}
	});

	Add("Rotate(11)", [&](){
		int A[11];

		function<void(void)> init = [&](){
			for (int i = 0; i < 11; i++) {
				A[i] = i;
			}
		};

		function<void(int)> checkLeft = [&](int d){
			for (int i = 0; i < 11; i++) {
				ASSERT1(A[i] == (i + d) % 11);
			}
		};

		for (int i = 0; i < 22; i++) {
			init();
			Test::Array::RotateLeft<int>(A, 11, i);
			checkLeft(i);
		}

		function<void(int)> checkRight = [&](int d){
			d = d % 11;
			for (int i = 0; i < 11; i++) {
				ASSERT1(A[i] == (i - d + 11) % 11);
			}
		};

		for (int i = 0; i < 22; i++) {
			init();
			Test::Array::RotateRight<int>(A, 11, i);
			checkRight(i);
		}
	});

	Add("MaxSubArray", [&](){
		int A1[] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
		int L = sizeof(A1) / sizeof(A1[0]);
		int l, r;
		long sum;

		auto check = [&](int el, int er, int es) -> void {
			ASSERT1(el == l);
			ASSERT1(er == r);
			ASSERT1(es == (int)sum);
		};

		Test::Array::MaxSubArray(A1, L, l, r, sum);
		check(7, 10, 43);

		Test::Array::MaxSubArray(A1, 1, l, r, sum);
		check(0, 0, 13);

		Test::Array::MaxSubArray(A1, 2, l, r, sum);
		check(0, 0, 13);

		Test::Array::MaxSubArray(A1, 3, l, r, sum);
		check(0, 0, 13);

		Test::Array::MaxSubArray(A1, 4, l, r, sum);
		check(3, 3, 20);

		Test::Array::MaxSubArray(A1, 5, l, r, sum);
		check(3, 3, 20);

		Test::Array::MaxSubArray(A1, 8, l, r, sum);
		check(3, 3, 20);

		int A2[] = { 13, 3, 25, 20, 3, 16, 23, 18, 20, 7, 12, 5, 22, 15, 4, 7 };
		Test::Array::MaxSubArray(A2, L, l, r, sum);
		check(0, L - 1, 213);

		Test::Array::MaxSubArray(A2, 1, l, r, sum);
		check(0, 0, 13);

		Test::Array::MaxSubArray(A2, 2, l, r, sum);
		check(0, 1, 16);

		Test::Array::MaxSubArray(A2, 3, l, r, sum);
		check(0, 2, 41);

		int A3[] = { -13, -3, -25, -20, -3, -16, -23, -18, -20, -7, -12, -5, -22, -15, -4, -7 };
		Test::Array::MaxSubArray(A3, L, l, r, sum);
		check(1, 1, -3);

		Test::Array::MaxSubArray(A3, 1, l, r, sum);
		check(0, 0, -13);

		Test::Array::MaxSubArray(A3, 2, l, r, sum);
		check(1, 1, -3);

		int A4[] = { 0, 0, -25, -20, -3, -16, -23, -18, -20, -7, -12, -5, -22, -15, -4, -7 };
		Test::Array::MaxSubArray(A4, L, l, r, sum);
		check(0, 0, 0);

		Test::Array::MaxSubArray(A4, 1, l, r, sum);
		check(0, 0, 0);

		int A5[] = { 0, 0, 25, 20, 3, 16, 23, 18, 20, 7, 12, 5, 22, 15, 0, 0 };
		Test::Array::MaxSubArray(A5, L, l, r, sum);
		check(2, 13, 186);

		Test::Array::MaxSubArray(A5, 1, l, r, sum);
		check(0, 0, 0);

		int A6[] = { -25, -20, -3, 0, 0, -16, -23, -18, -20, -7, -12, -5, -22, -15, -4, -7 };
		Test::Array::MaxSubArray(A6, L, l, r, sum);
		check(3, 3, 0);

		Test::Array::MaxSubArray(A6, 1, l, r, sum);
		check(0, 0, -25);

		Test::Array::MaxSubArray(A6, 2, l, r, sum);
		check(1, 1, -20);

		Test::Array::MaxSubArray(A6, 5, l, r, sum);
		check(3, 3, 0);

		int A7[] = { 1, 1, 1, -1, -1, -1, -1, -18, -20, -7, -12, -5, -22, -15, -4, -7 };
		Test::Array::MaxSubArray(A7, L, l, r, sum);
		check(0, 2, 3);

		Test::Array::MaxSubArray(A7, 6, l, r, sum);
		check(0, 2, 3);

		int A8[] = { 1, 1, 1, -1, -1, -1, -1, -18, -20, -7, -12, -5, -22, -15, -4, 7 };
		Test::Array::MaxSubArray(A8, L, l, r, sum);
		check(L - 1, L - 1, 7);
	});

	Add("MaxInversionDistance", [&](){
		auto check = [&](int A[], int l, int f, int d) {
			for (int i = 0; i < l; i++) {
				Logger().WriteInformation("\t%d", A[i]);
			}
			Logger().WriteInformation("\n");
			int first, first2;
			int distance, distance2;
			Test::Array::MaxInversionDistance(A, l, first, distance);
			Test::Array::MaxInversionDistance2(A, l, first2, distance2);
			Logger().WriteInformation("\t%d(%d)\t%d(%d)\n\n", first, f, distance, d);
			Logger().WriteInformation("\t%d(%d)\t%d(%d)\n\n", first2, f, distance2, d);
			ASSERT1(first == f);
			ASSERT1(distance == d);
			ASSERT1(first2 == f);
			ASSERT1(distance2 == d);
		};

		int A0[] = { 1 };
		check(A0, 1, 0, 0);

		int A1[] = { 2, 3 };
		check(A1, 2, 0, 0);

		int A2[] = { 3, 2 };
		check(A2, 2, 0, 1);

		int A3[] = { 4, 4 };
		check(A3, 2, 0, 0);

		int A4[] = { 5, 6, 7 };
		check(A4, 3, 0, 0);

		int A5[] = { 5, 7, 6 };
		check(A5, 3, 1, 1);

		int A6[] = { 6, 5, 7 };
		check(A6, 3, 0, 1);

		int A7[] = { 6, 7, 5 };
		check(A7, 3, 0, 2);

		int A8[] = { 7, 5, 6 };
		check(A8, 3, 0, 2);

		int A9[] = { 7, 6, 5 };
		check(A9, 3, 0, 2);

		int A10[] = { 5, 7, 7 };
		check(A10, 3, 0, 0);

		int A11[] = { 7, 5, 7 };
		check(A11, 3, 0, 1);

		int A12[] = { 7, 7, 5 };
		check(A12, 3, 0, 2);

		int A14[] = { 7, 7, 7 };
		check(A14, 3, 0, 0);

		int A15[] = { 1, 2, 3, 4 };
		check(A15, 4, 0, 0);

		int A16[] = { 1, 3, 2, 4 };
		check(A16, 4, 1, 1);

		int A17[] = { 4, 3, 2, 1 };
		check(A17, 4, 0, 3);

		int A18[] = { 3, 4, 1, 2 };
		check(A18, 4, 0, 3);

		int A19[] = { 2, 4, 1, 3 };
		check(A19, 4, 1, 2);

		int A20[] = { 2, 1, 4, 3 };
		check(A20, 4, 2, 1);

		int A21[] = { 4, 2, 3, 1 };
		check(A21, 4, 0, 3);

		int A22[] = { 1, 2, 4, 3 };
		check(A22, 4, 2, 1);

		int A23[] = { 1, 3, 4, 2 };
		check(A23, 4, 1, 2);

		int A24[] = { 1, 4, 3, 2 };
		check(A24, 4, 1, 2);

		int A25[] = { 1, 4, 2, 3 };
		check(A25, 4, 1, 2);
	});

	Add("MaxSlidingWindow", [&](){
		auto printArray = [&](int A[], int l){
			Logger().WriteInformation("Input:    ");
			for (int i = 0; i < l; i++) {
				Logger().WriteInformation("  %d", A[i]);
			}
			Logger().WriteInformation("\n");
		};

		auto printVector = [&](vector<int> & v, int w){
			for (int i = 0; i < w - 1; i++) {
				Logger().WriteInformation("   ");
			}

			for_each(v.begin(), v.end(), [&](int i){
				Logger().WriteInformation("  %d", i);
			});
			Logger().WriteInformation("\n");
		};

		auto checkWindow = [&](int A[], int l, int w) {
			vector<int> output;
			vector<int> output2;
			Test::Array::MaxSlidingWindow(A, l, w, output);
			Test::Array::MaxSlidingWindow2(A, l, w, output2);
			// Logger().WriteInformation("Output1:  ");
			// printVector(output, w);
			// Logger().WriteInformation("Output2:  ");
			// printVector(output2, w);

			ASSERT1(output.size() == output2.size());
			for (unsigned int i = 0; i < output.size(); i++) {
				ASSERT1(output[i] == output2[i]);
			}
		};

		auto check = [&](int A[], int l) {
			Logger().WriteInformation("\n");
			printArray(A, l);

			for (int w = 1; w <= l; w++) {
				Logger().WriteInformation("Window:     %d\n", w);
				checkWindow(A, l, w);
			}
		};

		int A0[] = { 1 };
		check(A0, 1);

		int A1[] = { 1, 2 };
		check(A1, 2);

		int A2[] = { 2, 1 };
		check(A2, 2);

		int A3[] = { 2, 2 };
		check(A3, 2);

		int A4[] = { 1, 2, 3 };
		check(A4, 3);

		int A5[] = { 3, 1, 2 };
		check(A5, 3);

		int A6[] = { 2, 3, 1 };
		check(A6, 3);

		int A7[] = { 1, 3, 2 };
		check(A7, 3);

		int A8[] = { 2, 1, 3 };
		check(A8, 3);

		int A9[] = { 3, 2, 1 };
		check(A9, 3);

		int A10[] = { 1, 2, 2 };
		check(A10, 3);

		int A11[] = { 2, 1, 2 };
		check(A11, 3);

		int A12[] = { 2, 2, 1 };
		check(A12, 3);

		int A13[] = { 2, 2, 2 };
		check(A13, 3);

		int A14[] = { 1, 2, 3, 4 };
		check(A14, 4);

		int A15[] = { 4, 1, 2, 3 };
		check(A15, 4);

		int A16[] = { 3, 4, 1, 2 };
		check(A16, 4);

		int A17[] = { 2, 3, 4, 1 };
		check(A17, 4);

		int A18[] = { 2, 1, 3, 4 };
		check(A18, 4);

		int A19[] = { 4, 2, 1, 3 };
		check(A19, 4);

		int A20[] = { 3, 4, 2, 1 };
		check(A20, 4);

		int A21[] = { 1, 3, 4, 2 };
		check(A21, 4);

		int A22[] = { 3, 2, 1, 4 };
		check(A22, 4);

		int A23[] = { 4, 3, 2, 1 };
		check(A23, 4);

		int A24[] = { 1, 4, 3, 2 };
		check(A24, 4);

		int A25[] = { 2, 1, 4, 3 };
		check(A25, 4);

		int A26[] = { 4, 2, 3, 1 };
		check(A26, 4);

		int A27[] = { 1, 4, 2, 3 };
		check(A27, 4);

		int A28[] = { 3, 1, 4, 2 };
		check(A28, 4);

		int A29[] = { 2, 3, 1, 4 };
		check(A29, 4);

		int A30[] = { 1, 3, 2, 4 };
		check(A30, 4);

		int A31[] = { 4, 1, 3, 2 };
		check(A31, 4);

		int A32[] = { 2, 4, 1, 3 };
		check(A32, 4);

		int A33[] = { 3, 2, 4, 1 };
		check(A33, 4);

		int A34[] = { 1, 2, 4, 3 };
		check(A34, 4);

		int A35[] = { 3, 1, 2, 4 };
		check(A35, 4);

		int A36[] = { 4, 3, 1, 2 };
		check(A36, 4);

		int A37[] = { 2, 4, 3, 1 };
		check(A37, 4);

		for (int i = 0; i < 100; i++) {
			int length = 1 + Test::Random::Next(100);

			unique_ptr<int[]> input(new int[length]);
			for (int j = 0; j < length; j++) {
				input[j] = Test::Random::Next();
			}

			int w = 1;
			do {
				Logger().WriteInformation("Run %d: %d window over %d elements\n", i, w, length);
				checkWindow(input.get(), length, w);

				if (w >= length - 10 && w < length) {
					w = length;
				} else {
					w += (1 + Test::Random::Next(9));
				}
			} while (w <= length);
		}
	});

	Add("ExclusiveMultiplication", [&](){
		auto printInt = [&](int * input, int length) {
			for (int i = 0; i < length; i++) {
				Logger().WriteInformation("\t%d", input[i]);
			}
			Logger().WriteInformation("\n");
		};

		auto printLongLong = [&](long long * input, int length) {
			for (int i = 0; i < length; i++) {
				Logger().WriteInformation("\t%ld", input[i]);
			}
			Logger().WriteInformation("\n");
		};

		auto check = [&](int * input, int length, long long * output, long long * expect) {
			Test::Array::ExclusiveMultiplication(input, length, output);
			Logger().WriteInformation("Input:");
			printInt(input, length);
			Logger().WriteInformation("Output:");
			printLongLong(output, length);
			for (int i = 0; i < length; i++) {
				ASSERT1(output[i] == expect[i]);
			}
		};
		{
			int A[] = { 4, 3, 2, 1, 2 };
			long long B[5];
			long long C[] = { 12, 16, 24, 48, 24 };
			check(A, 5, B, C);
		}
		{
			int A[] = { 4, 3, 2, 1, 2, 3 };
			long long B[6];
			long long C[] = { 36, 48, 72, 144, 72, 48 };
			check(A, 6, B, C);
		}
	});

	Add("BuySellStock", [&](){
		auto print = [&](int * input, int length) {
			for (int i = 0; i < length; i++) {
				Logger().WriteInformation("  %d", input[i]);
			}
			Logger().WriteInformation("\n");
		};
		auto check = [&](int * input, int length) {
			print(input, length);

			int buy;
			int sell;
			int profit;
			Test::Array::BuySellStock(input, length, buy, sell, profit);
			int buy2;
			int sell2;
			int profit2;
			Test::Array::BuySellStock2(input, length, buy2, sell2, profit2);
			Logger().WriteInformation("\t%d\t%d\t%ld\n", buy, sell, profit);
			Logger().WriteInformation("\t%d\t%d\t%ld\n", buy2, sell2, profit2);
			ASSERT1(buy == buy2);
			ASSERT1(sell == sell2);
			ASSERT1(profit == profit2);
		};
		{
			int A[] = { 1 };
			check(A, 1);
		}
		{
			int A[] = { 1, 2 };
			check(A, 2);
		}
		{
			int A[] = { 2, 1 };
			check(A, 2);
		}
		{
			int A[] = { 2, 2 };
			check(A, 2);
		}
		{
			int A[] = { 1, 2, 3 };
			check(A, 3);
		}
		{
			int A[] = { 1, 3, 2 };
			check(A, 3);
		}
		{
			int A[] = { 2, 1, 3 };
			check(A, 3);
		}
		{
			int A[] = { 2, 3, 1 };
			check(A, 3);
		}
		{
			int A[] = { 3, 1, 2 };
			check(A, 3);
		}
		{
			int A[] = { 3, 2, 1 };
			check(A, 3);
		}
		{
			int A[] = { 1, 2, 2 };
			check(A, 3);
		}
		{
			int A[] = { 2, 1, 2 };
			check(A, 3);
		}
		{
			int A[] = { 2, 2, 1 };
			check(A, 3);
		}
		{
			int A[] = { 2, 2, 2 };
			check(A, 3);
		}
		{
			int A[] = { 1, 2, 3, 4 };
			check(A, 4);
		}
		{
			int A[] = { 2, 1, 3, 4 };
			check(A, 4);
		}
		{
			int A[] = { 2, 1, 4, 3 };
			check(A, 4);
		}
		{
			int A[] = { 1, 2, 4, 3 };
			check(A, 4);
		}
		{
			int A[] = { 2, 7, 1, 6 };
			check(A, 4);
		}
		{
			int A[] = { 3, 7, 1, 6 };
			check(A, 4);
		}
		{
			for (int i = 0; i < 100; i++) {
				int len = 1 + Test::Random::Next(100);
				unique_ptr<int[]> A(new int[len]);
				for (int j = 0; j < len; j++) {
					A[j] = Test::Random::Next();
				}
				Logger().WriteInformation("\nRun %d with %d elements\n", i, len);
				check(A.get(), len);
			}
		}
	});

	Add("BuySellStockMultipleTransactions", [&](){
		auto print = [&](int * input, int length) {
			for (int i = 0; i < length; i++) {
				Logger().WriteInformation("  %d", input[i]);
			}
			Logger().WriteInformation("\n");
		};
		auto check = [&](int * input, int length) {
			print(input, length);

			vector<int> buy;
			vector<int> sell;
			vector<int> profit;
			Test::Array::BuySellStock(input, length, buy, sell, profit);
			int total = 0;
			for (size_t i = 0; i < buy.size(); i++) {
				total += profit[i];
				Logger().WriteInformation("\t%d\t%d\t%ld\n", buy[i], sell[i], profit[i]);
			}
			Logger().WriteInformation("\tTotal: %d\n", total);
		};
		{
			int A[] = { 1 };
			check(A, 1);
		}
		{
			int A[] = { 1, 2 };
			check(A, 2);
		}
		{
			int A[] = { 2, 1 };
			check(A, 2);
		}
		{
			int A[] = { 2, 2 };
			check(A, 2);
		}
		{
			int A[] = { 1, 2, 3 };
			check(A, 3);
		}
		{
			int A[] = { 1, 3, 2 };
			check(A, 3);
		}
		{
			int A[] = { 2, 1, 3 };
			check(A, 3);
		}
		{
			int A[] = { 2, 3, 1 };
			check(A, 3);
		}
		{
			int A[] = { 3, 1, 2 };
			check(A, 3);
		}
		{
			int A[] = { 3, 2, 1 };
			check(A, 3);
		}
		{
			int A[] = { 1, 2, 2 };
			check(A, 3);
		}
		{
			int A[] = { 2, 1, 2 };
			check(A, 3);
		}
		{
			int A[] = { 2, 2, 1 };
			check(A, 3);
		}
		{
			int A[] = { 2, 2, 2 };
			check(A, 3);
		}
		{
			int A[] = { 1, 2, 3, 4 };
			check(A, 4);
		}
		{
			int A[] = { 2, 1, 3, 4 };
			check(A, 4);
		}
		{
			int A[] = { 2, 1, 4, 3 };
			check(A, 4);
		}
		{
			int A[] = { 1, 2, 4, 3 };
			check(A, 4);
		}
		{
			int A[] = { 2, 7, 1, 6 };
			check(A, 4);
		}
		{
			int A[] = { 3, 7, 1, 6 };
			check(A, 4);
		}
		{
			int A[] = { 9, 7, 10, 9, 5, 8, 3, 7, 2, 1, 5, 3 };
			check(A, 12);
		}
		{
			int A[] = { 6, 1, 3, 2, 4, 7 };
			check(A, 6);
		}
	});

	Add("BuySellStockTwoTransactions", [&](){
		auto print = [&](int * input, int length) {
			for (int i = 0; i < length; i++) {
				Logger().WriteInformation("  %d", input[i]);
			}
			Logger().WriteInformation("\n");
		};
		auto check = [&](int * input, int length) {
			print(input, length);

			vector<int> buy;
			vector<int> sell;
			vector<int> profit;
			Test::Array::BuySellStock2(input, length, buy, sell, profit);
			int total = 0;
			for (size_t i = 0; i < buy.size(); i++) {
				total += profit[i];
				Logger().WriteInformation("\t%d\t%d\t%ld\n", buy[i], sell[i], profit[i]);
			}
			Logger().WriteInformation("\tTotal: %d\n", total);
		};
		{
			int A[] = { 1 };
			check(A, 1);
		}
		{
			int A[] = { 1, 2 };
			check(A, 2);
		}
		{
			int A[] = { 2, 1 };
			check(A, 2);
		}
		{
			int A[] = { 2, 2 };
			check(A, 2);
		}
		{
			int A[] = { 1, 2, 3 };
			check(A, 3);
		}
		{
			int A[] = { 1, 3, 2 };
			check(A, 3);
		}
		{
			int A[] = { 2, 1, 3 };
			check(A, 3);
		}
		{
			int A[] = { 2, 3, 1 };
			check(A, 3);
		}
		{
			int A[] = { 3, 1, 2 };
			check(A, 3);
		}
		{
			int A[] = { 3, 2, 1 };
			check(A, 3);
		}
		{
			int A[] = { 1, 2, 2 };
			check(A, 3);
		}
		{
			int A[] = { 2, 1, 2 };
			check(A, 3);
		}
		{
			int A[] = { 2, 2, 1 };
			check(A, 3);
		}
		{
			int A[] = { 2, 2, 2 };
			check(A, 3);
		}
		{
			int A[] = { 1, 2, 3, 4 };
			check(A, 4);
		}
		{
			int A[] = { 2, 1, 3, 4 };
			check(A, 4);
		}
		{
			int A[] = { 2, 1, 4, 3 };
			check(A, 4);
		}
		{
			int A[] = { 1, 2, 4, 3 };
			check(A, 4);
		}
		{
			int A[] = { 2, 7, 1, 6 };
			check(A, 4);
		}
		{
			int A[] = { 3, 7, 1, 6 };
			check(A, 4);
		}
		{
			int A[] = { 9, 7, 10, 9, 5, 8, 3, 7, 2, 1, 5, 3 };
			check(A, 12);
		}
		{
			int A[] = { 6, 1, 3, 2, 4, 7 };
			check(A, 6);
		}
	});
}