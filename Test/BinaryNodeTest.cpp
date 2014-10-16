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
			node->Left(new BinaryNodeWithParent<int>(1));
			node->Right(new BinaryNodeWithParent<int>(2));
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
			BinaryNode<int> * node3 = nullptr;
			for_each (v.begin(), v.end(), [&](int i){
				node3 = BinaryNode<int>::Insert(node3, i);
			});
			if (v.size() == 0) {
				ASSERT1(node == nullptr);
				ASSERT1(node2 == nullptr);
				ASSERT1(node3 == nullptr);
			} else {
				node->Print2();
				bool complete = BinaryNode<int>::IsCompleteTree(node);
				bool complete2 = BinaryNode<int>::IsCompleteTree(node2);
				bool complete3 = BinaryNode<int>::IsCompleteTree(node3);
				int equal = BinaryNode<int>::Compare(node, node2);
				int equal2 = BinaryNode<int>::Compare2(node, node2);
				int equal3 = BinaryNode<int>::Compare(node, node3);
				BinaryNode<int>::DeleteTree(node);
				BinaryNode<int>::DeleteTree(node2);
				BinaryNode<int>::DeleteTree(node3);
				ASSERT1(complete == true);
				ASSERT1(complete2 == true);
				ASSERT1(complete3 == true);
				ASSERT1(equal == 0);
				ASSERT1(equal2 == 0);
				ASSERT1(equal3 == 0);
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

	Add("LowestCommonAncestor1", [&](){
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
					BinaryNode<int> * a2 = BinaryNode<int>::LowestCommonAncestor2(node, f, s);
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

	Add("LowestCommonAncestor2", [&](){
		auto check = [&](size_t s){
			vector<int> v;
			for (size_t i = 0; i < s; i++) {
				v.push_back(i);
			}
			BinaryNode<int> * n = BinaryNode<int>::ToRandomTree(v);
			BinaryNodeWithParent<int> * node = BinaryNodeWithParent<int>::Clone2(n);
			BinaryNode<int>::DeleteTree(n);
			node->Print2();
			for (size_t i = 0; i < s - 1; i++) {
				for (size_t j = i + 1; j < s; j++) {
					BinaryNodeWithParent<int> * f = (BinaryNodeWithParent<int> *)BinaryNode<int>::Search(node, v[i]);
					BinaryNodeWithParent<int> * s = (BinaryNodeWithParent<int> *)BinaryNode<int>::Search(node, v[j]);
					BinaryNodeWithParent<int> * a = BinaryNodeWithParent<int>::LowestCommonAncestor(f, s);
					BinaryNodeWithParent<int> * a2 = BinaryNodeWithParent<int>::LowestCommonAncestor2(f, s);
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

	Add("LowestCommonAncestor3", [&](){
		auto check = [&](size_t s){
			vector<int> v;
			for (size_t i = 0; i < s; i++) {
				v.push_back(i);
			}
			BinaryNode<int> * n = BinaryNode<int>::SearchTreeRandom(v);
			BinaryNodeWithParent<int> * node = BinaryNodeWithParent<int>::Clone2(n);
			BinaryNode<int>::DeleteTree(n);
			node->Print2();
			for (size_t i = 0; i < s - 1; i++) {
				for (size_t j = i + 1; j < s; j++) {
					BinaryNodeWithParent<int> * f = (BinaryNodeWithParent<int> *)BinaryNode<int>::Search(node, v[i]);
					BinaryNodeWithParent<int> * s = (BinaryNodeWithParent<int> *)BinaryNode<int>::Search(node, v[j]);
					BinaryNodeWithParent<int> * a = (BinaryNodeWithParent<int> *)BinaryNode<int>::LowestCommonAncestor(node, f, s);
					BinaryNodeWithParent<int> * a2 = (BinaryNodeWithParent<int> *)BinaryNode<int>::LowestCommonAncestor2(node, f, s);
					BinaryNodeWithParent<int> * a3 = BinaryNodeWithParent<int>::LowestCommonAncestor(f, s);
					BinaryNodeWithParent<int> * a4 = BinaryNodeWithParent<int>::LowestCommonAncestor2(f, s);
					BinaryNodeWithParent<int> * a5 = (BinaryNodeWithParent<int> *)BinaryNode<int>::SearchTreeLowestCommonAncestor(node, v[i], v[j]);
					Logger().WriteInformation("LCA(%d, %d) = %d, %d, %d, %d, %d\n", v[i], v[j], a->Value(), a2->Value(), a3->Value(), a4->Value(), a5->Value());
					ASSERT1(a == a2);
					ASSERT1(a == a3);
					ASSERT1(a == a4);
					ASSERT1(a == a5);
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

	Add("Serialize", [&](){
		auto check = [&](int count) {
			Logger().WriteInformation("Serialize/deserialize a binary tree of %d nodes:\n", count);
			BinaryNode<int> * tree = nullptr;
			while (tree == nullptr) tree = BinaryNode<int>::RandomTree(count);
			tree->Print2();
			stringstream ss;
			BinaryNode<int>::Serialize(tree, ss);
			Logger().WriteInformation("%s\n", ss.str().c_str());
			BinaryNode<int> * tree2 = BinaryNode<int>::Deserialize(ss);
			tree2->Print2();
			int equal = BinaryNode<int>::Compare(tree, tree2);
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
		check(11);
		check(12);
		check(13);
		check(14);
		check(15);
		check(16);
	});

	Add("Clone1", [&](){
		auto check = [&](size_t s) {
			Node<int> * node = nullptr;
			while (node == nullptr) node = BinaryNode<int>::RandomTree(s);
			((BinaryNode<int> *)node)->Print2();
			BinaryNode<int> * copy = (BinaryNode<int> *)Node<int>::Clone(node);
			copy->Print2();
			int equal = BinaryNode<int>::Compare((BinaryNode<int> *)node, copy);
			BinaryNode<int>::DeleteTree((BinaryNode<int> *)node);
			BinaryNode<int>::DeleteTree(copy);
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
	});

	Add("Clone2", [&](){
		auto check = [&](size_t s) {
			BinaryNode<int> * node = nullptr;
			while (node == nullptr) node = BinaryNode<int>::RandomTree(s);
			node->Print2();
			BinaryNodeWithParent<int> * copy = BinaryNodeWithParent<int>::Clone2(node);
			copy->Print2();
			int equal = BinaryNode<int>::Compare(node, copy);
			BinaryNode<int>::DeleteTree(node);
			BinaryNode<int>::DeleteTree(copy);
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
	});

	Add("PreOrder", [&](){
		for (int i = 0; i < 100; i++) {
			int count = 1 + rand();
			BinaryNode<int> * tree = nullptr;
			while (tree == nullptr) tree = BinaryNode<int>::RandomTree(count);
			count = tree->Size();

			BinaryNodeWithParent<int> * tree2 = BinaryNodeWithParent<int>::Clone2(tree);

			cout << "Run " << i << ", " << count << " elements" << endl;

			if (count < 50) {
				tree->Print2();
				tree2->Print2();
			}

			vector<int> v1;
			vector<int> v2;
			vector<int> v3;
			vector<int> v4;
			vector<int> v5;
			vector<int> v6;
			vector<int> v7;
			vector<int> v8;
			vector<int> v9;

			function<function<void(int)>(vector<int> &)> f = [&](vector<int> & v)->function < void(int) > {
				function<void(int)> w = [&](int n){
					v.push_back(n);
				};

				return w;
			};

			tree->PreOrderWalk(f(v1));
			tree->PreOrderWalkWithStack(f(v2));
			tree->PreOrderWalkWithStack2(f(v3));
			tree->PreOrderWalkWithStack3(f(v4));
			tree2->PreOrderWalk(f(v5));
			tree2->PreOrderWalkWithStack(f(v6));
			tree2->PreOrderWalkWithStack2(f(v7));
			tree2->PreOrderWalkWithStack3(f(v8));
			tree2->PreOrderWalkWithOutStack(f(v9));

			BinaryNode<int>::DeleteTree(tree);
			BinaryNode<int>::DeleteTree(tree2);

			ASSERT2(v1.size() == count, String::Format("Expect %d elements, actual visited %d", count, v1.size()));
			ASSERT2(v2.size() == count, String::Format("Expect %d elements, actual visited %d", count, v2.size()));
			ASSERT2(v3.size() == count, String::Format("Expect %d elements, actual visited %d", count, v3.size()));
			ASSERT2(v4.size() == count, String::Format("Expect %d elements, actual visited %d", count, v4.size()));
			ASSERT2(v5.size() == count, String::Format("Expect %d elements, actual visited %d", count, v5.size()));
			ASSERT2(v6.size() == count, String::Format("Expect %d elements, actual visited %d", count, v6.size()));
			ASSERT2(v7.size() == count, String::Format("Expect %d elements, actual visited %d", count, v7.size()));
			ASSERT2(v8.size() == count, String::Format("Expect %d elements, actual visited %d", count, v8.size()));
			ASSERT2(v9.size() == count, String::Format("Expect %d elements, actual visited %d", count, v9.size()));

			for (int j = 0; j < count; j++) {
				ASSERT1(v1[j] == v2[j]);
				ASSERT1(v1[j] == v3[j]);
				ASSERT1(v1[j] == v4[j]);
				ASSERT1(v1[j] == v5[j]);
				ASSERT1(v1[j] == v6[j]);
				ASSERT1(v1[j] == v7[j]);
				ASSERT1(v1[j] == v8[j]);
				ASSERT1(v1[j] == v9[j]);
			}
		}
	});

	Add("InOrder", [&](){
		for (int i = 0; i < 100; i++) {
			int count = 1 + rand();
			BinaryNode<int> * tree = nullptr;
			while (tree == nullptr) tree = BinaryNode<int>::RandomTree(count);
			count = tree->Size();

			BinaryNodeWithParent<int> * tree2 = BinaryNodeWithParent<int>::Clone2(tree);

			cout << "Run " << i << ", " << count << " elements" << endl;

			if (count < 50) {
				tree->Print2();
				tree2->Print2();
			}

			vector<int> v1;
			vector<int> v2;
			vector<int> v3;
			vector<int> v4;
			vector<int> v5;
			vector<int> v6;
			vector<int> v7;

			function<function<void(int)>(vector<int> &)> f = [&](vector<int> & v)->function < void(int) > {
				function<void(int)> w = [&](int n){
					v.push_back(n);
				};

				return w;
			};

			tree->InOrderWalk(f(v1));
			tree->InOrderWalkWithStack(f(v2));
			tree->InOrderWalkWithStack2(f(v3));
			tree2->InOrderWalk(f(v4));
			tree2->InOrderWalkWithStack(f(v5));
			tree2->InOrderWalkWithStack2(f(v6));
			tree2->InOrderWalkWithOutStack(f(v7));

			BinaryNode<int>::DeleteTree(tree);
			BinaryNode<int>::DeleteTree(tree2);

			ASSERT2(v1.size() == count, String::Format("Expect %d elements, actual visited %d", count, v1.size()));
			ASSERT2(v2.size() == count, String::Format("Expect %d elements, actual visited %d", count, v2.size()));
			ASSERT2(v3.size() == count, String::Format("Expect %d elements, actual visited %d", count, v3.size()));
			ASSERT2(v4.size() == count, String::Format("Expect %d elements, actual visited %d", count, v4.size()));
			ASSERT2(v5.size() == count, String::Format("Expect %d elements, actual visited %d", count, v5.size()));
			ASSERT2(v6.size() == count, String::Format("Expect %d elements, actual visited %d", count, v6.size()));
			ASSERT2(v7.size() == count, String::Format("Expect %d elements, actual visited %d", count, v7.size()));

			for (int j = 0; j < count; j++) {
				ASSERT1(v1[j] == v2[j]);
				ASSERT1(v1[j] == v3[j]);
				ASSERT1(v1[j] == v4[j]);
				ASSERT1(v1[j] == v5[j]);
				ASSERT1(v1[j] == v6[j]);
				ASSERT1(v1[j] == v7[j]);
			}
		}
	});

	Add("PostOrder", [&](){
		for (int i = 0; i < 100; i++) {
			int count = 1 + rand();
			BinaryNode<int> * tree = nullptr;
			while (tree == nullptr) tree = BinaryNode<int>::RandomTree(count);
			count = tree->Size();

			BinaryNodeWithParent<int> * tree2 = BinaryNodeWithParent<int>::Clone2(tree);

			cout << "Run " << i << ", " << count << " elements" << endl;

			if (count < 50) {
				tree->Print2();
				tree2->Print2();
			}

			vector<int> v1;
			vector<int> v2;
			vector<int> v3;
			vector<int> v4;
			vector<int> v5;
			vector<int> v6;
			vector<int> v7;

			function<function<void(int)>(vector<int> &)> f = [&](vector<int> & v)->function < void(int) > {
				function<void(int)> w = [&](int n){
					v.push_back(n);
				};

				return w;
			};

			tree->PostOrderWalk(f(v1));
			tree->PostOrderWalkWithStack(f(v2));
			tree->PostOrderWalkWithStack2(f(v3));
			tree2->PostOrderWalk(f(v4));
			tree2->PostOrderWalkWithStack(f(v5));
			tree2->PostOrderWalkWithStack2(f(v6));
			tree2->PostOrderWalkWithOutStack(f(v7));

			BinaryNode<int>::DeleteTree(tree);
			BinaryNode<int>::DeleteTree(tree2);

			ASSERT2(v1.size() == count, String::Format("Expect %d elements, actual visited %d", count, v1.size()));
			ASSERT2(v2.size() == count, String::Format("Expect %d elements, actual visited %d", count, v2.size()));
			ASSERT2(v3.size() == count, String::Format("Expect %d elements, actual visited %d", count, v3.size()));
			ASSERT2(v4.size() == count, String::Format("Expect %d elements, actual visited %d", count, v4.size()));
			ASSERT2(v5.size() == count, String::Format("Expect %d elements, actual visited %d", count, v5.size()));
			ASSERT2(v6.size() == count, String::Format("Expect %d elements, actual visited %d", count, v6.size()));
			ASSERT2(v7.size() == count, String::Format("Expect %d elements, actual visited %d", count, v7.size()));

			for (int j = 0; j < count; j++) {
				ASSERT1(v1[j] == v2[j]);
				ASSERT1(v1[j] == v3[j]);
				ASSERT1(v1[j] == v4[j]);
				ASSERT1(v1[j] == v5[j]);
				ASSERT1(v1[j] == v6[j]);
				ASSERT1(v1[j] == v7[j]);
			}
		}
	});

	Add("Height", [&](){
		for (int i = 0; i < 100; i++) {
			int count = 1 + rand();
			BinaryNode<int> * tree = nullptr;
			while (tree == nullptr) tree = BinaryNode<int>::RandomTree(count);
			count = tree->Size();

			BinaryNodeWithParent<int> * tree2 = BinaryNodeWithParent<int>::Clone2(tree);

			cout << "Run " << i << ", " << count << " elements" << endl;

			if (count < 50) {
				tree->Print2();
				tree2->Print2();
			}

			int height = BinaryNode<int>::Height(tree);
			int height2 = BinaryNodeWithParent<int>::Height2(tree2);

			BinaryNode<int>::DeleteTree(tree);
			BinaryNode<int>::DeleteTree(tree2);

			ASSERT1(height == height2);
		}
	});

	Add("LevelOrderWalk1", [&](){
		auto check = [&](int count) {
			Logger().WriteInformation("Level order walk a binary tree of %d nodes:\n", count);
			BinaryNode<int> * tree = nullptr;
			while (tree == nullptr) tree = BinaryNode<int>::RandomTree(count);
			BinaryNodeWithRightSibling<int> * tree2 = BinaryNodeWithRightSibling<int>::Clone2(tree);
			BinaryNodeWithRightSibling<int>::SetRightSibling(tree2);

			tree->Print2();
			tree2->Print2();

			vector<int> v1;
			vector<int> v2;
			vector<int> v3;

			auto visit = [&](vector<int> & v) -> function<void(int)> {
				function<void(int)> f = [&](int c) {
					v.push_back(c);
				};
				return f;
			};

			tree->LevelOrderWalk(visit(v1));
			tree->LevelOrderWalk2(visit(v2));
			tree2->LevelOrderWalk3(visit(v3));
			Logger().Print(v1);
			Logger().Print(v2);
			Logger().Print(v3);

			ASSERT1(v1.size() == v2.size());
			ASSERT1(v1.size() == v3.size());
			for (unsigned int i = 0; i < v1.size(); i++) {
				ASSERT1(v1[i] == v2[i]);
				ASSERT1(v1[i] == v3[i]);
			}
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

	Add("LevelOrderWalk2", [&](){
		auto check = [&](int count) {
			Logger().WriteInformation("Level order walk a binary tree of %d nodes:\n", count);
			BinaryNode<int> * tree = nullptr;
			while (tree == nullptr) tree = BinaryNode<int>::RandomCompleteTree(count);

			BinaryNodeWithRightSibling<int> * tree2 = Test::BinaryNodeWithRightSibling<int>::Clone2(tree);
			BinaryNodeWithRightSibling<int>::SetRightSibling(tree2);

			BinaryNodeWithRightSibling<int> * tree3 = Test::BinaryNodeWithRightSibling<int>::Clone2(tree);
			BinaryNodeWithRightSibling<int>::SetRightSibling2(tree3);

			tree->Print2();
			tree2->Print2();
			tree3->Print2();

			vector<int> v1;
			vector<int> v2;
			vector<int> v3;
			vector<int> v4;

			auto visit = [&](vector<int> & v) -> function<void(int)> {
				function<void(int)> f = [&](int c) {
					v.push_back(c);
				};
				return f;
			};

			tree->LevelOrderWalk(visit(v1));
			tree->LevelOrderWalk2(visit(v2));
			tree2->LevelOrderWalk3(visit(v3));
			tree3->LevelOrderWalk3(visit(v4));

			Logger().Print(v1);
			Logger().Print(v2);
			Logger().Print(v3);
			Logger().Print(v4);

			ASSERT1(v1.size() == v2.size());
			ASSERT1(v1.size() == v3.size());
			ASSERT1(v1.size() == v4.size());
			for (unsigned int i = 0; i < v1.size(); i++) {
				ASSERT1(v1[i] == v2[i]);
				ASSERT1(v1[i] == v3[i]);
				ASSERT1(v1[i] == v4[i]);
			}
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

	Add("Min", [&](){
		auto check = [&](size_t s){
			vector<int> v;
			for (size_t i = 0; i < s; i++) {
				v.push_back(rand());
			}
			BinaryNode<int> * node = BinaryNode<int>::SearchTreeRandom(v);
			node->Print2();
			int m = *min_element(v.begin(), v.end());
			BinaryNode<int> * m1 = BinaryNode<int>::Min(node);
			BinaryNode<int> * m2 = BinaryNode<int>::SearchTreeMin(node);
			Logger().WriteInformation("Min = %d, %d, %d\n", m, m1->Value(), m2->Value());
			ASSERT1(m == m1->Value());
			ASSERT1(m == m2->Value());
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

	Add("Max", [&](){
		auto check = [&](size_t s){
			vector<int> v;
			for (size_t i = 0; i < s; i++) {
				v.push_back(rand());
			}
			BinaryNode<int> * node = BinaryNode<int>::SearchTreeRandom(v);
			node->Print2();
			int m = *max_element(v.begin(), v.end());
			BinaryNode<int> * m1 = BinaryNode<int>::Max(node);
			BinaryNode<int> * m2 = BinaryNode<int>::SearchTreeMax(node);
			Logger().WriteInformation("Max = %d, %d, %d\n", m, m1->Value(), m2->Value());
			ASSERT1(m == m1->Value());
			ASSERT1(m == m2->Value());
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

	Add("Successor", [&](){
		auto check = [&](size_t s){
			vector<int> v;
			for (size_t i = 0; i < s; i++) {
				v.push_back(i);
			}
			BinaryNodeWithParent<int> * node = BinaryNodeWithParent<int>::RandomTree2(v);
			node->Print2();
			for (size_t i = 0; i < s; i++) {
				BinaryNodeWithParent<int> * p = (BinaryNodeWithParent<int> *)BinaryNode<int>::SearchTreeSearch2(node, i);
				BinaryNodeWithParent<int> * n = BinaryNodeWithParent<int>::SearchTreeSuccessor(p);
				Logger().WriteInformation("Successor(%d) = %s\n", i, n == nullptr ? "null" : to_string(n->Value()).c_str());
				if (i == s - 1) ASSERT1(n == nullptr);
				else ASSERT1(i + 1 == n->Value());
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

	Add("Predecessor", [&](){
		auto check = [&](size_t s){
			vector<int> v;
			for (size_t i = 0; i < s; i++) {
				v.push_back(i);
			}
			BinaryNodeWithParent<int> * node = BinaryNodeWithParent<int>::RandomTree2(v);
			node->Print2();
			for (size_t i = 0; i < s; i++) {
				BinaryNodeWithParent<int> * p = (BinaryNodeWithParent<int> *)BinaryNode<int>::SearchTreeSearch2(node, i);
				BinaryNodeWithParent<int> * n = BinaryNodeWithParent<int>::SearchTreePredecessor(p);
				Logger().WriteInformation("Predecessor(%d) = %s\n", i, n == nullptr ? "null" : to_string(n->Value()).c_str());
				if (i == 0) ASSERT1(n == nullptr);
				else ASSERT1(i - 1 == n->Value());
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

	Add("Delete1", [&]() {
		auto check = [&](size_t s){
			vector<int> v;
			for (size_t i = 0; i < s; i++) {
				v.push_back(i);
			}
			BinaryNodeWithParent<int> * node = BinaryNodeWithParent<int>::RandomTree2(v);
			node->Print2();
			for (size_t i = 0; i < s; i++) {
				BinaryNodeWithParent<int> * n;
				if (i % 2 == 0) n = (BinaryNodeWithParent<int> *)BinaryNode<int>::SearchTreeMin(node);
				else n = (BinaryNodeWithParent<int> *)BinaryNode<int>::SearchTreeMax(node);
				Logger().WriteInformation("Delete %d\n", n->Value());
				node = BinaryNodeWithParent<int>::SearchTreeDelete(node, n);
				if (node != nullptr) node->Print2();
			}
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

	Add("Delete2", [&]() {
		auto check = [&](size_t s){
			vector<int> v(s);
			generate(v.begin(), v.end(), rand);
			sort(v.begin(), v.end());
			BinaryNodeWithParent<int> * node = BinaryNodeWithParent<int>::RandomTree2(v);
			node->Print2();
			for (size_t i = 0; i < s; i++) {
				vector<int>::iterator it = v.begin() + (rand() % v.size());
				BinaryNodeWithParent<int> * n = (BinaryNodeWithParent<int> *)BinaryNode<int>::SearchTreeSearch2(node, *it);
				v.erase(it);
				Logger().WriteInformation("Delete %d\n", n->Value());
				node = BinaryNodeWithParent<int>::SearchTreeDelete(node, n);
				if (node != nullptr) node->Print2();
			}
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
}