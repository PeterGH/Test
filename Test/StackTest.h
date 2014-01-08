#pragma once

#include <stack>
#include "..\Algorithm\Stack.h"
#include "..\Algorithm\TestClass.h"

using namespace std;

class StackTest : public Test::TestClass {
public:
	StackTest(Test::Log & log) : Test::TestClass(log) {}
	~StackTest(void) {}
	void Init(void);
};

