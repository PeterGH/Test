#include "CoinChange.h"
namespace Test {
	// Given an amount n and a set of coin denominations:
	// d_0, d_1, d_2, ......, d_(k-1)
	// The minimum count of coins to make up n:
	// N(n) = 1 + min{N(n - d_0), N(n - d_1), ..., N(n - d_(k-1))}
	void CoinChange::ComputeMinCounts(unsigned int amount, vector<unsigned int> & denominations, vector<pair<unsigned int, unsigned int>> & counts)
	{
		// Sort coins increasingly
		sort(denominations.begin(), denominations.end());		
		counts.push_back(make_pair(0, 0));
		counts.push_back(make_pair(1, 1));
		for (unsigned int i = 2; i <= amount; i++) {
			unsigned int minCount = amount;
			unsigned int change;
			unsigned int j = 0;
			while (j < denominations.size() && denominations[j] <= i) {
				if (counts[i - denominations[j]].first < minCount) {
					minCount = counts[i - denominations[j]].first;
					change = denominations[j];
				}

				j++;
			}

			counts.push_back(make_pair(1 + minCount, change));
		}
	}

	void CoinChange::ComputeSolution(unsigned int amount, vector<unsigned int> & denominations, map<unsigned int, unsigned int> & changes)
	{
		vector<pair<unsigned int, unsigned int>> minCounts;
		ComputeMinCounts(amount, denominations, minCounts);
		int i = amount;
		while (i > 0) {
			unsigned int c = minCounts[i].second;
			if (changes.find(c) == changes.end()) {
				changes[c] = 1;
			} else {
				changes[c]++;
			}

			i -= (int)c;
		}
	}

	unsigned int CoinChange::GreedySolution(unsigned int amount, vector<unsigned int> & denominations, map<unsigned int, unsigned int> & changes)
	{
		function<bool(unsigned int, unsigned int)> greater = [&](unsigned int first, unsigned int second)->bool{
			return first > second;
		};

		// Sort in decreasing order
		sort(denominations.begin(), denominations.end(), greater);

		for_each (denominations.begin(), denominations.end(), [&](unsigned int d){
			if (amount == 0) return;

			if (amount >= d) {
				unsigned int count = amount / d;
				changes[d] = count;
				amount = amount % d;
			}
		});

		// Return what ever cannot be changed, e.g. the minimum denomination is not 1.
		return amount;
	}
}