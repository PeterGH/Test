#pragma once
#include "..\Algorithm\LongestIncreasingSubsequence.h"
#include "..\Algorithm\TestClass.h"
class LongestIncreasingSubsequenceTest : public Test::TestClass {
public:
	LongestIncreasingSubsequenceTest(Test::Log & log) : Test::TestClass(log) {}
	~LongestIncreasingSubsequenceTest(void) {}
	void Init(void);
};

