#pragma once
#include "..\Algorithm\CoinChange.h"
#include "..\Algorithm\Random.h"
#include "..\Algorithm\TestClass.h"
class CoinChangeTest : public Test::TestClass {
public:
	CoinChangeTest(Test::Log & log) : Test::TestClass(log) {}
	~CoinChangeTest(void) {}
	void Init(void);
};

