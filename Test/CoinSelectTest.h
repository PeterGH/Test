#pragma once
#include "..\Algorithm\CoinSelect.h"
#include "..\Algorithm\Random.h"
#include "..\Algorithm\TestClass.h"
using namespace Test;
class CoinSelectTest : public TestClass {
public:
	CoinSelectTest(Log & log) : TestClass(log) {}
	~CoinSelectTest(void) {}
	void Init(void);
};

