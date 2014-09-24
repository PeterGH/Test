#include "BreakStringTest.h"

void BreakStringTest::Init(void)
{
	Add("1", [&](){
		int positions[] = {0, 2, 8, 10, 20};
		Matrix<pair<int, int>> cost(5, 5);
		BreakString::ComputeCostTable(positions, 5, cost);
		Logger().Print(positions, 5);
		auto print = [&](Log & l, pair<int,int> &p) {
			l.WriteInformation("(%d, %d)", p.first, p.second);
		};
		Logger().Print<pair<int,int>>(cost, print);

		vector<int> breaks;
		int totalCost = Test::BreakString::ComputeBreaks(positions, 5, breaks);
		Logger().WriteInformation("Cost: %d\n", totalCost);
		Logger().WriteInformation("Breaks: ");
		Logger().Print(breaks);
	});
}