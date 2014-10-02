#include "BinaryNodeTest.h"

void BinaryNodeTest::Init(void)
{
	Add("Destructor", [&](){
		{
			Test::BinaryNode<int> * node = new Test::BinaryNode<int>(0);
			node->Left() = new Test::BinaryNode<int>(1);
			node->Right() = new Test::BinaryNode<int>(2);
			cout << node->Left()->Value() << endl;
			cout << node->Right()->Value() << endl;
			cout << node->Value() << endl;
			node->DeleteTree();
			delete node;
		}
		{
			Test::BinaryNodeWithParent<int> * node = new Test::BinaryNodeWithParent<int>(0);
			node->Left() = new Test::BinaryNodeWithParent<int>(1);
			node->Right() = new Test::BinaryNodeWithParent<int>(2);
			cout << node->Left()->Value() << endl;
			cout << node->Right()->Value() << endl;
			cout << node->Value() << endl;
			node->DeleteTree();
			delete node;
		}
	});
}