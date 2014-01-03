#pragma once

#include <vector>
#include "..\Algorithm\HeapSort.h"
#include "..\Algorithm\Random.h"
#include "..\Algorithm\TestClass.h"

class HeapSortTest : public Test::TestClass {
public:
	HeapSortTest(Test::Log & log) : Test::TestClass(log) {}
	~HeapSortTest(void) {}
	void Init(void);
};

