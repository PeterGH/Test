#pragma once
#include "..\Algorithm\LongestCommonSubsequence.h"
#include "..\Algorithm\TestClass.h"

class LongestCommonSubsequenceTest : public Test::TestClass {
public:
	LongestCommonSubsequenceTest(Test::Log & log) : Test::TestClass(log) {}
	~LongestCommonSubsequenceTest(void) {}
	void Init(void);
};

