#pragma once
#include "..\Algorithm\BinaryNode.h"
#include "..\Algorithm\BinaryNodeWithParent.h"
#include "..\Algorithm\TestClass.h"
using namespace std;
using namespace Test;
class BinaryNodeTest : public TestClass {
public:
	BinaryNodeTest(Log & log) : TestClass(log) {}
	~BinaryNodeTest(void) {}
	void Init(void);
};

