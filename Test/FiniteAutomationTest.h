#pragma once
#include "..\Algorithm\FiniteAutomation.h"
#include "..\Algorithm\TestClass.h"

class FiniteAutomationTest : public Test::TestClass {
public:
	FiniteAutomationTest(Test::Log & log) : Test::TestClass(log) {}
	~FiniteAutomationTest(void) {}
	void Init(void);
};

