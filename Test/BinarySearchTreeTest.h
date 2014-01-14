#pragma once

#include "..\Algorithm\BinarySearchTree.h"
#include "..\Algorithm\TestClass.h"

class BinarySearchTreeTest : public Test::TestClass {
public:
	BinarySearchTreeTest(Test::Log & log) : Test::TestClass(log) {}
	~BinarySearchTreeTest(void) {}
	void Init(void);
};

