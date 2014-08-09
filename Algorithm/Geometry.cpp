#include "Geometry.h"

namespace Test {
	bool Geometry::IsOverlap(const Range & r1, const Range & r2)
	{
		// Non-overlap r1.second <= r2.first || r2.second <= r1.first;
		return r1.first < r2.second && r2.first < r1.second;
	}

	bool Geometry::IsOverlap(const Rectangle & r1, const Rectangle & r2)
	{
		// r1 and r2 overlaps if their projections onto x-axis and y-axis overlap
		// [r1.first.first, r1.second.first] and [r2.first.first, r2.second.first] overlaps.
		// [r1.second.second, r1.first.second] and [r2.second.second, r2.first.second] overlaps.
		return r1.first.first < r2.second.first && r2.first.first < r1.second.first
			&& r1.second.second < r2.first.second && r2.second.second < r1.first.second;
	}

	// slope = (p1.y - p0.y) / (p1.x - p0.x)
	// Reduce the slope so that the numerator and denominator are co-prime
	// Return a pair <deltaX, deltaY> after reduction
	pair<int, int> Geometry::NomalizeSlope(const IntPoint & p0, const IntPoint & p1)
	{
		int dX = p1.x - p0.x;
		int dY = p1.y - p0.y;
		int gcd = Math::GreatestCommonDivisor(dX, dY);
		dX = dX / gcd;
		dY = dY / gcd;
		return make_pair(dX, dY);
	}

	// Find a line containing maximum number of points
	int Geometry::MaxPointsOnALine(vector<IntPoint> & points, set<IntPoint> & output)
	{
		if (points.size() <= 1) {
			output.clear();
			output.insert(points.begin(), points.end());
			return points.size();
		}

		sort(points.begin(), points.end());

		map<pair<int, int>, vector<pair<IntPoint, IntPoint>>> slopes;
		for (size_t i = 0; i < points.size() - 1; i++) {
			for (size_t j = i + 1; j < points.size(); j++) {
				if (points[i] == points[j]) {
					// Ignore duplication
					continue;
				}

				pair<int, int> slope = NomalizeSlope(points[i], points[j]);

				// Treat vertical line specially
				if (slope.first == 0) slope.second = 1;
				// Treat horizontal line specially
				if (slope.second == 0) slope.first = 1;

				if (slopes.find(slope) == slopes.end()) {
					slopes[slope] = vector<pair<IntPoint, IntPoint>> { };
				}

				slopes[slope].push_back(make_pair(points[i], points[j]));
			}
		}

		size_t max = 0;

		for (map<pair<int, int>, vector<pair<IntPoint, IntPoint>>>::iterator slope = slopes.begin(); slope != slopes.end(); slope++) {
			vector<set<IntPoint>> lines;
			for_each(slope->second.begin(), slope->second.end(), [&](pair<IntPoint, IntPoint> & s){
				vector<set<IntPoint>>::iterator & first = lines.end();
				vector<set<IntPoint>>::iterator & second = lines.end();
				for(vector<set<IntPoint>>::iterator it = lines.begin(); it != lines.end(); it++){
					if (it->find(s.first) != it->end()) {
						first = it;
					}
					if (it->find(s.second) != it->end()) {
						second = it;
					}
				}

				if (first == lines.end() && second == lines.end()) {
					set<IntPoint> line;
					line.insert(s.first);
					line.insert(s.second);
					lines.push_back(line);
				} else if (first == lines.end()) {
					second->insert(s.first);
				} else if (second == lines.end()) {
					first->insert(s.second);
				} else if (first == second) {
					;
				} else {
					set<IntPoint> line;
					line.insert(first->begin(), first->end());
					line.insert(second->begin(), second->end());
					lines.erase(first);
					lines.erase(second);
					lines.push_back(line);
				}
			});
			for_each(lines.begin(), lines.end(), [&](set<IntPoint> & l){
				if (l.size() > max) {
					max = l.size();
					output.clear();
					output.insert(l.begin(), l.end());
				}
			});
		}

		return max;
	}
}