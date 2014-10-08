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

	Add("Search", [&](){
		auto check = [&](size_t s){
			vector<int> v;
			for (size_t i = 0; i < s; i++) {
				v.push_back(i);
			}
			BinaryNode<int> * node = BinaryNode<int>::ToRandomTree(v);
			node->Print2();
			bool pass = true;
			int num;
			bool pass2 = true;
			int num2;
			BinaryNode<int> * n;
			for_each (v.begin(), v.end(), [&](int i){
				n = BinaryNode<int>::Search(node, i);
				if (n == nullptr || n->Value() != i) {
					pass = false;
					num = i;
				}
				i = s + rand();
				n = BinaryNode<int>::Search(node, i);
				if (n != nullptr && n->Value() == i) {
					pass2 = false;
					num2 = i;
				}
			});
			BinaryNode<int>::DeleteTree(node);
			ASSERT2(pass == true, String::Format("%d is not found", num));
			ASSERT2(pass2 == true, String::Format("%d is found", num2));
		};
		check(1);
		check(2);
		check(3);
		check(4);
		check(5);
		check(6);
		for (int i = 7; i < 50; i++) {
			check(i);
		}
	});

	Add("LowestCommonAncestor", [&](){
		auto check = [&](size_t s){
			vector<int> v;
			for (size_t i = 0; i < s; i++) {
				v.push_back(i);
			}
			BinaryNode<int> * node = BinaryNode<int>::ToRandomTree(v);
			node->Print2();
			for (size_t i = 0; i < s - 1; i++) {
				for (size_t j = i + 1; j < s; j++) {
					BinaryNode<int> * f = BinaryNode<int>::Search(node, v[i]);
					BinaryNode<int> * s = BinaryNode<int>::Search(node, v[j]);
					BinaryNode<int> * a = BinaryNode<int>::LowestCommonAncestor(node, f, s);
					BinaryNode<int> * a2 = BinaryNode<int>::LowestCommonAncestor(node, f, s);
					Logger().WriteInformation("LCA(%d, %d) = %d, %d\n", v[i], v[j], a->Value(), a2->Value());
					ASSERT1(a == a2);
				}
			}
			BinaryNode<int>::DeleteTree(node);
		};
		check(2);
		check(3);
		check(4);
		check(5);
		check(6);
		for (int i = 7; i < 50; i++) {
			check(i);
		}
	});

	Add("BuildTreePreOrderInOrder", [&](){
		auto check = [&](size_t s){
			BinaryNode<int> * node = nullptr;
			while (node == nullptr) node = BinaryNode<int>::RandomTree(s);
			node->Print2();

			int count = BinaryNode<int>::Size(node);
			unique_ptr<int[]> preOrder(new int[count]);
			unique_ptr<int[]> inOrder(new int[count]);

			function<function<void(int)>(unique_ptr<int[]> &, int &)>
			f = [&](unique_ptr<int[]> & v, int & k) -> function<void(int)> {
				function<void(int)> w = [&](int n){
					v[k++] = n;
				};
				return w;
			};

			int i = 0;
			int j = 0;
			BinaryNode<int>::PreOrderWalk(node, f(preOrder, i));
			BinaryNode<int>::InOrderWalk(node, f(inOrder, j));

			Logger().WriteInformation("PreOrder: ");
			Logger().Print(preOrder.get(), count);
			Logger().WriteInformation("InOrder: ");
			Logger().Print(inOrder.get(), count);

			int equal2;
			int equal3;
			BinaryNode<int> * node2 = BinaryNode<int>::BuildTreePreOrderInOrder(preOrder.get(), count, inOrder.get(), count);
			BinaryNode<int> * node3 = BinaryNode<int>::BuildTreePreOrderInOrder2(preOrder.get(), count, inOrder.get(), count);
			node2->Print2();
			node3->Print2();
			equal2 = BinaryNode<int>::Compare(node, node2);
			equal3 = BinaryNode<int>::Compare(node, node3);
			BinaryNode<int>::DeleteTree(node);
			BinaryNode<int>::DeleteTree(node2);
			BinaryNode<int>::DeleteTree(node3);
			ASSERT1(equal2 == 0);
			ASSERT1(equal3 == 0);
		};
		check(1);
		check(2);
		check(3);
		check(4);
		check(5);
		check(6);
		check(7);
		check(8);
		check(9);
		check(10);
		for (int i = 11; i < 50; i++) {
			check(i);
		}
	});

	Add("BuildTreeInOrderPostOrder", [&](){
		auto check = [&](size_t s){
			BinaryNode<int> * node = nullptr;
			while (node == nullptr) node = BinaryNode<int>::RandomTree(s);
			node->Print2();

			int count = BinaryNode<int>::Size(node);
			unique_ptr<int[]> inOrder(new int[count]);
			unique_ptr<int[]> postOrder(new int[count]);

			function<function<void(int)>(unique_ptr<int[]> &, int &)>
			f = [&](unique_ptr<int[]> & v, int & k) -> function<void(int)> {
				function<void(int)> w = [&](int n){
					v[k++] = n;
				};
				return w;
			};

			int i = 0;
			int j = 0;
			BinaryNode<int>::InOrderWalk(node, f(inOrder, i));
			BinaryNode<int>::PostOrderWalk(node, f(postOrder, j));

			Logger().WriteInformation("InOrder: ");
			Logger().Print(inOrder.get(), count);
			Logger().WriteInformation("PostOrder: ");
			Logger().Print(postOrder.get(), count);

			int equal2;
			int equal3;
			BinaryNode<int> * node2 = BinaryNode<int>::BuildTreeInOrderPostOrder(inOrder.get(), count, postOrder.get(), count);
			BinaryNode<int> * node3 = BinaryNode<int>::BuildTreeInOrderPostOrder2(inOrder.get(), count, postOrder.get(), count);
			node2->Print2();
			node3->Print2();
			equal2 = BinaryNode<int>::Compare(node, node2);
			equal3 = BinaryNode<int>::Compare(node, node3);
			BinaryNode<int>::DeleteTree(node);
			BinaryNode<int>::DeleteTree(node2);
			BinaryNode<int>::DeleteTree(node3);
			ASSERT1(equal2 == 0);
			ASSERT1(equal3 == 0);
		};
		check(1);
		check(2);
		check(3);
		check(4);
		check(5);
		check(6);
		check(7);
		check(8);
		check(9);
		check(10);
		for (int i = 11; i < 50; i++) {
			check(i);
		}
	});

	Add("ToPreOrderLinkList", [&](){
		auto check = [&](size_t s){
			BinaryNode<int> * node = nullptr;
			while (node == nullptr) node = BinaryNode<int>::RandomTree(s);
			node->Print2();

			vector<int> preOrder;
			auto f = [&](int n){ preOrder.push_back(n); };
			BinaryNode<int>::PreOrderWalk(node, f);
			Logger().Print(preOrder);

			DoubleNode<int> * list = (DoubleNode<int> * )BinaryNode<int>::ToPreOrderLinkList(node);
			cout << list;

			size_t i = 0;
			DoubleNode<int> * p = list;
			while (i < preOrder.size() && p != nullptr) {
				ASSERT1(preOrder[i] == p->Value());
				i++;
				p = p->Next();
			}
			DoubleNode<int>::DeleteList(list);
			ASSERT1(i == preOrder.size());
			ASSERT1(p == nullptr);
		};
		check(1);
		check(2);
		check(3);
		check(4);
		check(5);
		check(6);
		check(7);
		check(8);
		check(9);
		check(10);
		for (int i = 11; i < 50; i++) {
			check(i);
		}
	});

	Add("ToInOrderLinkList", [&](){
		auto check = [&](size_t s){
			BinaryNode<int> * node = nullptr;
			while (node == nullptr) node = BinaryNode<int>::RandomTree(s);
			node->Print2();

			vector<int> inOrder;
			auto f = [&](int n){ inOrder.push_back(n); };
			BinaryNode<int>::InOrderWalk(node, f);
			Logger().Print(inOrder);

			DoubleNode<int> * list = (DoubleNode<int> * )BinaryNode<int>::ToInOrderLinkList(node);
			cout << list;

			size_t i = 0;
			DoubleNode<int> * p = list;
			while (i < inOrder.size() && p != nullptr) {
				ASSERT1(inOrder[i] == p->Value());
				i++;
				p = p->Next();
			}
			DoubleNode<int>::DeleteList(list);
			ASSERT1(i == inOrder.size());
			ASSERT1(p == nullptr);
		};
		check(1);
		check(2);
		check(3);
		check(4);
		check(5);
		check(6);
		check(7);
		check(8);
		check(9);
		check(10);
		for (int i = 11; i < 50; i++) {
			check(i);
		}
	});

	Add("ToPostOrderLinkList", [&](){
		auto check = [&](size_t s){
			BinaryNode<int> * node = nullptr;
			while (node == nullptr) node = BinaryNode<int>::RandomTree(s);
			node->Print2();

			vector<int> postOrder;
			auto f = [&](int n){ postOrder.push_back(n); };
			BinaryNode<int>::PostOrderWalk(node, f);
			Logger().Print(postOrder);

			DoubleNode<int> * list = (DoubleNode<int> * )BinaryNode<int>::ToPostOrderLinkList(node);
			cout << list;

			size_t i = 0;
			DoubleNode<int> * p = list;
			while (i < postOrder.size() && p != nullptr) {
				ASSERT1(postOrder[i] == p->Value());
				i++;
				p = p->Next();
			}
			DoubleNode<int>::DeleteList(list);
			ASSERT1(i == postOrder.size());
			ASSERT1(p == nullptr);
		};
		check(1);
		check(2);
		check(3);
		check(4);
		check(5);
		check(6);
		check(7);
		check(8);
		check(9);
		check(10);
		for (int i = 11; i < 50; i++) {
			check(i);
		}
	});

	Add("ToBalancedTree", [&](){
		auto check = [&](size_t s){
			SingleNode<int> * list = SingleNode<int>::RandomList(s);
			cout << list;
			SingleNode<int> * list2 = (SingleNode<int> * )Node<int>::Clone(list);
			cout << list2;
			BinaryNode<int> * tree = BinaryNode<int>::ToBalancedTree(list);
			tree->Print2();
			BinaryNode<int> * tree2 = BinaryNode<int>::ToBalancedTree2(list2);
			tree2->Print2();
			int equal = BinaryNode<int>::Compare(tree, tree2);
			BinaryNode<int>::DeleteTree(tree);
			BinaryNode<int>::DeleteTree(tree2);
			ASSERT1(equal == 0);
		};
		check(1);
		check(2);
		check(3);
		check(4);
		check(5);
		check(6);
		check(7);
		check(8);
		check(9);
		check(10);
		for (int i = 11; i < 50; i++) {
			check(i);
		}
	});

	Add("GetBoundaryValues1", [&](){
		auto check = [&](int count) {
			Logger().WriteInformation("Get boundary values of a binary tree of %d nodes:\n", count);
			BinaryNode<int> * tree = nullptr;
			while (tree == nullptr) tree = BinaryNode<int>::RandomTree(count);
			tree->Print2();
			vector<int> values;
			tree->GetBoundaryValues(values);
			Logger().Print(values);
		};

		check(1);
		check(2);
		check(3);
		check(4);
		check(5);
		check(6);
		check(7);
		check(8);
		check(9);
		check(10);
		check(11);
		check(12);
		check(13);
		check(14);
		check(15);
		check(16);
	});

	Add("GetBoundaryValues2", [&](){
		Logger().WriteInformation("Get boundary values of a binary tree\n");
		BinaryNode<int> * n0 = new BinaryNode<int>(0);
		BinaryNode<int> * n1 = new BinaryNode<int>(1);
		BinaryNode<int> * n2 = new BinaryNode<int>(2);
		BinaryNode<int> * n3 = new BinaryNode<int>(3);
		BinaryNode<int> * n4 = new BinaryNode<int>(4);
		BinaryNode<int> * n5 = new BinaryNode<int>(5);
		BinaryNode<int> * n6 = new BinaryNode<int>(6);
		BinaryNode<int> * n7 = new BinaryNode<int>(7);
		BinaryNode<int> * n8 = new BinaryNode<int>(8);
		BinaryNode<int> * n9 = new BinaryNode<int>(9);
		BinaryNode<int> * n10 = new BinaryNode<int>(10);
		BinaryNode<int> * n11 = new BinaryNode<int>(11);
		BinaryNode<int> * n12 = new BinaryNode<int>(12);
		BinaryNode<int> * n13 = new BinaryNode<int>(13);
		BinaryNode<int> * n14 = new BinaryNode<int>(14);
		BinaryNode<int> * n15 = new BinaryNode<int>(15);
		BinaryNode<int> * n16 = new BinaryNode<int>(16);
		n0->Left() = n1;
		n0->Right() = n9;
		n1->Right() = n2;
		n2->Left() = n3;
		n2->Right() = n5;
		n3->Right() = n4;
		n5->Left() = n6;
		n5->Right() = n8;
		n6->Left() = n7;
		n9->Left() = n10;
		n10->Left() = n11;
		n10->Right() = n15;
		n11->Left() = n12;
		n11->Right() = n13;
		n13->Right() = n14;
		n15->Left() = n16;

		n0->Print2();

		vector<int> expect = { 0, 1, 2, 3, 4, 7, 8, 12, 14, 16, 15, 10, 9 };

		vector<int> values;
		n0->GetBoundaryValues(values);

		Logger().Print(values);

		ASSERT1(values.size() == expect.size());
		for (unsigned int i = 0; i < expect.size(); i++) {
			ASSERT1(values[i] == expect[i]);
		}
	});

}