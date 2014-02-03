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
}
