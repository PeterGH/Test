#pragma once
#include "..\Algorithm\Matrix.h"
#include "..\Algorithm\TestClass.h"
using namespace Test;
class MatrixTest : public TestClass {
public:
	MatrixTest(Log & log) : TestClass(log) {}
	~MatrixTest(void) {}
	void Init(void);
};

