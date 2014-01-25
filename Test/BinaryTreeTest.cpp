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

	Add("Height", [&](){
		Test::BinaryTree<int> tree;
		ASSERT1(0 == tree.Height());

		int count = Test::Random::Next();
		int h1, h2;
		for (int i = 0; i < count; i++) {
			tree.Insert(i);
			h1 = Test::BinaryTree<int>::Height(i);
			h2 = tree.Height();
			ASSERT2(h1 == h2, Test::String::Format("h1 %d != h2 %d", h1, h2));
		}

		tree.Print();
	});
}