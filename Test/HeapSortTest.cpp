#include "HeapSortTest.h"

void HeapSortTest::Init(void)
{
	Add("Sort 1", [&](){
		int I[] = { 3 };
		Test::HeapSort::Sort(I, 1);
		ASSERT1(I[0] == 3);
	});

	Add("Sort 2", [&](){
		int I[] = { 3, 1 };
		Test::HeapSort::Sort(I, 2);
		ASSERT1(I[0] == 1);
		ASSERT1(I[1] == 3);
	});

	Add("Sort 3", [&](){
		int I[] = { -3, -1 };
		Test::HeapSort::Sort(I, 2);
		ASSERT1(I[0] == -3);
		ASSERT1(I[1] == -1);
	});

	Add("Sort 4", [&](){
		int I[] = { 3, 43, 42, 1, 3, 3556, 7, 34, 8, 8769, 96656532, 1, 445, 35, 64 };
		int L = sizeof(I) / sizeof(I[0]);

		std::vector<int> V;
		for (int i = 0; i < L; i++) {
			V.push_back(I[i]);
		}

		Test::HeapSort::Sort(I, L);

		std::make_heap(V.begin(), V.end());
		std::sort_heap(V.begin(), V.end());

		for (int i = 0; i < L; i++) {
			ASSERT1(V[i] == I[i]);
		}
	});

	Add("Sort Random", [&](){
		for (int j = 0; j < 100; j++) {
			unsigned int length = (unsigned int)Test::Random::Next();
			Logger().WriteInformation("Run %d, %d elements\n", j, length);

			unique_ptr<int[]> a(new int[length]);
			vector<int> v;
			for (unsigned int i = 0; i < length; i++) {
				int t = Test::Random::Next();
				a[i] = t;
				v.push_back(t);
			}

			Test::HeapSort::Sort(a.get(), length);
			std::make_heap(v.begin(), v.end());
			std::sort_heap(v.begin(), v.end());

			for (unsigned int i = 0; i < length; i++) {
				ASSERT2(a[i] == v[i], Test::String::Format("i[%d] %d != v[%d] %d", i, a[i], i, v[i]));
			}
		}
	});

	Add("Heapify", [&](){
		for (int j = 0; j < 100; j++) {
			unsigned int length = (unsigned int)Test::Random::Next();
			Logger().WriteInformation("Run %d, %d elements\n", j, length);

			unique_ptr<int[]> i1(new int[length]);
			unique_ptr<int[]> i2(new int[length]);
			for (unsigned int i = 0; i < length; i++) {
				int t = Test::Random::Next();
				i1[i] = t;
				i2[i] = t;
			}

			Test::HeapSort::Heapify(i1.get(), length);
			Test::HeapSort::ParallelHeapify(i2.get(), length);

			for (unsigned int i = 0; i < length; i++) {
				ASSERT2(i1[i] == i2[i], Test::String::Format("i1[%d] %d != i2[%d] %d", i, i1[i], i, i2[i]));
			}
		}
	});
}