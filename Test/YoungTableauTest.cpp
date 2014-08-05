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
			int cols = Test::Random::Next(1, len >> 3);
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
			int cols = Test::Random::Next(1, len >> 3);
			int rows = Test::Random::Next(1, (len / cols) << 3);

			Logger().WriteInformation("Run %d, tableau %d X %d, , %d elements and then push %d elements\n", i, rows, cols, lenA, lenB);
			Test::YoungTableau<int> yt(rows, cols);
			yt.Push(A.get(), lenA, false);
			ASSERT1(yt.Verify());
			yt.Push(B.get(), lenB, false);
			ASSERT1(yt.Verify());
		}
	});

	Add("Search1", [&]() {
		int A[20];
		for (int i = 0; i < 20; i++) {
			A[i] = 20 - i;
		}

		Test::YoungTableau<int> yt(1, 20, A, 20);
		Logger() << yt;
		ASSERT1(yt.Verify());

		pair<int, int> index;
		pair<int, int> index2;
		for (int i = 1; i <= 20; i++) {
			index = yt.Search(i);
			index2 = yt.Search2(i);
			Logger().WriteInformation("%d is at (%d, %d) (%d, %d)\n", i, index.first, index.second, index2.first, index2.second);
			ASSERT1(index.first == 0);
			ASSERT1(index.second == i - 1);
			ASSERT1(index.first == index2.first);
			ASSERT1(index.second == index2.second);
		}

		index = yt.Search(21);
		index2 = yt.Search2(21);
		ASSERT1(index.first == -1);
		ASSERT1(index.second == -1);
		ASSERT1(index2.first == -1);
		ASSERT1(index2.second == -1);
	});

	Add("Search2", [&]() {
		int A[20];
		for (int i = 0; i < 20; i++) {
			A[i] = 20 - i;
		}

		Test::YoungTableau<int> yt(4, 5, A, 20);
		Logger() << yt;
		ASSERT1(yt.Verify());

		pair<int, int> index;
		pair<int, int> index2;
		for (int i = 1; i <= 20; i++) {
			index = yt.Search(i);
			index2 = yt.Search2(i);
			Logger().WriteInformation("%d is at (%d, %d) (%d, %d)\n", i, index.first, index.second, index2.first, index2.second);
			ASSERT1(index.first == ((i - 1) / 5));
			ASSERT1(index.second == ((i - 1) % 5));
			ASSERT1(index.first == index2.first);
			ASSERT1(index.second == index2.second);
		}

		index = yt.Search(21);
		index2 = yt.Search2(21);
		ASSERT1(index.first == -1);
		ASSERT1(index.second == -1);
		ASSERT1(index2.first == -1);
		ASSERT1(index2.second == -1);
	});

	Add("Search3", [&]() {
		int A[20];
		for (int i = 0; i < 20; i++) {
			A[i] = 20 - i;
		}

		Test::YoungTableau<int> yt(5, 6, A, 20);
		Logger() << yt;
		ASSERT1(yt.Verify());

		pair<int, int> index;
		pair<int, int> index2;
		for (int i = 1; i <= 20; i++) {
			index = yt.Search(i);
			index2 = yt.Search2(i);
			Logger().WriteInformation("%d is at (%d, %d) (%d, %d)\n", i, index.first, index.second, index2.first, index2.second);
			ASSERT1(index.first != -1);
			ASSERT1(index.second != -1);
			ASSERT1(index.first == index2.first);
			ASSERT1(index.second == index2.second);
		}

		index = yt.Search(21);
		index2 = yt.Search2(21);
		ASSERT1(index.first == -1);
		ASSERT1(index.second == -1);
		ASSERT1(index2.first == -1);
		ASSERT1(index2.second == -1);
	});

	Add("Search4", [&]() {
		int A[20];
		for (int i = 0; i < 20; i++) {
			A[i] = 20 - i;
		}

		Test::YoungTableau<int> yt(5, 6, A, 20);
		yt(3, 0) = 21;
		yt(3, 1) = 22;

		Logger() << yt;
		ASSERT1(yt.Verify());

		pair<int, int> index;
		pair<int, int> index2;
		for (int i = 21; i <= 22; i++) {
			index = yt.Search(i);
			index2 = yt.Search2(i);
			Logger().WriteInformation("%d is at (%d, %d) (%d, %d)\n", i, index.first, index.second, index2.first, index2.second);
			ASSERT1(index.first != -1);
			ASSERT1(index.second != -1);
			ASSERT1(index.first == index2.first);
			ASSERT1(index.second == index2.second);
		}

		index = yt.Search(23);
		index2 = yt.Search2(23);
		ASSERT1(index.first == -1);
		ASSERT1(index.second == -1);
		ASSERT1(index2.first == -1);
		ASSERT1(index2.second == -1);
	});

	Add("Search5", [&]() {
		for (int i = 0; i < 100; i++) {
			int len = Test::Random::Next();
			unique_ptr<int[]> A(new int[len]);
			set<int> values;
			for (int j = 0; j < len; j++) {
				int v = Test::Random::Next(1000);
				if (values.find(v) == values.end()) {
					A[j] = v;
					values.insert(v);
				}
			}

			len = values.size();
			int len2 = max(500, len >> 3);
			int cols = Test::Random::Next(1, len2 >> 3);
			int rows = Test::Random::Next(1, (len2 / cols) << 3);
			Logger().WriteInformation("Run %d: YoungTableau (%d x %d) with %d elements.\n", i, rows, cols, len);

			Test::YoungTableau<int> yt(rows, cols, A.get(), len);
			ASSERT1(yt.Verify());

			pair<int, int> index;
			pair<int, int> index2;
			for_each(values.begin(), values.end(), [&](int n){
				index = yt.Search(n);
				index2 = yt.Search2(n);
				Logger().WriteInformation("%d is at (%d, %d) (%d, %d)\n", n, index.first, index.second, index2.first, index2.second);
				ASSERT1(index.first == index2.first);
				ASSERT1(index.second == index2.second);
			});
		}
	});

	Add("CountLessThan1", [&]() {
		int A[20];
		for (int i = 0; i < 20; i++) {
			A[i] = 20 - i;
		}

		Test::YoungTableau<int> yt(1, 20, A, 20);
		Logger() << yt;
		ASSERT1(yt.Verify());

		int count;
		int count2;
		for (int i = 1; i <= 21; i++) {
			count = yt.CountLessThan(i);
			count2 = yt.CountLessThan2(i);
			Logger().WriteInformation("(%d, %d) elements is less than %d\n", count, count2, i);
			ASSERT1(count == i - 1);
			ASSERT1(count2 == i - 1);
		}
	});

	Add("CountLessThan2", [&]() {
		int A[20];
		for (int i = 0; i < 20; i++) {
			A[i] = 20 - i;
		}

		Test::YoungTableau<int> yt(4, 5, A, 20);
		Logger() << yt;
		ASSERT1(yt.Verify());

		int count;
		int count2;
		for (int i = 1; i <= 21; i++) {
			count = yt.CountLessThan(i);
			count2 = yt.CountLessThan2(i);
			Logger().WriteInformation("(%d, %d) elements is less than %d\n", count, count2, i);
			ASSERT1(count == i - 1);
			ASSERT1(count2 == i - 1);
		}
	});

	Add("CountLessThan3", [&]() {
		int A[20];
		for (int i = 0; i < 20; i++) {
			A[i] = 20 - i;
		}

		Test::YoungTableau<int> yt(5, 6, A, 20);
		Logger() << yt;
		ASSERT1(yt.Verify());

		int count;
		int count2;
		for (int i = 1; i <= 21; i++) {
			count = yt.CountLessThan(i);
			count2 = yt.CountLessThan2(i);
			Logger().WriteInformation("(%d, %d) elements is less than %d\n", count, count2, i);
			ASSERT1(count == i - 1);
			ASSERT1(count2 == i - 1);
		}
	});

	Add("CountLessThan4", [&]() {
		for (int i = 0; i < 100; i++) {
			int len = Test::Random::Next(10000);
			unique_ptr<int[]> A(new int[len]);
			set<int> values;
			for (int j = 0; j < len; j++) {
				A[j] = j;
			}

			int cols = Test::Random::Next(1, max(500, len >> 4));
			int rows = len / cols + 1;
			Logger().WriteInformation("Run %d: YoungTableau (%d x %d) with %d elements.\n", i, rows, cols, len);

			Test::YoungTableau<int> yt(rows, cols, A.get(), len);
			ASSERT1(yt.Verify());

			int count;
			int count2;
			for (int j = 0; j < len; j++) {
				count = yt.CountLessThan(A[j]);
				count2 = yt.CountLessThan2(A[j]);
				ASSERT1(count == j);
				ASSERT1(count2 == j);
			}
		}
	});
}