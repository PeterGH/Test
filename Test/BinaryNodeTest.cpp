#include "BinaryNodeTest.h"

void BinaryNodeTest::Init(void)
{
	Add("Destructor", [&](){
		{
			BinaryNode<int> * node = new BinaryNode<int>(0);
			node->Left() = new BinaryNode<int>(1);
			node->Right() = new BinaryNode<int>(2);
			cout << node->Left()->Value() << endl;
			cout << node->Right()->Value() << endl;
			cout << node->Value() << endl;
			node->Print();
			node->Print2();
			node->DeleteTree();
			delete node;
		}
		{
			BinaryNodeWithParent<int> * node = new BinaryNodeWithParent<int>(0);
			node->Left() = new BinaryNodeWithParent<int>(1);
			node->Right() = new BinaryNodeWithParent<int>(2);
			cout << node->Left()->Value() << endl;
			cout << node->Right()->Value() << endl;
			cout << node->Value() << endl;
			node->Print();
			node->Print2();
			node->DeleteTree();
			delete node;
		}
	});

	Add("RandomTree", [&](){
		auto check = [&](vector<int> & v){
			BinaryNode<int> * node = BinaryNode<int>::ToRandomTree(v);
			node->Print2();
			BinaryNode<int>::DeleteTree(node);
		};
		{
			vector<int> v = { 0 };
			check(v);
			check(v);
			check(v);
		}
		{
			vector<int> v = { 0, 1 };
			for (int i = 0; i < 10; i++) check(v);
		}
		{
			vector<int> v = { 0, 1, 2 };
			for (int i = 0; i < 10; i++) check(v);
		}
		{
			vector<int> v = { 0, 1, 2, 3, 4 };
			for (int i = 0; i < 50; i++) check(v);
		}
		{
			for (int i = 0; i < 100; i++) {
				int n = 1 + (rand() % 25);
				vector<int> v;
				for (int j = 0; j < n; j++) {
					v.push_back(rand());
				}
				check(v);
			}
		}
	});

	Add("CompleteTree", [&](){
		auto check = [&](vector<int> & v){
			BinaryNode<int> * node = BinaryNode<int>::ToCompleteTree(v);
			BinaryNode<int> * node2 = BinaryNode<int>::FillToComplete(nullptr, v);
			if (v.size() == 0) {
				ASSERT1(node == nullptr);
				ASSERT1(node2 == nullptr);
			} else {
				node->Print2();
				bool complete = BinaryNode<int>::IsCompleteTree(node);
				bool complete2 = BinaryNode<int>::IsCompleteTree(node2);
				int equal = BinaryNode<int>::Compare(node, node2);
				int equal2 = BinaryNode<int>::Compare2(node, node2);
				BinaryNode<int>::DeleteTree(node);
				BinaryNode<int>::DeleteTree(node2);
				ASSERT1(complete == true);
				ASSERT1(complete2 == true);
				ASSERT1(equal == 0);
				ASSERT1(equal2 == 0);
			}
		};
		check(vector<int> { });
		check(vector<int> { 0 });
		check(vector<int> { 0, 1 });
		check(vector<int> { 0, 1, 2 });
		check(vector<int> { 0, 1, 2, 3 });
		check(vector<int> { 0, 1, 2, 3, 4 });
		for (int i = 5; i < 50; i++) {
			vector<int> v;
			for (int j = 0; j <= i; j++) {
				v.push_back(j);
			}
			check(v);
		}
	});

	Add("IsComplete", [&](){
		auto check = [&](BinaryNode<int> * node, bool expect){
			node->Print2();
			bool complete = BinaryNode<int>::IsCompleteTree(node);
			BinaryNode<int>::DeleteTree(node);
			ASSERT1(complete == expect);
		};
		{
			BinaryNode<int> * n0 = new BinaryNode<int>(0);
			check(n0, true);
		}
		{
			BinaryNode<int> * n0 = new BinaryNode<int>(0);
			BinaryNode<int> * n1 = new BinaryNode<int>(1);
			n0->Right() = n1;
			check(n0, false);
		}
		{
			BinaryNode<int> * n0 = new BinaryNode<int>(0);
			BinaryNode<int> * n1 = new BinaryNode<int>(1);
			BinaryNode<int> * n2 = new BinaryNode<int>(2);
			n0->Left() = n1;
			n1->Left() = n2;
			check(n0, false);
		}
		{
			BinaryNode<int> * n0 = new BinaryNode<int>(0);
			BinaryNode<int> * n1 = new BinaryNode<int>(1);
			BinaryNode<int> * n2 = new BinaryNode<int>(2);
			n0->Right() = n1;
			n1->Right() = n2;
			check(n0, false);
		}
		{
			BinaryNode<int> * n0 = new BinaryNode<int>(0);
			BinaryNode<int> * n1 = new BinaryNode<int>(1);
			BinaryNode<int> * n2 = new BinaryNode<int>(2);
			BinaryNode<int> * n3 = new BinaryNode<int>(3);
			n0->Left() = n1;
			n0->Right() = n2;
			n1->Left() = n3;
			check(n0, true);
		}
		{
			BinaryNode<int> * n0 = new BinaryNode<int>(0);
			BinaryNode<int> * n1 = new BinaryNode<int>(1);
			BinaryNode<int> * n2 = new BinaryNode<int>(2);
			BinaryNode<int> * n3 = new BinaryNode<int>(3);
			n0->Left() = n1;
			n0->Right() = n2;
			n1->Right() = n3;
			check(n0, false);
		}
		{
			BinaryNode<int> * n0 = new BinaryNode<int>(0);
			BinaryNode<int> * n1 = new BinaryNode<int>(1);
			BinaryNode<int> * n2 = new BinaryNode<int>(2);
			BinaryNode<int> * n3 = new BinaryNode<int>(3);
			BinaryNode<int> * n4 = new BinaryNode<int>(4);
			BinaryNode<int> * n5 = new BinaryNode<int>(5);
			n0->Left() = n1;
			n0->Right() = n2;
			n1->Left() = n3;
			n1->Right() = n4;
			n2->Left() = n5;
			check(n0, true);
		}
		{
			BinaryNode<int> * n0 = new BinaryNode<int>(0);
			BinaryNode<int> * n1 = new BinaryNode<int>(1);
			BinaryNode<int> * n2 = new BinaryNode<int>(2);
			BinaryNode<int> * n3 = new BinaryNode<int>(3);
			BinaryNode<int> * n4 = new BinaryNode<int>(4);
			BinaryNode<int> * n5 = new BinaryNode<int>(5);
			BinaryNode<int> * n6 = new BinaryNode<int>(6);
			n0->Left() = n1;
			n0->Right() = n2;
			n1->Left() = n3;
			n1->Right() = n4;
			n2->Left() = n5;
			n3->Left() = n6;
			check(n0, false);
		}
	});

	Add("FillToComplete", [&](){
		auto check = [&](BinaryNode<int> * node, vector<int> values){
			node->Print2();
			node = BinaryNode<int>::FillToComplete(node, values);
			node->Print2();
			BinaryNode<int>::DeleteTree(node);
		};
		{
			BinaryNode<int> * n0 = new BinaryNode<int>(0);
			vector<int> v = { 1 };
			check(n0, v);
		}
		{
			BinaryNode<int> * n0 = new BinaryNode<int>(0);
			vector<int> v = { 1, 2 };
			check(n0, v);
		}
		{
			BinaryNode<int> * n0 = new BinaryNode<int>(0);
			BinaryNode<int> * n1 = new BinaryNode<int>(1);
			n0->Left() = n1;
			vector<int> v = { 2 };
			check(n0, v);
		}
		{
			BinaryNode<int> * n0 = new BinaryNode<int>(0);
			BinaryNode<int> * n2 = new BinaryNode<int>(2);
			n0->Right() = n2;
			vector<int> v = { 1 };
			check(n0, v);
		}
		{
			BinaryNode<int> * n0 = new BinaryNode<int>(0);
			BinaryNode<int> * n1 = new BinaryNode<int>(1);
			n0->Left() = n1;
			vector<int> v = { 2, 3 };
			check(n0, v);
		}
		{
			BinaryNode<int> * n0 = new BinaryNode<int>(0);
			BinaryNode<int> * n2 = new BinaryNode<int>(2);
			n0->Right() = n2;
			vector<int> v = { 1, 3 };
			check(n0, v);
		}
		{
			BinaryNode<int> * n0 = new BinaryNode<int>(0);
			BinaryNode<int> * n2 = new BinaryNode<int>(2);
			BinaryNode<int> * n5 = new BinaryNode<int>(5);
			n0->Right() = n2;
			n2->Left() = n5;
			vector<int> v = { 1, 3 };
			check(n0, v);
		}
		{
			BinaryNode<int> * n0 = new BinaryNode<int>(0);
			BinaryNode<int> * n2 = new BinaryNode<int>(2);
			BinaryNode<int> * n5 = new BinaryNode<int>(5);
			n0->Right() = n2;
			n2->Left() = n5;
			vector<int> v = { 1, 3, 4, 6 };
			check(n0, v);
		}
	});
}