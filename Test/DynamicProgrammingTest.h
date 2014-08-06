#pragma once
#include "..\Algorithm\DynamicProgramming.h"
#include "..\Algorithm\TestClass.h"

class DynamicProgrammingTest : public Test::TestClass {
public:
	DynamicProgrammingTest(Test::Log & log) : Test::TestClass(log) {}
	~DynamicProgrammingTest(void) {}
	void Init(void);
};

