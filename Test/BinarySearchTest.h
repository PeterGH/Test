#pragma once

#include "..\Algorithm\BinarySearch.h"
#include "..\Algorithm\MergeSort.h"
#include "..\Algorithm\Random.h"
#include "..\Algorithm\TestClass.h"

class BinarySearchTest : public Test::TestClass {
public:
	BinarySearchTest(Test::Log & log) : Test::TestClass(log) {}
	~BinarySearchTest(void) {}
	void Init(void);
};

