#pragma once
#include "..\Algorithm\Palindrome.h"
#include "..\Algorithm\TestClass.h"
using namespace Test;
class PalindromeTest : public TestClass {
public:
	PalindromeTest(Log & log) : TestClass(log) {}
	~PalindromeTest(void) {}
	void Init(void);
};

