#pragma once

#include "..\Algorithm\CountingSort.h"
#include "..\Algorithm\Random.h"
#include "..\Algorithm\TestClass.h"

class CountingSortTest : public Test::TestClass {
public:
	CountingSortTest(Test::Log & log) : Test::TestClass(log) {}
	~CountingSortTest(void) {}
	void Init(void);
};

