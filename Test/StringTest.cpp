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

	Add("Join", [&](){
		int i1[] = { 0, 1, 2, 3 };
		string o1 = Test::String::Join(i1, 4, ":");
		Logger().WriteInformation("%s\n", o1.c_str());
		ASSERT1(0 == strcmp("0:1:2:3", o1.c_str()));

		wstring o2 = Test::String::Join(i1, 4, L":");
		Logger().WriteInformation("%S\n", o2.c_str());
		ASSERT1(0 == wcscmp(L"0:1:2:3", o2.c_str()));

		double i2[] = { 0.1, 1.2, 2.3, 3.4 };
		string o3 = Test::String::Join(i2, 4, ":");
		Logger().WriteInformation("%s\n", o3.c_str());
		ASSERT1(0 == strcmp("0.1:1.2:2.3:3.4", o3.c_str()));

		wstring o4 = Test::String::Join(i2, 4, L":");
		Logger().WriteInformation("%S\n", o4.c_str());
		ASSERT1(0 == wcscmp(L"0.1:1.2:2.3:3.4", o4.c_str()));
	});
}