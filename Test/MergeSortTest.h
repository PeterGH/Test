#pragma once

#include "..\Algorithm\MergeSort.h"
#include "..\Algorithm\TestClass.h"

class MergeSortTest : public Test::TestClass {
public:
	MergeSortTest(Test::Log & log) : Test::TestClass(log) {}
	~MergeSortTest(void) {}
	void Init(void);
};

