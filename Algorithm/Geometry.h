#pragma once
#pragma once
#include <utility>
using namespace std;
namespace Test {
	class Geometry {
	public:
		__declspec(dllexport) Geometry();
		__declspec(dllexport) ~Geometry();

		// [pair.first, pair.second]
		typedef pair<double, double> Range;

		// (Point.x, Point.y) = (pair.first, pair.second)
		typedef pair<double, double> Point;

		// The sides of Rectangle are in parallel with x-axis or y-axis
		// Top-Left Point = pair.first
		// Bottom-Right Point = pair.second
		typedef pair<Point, Point> Rectangle;

		__declspec(dllexport) static bool IsOverlap(const Range & r1, const Range & r2);
		__declspec(dllexport) static bool IsOverlap(const Rectangle & r1, const Rectangle & r2);
	};
}
