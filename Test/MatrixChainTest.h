#pragma once

#include "..\Algorithm\Array.h"
#include "..\Algorithm\MatrixChain.h"
#include "..\Algorithm\TestClass.h"

class MatrixChainTest : public Test::TestClass {
public:
	MatrixChainTest(Test::Log & log) : Test::TestClass(log) {}
	~MatrixChainTest(void) {}
	void Init(void);
};

