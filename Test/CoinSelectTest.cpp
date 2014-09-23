#include "CoinSelectTest.h"

void CoinSelectTest::Init()
{
	Add("1", [&](){
		auto check = [&](int * input, int length){
			Logger().WriteInformation("Input:");
			Logger().Print(input, length);

			auto print = [&](int value, vector<int> & indices){
				Logger().WriteInformation("\tMax value:\t  %d\n", value);
				Logger().WriteInformation("\tIndices:\t");
				Logger().Print(indices);
				Logger().WriteInformation("\tItems:\t");
				Logger().Print<int>(indices, [&](Log & l, int i){
					l.WriteInformation("%d", input[i]);
				});
			};

			vector<int> indices;
			vector<int> indices2;
			int v = CoinSelect::MaxSelection(input, length, indices);
			Logger().WriteInformation("Solution 1\n");
			print(v, indices);
			int v2 = CoinSelect::MaxSelection2(input, length, indices2);
			Logger().WriteInformation("Solution 2\n");
			print(v2, indices2);

			ASSERT1(v == v2);
			ASSERT1(indices.size() == indices2.size());
			for (unsigned int i = 0; i < indices.size(); i++) {
				ASSERT1(indices[i] == indices2[i]);
			}
		};

		int c[] = { 3, 2, 2, 3, 1, 2 };
		int l = sizeof(c) / sizeof(c[0]);
		check(c, l);

		int c2[] = { 3, 2, 2, 3, 1, 2, 1 };
		int l2 = sizeof(c2) / sizeof(c2[0]);
		check(c2, l2);

		for (int i = 0; i < 100; i++) {
			int length = 1 + Test::Random::Next(100);
			unique_ptr<int[]> input(new int[length]);
			for (int j = 0; j < length; j++) {
				input[j] = Test::Random::Next();
			}
			Logger().WriteInformation("Run %d: %d elements\n", i, length);
			check(input.get(), length);
		}
	});
}