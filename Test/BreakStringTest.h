#pragma once
#include "..\Algorithm\BreakString.h"
#include "..\Algorithm\TestClass.h"
class BreakStringTest : public Test::TestClass {
public:
	BreakStringTest(Test::Log & log) : Test::TestClass(log) {}
	~BreakStringTest(void) {}
	void Init(void);
};

