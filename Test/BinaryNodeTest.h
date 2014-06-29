#pragma once
#include "..\Algorithm\BinaryNode.h"
#include "..\Algorithm\BinaryNodeWithParent.h"
#include "..\Algorithm\TestClass.h"
using namespace std;
class BinaryNodeTest : public Test::TestClass {
public:
	BinaryNodeTest(Test::Log & log) : Test::TestClass(log) {}
	~BinaryNodeTest(void) {}
	void Init(void);
};

