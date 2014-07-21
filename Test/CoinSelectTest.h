#pragma once
#include "..\Algorithm\CoinSelect.h"
#include "..\Algorithm\Random.h"
#include "..\Algorithm\TestClass.h"
class CoinSelectTest : public Test::TestClass {
public:
	CoinSelectTest(Test::Log & log) : Test::TestClass(log) {}
	~CoinSelectTest(void) {}
	void Init(void);
};

