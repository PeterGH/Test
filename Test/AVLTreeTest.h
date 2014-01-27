#pragma once

#include "..\Algorithm\AVLTree.h"
#include "..\Algorithm\Random.h"
#include "..\Algorithm\TestClass.h"

class AVLTreeTest : public Test::TestClass {
public:
	AVLTreeTest(Test::Log & log) : Test::TestClass(log) {}
	~AVLTreeTest(void) {}
	void Init(void);
};

