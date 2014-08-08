#pragma once
#include "..\Algorithm\Math.h"
#include "..\Algorithm\Random.h"
#include "..\Algorithm\TestClass.h"
class MathTest : public Test::TestClass {
public:
	MathTest(Test::Log & log) : Test::TestClass(log) {}
	~MathTest(void) {}
	void Init(void);
};

