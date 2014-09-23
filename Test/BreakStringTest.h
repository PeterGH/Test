#pragma once
#include "..\Algorithm\BreakString.h"
#include "..\Algorithm\TestClass.h"
using namespace Test;
class BreakStringTest : public TestClass {
public:
	BreakStringTest(Log & log) : TestClass(log) {}
	~BreakStringTest(void) {}
	void Init(void);
};

