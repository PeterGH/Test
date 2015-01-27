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
		}
	});
}