#include "FiniteAutomationTest.h"

void FiniteAutomationTest::Init(void)
{
	Add("Invalid Pattern", [&](){
		ASSERTERROR(Test::FiniteAutomation fa(nullptr, 1), invalid_argument);
		ASSERTERROR(Test::FiniteAutomation fa("", 1), invalid_argument);
		ASSERTERROR(Test::FiniteAutomation fa("test", 0), invalid_argument);
	});

	Add("Invalid Input", [&](){
		Test::FiniteAutomation fa("a", 1);
		vector<int> i = fa.SearchString("", 0);
		ASSERT1(i.size() == 0);
	});

	Add("1", [&](){
		Test::FiniteAutomation fa("a", 1);
		fa.Print();

		vector<int> indices = fa.SearchString("b", 1);
		ASSERT1(indices.size() == 0);

		indices = fa.SearchString("a", 1);
		ASSERT1(indices.size() == 1);
		ASSERT1(indices[0] == 0);

		indices = fa.SearchString("ba", 2);
		ASSERT1(indices.size() == 1);
		ASSERT1(indices[0] == 1);

		indices = fa.SearchString("ab", 1);
		ASSERT1(indices.size() == 1);
		ASSERT1(indices[0] == 0);

		indices = fa.SearchString("bb", 2);
		ASSERT1(indices.size() == 0);

		indices = fa.SearchString("aa", 2);
		ASSERT1(indices.size() == 2);
		ASSERT1(indices[0] == 0);
		ASSERT1(indices[1] == 1);

		indices = fa.SearchString("baa", 3);
		ASSERT1(indices.size() == 2);
		ASSERT1(indices[0] == 1);
		ASSERT1(indices[1] == 2);

		indices = fa.SearchString("aba", 3);
		ASSERT1(indices.size() == 2);
		ASSERT1(indices[0] == 0);
		ASSERT1(indices[1] == 2);

		indices = fa.SearchString("bba", 3);
		ASSERT1(indices.size() == 1);
		ASSERT1(indices[0] == 2);
	});

	Add("2", [&](){
		Test::FiniteAutomation fa("aa", 2);
		fa.Print();

		vector<int> indices = fa.SearchString("b", 1);
		ASSERT1(indices.size() == 0);

		indices = fa.SearchString("a", 1);
		ASSERT1(indices.size() == 0);

		indices = fa.SearchString("aa", 2);
		ASSERT1(indices.size() == 1);
		ASSERT1(indices[0] == 0);

		indices = fa.SearchString("ba", 2);
		ASSERT1(indices.size() == 0);

		indices = fa.SearchString("baa", 3);
		ASSERT1(indices.size() == 1);
		ASSERT1(indices[0] == 1);

		indices = fa.SearchString("bab", 3);
		ASSERT1(indices.size() == 0);

		indices = fa.SearchString("aab", 3);
		ASSERT1(indices.size() == 1);
		ASSERT1(indices[0] == 0);

		indices = fa.SearchString("aaa", 3);
		ASSERT1(indices.size() == 2);
		ASSERT1(indices[0] == 0);
		ASSERT1(indices[1] == 1);
	});
}