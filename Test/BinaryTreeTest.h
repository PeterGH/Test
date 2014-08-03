#pragma once
#include "..\Algorithm\BinaryNode.h"
#include "..\Algorithm\BinaryNodeWithParent.h"
#include "..\Algorithm\BinaryNodeWithRightSibling.h"
#include "..\Algorithm\CompleteBinaryTree.h"
#include "..\Algorithm\Random.h"
#include "..\Algorithm\TestClass.h"

class BinaryTreeTest : public Test::TestClass {
public:
	BinaryTreeTest(Test::Log & log) : Test::TestClass(log) {}
	~BinaryTreeTest(void) {}
	void Init(void);
};

