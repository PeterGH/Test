#include "StringTest.h"

void StringTest::Init(void)
{
	Add("RemoveDuplicateChar", [&](){
		char * c;
		c = nullptr;
		int l = Test::String::RemoveDuplicateChars(c, 0);
		ASSERT1(l == -1);

		char c1[] = "Test";
		Logger().WriteInformation("%s\t", c1);
		l = Test::String::RemoveDuplicateChars(c1, 4);
		Logger().WriteInformation("%s\n", c1);
		ASSERT1(0 == strcmp("Test", c1));
		ASSERT1(4 == l);

		char c2[] = "TTeesstt";
		Logger().WriteInformation("%s\t", c2);
		l = Test::String::RemoveDuplicateChars(c2, 8);
		Logger().WriteInformation("%s\n", c2);
		ASSERT1(0 == strcmp("Test", c2));
		ASSERT1(4 == l);

		char c3[] = "TestTest";
		Logger().WriteInformation("%s\t", c3);
		l = Test::String::RemoveDuplicateChars(c3, 8);
		Logger().WriteInformation("%s\n", c3);
		ASSERT1(0 == strcmp("Test", c3));
		ASSERT1(4 == l);

		char c4[] = "";
		Logger().WriteInformation("%s\t", c4);
		l = Test::String::RemoveDuplicateChars(c4, 0);
		Logger().WriteInformation("%s\n", c4);
		ASSERT1(0 == strcmp("", c4));
		ASSERT1(0 == l);
	});
}