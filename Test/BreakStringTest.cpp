#include "BreakStringTest.h"

void BreakStringTest::Init(void)
{
	Add("1", [&](){
		int positions[] = {0, 2, 8, 10, 20};
		Test::Array2D<pair<int, int>> cost(5, 5);
		Test::BreakString::ComputeCostTable(positions, 5, cost);
		for (int i = 0; i < 5; i++) {
			cout << "\t" << positions[i];
		}

		cout << endl;
		cost.Print([&](pair<int,int> & p){ cout << "(" << p.first << ", " << p.second << ")"; });

		vector<int> breaks;
		int totalCost = Test::BreakString::ComputeBreaks(positions, 5, breaks);
		cout << "Cost: " << totalCost << endl;
		cout << "Breaks: ";
		for_each(breaks.begin(), breaks.end(), [&](int i){
			cout << " " << i;
		});

		cout << endl;
	});
}