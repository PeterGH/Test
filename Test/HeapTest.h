#pragma once

#include "..\Algorithm\Heap.h"
#include "..\Algorithm\TestClass.h"

class HeapTest : public Test::TestClass {
public:
	HeapTest(Test::Log & log) : Test::TestClass(log) {}
	~HeapTest(void) {}
	void Init(void);
};