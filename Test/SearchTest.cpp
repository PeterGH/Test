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
}