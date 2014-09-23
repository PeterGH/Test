#include "KnapsackTest.h"

void KnapsackTest::Init(void)
{
	Add("Knapsack", [&]() {
		vector<pair<int,int>> items;
		items.push_back(make_pair(60, 2));
		items.push_back(make_pair(100, 4));
		items.push_back(make_pair(120, 6));
		Matrix<int> values(3, 11);
		Test::Knapsack::PrintSolution(items, values);
	});

	Add("Same weight", [&]() {
		vector<pair<int,int>> items;
		items.push_back(make_pair(60, 2));
		items.push_back(make_pair(100, 2));
		items.push_back(make_pair(120, 6));
		Matrix<int> values(3, 11);
		Test::Knapsack::ComputeValues(items, values);
		Test::Knapsack::PrintSolution(items, values);
	});
}