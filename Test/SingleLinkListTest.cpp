#include "SingleLinkListTest.h"

void SingleLinkListTest::Init(void)
{
	Add("Insert", [&]() {
		Test::SingleLinkList<int> list;
		(Logger() << list).WriteInformation("\n");
		for (int i = 0; i < 10; i++) {
			list.Insert(i);
			(Logger() << list).WriteInformation("\n");
		}

		for (int i = 0; i < 10; i++) {
			int v = list[i];
			ASSERT2(v == (9 - i), Test::String::Format("list[%d] = %d", i, v));
		}

		ASSERTERROR(list[10], std::invalid_argument);
	});

	Add("Middle", [&]() {
		Test::SingleLinkList<int> list;
		(Logger() << list).WriteInformation("\n");
		ASSERTERROR(list.Middle(), std::invalid_argument);

		for (int i = 0; i < 10; i++) {
			list.Insert(i);
			(Logger() << list).WriteInformation("\n");
			int v = list.Middle();
			Logger().WriteInformation("Middle = %d\n", v);
			ASSERT2(v == i - (i >> 1), Test::String::Format("list[%d] = %d", i, v));
		}

		ASSERTERROR(list[10], std::invalid_argument);
	});

	Add("Reverse", [&]() {
		Test::SingleLinkList<int> list;
		(Logger() << list).WriteInformation("\n");
		list.Reverse();
		(Logger() << list).WriteInformation("\n");
		for (int i = 0; i < 10; i++) {
			list.Insert(i);
			(Logger() << list).WriteInformation("\n");
			list.Reverse();
			(Logger() << list).WriteInformation("\n");
			for (int j = 0; j <= i; j++) {
				int v = list[j];
				ASSERT2(v == j, Test::String::Format("list[%d] = %d", j, v));
			}

			list.Reverse();
		}

		ASSERTERROR(list[10], std::invalid_argument);
	});

	Add("Iterator", [&]() {
		Test::SingleLinkList<int> list;
		(Logger() << list).WriteInformation("\n");
		for (int i = 0; i < 10; i++) {
			list.Insert(9 - i);
			(Logger() << list).WriteInformation("\n");
		}

		Logger().WriteInformation("++ it, it->\n");
		for (Test::SingleLinkList<int>::iterator it = list.begin(); it != list.end(); ++it) {
			unsigned int i = it.Index();
			int v = it->data;
			Logger().WriteInformation("%d\t%d\n", i, v);
			ASSERT2(v == i, Test::String::Format("list[%d] = %d", i, v));
		}

		Logger().WriteInformation("it ++, it.current()\n");
		for (Test::SingleLinkList<int>::iterator it = list.begin(); it != list.end(); it++) {
			unsigned int i = it.Index();
			int v = it.current();
			Logger().WriteInformation("%d\t%d\n", i, v);
			ASSERT2(v == i, Test::String::Format("list[%d] = %d", i, v));
		}

		Logger().WriteInformation("++ it, *it\n");
		for (Test::SingleLinkList<int>::iterator it = list.begin(); it != list.end(); ++it) {
			unsigned int i = it.Index();
			int v = *it;
			Logger().WriteInformation("%d\t%d\n", i, v);
			ASSERT2(v == i, Test::String::Format("list[%d] = %d", i, v));
		}

		Logger().WriteInformation("bool(it) == true\n");
		Test::SingleLinkList<int>::iterator it = list.begin();
		ASSERT1(it);

		Logger().WriteInformation("bool(it) == false\n");
		it = list.end();
		ASSERTERROR(it, std::invalid_argument);
	});
}