#include "PalindromeTest.h"

void PalindromeTest::Init(void)
{
	Add("Palindrome", [&](){
		string s = "character";
		string t;
		string a;
		cout << "Input: " << s << endl;
		Test::Palindrome::LongestSubsequenceByTable(s, t);
		cout << "Table: " << t << endl;
		Test::Palindrome::LongestSubsequenceByArray(s, a);
		cout << "Array: " << a << endl;
		cout << endl;
		ASSERT1(0 == t.compare(a));
		
		s = "racecar";
		t = "";
		a = "";
		cout << "Input: " << s << endl;
		Test::Palindrome::LongestSubsequenceByTable(s, t);
		cout << "Table: " << t << endl;
		Test::Palindrome::LongestSubsequenceByArray(s, a);
		cout << "Array: " << a << endl;
		cout << endl;
		ASSERT1(0 == t.compare(a));
		
		s = "raceecar";
		t = "";
		a = "";
		cout << "Input: " << s << endl;
		Test::Palindrome::LongestSubsequenceByTable(s, t);
		cout << "Table: " << t << endl;
		Test::Palindrome::LongestSubsequenceByArray(s, a);
		cout << "Array: " << a << endl;
		cout << endl;
		ASSERT1(0 == t.compare(a));
		
		s = "racefcar";
		t = "";
		a = "";
		cout << "Input: " << s << endl;
		Test::Palindrome::LongestSubsequenceByTable(s, t);
		cout << "Table: " << t << endl;
		Test::Palindrome::LongestSubsequenceByArray(s, a);
		cout << "Array: " << a << endl;
		cout << endl;
		ASSERT1(0 == t.compare(a));
		
		s = "ra";
		t = "";
		a = "";
		cout << "Input: " << s << endl;
		Test::Palindrome::LongestSubsequenceByTable(s, t);
		cout << "Table: " << t << endl;
		Test::Palindrome::LongestSubsequenceByArray(s, a);
		cout << "Array: " << a << endl;
		cout << endl;
		ASSERT1(0 == t.compare(a));
		
		s = "rac";
		t = "";
		a = "";
		cout << "Input: " << s << endl;
		Test::Palindrome::LongestSubsequenceByTable(s, t);
		cout << "Table: " << t << endl;
		Test::Palindrome::LongestSubsequenceByArray(s, a);
		cout << "Array: " << a << endl;
		cout << endl;
		ASSERT1(0 == t.compare(a));
	});

	Add("Number", [&](){
		auto check = [&](unsigned int n, bool e){
			bool r = Test::Palindrome::IsPalindrom(n);
			Logger().WriteInformation("%d is %s palindrome\n", n, r ? "" : "not");
			ASSERT1(r == e);
		};

		check(3, true);
		check(33, true);
		check(23, false);
		check(232, true);
		check(1231, false);
		check(12344321, true);
		check(123454321, true);
		check(1234567, false);
	});

	Add("Substring", [&](){
		string i = "babcbabcbaccba";
		string o;
		Logger().WriteInformation("%s\n", i.c_str());
		Test::Palindrome::LongestSubstring(i, o);
		Logger().WriteInformation("%s\n", o.c_str());
		ASSERT1(o == "abcbabcba");
	});

	Add("Substring2", [&](){
		string i = "xabcbabcbayzaw";
		string o1;
		Logger().WriteInformation("%s\n", i.c_str());
		Test::Palindrome::LongestSubstring(i, o1);
		Logger().WriteInformation("%s\n", o1.c_str());
		string o2;
		Test::Palindrome::LongestSubsequenceByTable(i, o2);
		Logger().WriteInformation("%s\n", o2.c_str());
		string o3;
		Test::Palindrome::LongestSubsequenceByArray(i, o3);
		Logger().WriteInformation("%s\n", o3.c_str());
		ASSERT1(o1 == "abcbabcba");
		ASSERT1(o2 == o1);
		ASSERT1(o3 == o1);
	});

	Add("Substring3", [&](){
		string i = "xabcbabcbayztw";
		string o1;
		Logger().WriteInformation("%s\n", i.c_str());
		Test::Palindrome::LongestSubstring(i, o1);
		Logger().WriteInformation("%s\n", o1.c_str());
		string o2;
		Test::Palindrome::LongestSubsequenceByTable(i, o2);
		Logger().WriteInformation("%s\n", o2.c_str());
		string o3;
		Test::Palindrome::LongestSubsequenceByArray(i, o3);
		Logger().WriteInformation("%s\n", o3.c_str());
		ASSERT1(o1 == "abcbabcba");
		ASSERT1(o2 == o1);
		ASSERT1(o3 == o1);
	});
}
