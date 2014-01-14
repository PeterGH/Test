#include "BinaryTreeTest.h"

void BinaryTreeTest::Init(void)
{
	Add("Insert", [&](){
		Test::BinaryTree<int> tree;

		for (int i = 0; i < 20; i++) {
			tree.Insert(i);
		}

		tree.Print();
	});
}