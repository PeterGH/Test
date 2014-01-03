#pragma once

#include "..\Algorithm\MRInteger.h"
#include "..\Algorithm\RadixSort.h"
#include "..\Algorithm\TestClass.h"

class MRIntegerTest : public Test::TestClass {
public:
	MRIntegerTest(Test::Log & log) : Test::TestClass(log) {}
	~MRIntegerTest(void) {}
	void Init(void);
};

