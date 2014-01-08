#include "StackTest.h"

void StackTest::Init(void)
{
	Add("Stack", [&](){
		Test::Stack<int> s1;
		stack<int> s2;

		ASSERTERROR(s1.Top(), runtime_error);
		ASSERTERROR(s1.Pop(), runtime_error);
		ASSERT1(s1.Empty() == true);
		ASSERT1(s2.empty() == true);
		ASSERT1(s1.Size() == s2.size());

		for (int i = 0; i < 100; i++) {
			s1.Push(i);
			s2.push(i);
			ASSERT1(s1.Top() == i);
			ASSERT1(s2.top() == i);
			ASSERT1(s1.Empty() == false);
			ASSERT1(s2.empty() == false);
			ASSERT1(s1.Size() == s2.size());
		}

		int v1, v2;
		for (int i = 0; i < 99; i++) {
			v1 = s1.Top();
			s1.Pop();
			v2 = s2.top();
			s2.pop();
			ASSERT1(v1 == 99 - i);
			ASSERT1(v2 == 99 - i);
			ASSERT1(s1.Top() == 99 - i - 1);
			ASSERT1(s2.top() == 99 - i - 1);
			ASSERT1(s1.Empty() == false);
			ASSERT1(s2.empty() == false);
			ASSERT1(s1.Size() == s2.size());
		}

		v1 = s1.Top();
		s1.Pop();
		v2 = s2.top();
		s2.pop();
		ASSERT1(v1 == 0);
		ASSERT1(v2 == 0);
		ASSERTERROR(s1.Top(), runtime_error);
		ASSERTERROR(s1.Pop(), runtime_error);
		ASSERT1(s1.Empty() == true);
		ASSERT1(s2.empty() == true);
		ASSERT1(s1.Size() == s2.size());
	});
}