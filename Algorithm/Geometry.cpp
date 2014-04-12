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
}