#include "GeometryTest.h"

void GeometryTest::Init(void)
{
	Add("Range", [&](){
		auto check = [&](double b1, double e1, double b2, double e2, bool o){
			Test::Geometry::Range r1 = make_pair(b1, e1);
			Test::Geometry::Range r2 = make_pair(b2, e2);
			bool r = Test::Geometry::IsOverlap(r1, r2);
			Logger().WriteInformation("(%.2f, %.2f) and (%.2f, %.2f) %s overlap\n", b1, e1, b2, e2, r ? "" : "not");
			ASSERT1(r == o);
		};

		check(0.0, 1.0, 2.0, 3.0, false);
		check(0.0, 2.0, 1.5, 3.0, true);
		check(0.0, 4.0, 2.0, 3.0, true);
	});

	Add("Rectangle", [&](){
		auto check = [&](
			double b1, double e1, double b2, double e2,
			double b3, double e3, double b4, double e4,
			bool o){
			Test::Geometry::Rectangle r1 = make_pair(make_pair(b1, e1), make_pair(b2, e2));
			Test::Geometry::Rectangle r2 = make_pair(make_pair(b3, e3), make_pair(b4, e4));
			bool r = Test::Geometry::IsOverlap(r1, r2);
			Logger().WriteInformation(
				"((%.2f, %.2f), (%.2f, %.2f)) and ((%.2f, %.2f), (%.2f, %.2f)) %s overlap\n",
				b1, e1, b2, e2, b3, e3, b4, e4, r ? "" : "not");
			ASSERT1(r == o);
		};

		check(0, 6, 2, 5, 3, 4, 5, 3, false);
		check(1, 6, 3, 5, 3, 4, 5, 3, false);
		check(2, 6, 4, 5, 3, 4, 5, 3, false);
		check(3, 6, 5, 5, 3, 4, 5, 3, false);
		check(4, 6, 6, 5, 3, 4, 5, 3, false);
		check(5, 6, 7, 5, 3, 4, 5, 3, false);
		check(6, 6, 8, 5, 3, 4, 5, 3, false);

		check(0, 4.5, 2, 3.5, 3, 4, 5, 3, false);
		check(1, 4.5, 3, 3.5, 3, 4, 5, 3, false);
		check(2, 4.5, 4, 3.5, 3, 4, 5, 3, true);
		check(3, 4.5, 5, 3.5, 3, 4, 5, 3, true);
		check(4, 4.5, 6, 3.5, 3, 4, 5, 3, true);
		check(5, 4.5, 7, 3.5, 3, 4, 5, 3, false);
		check(6, 4.5, 8, 3.5, 3, 4, 5, 3, false);

		check(0, 4, 2, 3, 3, 4, 5, 3, false);
		check(1, 4, 3, 3, 3, 4, 5, 3, false);
		check(2, 4, 4, 3, 3, 4, 5, 3, true);
		check(3, 4, 5, 3, 3, 4, 5, 3, true);
		check(4, 4, 6, 3, 3, 4, 5, 3, true);
		check(5, 4, 7, 3, 3, 4, 5, 3, false);
		check(6, 4, 8, 3, 3, 4, 5, 3, false);

		check(0, 3.5, 2, 2.5, 3, 4, 5, 3, false);
		check(1, 3.5, 3, 2.5, 3, 4, 5, 3, false);
		check(2, 3.5, 4, 2.5, 3, 4, 5, 3, true);
		check(3, 3.5, 5, 2.5, 3, 4, 5, 3, true);
		check(4, 3.5, 6, 2.5, 3, 4, 5, 3, true);
		check(5, 3.5, 7, 2.5, 3, 4, 5, 3, false);
		check(6, 3.5, 8, 2.5, 3, 4, 5, 3, false);

		check(0, 2, 2, 1, 3, 4, 5, 3, false);
		check(1, 2, 3, 1, 3, 4, 5, 3, false);
		check(2, 2, 4, 1, 3, 4, 5, 3, false);
		check(3, 2, 5, 1, 3, 4, 5, 3, false);
		check(4, 2, 6, 1, 3, 4, 5, 3, false);
		check(5, 2, 7, 1, 3, 4, 5, 3, false);
		check(6, 2, 8, 1, 3, 4, 5, 3, false);
	});
}