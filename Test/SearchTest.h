#pragma once
#include "..\Algorithm\Search.h"
#include "..\Algorithm\TestClass.h"
using namespace Test;
class SearchTest : public TestClass {
public:
	SearchTest(Log & log) : TestClass(log) {}
	~SearchTest(void) {}
	void Init(void);
};

