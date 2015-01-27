#pragma once
#include <vector>
#include "..\Algorithm\Sort.h"
#include "..\Algorithm\TestClass.h"
class SortTest : public Test::TestClass  {
public:
	SortTest(Test::Log & log) : Test::TestClass(log) {}
	~SortTest(void) {}
	void Init(void);
};

