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

	Add("IsMatch", [&](){
		auto check = [&](char * s, char * p, bool e){
			bool m = Test::String::IsMatch(s, p);
			bool m2 = Test::String::IsMatch2(s, p);
			Logger().WriteInformation("IsMatch:\t%s %s %s\n", s, m ? "==" : "!=", p);
			Logger().WriteInformation("IsMatch2:\t%s %s %s\n", s, m2 ? "==" : "!=", p);
			ASSERT1(m == e);
			ASSERT1(m2 == e);
		};

		check("aa", "a", false);
		check("aa", ".", false);
		check("aa", "aa", true);
		check("aa", "..", true);
		check("aa", "*aa", true);
		check("aaa", "aa", false);
		check("aaa", "*aa", false);
		check("aaa", "aa*", true);
		check("aaa", "aa**", true);
		check("aaa", "a*a", true);
		check("aaa", "...", true);
		check("aaa", ".*.", true);
		check("aa", "a*", true);
		check("aa", ".*", true);
		check("ab", ".*", true);
		check("ab", "..", true);
		check("aab", "c*a*b", true);
		check("aab", "c***a**b", true);
		check("abbbc", "ab*c", true);
		check("ac", "ab*c", true);
		check("abbc", "ab*bbc", true);
		check("abcbcd", "a.*c.*d", true);
	});

	Add("LongestSubStringWithUniqueChars", [&](){
		auto check = [&](char * s, int i, int l) {
			string ss(s);
			int ai;
			int al;
			Test::String::LongestSubStringWithUniqueChars(ss, ai, al);
			Logger().WriteInformation(
				"%s, (%d%s%d, %d%s%d), %s\n",
				ss.c_str(),
				ai,
				ai == i ? "==" : "!=",
				i,
				al,
				al == l ? "==" : "!=",
				l,
				ss.substr(ai, al).c_str());
			ASSERT1(ai == i);
			ASSERT1(al == l);
		};

		check("a", 0, 1);
		check("aa", 0, 1);
		check("ab", 0, 2);
		check("aaa", 0, 1);
		check("aba", 0, 2);
		check("aab", 1, 2);
		check("abc", 0, 3);
		check("abab", 0, 2);
		check("abba", 0, 2);
		check("abca", 0, 3);
		check("aabc", 1, 3);
		check("abac", 1, 3);
		check("abcd", 0, 4);
		check("abcabc", 0, 3);
		check("abcad", 1, 4);
		check("aaabcd", 2, 4);
		check("abcabcbb", 0, 3);
	});
}