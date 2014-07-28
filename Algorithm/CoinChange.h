#pragma once
#include <algorithm>
#include <functional>
#include <map>
#include <vector>
using namespace std;
namespace Test {
	class __declspec(dllexport) CoinChange {
	public:
		CoinChange() {}
		~CoinChange() {}
		static void ComputeMinCounts(unsigned int amount, vector<unsigned int> & denominations, vector<pair<unsigned int, unsigned int>> & minCounts);
		static void ComputeSolution(unsigned int amount, vector<unsigned int> & denominations, map<unsigned int, unsigned int> & changes);
		static unsigned int GreedySolution(unsigned int amount, vector<unsigned int> & denominations, map<unsigned int, unsigned int> & changes);
		static void ComputeAllSolutions(unsigned int amount, vector<unsigned int> & denominations, vector<map<unsigned int, unsigned int>> & changes);
		static void ComputeSubSetSolutions(unsigned int amount, vector<unsigned int> & denominations, vector<map<unsigned int, unsigned int>> & changes);
	};
}