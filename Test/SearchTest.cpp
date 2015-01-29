#include "SearchTest.h"

void SearchTest::Init()
{
	Add("Search", [&](){
		int I[] = { 1, 1, 3, 3, 7, 8, 34, 35, 42, 43, 64, 445, 3556, 8769, 96656532 };
		int L = sizeof(I) / sizeof(I[0]);
		ASSERT1(0 == Search::BinarySearch<int>(1, I, 1));
		ASSERT1(0 == Search::BinarySearch<int>(1, I, 1, false));
		ASSERT1(1 == Search::BinarySearch<int>(1, I, 2, false));

		ASSERT1(0 == Search::BinarySearchRecursively<int>(1, I, 0, 0));
		ASSERT1(0 == Search::BinarySearchRecursively<int>(1, I, 0, 0, false));

		ASSERT1(0 == Search::BinarySearchRecursively<int>(1, I, 0, 1));
		ASSERT1(1 == Search::BinarySearchRecursively<int>(1, I, 0, 1, false));
		ASSERT1(1 == Search::BinarySearchRecursively<int>(1, I, 0, 2, false));

		ASSERT1(0 == Search::BinarySearch<int>(1, I, L));
		ASSERT1(1 != Search::BinarySearch<int>(1, I, L));
		ASSERT1(1 == Search::BinarySearch<int>(1, I, L, false));

		ASSERT1(0 == Search::BinarySearchRecursively<int>(1, I, 0, L - 1));
		ASSERT1(1 != Search::BinarySearchRecursively<int>(1, I, 0, L - 1));
		ASSERT1(1 == Search::BinarySearchRecursively<int>(1, I, 0, L - 1, false));

		ASSERT1(2 == Search::BinarySearch<int>(3, I, L));
		ASSERT1(3 != Search::BinarySearch<int>(3, I, L));
		ASSERT1(3 == Search::BinarySearch<int>(3, I, L, false));

		ASSERT1(2 == Search::BinarySearchRecursively<int>(3, I, 0, L - 1));
		ASSERT1(3 != Search::BinarySearchRecursively<int>(3, I, 0, L - 1));
		ASSERT1(3 == Search::BinarySearchRecursively<int>(3, I, 0, L - 1, false));

		ASSERT1(9 == Search::BinarySearch<int>(43, I, L));
		ASSERT1(9 == Search::BinarySearch<int>(43, I, L, false));
		ASSERT1(9 == Search::BinarySearchRecursively<int>(43, I, 0, L - 1));
		ASSERT1(9 == Search::BinarySearchRecursively<int>(43, I, 0, L - 1, false));

		ASSERT1(L - 1 == Search::BinarySearch<int>(96656532, I, L));
		ASSERT1(L - 1 == Search::BinarySearch<int>(96656532, I, L, false));
		ASSERT1(L - 1 == Search::BinarySearchRecursively<int>(96656532, I, 0, L - 1));
		ASSERT1(L - 1 == Search::BinarySearchRecursively<int>(96656532, I, 0, L - 1, false));

		ASSERT1(-1 == Search::BinarySearch<int>(222, I, L));
		ASSERT1(-1 == Search::BinarySearchRecursively<int>(222, I, 0, L - 1));
	});

	Add("Insert", [&](){
		int I[] = { 1, 1, 3, 3, 7, 8, 34, 35, 42, 43, 64, 445, 3556, 8769, 96656532 };
		int L = sizeof(I) / sizeof(I[0]);
		ASSERT1(-1 == Test::Search::FindPositionToInsert<int>(0, I, 1));
		ASSERT1(-1 == Test::Search::FindPositionToInsert<int>(0, I, 2));
		ASSERT1(-1 == Test::Search::FindPositionToInsert<int>(0, I, L));

		ASSERT1(-1 == Test::Search::FindPositionToInsert<int>(0, I, 1, false));
		ASSERT1(-1 == Test::Search::FindPositionToInsert<int>(0, I, 2, false));
		ASSERT1(-1 == Test::Search::FindPositionToInsert<int>(0, I, L, false));

		ASSERT1(-1 == Test::Search::FindPositionToInsert<int>(1, I, 1));
		ASSERT1(-1 == Test::Search::FindPositionToInsert<int>(1, I, 2));
		ASSERT1(-1 == Test::Search::FindPositionToInsert<int>(1, I, L));

		ASSERT1(0 == Test::Search::FindPositionToInsert<int>(1, I, 1, false));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(1, I, 2, false));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(1, I, L, false));

		ASSERT1(0 == Test::Search::FindPositionToInsert<int>(2, I, 1));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(2, I, 2));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(2, I, 3));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(2, I, L));

		ASSERT1(0 == Test::Search::FindPositionToInsert<int>(2, I, 1, false));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(2, I, 2, false));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(2, I, 3, false));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(2, I, L, false));

		ASSERT1(0 == Test::Search::FindPositionToInsert<int>(3, I, 1));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(3, I, 2));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(3, I, 3));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(3, I, L));

		ASSERT1(0 == Test::Search::FindPositionToInsert<int>(3, I, 1, false));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(3, I, 2, false));
		ASSERT1(2 == Test::Search::FindPositionToInsert<int>(3, I, 3, false));
		ASSERT1(3 == Test::Search::FindPositionToInsert<int>(3, I, L, false));

		ASSERT1(0 == Test::Search::FindPositionToInsert<int>(4, I, 1));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(4, I, 2));
		ASSERT1(2 == Test::Search::FindPositionToInsert<int>(4, I, 3));
		ASSERT1(3 == Test::Search::FindPositionToInsert<int>(4, I, 4));
		ASSERT1(3 == Test::Search::FindPositionToInsert<int>(4, I, L));

		ASSERT1(0 == Test::Search::FindPositionToInsert<int>(4, I, 1, false));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(4, I, 2, false));
		ASSERT1(2 == Test::Search::FindPositionToInsert<int>(4, I, 3, false));
		ASSERT1(3 == Test::Search::FindPositionToInsert<int>(4, I, 4, false));
		ASSERT1(3 == Test::Search::FindPositionToInsert<int>(4, I, L, false));

		ASSERT1(7 == Test::Search::FindPositionToInsert<int>(42, I, 8));
		ASSERT1(7 == Test::Search::FindPositionToInsert<int>(42, I, 9));
		ASSERT1(7 == Test::Search::FindPositionToInsert<int>(42, I, 10));
		ASSERT1(7 == Test::Search::FindPositionToInsert<int>(42, I, L));

		ASSERT1(7 == Test::Search::FindPositionToInsert<int>(42, I, 8, false));
		ASSERT1(8 == Test::Search::FindPositionToInsert<int>(42, I, 9, false));
		ASSERT1(8 == Test::Search::FindPositionToInsert<int>(42, I, 10, false));
		ASSERT1(8 == Test::Search::FindPositionToInsert<int>(42, I, L, false));

		ASSERT1(9 == Test::Search::FindPositionToInsert<int>(50, I, 10));
		ASSERT1(9 == Test::Search::FindPositionToInsert<int>(50, I, 11));
		ASSERT1(9 == Test::Search::FindPositionToInsert<int>(50, I, L));

		ASSERT1(9 == Test::Search::FindPositionToInsert<int>(50, I, 10, false));
		ASSERT1(9 == Test::Search::FindPositionToInsert<int>(50, I, 11, false));
		ASSERT1(9 == Test::Search::FindPositionToInsert<int>(50, I, L, false));
	});

	Add("TwoSum1", [&](){
		std::vector<pair<int, int>> pairs, pairs2, pairs3, pairs4;
		int I[][1] = { { -1 }, { 0 }, { 1 } };
		int S[] = { -1, 0, 1 };
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				Test::Search::TwoSum<int>(I[i], 1, S[j], pairs);
				Test::Search::TwoSum2<int>(I[i], 1, S[j], pairs2);
				Test::Search::TwoSum3<int>(I[i], 1, S[j], pairs3);
				Test::Search::TwoSum4<int>(I[i], 1, S[j], pairs4);
				ASSERT1(pairs.size() == 0);
				ASSERT1(pairs2.size() == 0);
				ASSERT1(pairs3.size() == 0);
				ASSERT1(pairs4.size() == 0);
			}
		}
	});

	Add("TwoSum2", [&](){
		int I[][2] = { { -3, -1 }, { -2, -2 }, { -4, 0 }, { 1, -5 } };
		int S[] = { 0, -1, -2, -3, -5, -6, -7, -8 };
		auto check = [&](function<void(int *, int, int, vector<pair<int, int>> &)> f){
			int J[4][2];
			memcpy(J, I, 8 * sizeof(int));
			for (int j = 0; j < 4; j++) {
				std::vector<pair<int, int>> pairs;
				for (int i = 0; i < 8; i++) {
					f(J[j], 2, S[i], pairs);
					ASSERT1(pairs.size() == 0);
				}
				f(J[j], 2, -4, pairs);
				for_each(pairs.begin(), pairs.end(), [&](pair<int, int> p){
					Logger().WriteInformation("I[%d] + I[%d] = %d + %d = %d\n", p.first, p.second, J[j][p.first], J[j][p.second], J[j][p.first] + J[j][p.second]);
				});
				ASSERT1(pairs.size() == 1);
				ASSERT1(J[j][pairs[0].first] + J[j][pairs[0].second] == -4);
			}
		};
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum<int>(input, length, sum, indices); });
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum2<int>(input, length, sum, indices); });
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum3<int>(input, length, sum, indices); });
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum4<int>(input, length, sum, indices); });
	});

	Add("TwoSum3", [&](){
		int I[][2] = { { 3, 1 }, { 2, 2 }, { 4, 0 }, { -1, 5 } };
		int S[] = { 0, 1, 2, 3, 5, 6, 7, 8 };
		auto check = [&](function<void(int *, int, int, vector<pair<int, int>> &)> f){
			int J[4][2];
			memcpy(J, I, 8 * sizeof(int));
			for (int j = 0; j < 4; j++) {
				std::vector<pair<int, int>> pairs;
				for (int i = 0; i < 8; i++) {
					f(J[j], 2, S[i], pairs);
					ASSERT1(pairs.size() == 0);
				}
				f(J[j], 2, 4, pairs);
				for_each(pairs.begin(), pairs.end(), [&](pair<int, int> p){
					Logger().WriteInformation("I[%d] + I[%d] = %d + %d = %d\n", p.first, p.second, J[j][p.first], J[j][p.second], J[j][p.first] + J[j][p.second]);
				});
				ASSERT1(pairs.size() == 1);
				ASSERT1(J[j][pairs[0].first] + J[j][pairs[0].second] == 4);
			}
		};
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum<int>(input, length, sum, indices); });
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum2<int>(input, length, sum, indices); });
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum3<int>(input, length, sum, indices); });
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum4<int>(input, length, sum, indices); });
	});

	Add("TwoSum4", [&](){
		int I[][2] = { { 0, 0 }, { -1, 1 }, { 2, -2 }, { 3, -3 }, { -4, 4 } };
		int S[] = { -9, -8, -7, -6, -5, -4, -3, -2, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		auto check = [&](function<void(int *, int, int, vector<pair<int, int>> &)> f){
			int J[5][2];
			memcpy(J, I, 10 * sizeof(int));
			for (int j = 0; j < 5; j++) {
				std::vector<pair<int, int>> pairs;
				for (int i = 0; i < 18; i++) {
					f(J[j], 2, S[i], pairs);
					ASSERT1(pairs.size() == 0);
				}
				f(J[j], 2, 0, pairs);
				for_each(pairs.begin(), pairs.end(), [&](pair<int, int> p){
					Logger().WriteInformation("I[%d] + I[%d] = %d + %d = %d\n", p.first, p.second, J[j][p.first], J[j][p.second], J[j][p.first] + J[j][p.second]);
				});
				ASSERT1(pairs.size() == 1);
				ASSERT1(J[j][pairs[0].first] + J[j][pairs[0].second] == 0);
			}
		};
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum<int>(input, length, sum, indices); });
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum2<int>(input, length, sum, indices); });
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum3<int>(input, length, sum, indices); });
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum4<int>(input, length, sum, indices); });
	});

	Add("TwoSum5", [&](){
		int I[][3] = { { -3, -2, -1 }, { -4, -2, -1 }, { -5, 1, 0 }, { 1, 0, -6 }, { 1, 2, -7 } };
		int S[] = { -1, -2, -7, -8, -9, -10, -11, -12, -13, -14, -15 };
		auto check = [&](function<void(int *, int, int, vector<pair<int, int>> &)> f){
			int J[5][3];
			memcpy(J, I, 15 * sizeof(int));
			for (int j = 0; j < 5; j++) {
				std::vector<pair<int, int>> pairs;
				for (int i = 0; i < 11; i++) {
					f(J[j], 3, S[i], pairs);
					ASSERT1(pairs.size() == 0);
				}
				f(J[j], 3, -5, pairs);
				for_each(pairs.begin(), pairs.end(), [&](pair<int, int> p){
					Logger().WriteInformation("I[%d] + I[%d] = %d + %d = %d\n", p.first, p.second, J[j][p.first], J[j][p.second], J[j][p.first] + J[j][p.second]);
				});
				ASSERT1(pairs.size() == 1);
				ASSERT1(J[j][pairs[0].first] + J[j][pairs[0].second] == -5);
			}
		};
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum<int>(input, length, sum, indices); });
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum2<int>(input, length, sum, indices); });
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum3<int>(input, length, sum, indices); });
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum4<int>(input, length, sum, indices); });
	});

	Add("TwoSum6", [&](){
		int I[][3] = { { 3, 2, 1 }, { 4, 2, 1 }, { 5, -1, 0 }, { -1, 0, 6 }, { -1, -2, 7 } };
		int S[] = { 1, 2, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
		auto check = [&](function<void(int *, int, int, vector<pair<int, int>> &)> f){
			int J[5][3];
			memcpy(J, I, 15 * sizeof(int));
			for (int j = 0; j < 5; j++) {
				std::vector<pair<int, int>> pairs;
				for (int i = 0; i < 11; i++) {
					f(J[j], 3, S[i], pairs);
					ASSERT1(pairs.size() == 0);
				}
				f(J[j], 3, 5, pairs);
				for_each(pairs.begin(), pairs.end(), [&](pair<int, int> p){
					Logger().WriteInformation("I[%d] + I[%d] = %d + %d = %d\n", p.first, p.second, J[j][p.first], J[j][p.second], J[j][p.first] + J[j][p.second]);
				});
				ASSERT1(pairs.size() == 1);
				ASSERT1(J[j][pairs[0].first] + J[j][pairs[0].second] == 5);
			}
		};
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum<int>(input, length, sum, indices); });
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum2<int>(input, length, sum, indices); });
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum3<int>(input, length, sum, indices); });
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum4<int>(input, length, sum, indices); });
	});

	Add("TwoSum7", [&](){
		int I[][3] = { { 0, 1, 0 }, { 0, -1, 0 }, { -1, 0, 1 }, { 0, 2, -2 }, { 3, -3, 0 }, { -4, 0, 4 } };
		int S[] = { -9, -8, -7, -6, -5, 5, 6, 7, 8, 9 };
		auto check = [&](function<void(int *, int, int, vector<pair<int, int>> &)> f){
			int J[6][3];
			memcpy(J, I, 18 * sizeof(int));
			for (int j = 0; j < 6; j++) {
				std::vector<pair<int, int>> pairs;
				for (int i = 0; i < 10; i++) {
					f(J[j], 3, S[i], pairs);
					ASSERT1(pairs.size() == 0);
				}
				f(J[j], 3, 0, pairs);
				for_each(pairs.begin(), pairs.end(), [&](pair<int, int> p){
					Logger().WriteInformation("I[%d] + I[%d] = %d + %d = %d\n", p.first, p.second, J[j][p.first], J[j][p.second], J[j][p.first] + J[j][p.second]);
				});
				ASSERT1(pairs.size() == 1);
				ASSERT1(J[j][pairs[0].first] + J[j][pairs[0].second] == 0);
			}
		};
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum<int>(input, length, sum, indices); });
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum2<int>(input, length, sum, indices); });
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum3<int>(input, length, sum, indices); });
		check([&](int * input, int length, int sum, vector<pair<int, int>> & indices){ Test::Search::TwoSum4<int>(input, length, sum, indices); });
	});

	Add("TwoSum8", [&](){
		vector<LONGLONG> times1, times2, times3, times4;

		for (int j = 0; j < 100; j++) {
			int length = 1 + rand();
			int size = length * sizeof(long);

			unique_ptr<long[]> input(new long[length]);
			unique_ptr<long[]> input1(new long[length]);
			unique_ptr<long[]> input2(new long[length]);
			unique_ptr<long[]> input3(new long[length]);
			unique_ptr<long[]> input4(new long[length]);

			int bias = RAND_MAX >> 1;
			long min = 0;
			long max = 0;
			for (int i = 0; i < length; i++) {
				int t = rand() - bias;
				input[i] = t;
				if (t < min) min = t;
				if (t > max) max = t;
			}

			min = min << 1;
			max = max << 1;
			int loops = 10;
			int delta = (max - min) / loops;

			LONGLONG ticks, time1, time2, time3, time4;
			function<LONGLONG(void)> GetTicks = [&](void)->LONGLONG{
				LARGE_INTEGER t;
				if (!QueryPerformanceCounter(&t)) t.QuadPart = 0;
				return t.QuadPart;
			};

			vector<pair<int, int>> pairs1, pairs2, pairs3, pairs4;
			for (long s = min; s <= max; s += delta) {
				memcpy_s(input1.get(), size, input.get(), size);
				ticks = GetTicks();
				Test::Search::TwoSum<long>(input1.get(), length, s, pairs1);
				time1 = GetTicks() - ticks;
				times1.push_back(time1);
				for_each(pairs1.begin(), pairs1.end(), [&](pair<int, int> p){
					ASSERT2(
						input1[p.first] + input1[p.second] == s,
						Test::String::Format(
						"input1[%d] + input1[%d] = %d + %d = %d != %d\n",
						p.first, p.second, input1[p.first], input1[p.second], input1[p.first] + input1[p.second], s));
				});

				memcpy_s(input2.get(), size, input.get(), size);
				ticks = GetTicks();
				Test::Search::TwoSum2<long>(input2.get(), length, s, pairs2);
				time2 = GetTicks() - ticks;
				times2.push_back(time2);
				for_each(pairs2.begin(), pairs2.end(), [&](pair<int, int> p){
					ASSERT2(
						input2[p.first] + input2[p.second] == s,
						Test::String::Format(
						"input2[%d] + input2[%d] = %d + %d = %d != %d\n",
						p.first, p.second, input2[p.first], input2[p.second], input2[p.first] + input2[p.second], s));
				});

				memcpy_s(input3.get(), size, input.get(), size);
				ticks = GetTicks();
				Test::Search::TwoSum3<long>(input3.get(), length, s, pairs3);
				time3 = GetTicks() - ticks;
				times3.push_back(time3);
				for_each(pairs3.begin(), pairs3.end(), [&](pair<int, int> p){
					ASSERT2(
						input3[p.first] + input3[p.second] == s,
						Test::String::Format(
						"input3[%d] + input3[%d] = %d + %d = %d != %d\n",
						p.first, p.second, input3[p.first], input3[p.second], input3[p.first] + input3[p.second], s));
				});

				memcpy_s(input4.get(), size, input.get(), size);
				ticks = GetTicks();
				Test::Search::TwoSum4<long>(input4.get(), length, s, pairs4);
				time4 = GetTicks() - ticks;
				times4.push_back(time4);
				for_each(pairs4.begin(), pairs4.end(), [&](pair<int, int> p){
					ASSERT2(
						input4[p.first] + input4[p.second] == s,
						Test::String::Format(
						"input4[%d] + input4[%d] = %d + %d = %d != %d\n",
						p.first, p.second, input4[p.first], input4[p.second], input4[p.first] + input4[p.second], s));
				});

				ASSERT2(
					pairs1.size() == pairs2.size(),
					Test::String::Format("input1 has %d pairs sumed up to %d, but input2 has %d pairs\n", pairs1.size(), s, pairs2.size()));
				ASSERT2(
					pairs1.size() == pairs3.size(),
					Test::String::Format("input1 has %d pairs sumed up to %d, but input3 has %d pairs\n", pairs1.size(), s, pairs3.size()));
				ASSERT2(
					pairs1.size() == pairs4.size(),
					Test::String::Format("input1 has %d pairs sumed up to %d, but input4 has %d pairs\n", pairs1.size(), s, pairs4.size()));

				if (pairs1.size() != 0 || pairs2.size() != 0 || pairs3.size() != 0 || pairs4.size() != 0) {
					Logger().WriteInformation(
						"Run %d, %d elements, sum %d, pairs1 %d (time1 %I64d), pairs2 %d (time2 %I64d), pairs3 %d (time3 %I64d), pairs4 %d (time4 %I64d)\n",
						j, length, s, pairs1.size(), time1, pairs2.size(), time2, pairs3.size(), time3, pairs4.size(), time4);
					pairs1.clear();
					pairs2.clear();
					pairs3.clear();
					pairs4.clear();
				}
			}
		}

		int count1 = 0;
		int count2 = 0;
		int count3 = 0;
		int count4 = 0;
		for (size_t i = 0; i < times1.size(); i++) {
			int j = 1;
			LONGLONG m = times1[i];
			if (times2[i] < m) {
				j = 2;
				m = times2[i];
			}
			if (times3[i] < m) {
				j = 3;
				m = times3[i];
			}
			if (times4[i] < m) {
				j = 4;
				m = times4[i];
			}
			switch (j) {
			case 1:
				count1++;
				break;
			case 2:
				count2++;
				break;
			case 3:
				count3++;
				break;
			case 4:
				count4++;
				break;
			default:
				break;
			}
		}

		Logger().WriteInformation("In total %d runs, fastest runs per method are (TwoSum %d, TwoSum2 %d, TwoSum3 %d, TwoSum4 %d)\n", times1.size(), count1, count2, count3, count4);
	});
}