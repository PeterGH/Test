#pragma once

#include "..\Algorithm\BinaryTree.h"
#include "..\Algorithm\TestClass.h"

class BinaryTreeTest : public Test::TestClass {
public:
	BinaryTreeTest(Test::Log & log) : Test::TestClass(log) {}
	~BinaryTreeTest(void) {}
	void Init(void);
};

