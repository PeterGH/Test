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

	Add("ShortestSubStringContainingGivenChars", [&](){
		auto check = [&](const string & input, const string & chars, const string & expect) {
			int index;
			int length;
			Test::String::ShortestSubStringContainingGivenChars(chars, input, index, length);
			string match = index == -1 ? "" : input.substr(index, length);
			Logger().WriteInformation("Input: %s\n", input.c_str());
			Logger().WriteInformation("Chars: %s\n", chars.c_str());
			Logger().WriteInformation("Match: %s %s %s\n", match.c_str(), match == expect ? "==" : "!=", expect.c_str());
			ASSERT1(match == expect);
		};

		check("aaaaa", "a", "a");
		check("aaaaa", "b", "");
		check("aaaaa", "ab", "");
		check("abaa", "ab", "ab");
		check("abaa", "ba", "ab");
		check("ccab", "ab", "ab");
		check("ccab", "ba", "ab");
		check("aabaa", "ab", "ab");
		check("aabaa", "ba", "ab");
		check("ccaba", "ab", "ab");
		check("ccaba", "ba", "ab");
		check("aacbddaa", "ba", "acb");
		check("aacdbddbeaa", "ab", "bea");
		check("ADOBECODEBANC", "ABC", "BANC");
	});

	Add("ReplaceWithShorterString", [&](){
		auto check = [&](char * input, char * pattern, char * shorter, char * expect) {
			Logger().WriteInformation("\nInput:   %s\n", input);
			Logger().WriteInformation("Pattern: %s\n", pattern);
			Logger().WriteInformation("Shorter: %s\n", shorter);
			Test::String::ReplaceWithShorterString(input, pattern, shorter);
			Logger().WriteInformation("Output:  %s\n", input);
			while (*input != '\0') {
				ASSERT1(*input++ == *expect++);
			}
		};

		char A[][4][256] = {
				{ "a", "a", "X", "X" },
				{ "aa", "aa", "X", "X" },
				{ "aa", "a", "X", "X" },
				{ "aa", "aaa", "X", "aa" },
				{ "abc", "abc", "X", "X" },
				{ "abcabc", "abc", "X", "X" },
				{ "abcabcabc", "abc", "X", "X" },
				{ "abcaabcaabc", "abc", "X", "XaXaX" },
				{ "abcaaabcaaabca", "abc", "X", "XaaXaaXa" },
				{ "abcabcabababcabc", "abc", "X", "XababX" },
				{ "abcabcabababcabcab", "abc", "X", "XababXab" },
				{ "aabbaabbaaabbbaabb", "aabb", "X", "XaXbX" },
				{ "aabbaabbaaabbbaabb", "aaabb", "X", "aabbaabbXbaabb" },
				{ "aabbaabbaaabbbaaabb", "aaabb", "X", "aabbaabbXbX" },
				{ "aabbaabbaaabbbaaabc", "aaabb", "X", "aabbaabbXbaaabc" },
				{ "abcdeffdfegabcabc", "abc", "X", "XdeffdfegX" },
				{ "abcdeffdfegabcabc", "ab", "X", "XcdeffdfegXcXc" },
				{ "abcdeffdfegabcabc", "a", "X", "XbcdeffdfegXbcXbc" },
				{ "abcdeffdfegabcab", "abc", "X", "XdeffdfegXab" },
				{ "abcdeffdfegabcabcab", "abc", "X", "XdeffdfegXab" },
				{ "abcdeffdfegabcaabcab", "abc", "X", "XdeffdfegXaXab" },
				{ "abcdeffdfegabcaaaabcab", "abc", "X", "XdeffdfegXaaaXab" },
				{ "aaaaaa", "a", "X", "X" },
				{ "aaaaaa", "aa", "X", "X" },
				{ "aaaaaa", "aaaaaa", "X", "X" },
				{ "aaaaaa", "aaaaaaa", "X", "aaaaaa" },
				{ "aabaababaaab", "a", "X", "XbXbXbXb" },
				{ "aabaababaaa", "a", "X", "XbXbXbX" },
				{ "aaaab", "a", "X", "Xb" },
				{ "baaa", "a", "X", "bX" },
				{ "aabaaabaab", "aaa", "X", "aabXbaab" },
				{ "aabaaabaab", "aa", "X", "XbXabXb" },
				{ "aabaaabaa", "aa", "X", "XbXabX" },
				{ "aa", "aa", "XY", "XY" },
				{ "aa", "aaa", "XY", "aa" },
				{ "abc", "abc", "XY", "XY" },
				{ "abcabc", "abc", "XY", "XY" },
				{ "abcabcabc", "abc", "XY", "XY" },
				{ "abcaabcaabc", "abc", "XY", "XYaXYaXY" },
				{ "abcaaabcaaabca", "abc", "XY", "XYaaXYaaXYa" },
				{ "abcabcabababcabc", "abc", "XY", "XYababXY" },
				{ "abcabcabababcabcab", "abc", "XY", "XYababXYab" },
				{ "aabbaabbaaabbbaabb", "aabb", "XY", "XYaXYbXY" },
				{ "aabbaabbaaabbbaabb", "aaabb", "XY", "aabbaabbXYbaabb" },
				{ "aabbaabbaaabbbaaabb", "aaabb", "XY", "aabbaabbXYbXY" },
				{ "aabbaabbaaabbbaaabc", "aaabb", "XY", "aabbaabbXYbaaabc" },
				{ "abcdeffdfegabcabc", "abc", "XY", "XYdeffdfegXY" },
				{ "abcdeffdfegabcabc", "ab", "XY", "XYcdeffdfegXYcXYc" },
				{ "abcdeffdfegabcab", "abc", "XY", "XYdeffdfegXYab" },
				{ "abcdeffdfegabcabcab", "abc", "XY", "XYdeffdfegXYab" },
				{ "abcdeffdfegabcaabcab", "abc", "XY", "XYdeffdfegXYaXYab" },
				{ "abcdeffdfegabcaaaabcab", "abc", "XY", "XYdeffdfegXYaaaXYab" },
				{ "aaaaaa", "aa", "XY", "XY" },
				{ "aaaaaa", "aaaaaa", "XY", "XY" },
				{ "aaaaaa", "aaaaaaa", "XY", "aaaaaa" },
				{ "aabaaabaab", "aaa", "XY", "aabXYbaab" },
				{ "aabaaabaab", "aa", "XY", "XYbXYabXYb" },
				{ "aabaaabaa", "aa", "XY", "XYbXYabXY" }
		};
		int len = sizeof(A) / sizeof(A[0]);
		for (int i = 0; i < len; i++) {
			check(A[i][0], A[i][1], A[i][2], A[i][3]);
		}
	});

	Add("StrStr", [&](){
		auto check = [&](char * input1, char * input2, int index) {
			Logger().WriteInformation("\nInput1:\t%s\n", input1);
			Logger().WriteInformation("Input2:\t%s\n", input2);
			const char * p = Test::String::StrStr(input1, input2);
			int i = p == nullptr ? -1 : p - input1;
			Logger().WriteInformation("Index:\t%d\n", i);
			ASSERT1(i == index);
		};

		check("a", "a", 0);
		check("a", "b", -1);
		check("a", "aa", -1);
		check("aa", "a", 0);
		check("aa", "b", -1);
		check("aa", "aa", 0);
		check("aa", "aaa", -1);
		check("ab", "a", 0);
		check("ab", "b", 1);
		check("ab", "c", -1);
		check("ab", "ab", 0);
		check("abc", "a", 0);
		check("abc", "b", 1);
		check("abc", "c", 2);
		check("abc", "d", -1);
		check("abc", "ab", 0);
		check("abc", "bc", 1);
		check("abc", "abc", 0);
		check("ababa", "ab", 0);
		check("ababa", "ba", 1);
		check("ababa", "aba", 0);
		check("ababa", "bab", 1);
		check("ababa", "ababa", 0);
		check("abcabcab", "abc", 0);
		check("abcabcab", "bca", 1);
		check("abcabcab", "cab", 2);
		check("abdabcab", "abc", 3);
		check("abdabcab", "bca", 4);
		check("abdabcab", "cab", 5);
	});
}