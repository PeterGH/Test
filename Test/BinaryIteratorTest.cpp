#include "BinaryIteratorTest.h"

void BinaryIteratorTest::Init(void)
{
	Add("Constructor", [&](){
		Test::BinaryNode<int> node(3);
		Test::BinaryIterator<int, Test::BinaryNode> it(&node);
		Logger().WriteInformation("it.Current() = %d\n", it.Current());
		Logger().WriteInformation("it->content = %d\n", it->content);
		Logger().WriteInformation("*it = %d\n", *it);

		Test::BinaryIterator<int, Test::BinaryNode> it2(it);
		Logger().WriteInformation("it2.Current() = %d\n", it2.Current());
		Logger().WriteInformation("it2->content = %d\n", it2->content);
		Logger().WriteInformation("*it2 = %d\n", *it2);

		ASSERT1(it.Current() == it2.Current());
		ASSERT1(it->content == it2->content);
		ASSERT1(*it == it2.Current());
		ASSERT1(*it == it2->content);
		ASSERT1(*it == *it2);

		ASSERT1(it);
		ASSERT1(it2);
	});
}