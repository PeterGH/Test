#pragma once

#include "..\Algorithm\Array.h"
#include "..\Algorithm\TestClass.h"

class ArrayTest : public Test::TestClass {
private:
	// Print a two dimensional matrix
	void Print(const int * input, const int length, const int columns); 
	void Test(int * A, int * B, int length, int columns, int rows);
public:
	ArrayTest(Test::Log & log) : Test::TestClass(log) {}
	~ArrayTest(void) {}
	void Init(void);
};

