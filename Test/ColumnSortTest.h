#pragma once

#include <time.h>
#include "..\Algorithm\ColumnSort.h"
#include "..\Algorithm\TestClass.h"

using namespace std;

class ColumnSortTest : public Test::TestClass {
public:
	ColumnSortTest(Test::Log & log) : Test::TestClass(log) {}
	~ColumnSortTest(void) {}
	void Init(void);
};

