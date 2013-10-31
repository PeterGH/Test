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
}