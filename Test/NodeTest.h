#pragma once
#include "..\Algorithm\Node.h"
#include "..\Algorithm\Node1.h"
#include "..\Algorithm\Node2.h"
#include "..\Algorithm\DoubleNode.h"
#include "..\Algorithm\SingleNode.h"
#include "..\Algorithm\TestClass.h"
class NodeTest : public Test::TestClass {
public:
	NodeTest(Test::Log & log) : Test::TestClass(log) {}
	~NodeTest(void) {}
	void Init(void);
};

