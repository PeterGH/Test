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
	Test::Array::Transpose(B, length, columns);
	Print(B, length, rows);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			int s = i * columns + j;
			int t = j * rows + i;
			ASSERT1(A[s] == B[t]);
		}
	}

	Test::Array::Transpose(B, length, rows);
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
}