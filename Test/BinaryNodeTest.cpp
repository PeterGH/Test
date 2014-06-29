#include "BinaryNodeTest.h"

void BinaryNodeTest::Init(void)
{
	Add("Destructor", [&](){
		{
			Test::BinaryNode<int> * node = new Test::BinaryNode<int>(0);
			node->left = new Test::BinaryNode<int>(1);
			node->right = new Test::BinaryNode<int>(2);
			cout << node->left->content << endl;
			cout << node->right->content << endl;
			cout << node->content << endl;
			delete node;
		}
		{
			Test::BinaryNodeWithParent<int> * node = new Test::BinaryNodeWithParent<int>(0);
			node->left = new Test::BinaryNodeWithParent<int>(1);
			node->right = new Test::BinaryNodeWithParent<int>(2);
			cout << node->left->content << endl;
			cout << node->right->content << endl;
			cout << node->content << endl;
			delete node;
		}
	});
}