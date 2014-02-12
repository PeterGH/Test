#pragma once
#include "..\Algorithm\Knapsack.h"
#include "..\Algorithm\TestClass.h"
class KnapsackTest : public Test::TestClass {
public:
	KnapsackTest(Test::Log & log) : Test::TestClass(log) {}
	~KnapsackTest(void) {}
	void Init(void);
};

