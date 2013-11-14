#pragma once

#include "..\Algorithm\QuickSort.h"
#include "..\Algorithm\TestClass.h"

class QuickSortTest : public Test::TestClass {
public:
	QuickSortTest(Test::Log & log) : Test::TestClass(log) {}
	~QuickSortTest(void) {}
	void Init(void);
};

