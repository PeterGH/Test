#include "SearchTest.h"

void SearchTest::Init()
{
	Add("Search", [&](){
		int I[] = { 1, 1, 3, 3, 7, 8, 34, 35, 42, 43, 64, 445, 3556, 8769, 96656532 };
		int L = sizeof(I) / sizeof(I[0]);
		ASSERT1(0 == Search::BinarySearch<int>(1, I, 1));
		ASSERT1(0 == Search::BinarySearch<int>(1, I, 1, false));
		ASSERT1(1 == Search::BinarySearch<int>(1, I, 2, false));

		ASSERT1(0 == Search::BinarySearchRecursively<int>(1, I, 0, 0));
		ASSERT1(0 == Search::BinarySearchRecursively<int>(1, I, 0, 0, false));

		ASSERT1(0 == Search::BinarySearchRecursively<int>(1, I, 0, 1));
		ASSERT1(1 == Search::BinarySearchRecursively<int>(1, I, 0, 1, false));
		ASSERT1(1 == Search::BinarySearchRecursively<int>(1, I, 0, 2, false));

		ASSERT1(0 == Search::BinarySearch<int>(1, I, L));
		ASSERT1(1 != Search::BinarySearch<int>(1, I, L));
		ASSERT1(1 == Search::BinarySearch<int>(1, I, L, false));

		ASSERT1(0 == Search::BinarySearchRecursively<int>(1, I, 0, L - 1));
		ASSERT1(1 != Search::BinarySearchRecursively<int>(1, I, 0, L - 1));
		ASSERT1(1 == Search::BinarySearchRecursively<int>(1, I, 0, L - 1, false));

		ASSERT1(2 == Search::BinarySearch<int>(3, I, L));
		ASSERT1(3 != Search::BinarySearch<int>(3, I, L));
		ASSERT1(3 == Search::BinarySearch<int>(3, I, L, false));

		ASSERT1(2 == Search::BinarySearchRecursively<int>(3, I, 0, L - 1));
		ASSERT1(3 != Search::BinarySearchRecursively<int>(3, I, 0, L - 1));
		ASSERT1(3 == Search::BinarySearchRecursively<int>(3, I, 0, L - 1, false));

		ASSERT1(9 == Search::BinarySearch<int>(43, I, L));
		ASSERT1(9 == Search::BinarySearch<int>(43, I, L, false));
		ASSERT1(9 == Search::BinarySearchRecursively<int>(43, I, 0, L - 1));
		ASSERT1(9 == Search::BinarySearchRecursively<int>(43, I, 0, L - 1, false));

		ASSERT1(L - 1 == Search::BinarySearch<int>(96656532, I, L));
		ASSERT1(L - 1 == Search::BinarySearch<int>(96656532, I, L, false));
		ASSERT1(L - 1 == Search::BinarySearchRecursively<int>(96656532, I, 0, L - 1));
		ASSERT1(L - 1 == Search::BinarySearchRecursively<int>(96656532, I, 0, L - 1, false));

		ASSERT1(-1 == Search::BinarySearch<int>(222, I, L));
		ASSERT1(-1 == Search::BinarySearchRecursively<int>(222, I, 0, L - 1));
	});

	Add("Insert", [&](){
		int I[] = { 1, 1, 3, 3, 7, 8, 34, 35, 42, 43, 64, 445, 3556, 8769, 96656532 };
		int L = sizeof(I) / sizeof(I[0]);
		ASSERT1(-1 == Test::Search::FindPositionToInsert<int>(0, I, 1));
		ASSERT1(-1 == Test::Search::FindPositionToInsert<int>(0, I, 2));
		ASSERT1(-1 == Test::Search::FindPositionToInsert<int>(0, I, L));

		ASSERT1(-1 == Test::Search::FindPositionToInsert<int>(0, I, 1, false));
		ASSERT1(-1 == Test::Search::FindPositionToInsert<int>(0, I, 2, false));
		ASSERT1(-1 == Test::Search::FindPositionToInsert<int>(0, I, L, false));

		ASSERT1(-1 == Test::Search::FindPositionToInsert<int>(1, I, 1));
		ASSERT1(-1 == Test::Search::FindPositionToInsert<int>(1, I, 2));
		ASSERT1(-1 == Test::Search::FindPositionToInsert<int>(1, I, L));

		ASSERT1(0 == Test::Search::FindPositionToInsert<int>(1, I, 1, false));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(1, I, 2, false));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(1, I, L, false));

		ASSERT1(0 == Test::Search::FindPositionToInsert<int>(2, I, 1));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(2, I, 2));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(2, I, 3));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(2, I, L));

		ASSERT1(0 == Test::Search::FindPositionToInsert<int>(2, I, 1, false));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(2, I, 2, false));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(2, I, 3, false));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(2, I, L, false));

		ASSERT1(0 == Test::Search::FindPositionToInsert<int>(3, I, 1));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(3, I, 2));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(3, I, 3));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(3, I, L));

		ASSERT1(0 == Test::Search::FindPositionToInsert<int>(3, I, 1, false));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(3, I, 2, false));
		ASSERT1(2 == Test::Search::FindPositionToInsert<int>(3, I, 3, false));
		ASSERT1(3 == Test::Search::FindPositionToInsert<int>(3, I, L, false));

		ASSERT1(0 == Test::Search::FindPositionToInsert<int>(4, I, 1));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(4, I, 2));
		ASSERT1(2 == Test::Search::FindPositionToInsert<int>(4, I, 3));
		ASSERT1(3 == Test::Search::FindPositionToInsert<int>(4, I, 4));
		ASSERT1(3 == Test::Search::FindPositionToInsert<int>(4, I, L));

		ASSERT1(0 == Test::Search::FindPositionToInsert<int>(4, I, 1, false));
		ASSERT1(1 == Test::Search::FindPositionToInsert<int>(4, I, 2, false));
		ASSERT1(2 == Test::Search::FindPositionToInsert<int>(4, I, 3, false));
		ASSERT1(3 == Test::Search::FindPositionToInsert<int>(4, I, 4, false));
		ASSERT1(3 == Test::Search::FindPositionToInsert<int>(4, I, L, false));

		ASSERT1(7 == Test::Search::FindPositionToInsert<int>(42, I, 8));
		ASSERT1(7 == Test::Search::FindPositionToInsert<int>(42, I, 9));
		ASSERT1(7 == Test::Search::FindPositionToInsert<int>(42, I, 10));
		ASSERT1(7 == Test::Search::FindPositionToInsert<int>(42, I, L));

		ASSERT1(7 == Test::Search::FindPositionToInsert<int>(42, I, 8, false));
		ASSERT1(8 == Test::Search::FindPositionToInsert<int>(42, I, 9, false));
		ASSERT1(8 == Test::Search::FindPositionToInsert<int>(42, I, 10, false));
		ASSERT1(8 == Test::Search::FindPositionToInsert<int>(42, I, L, false));

		ASSERT1(9 == Test::Search::FindPositionToInsert<int>(50, I, 10));
		ASSERT1(9 == Test::Search::FindPositionToInsert<int>(50, I, 11));
		ASSERT1(9 == Test::Search::FindPositionToInsert<int>(50, I, L));

		ASSERT1(9 == Test::Search::FindPositionToInsert<int>(50, I, 10, false));
		ASSERT1(9 == Test::Search::FindPositionToInsert<int>(50, I, 11, false));
		ASSERT1(9 == Test::Search::FindPositionToInsert<int>(50, I, L, false));
	});
}