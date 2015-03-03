#include "SortTest.h"

void SortTest::Init()
{
	Add("Sort1", [&](){
		int I[] = { 1 };
		auto check = [&](function<void(int *, size_t l)> sort){
			int J[1];
			J[0] = I[0];
			sort(J, 1);
			ASSERT1(J[0] == 1);
		};
		check([&](int * a, size_t l) { Test::Sort::Insert::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Insert::SortRecursively<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Select::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Merge::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Heap::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Heap::Sort<int>(a, l, 3); });
	});

	Add("Sort2", [&](){
		int I[] = { 2, 1 };
		auto check = [&](function<void(int *, size_t l)> sort){
			int J[2];
			J[0] = I[0];
			J[1] = I[1];
			sort(J, 2);
			ASSERT1(J[0] == 1);
			ASSERT1(J[1] == 2);
			sort(J, 2);
			ASSERT1(J[0] == 1);
			ASSERT1(J[1] == 2);
			J[1] = J[0];
			sort(J, 2);
			ASSERT1(J[0] == 1);
			ASSERT1(J[1] == 1);
		};
		check([&](int * a, size_t l) { Test::Sort::Insert::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Insert::SortRecursively<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Select::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Merge::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Heap::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Heap::Sort<int>(a, l, 3); });
	});

	Add("Sort3", [&](){
		int I[] = { 3, 2, 1 };
		auto check = [&](function<void(int *, size_t l)> sort){
			int J[3];
			J[0] = I[0];
			J[1] = I[1];
			J[2] = I[2];
			sort(J, 3);
			ASSERT1(J[0] == 1);
			ASSERT1(J[1] == 2);
			ASSERT1(J[2] == 3);
			sort(J, 3);
			ASSERT1(J[0] == 1);
			ASSERT1(J[1] == 2);
			ASSERT1(J[2] == 3);
			J[1] = J[0];
			J[2] = J[0];
			sort(J, 3);
			ASSERT1(J[0] == 1);
			ASSERT1(J[1] == 1);
			ASSERT1(J[2] == 1);
		};
		check([&](int * a, size_t l) { Test::Sort::Insert::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Insert::SortRecursively<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Select::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Merge::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Heap::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Heap::Sort<int>(a, l, 3); });
	});

	Add("Sort4", [&](){
		int I[] = { 3, 43, 42, 1, 3, 3556, 7, 34, 8, 8769, 96656532, 1, 445, 35, 64 };
		int L = sizeof(I) / sizeof(I[0]);
		std::vector<int> V;
		for (int i = 0; i < L; i++) {
			V.push_back(I[i]);
		}
		std::sort(V.begin(), V.end());
		auto check = [&](function<void(int *, size_t l)> sort){
			unique_ptr<int[]> J(new int[L]);
			memcpy(J.get(), I, L * sizeof(int));
			sort(J.get(), L);
			for (int i = 0; i < L; i++) {
				ASSERT1(J[i] == V[i]);
			}
		};
		check([&](int * a, size_t l) { Test::Sort::Insert::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Insert::SortRecursively<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Select::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Merge::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Heap::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Heap::Sort<int>(a, l, 3); });
	});

	Add("Sort5", [&](){
		int I[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
		int L = sizeof(I) / sizeof(I[0]);
		std::vector<int> V;
		for (int i = 0; i < L; i++) {
			V.push_back(I[i]);
		}
		std::sort(V.begin(), V.end());
		auto check = [&](function<void(int *, size_t l)> sort){
			unique_ptr<int[]> J(new int[L]);
			memcpy(J.get(), I, L * sizeof(int));
			sort(J.get(), L);
			for (int i = 0; i < L; i++) {
				ASSERT1(J[i] == V[i]);
			}
		};
		check([&](int * a, size_t l) { Test::Sort::Insert::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Insert::SortRecursively<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Select::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Merge::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Heap::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Heap::Sort<int>(a, l, 3); });
	});

	Add("Sort6", [&](){
		int I[] = { 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2 };
		int L = sizeof(I) / sizeof(I[0]);
		std::vector<int> V;
		for (int i = 0; i < L; i++) {
			V.push_back(I[i]);
		}
		std::sort(V.begin(), V.end());
		auto check = [&](function<void(int *, size_t l)> sort){
			unique_ptr<int[]> J(new int[L]);
			memcpy(J.get(), I, L * sizeof(int));
			sort(J.get(), L);
			for (int i = 0; i < L; i++) {
				ASSERT1(J[i] == V[i]);
			}
		};
		check([&](int * a, size_t l) { Test::Sort::Insert::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Insert::SortRecursively<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Select::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Merge::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Heap::Sort<int>(a, l); });
		check([&](int * a, size_t l) { Test::Sort::Heap::Sort<int>(a, l, 3); });
	});

	Add("Sort7", [&](){
		for (int j = 0; j < 100; j++) {
			size_t L = 1 + rand();
			L = min(L, 1000);
			Logger().WriteInformation("Run %d, %d elements\n", j, L);
			unique_ptr<int[]> I(new int[L]);
			std::vector<int> V;
			for (size_t i = 0; i < L; i++) {
				I[i] = rand();
				V.push_back(I[i]);
			}
			std::sort(V.begin(), V.end());
			auto check = [&](function<void(int *, size_t l)> sort){
				unique_ptr<int[]> J(new int[L]);
				memcpy(J.get(), I.get(), L * sizeof(int));
				sort(J.get(), L);
				for (size_t i = 0; i < L; i++) {
					ASSERT1(J[i] == V[i]);
				}
			};
			check([&](int * a, size_t l) { Test::Sort::Insert::Sort<int>(a, l); });
			check([&](int * a, size_t l) { Test::Sort::Insert::SortRecursively<int>(a, l); });
			check([&](int * a, size_t l) { Test::Sort::Select::Sort<int>(a, l); });
			check([&](int * a, size_t l) { Test::Sort::Merge::Sort<int>(a, l); });
			check([&](int * a, size_t l) { Test::Sort::Heap::Sort<int>(a, l); });
			check([&](int * a, size_t l) { Test::Sort::Heap::Sort<int>(a, l, 3); });
		}
	});

	Add("Heapify", [&](){
		for (int j = 0; j < 100; j++) {
			unsigned int length = 1 + rand();
			Logger().WriteInformation("Run %d, %d elements\n", j, length);

			unique_ptr<int[]> i1(new int[length]);
			unique_ptr<int[]> i2(new int[length]);
			for (unsigned int i = 0; i < length; i++) {
				int t = rand();
				i1[i] = t;
				i2[i] = t;
			}

			Test::Sort::Heap::Heapify(i1.get(), length);
			Test::Sort::Heap::ParallelHeapify(i2.get(), length);

			for (unsigned int i = 0; i < length; i++) {
				ASSERT2(i1[i] == i2[i], Test::String::Format("i1[%d] %d != i2[%d] %d", i, i1[i], i, i2[i]));
			}
		}
	});

	Add("DHeapSort", [&](){
		for (int j = 0; j < 100; j++) {
			unsigned int length = 1 + rand();
			unsigned int dimension = Test::Random::Next(2, 100);
			Logger().WriteInformation("Run %d, %d elements, %d-heap\n", j, length, dimension);

			unique_ptr<int[]> a(new int[length]);
			vector<int> v;
			for (unsigned int i = 0; i < length; i++) {
				int t = Test::Random::Next();
				a[i] = t;
				v.push_back(t);
			}

			Test::Sort::Heap::Sort(a.get(), length, dimension);
			std::make_heap(v.begin(), v.end());
			std::sort_heap(v.begin(), v.end());

			for (unsigned int i = 0; i < length; i++) {
				ASSERT2(a[i] == v[i], Test::String::Format("i[%d] %d != v[%d] %d", i, a[i], i, v[i]));
			}
		}
	});

	Add("DHeapify", [&](){
		for (int j = 0; j < 100; j++) {
			unsigned int length = 1 + rand();
			unsigned int dimension = Test::Random::Next(2, min(length, 100));
			Logger().WriteInformation("Run %d, %d elements, %d-heap\n", j, length, dimension);

			unique_ptr<int[]> i1(new int[length]);
			unique_ptr<int[]> i2(new int[length]);
			for (unsigned int i = 0; i < length; i++) {
				int t = rand();
				i1[i] = t;
				i2[i] = t;
			}

			Test::Sort::Heap::Heapify(i1.get(), length, dimension);
			Test::Sort::Heap::ParallelHeapify(i2.get(), length, dimension);

			for (unsigned int i = 0; i < length; i++) {
				ASSERT2(i1[i] == i2[i], Test::String::Format("i1[%d] %d != i2[%d] %d", i, i1[i], i, i2[i]));
			}
		}
	});

	Add("MergeInputs", [&](){
		int * inputs[3];
		size_t sizes[3];

		int a0[] = { 0, 5, 9, 11 };
		inputs[0] = a0;
		sizes[0] = 4;

		int a1[] = { 0, 1, 2, 3, 5, 6 };
		inputs[1] = a1;
		sizes[1] = 6;

		int a2[] = { 6, 7, 8 };
		inputs[2] = a2;
		sizes[2] = 3;

		vector<int> output;

		Test::Sort::Merge::Sort<int>(inputs, sizes, (size_t)3, output);

		ASSERT1(is_sorted(output.begin(), output.end()));
		ASSERT1(output.size() == 13);

		Logger().Print(output);
		Logger().WriteInformation("\n");
	});

	Add("MergeInputs2", [&](){
		for (int i = 0; i < 100; i++) {
			size_t size = 2 + (rand() % 50);
			unique_ptr<int * []> inputs(new int * [size]);
			unique_ptr<size_t[]> sizes(new size_t[size]);
			size_t total = 0;
			for (size_t j = 0; j < size; j++) {
				sizes[j] = 2 + (rand() % 50);
				total += sizes[j];
				inputs[j] = (int *)malloc(sizes[j] * sizeof(int));
				for (size_t k = 0; k < sizes[j]; k++) {
					inputs[j][k] = rand();
				}
				Test::Sort::Merge::Sort(inputs[j], sizes[j]);
			}
			Logger().WriteInformation("Run %d, %d inputs, %d elements\n", i, size, total);
			vector<int> output;
			Test::Sort::Merge::Sort<int>(inputs.get(), sizes.get(), size, output);
			for (size_t j = 0; j < size; j++) {
				delete[] inputs[j];
			}
			ASSERT1(is_sorted(output.begin(), output.end()));
			ASSERT1(output.size() == total);
			Logger().Print(output);
			Logger().WriteInformation("\n");
		}
	});
}