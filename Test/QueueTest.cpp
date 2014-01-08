#include "QueueTest.h"

void QueueTest::Init(void)
{
	Add("Empty", [&](){
		Test::Queue<int> q1;
		queue<int> q2;

		ASSERT1(q1.Empty() == true);
		ASSERT1(q2.empty() == true);
		ASSERT1(q1.Size() == q2.size());

		for (int i = 0; i < 100; i++){
			q1.Push(i);
			q2.push(i);
			ASSERT1(q1.Empty() == false);
			ASSERT1(q2.empty() == false);
			ASSERT1(q1.Size() == q2.size());
		}

		for (int i = 0; i < 99; i++){
			q1.Pop();
			q2.pop();
			ASSERT1(q1.Empty() == false);
			ASSERT1(q2.empty() == false);
			ASSERT1(q1.Size() == q2.size());
		}

		q1.Pop();
		q2.pop();
		ASSERT1(q1.Empty() == true);
		ASSERT1(q2.empty() == true);
		ASSERT1(q1.Size() == q2.size());
	});

	Add("Front", [&](){
		Test::Queue<int> q1;
		queue<int> q2;

		ASSERTERROR(q1.Front(), runtime_error);
		ASSERT1(q1.Size() == q2.size());

		int v1, v2;
		for (int i = 0; i < 100; i++){
			q1.Push(i);
			q2.push(i);
			v1 = q1.Front();
			v2 = q2.front();
			ASSERT1(v1 == 0);
			ASSERT1(v2 == 0);
			ASSERT1(q1.Size() == q2.size());
		}

		for (int i = 0; i < 99; i++){
			q1.Pop();
			q2.pop();
			v1 = q1.Front();
			v2 = q2.front();
			ASSERT1(v1 == i + 1);
			ASSERT1(v2 == i + 1);
			ASSERT1(q1.Size() == q2.size());
		}

		v1 = q1.Front();
		v2 = q2.front();
		ASSERT1(v1 == 99);
		ASSERT1(v2 == 99);
		ASSERT1(q1.Size() == q2.size());

		q1.Pop();
		q2.pop();

		ASSERTERROR(q1.Front(), runtime_error);
		ASSERT1(q1.Empty() == true);
		ASSERT1(q2.empty() == true);
		ASSERT1(q1.Size() == q2.size());
	});

	Add("Back", [&](){
		Test::Queue<int> q1;
		queue<int> q2;

		ASSERTERROR(q1.Back(), runtime_error);
		ASSERT1(q1.Size() == q2.size());

		int v1, v2;
		for (int i = 0; i < 100; i++){
			q1.Push(i);
			q2.push(i);
			v1 = q1.Back();
			v2 = q2.back();
			ASSERT1(v1 == i);
			ASSERT1(v2 == i);
			ASSERT1(q1.Size() == q2.size());
		}

		for (int i = 0; i < 99; i++){
			q1.Pop();
			q2.pop();
			v1 = q1.Back();
			v2 = q2.back();
			ASSERT1(v1 == 99);
			ASSERT1(v2 == 99);
			ASSERT1(q1.Size() == q2.size());
		}

		q1.Pop();
		q2.pop();

		ASSERTERROR(q1.Back(), runtime_error);
		ASSERT1(q1.Empty() == true);
		ASSERT1(q2.empty() == true);
		ASSERT1(q1.Size() == q2.size());
	});
}