#pragma once

#include "..\Algorithm\Permutation.h"
#include "..\Algorithm\TestClass.h"

class PermutationTest : public Test::TestClass {
public:
	PermutationTest(Test::Log & log) : Test::TestClass(log) {}
	~PermutationTest(void) {}
	void Init(void);
};

