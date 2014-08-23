#pragma once
#include "..\Algorithm\LeetCode.h"
#include "..\Algorithm\TestClass.h"
class LeetCodeTest : public Test::TestClass {
public:
	LeetCodeTest(Test::Log & log) : Test::TestClass(log) {}
	~LeetCodeTest(void) {}
	void Init(void);
};

