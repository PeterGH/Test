#pragma once
#include "..\Algorithm\Knapsack.h"
#include "..\Algorithm\TestClass.h"
using namespace Test;
class KnapsackTest : public TestClass {
public:
	KnapsackTest(Log & log) : TestClass(log) {}
	~KnapsackTest(void) {}
	void Init(void);
};

