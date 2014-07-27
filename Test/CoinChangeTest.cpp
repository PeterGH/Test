#include "CoinChangeTest.h"

void CoinChangeTest::Init(void)
{
	Add("1", [&](){
		vector<unsigned int> denoms { 1, 3, 4};
		map<unsigned int, unsigned int> changes;
		unsigned int amount = 6;
		Test::CoinChange::ComputeSolution(amount, denoms, changes);
		map<unsigned int, unsigned int>::iterator it;
		Logger().WriteInformation("For amount %d, changes are :\n", amount);
		for (it = changes.begin(); it != changes.end(); it++) {
			Logger().WriteInformation("\tcoint %d, count %d\n", it->first, it->second);
		}

		ASSERT1(changes.size() == 1);
		ASSERT1(changes[3] == 2);
	});

	Add("2", [&](){
		vector<unsigned int> denoms { 1, 5, 10, 25};
		for (int i = 0; i < 100; i ++) {
			unsigned int amount = Test::Random::Next(1, 1000);
			map<unsigned int, unsigned int> changes1;
			map<unsigned int, unsigned int> changes2;
			Test::CoinChange::ComputeSolution(amount, denoms, changes1);
			Test::CoinChange::GreedySolution(amount, denoms, changes2);

			ASSERT1(changes1.size() == changes2.size());

			map<unsigned int, unsigned int>::iterator it;
			Logger().WriteInformation("Run %d, amount %d, changes are :\n", i, amount);
			for (it = changes1.begin(); it != changes1.end(); it++) {
				Logger().WriteInformation("\tcoint %d, count %d\n", it->first, it->second);
				ASSERT1(it->second == changes2[it->first]);
			}
		}
	});

	Add("AllSolutions", [&](){
		auto check = [&](unsigned int sum, vector<unsigned int> & denoms, unsigned int count) {
			vector<map<unsigned int, unsigned int>> solutions;
			Test::CoinChange::ComputeAllSolutions(sum, denoms, solutions);
			Logger().WriteInformation("Sum %d numbers:", sum);
			for_each (denoms.begin(), denoms.end(), [&](unsigned int d){
				Logger().WriteInformation("  %d", d);
			});
			Logger().WriteInformation("\n");
			for_each (solutions.begin(), solutions.end(), [&](map<unsigned int, unsigned int> & m){
				Logger().WriteInformation("  %d = ", sum);
				int i = 0;
				for_each (m.begin(), m.end(), [&](pair<unsigned int, unsigned int> p) {
					if (i != 0) {
						Logger().WriteInformation(" + ");
					}
					Logger().WriteInformation("%d x %d", p.second, p.first);
					i++;
				});
				Logger().WriteInformation("\n");
			});
			ASSERT1(solutions.size() == count);
		};

		vector<unsigned int> denoms { 2, 3, 6, 7 };
		check(7, denoms, 2);
	});
}