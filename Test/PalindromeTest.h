#pragma once
#include "..\Algorithm\Palindrome.h"
#include "..\Algorithm\TestClass.h"
class PalindromeTest : public Test::TestClass {
public:
	PalindromeTest(Test::Log & log) : Test::TestClass(log) {}
	~PalindromeTest(void) {}
	void Init(void);
};

