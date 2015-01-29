#pragma once
#include "..\Algorithm\Count.h"
#include "..\Algorithm\TestClass.h"
class CountTest : public Test::TestClass {
public:
	CountTest(Test::Log & log) : Test::TestClass(log) {}
	~CountTest(void) {}
	void Init(void);
};

