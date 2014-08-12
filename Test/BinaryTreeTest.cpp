#include "BinaryTreeTest.h"

void BinaryTreeTest::Init(void)
{
	Add("BinaryNodeInsert", [&](){
		Test::CompleteBinaryTree<int, Test::BinaryNode> tree;

		for (int i = 0; i < 20; i++) {
			tree.Insert(i);
		}

		tree.Print();

		int v;
		for (int i = 0; i < 20; i++) {
			v = tree.Search(i)->content;
			ASSERT1(v == i);
		}

		int minV = tree.Min();
		ASSERT1(minV == 0);

		int maxV = tree.Max();
		ASSERT1(maxV == 19);

		Logger().WriteInformation("PreOrder iteration:\n");
		for (Test::PreOrderBinaryIterator<int, Test::BinaryNode> it = tree.PreOrderBegin(); it != tree.PreOrderEnd(); it++) {
			Logger().WriteInformation(" %d", *it);
		}

		Logger().WriteInformation("\n");

		Logger().WriteInformation("InOrder iteration:\n");
		for (Test::InOrderBinaryIterator<int, Test::BinaryNode> it = tree.InOrderBegin(); it != tree.InOrderEnd(); it++) {
			Logger().WriteInformation(" %d", *it);
		}

		Logger().WriteInformation("\n");

		Logger().WriteInformation("PostOrder iteration:\n");
		for (Test::PostOrderBinaryIterator<int, Test::BinaryNode> it = tree.PostOrderBegin(); it != tree.PostOrderEnd(); it++) {
			Logger().WriteInformation(" %d", *it);
		}

		Logger().WriteInformation("\n");

		int a = tree.LowestCommonAncestor(10, 15);
		Logger().WriteInformation("10 and 15 lowest common ancestor is %d\n", a);
		int b = tree.LowestCommonAncestor2(10, 15);
		Logger().WriteInformation("10 and 15 lowest common ancestor is %d\n", b);
	});

	Add("BinaryNodeWithParentInsert", [&](){
		Test::CompleteBinaryTree<int, Test::BinaryNodeWithParent> tree;

		for (int i = 0; i < 20; i++) {
			tree.Insert(i);
		}

		tree.Print();

		int v;
		for (int i = 0; i < 20; i++) {
			v = tree.Search(i)->content;
			ASSERT1(v == i);
		}

		int minV = tree.Min();
		ASSERT1(minV == 0);

		int maxV = tree.Max();
		ASSERT1(maxV == 19);

		Logger().WriteInformation("PreOrder iteration:\n");
		for (Test::PreOrderBinaryIterator<int, Test::BinaryNodeWithParent> it = tree.PreOrderBegin(); it != tree.PreOrderEnd(); it++) {
			Logger().WriteInformation(" %d", *it);
		}

		Logger().WriteInformation("\n");

		Logger().WriteInformation("InOrder iteration:\n");
		for (Test::InOrderBinaryIterator<int, Test::BinaryNodeWithParent> it = tree.InOrderBegin(); it != tree.InOrderEnd(); it++) {
			Logger().WriteInformation(" %d", *it);
		}

		Logger().WriteInformation("\n");

		Logger().WriteInformation("PostOrder iteration:\n");
		for (Test::PostOrderBinaryIterator<int, Test::BinaryNodeWithParent> it = tree.PostOrderBegin(); it != tree.PostOrderEnd(); it++) {
			Logger().WriteInformation(" %d", *it);
		}

		Logger().WriteInformation("\n");

		int a = tree.LowestCommonAncestor(10, 15);
		Logger().WriteInformation("10 and 15 lowest common ancestor is %d\n", a);
		int b = tree.LowestCommonAncestor2(10, 15);
		Logger().WriteInformation("10 and 15 lowest common ancestor is %d\n", b);
	});

	Add("BinaryNodeHeight", [&](){
		Test::CompleteBinaryTree<int, Test::BinaryNode> tree;
		ASSERT1(0 == tree.Height());

		int count = Test::Random::Next();
		int h1, h2;
		for (int i = 0; i < count; i++) {
			tree.Insert(i);
			h1 = Test::CompleteBinaryTree<int, Test::BinaryNode>::Height(i);
			h2 = tree.Height();
			ASSERT2(h1 == h2, Test::String::Format("h1 %d != h2 %d", h1, h2));
		}

		tree.Print();
	});

	Add("BinaryNodeWithParentHeight", [&](){
		Test::CompleteBinaryTree<int, Test::BinaryNodeWithParent> tree;
		ASSERT1(0 == tree.Height());

		int count = Test::Random::Next();
		int h1, h2;
		for (int i = 0; i < count; i++) {
			tree.Insert(i);
			h1 = Test::CompleteBinaryTree<int, Test::BinaryNode>::Height(i);
			h2 = tree.Height();
			ASSERT2(h1 == h2, Test::String::Format("h1 %d != h2 %d", h1, h2));
		}

		tree.Print();
	});

	Add("BinaryNodeLCA", [&](){
		Test::CompleteBinaryTree<int, Test::BinaryNode> tree;

		for (int i = 0; i < 20; i++) {
			tree.Insert(i);
		}

		tree.Print();

		for (int i = 0; i < 19; i++) {
			for (int j = i + 1; j < 20; j++) {
				int a = tree.LowestCommonAncestor(i, j);
				int b = tree.LowestCommonAncestor2(i, j);
				Logger().WriteInformation("%d and %d lowest common ancestor is (%d, %d)\n", i, j, a, b);
				ASSERT1(a == b);
			}
		}
	});

	Add("BinaryNodeWithParentLCA", [&](){
		Test::CompleteBinaryTree<int, Test::BinaryNodeWithParent> tree;

		for (int i = 0; i < 20; i++) {
			tree.Insert(i);
		}

		tree.Print();

		for (int i = 0; i < 19; i++) {
			for (int j = i + 1; j < 20; j++) {
				int a = tree.LowestCommonAncestor(i, j);
				int b = tree.LowestCommonAncestor2(i, j);
				Logger().WriteInformation("%d and %d lowest common ancestor is (%d, %d)\n", i, j, a, b);
				ASSERT1(a == b);
			}
		}
	});

	Add("PreOrder", [&](){
		for (int i = 0; i < 100; i++) {
			Test::CompleteBinaryTree<int, Test::BinaryNode> tree;
			Test::CompleteBinaryTree<int, Test::BinaryNodeWithParent> tree2;
			int count = 1 + Test::Random::Next();

			for (int j = 0; j < count; j++) {
				int v = Test::Random::Next();
				tree.Insert(v);
				tree2.Insert(v);
			}

			cout << "Run " << i << ", " << count << " elements, height " << tree.Height() << endl;

			vector<int> v1;
			vector<int> v2;
			vector<int> v3;
			vector<int> v4;
			vector<int> v5;
			vector<int> v6;
			vector<int> v7;
			vector<int> v8;

			function<function<void(int)>(vector<int> &)> f = [&](vector<int> & v)->function < void(int) > {
				function<void(int)> w = [&](int n){
					v.push_back(n);
				};

				return w;
			};

			tree.PreOrderWalk(f(v1));
			tree.PreOrderWalkWithStack(f(v2));
			tree.PreOrderWalkWithStack2(f(v3));
			tree.PreOrderWalkWithStack3(f(v4));
			tree2.PreOrderWalk(f(v5));
			tree2.PreOrderWalkWithStack(f(v6));
			tree2.PreOrderWalkWithStack2(f(v7));
			tree2.PreOrderWalkWithStack3(f(v8));

			ASSERT2(v1.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v1.size()));
			ASSERT2(v2.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v2.size()));
			ASSERT2(v3.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v3.size()));
			ASSERT2(v4.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v4.size()));
			ASSERT2(v5.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v5.size()));
			ASSERT2(v6.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v6.size()));
			ASSERT2(v7.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v7.size()));
			ASSERT2(v8.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v8.size()));

			for (int j = 0; j < count; j++) {
				ASSERT1(v1[j] == v2[j]);
				ASSERT1(v1[j] == v3[j]);
				ASSERT1(v1[j] == v4[j]);
				ASSERT1(v1[j] == v5[j]);
				ASSERT1(v1[j] == v6[j]);
				ASSERT1(v1[j] == v7[j]);
				ASSERT1(v1[j] == v8[j]);
			}
		}
	});

	Add("InOrder", [&](){
		for (int i = 0; i < 100; i++) {
			Test::CompleteBinaryTree<int, Test::BinaryNode> tree;
			Test::CompleteBinaryTree<int, Test::BinaryNodeWithParent> tree2;
			int count = 1 + Test::Random::Next();

			for (int j = 0; j < count; j++) {
				int v = Test::Random::Next();
				tree.Insert(v);
				tree2.Insert(v);
			}

			cout << "Run " << i << ", " << count << " elements, height " << tree.Height() << endl;

			vector<int> v1;
			vector<int> v2;
			vector<int> v3;
			vector<int> v4;
			vector<int> v5;
			vector<int> v6;

			function<function<void(int)>(vector<int> &)> f = [&](vector<int> & v)->function < void(int) > {
				function<void(int)> w = [&](int n){
					v.push_back(n);
				};

				return w;
			};

			tree.InOrderWalk(f(v1));
			tree.InOrderWalkWithStack(f(v2));
			tree.InOrderWalkWithStack2(f(v3));
			tree2.InOrderWalk(f(v4));
			tree2.InOrderWalkWithStack(f(v5));
			tree2.InOrderWalkWithStack2(f(v6));

			ASSERT2(v1.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v1.size()));
			ASSERT2(v2.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v2.size()));
			ASSERT2(v3.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v3.size()));
			ASSERT2(v4.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v4.size()));
			ASSERT2(v5.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v4.size()));
			ASSERT2(v6.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v4.size()));

			for (int j = 0; j < count; j++) {
				ASSERT1(v1[j] == v2[j]);
				ASSERT1(v1[j] == v3[j]);
				ASSERT1(v1[j] == v4[j]);
				ASSERT1(v1[j] == v5[j]);
				ASSERT1(v1[j] == v6[j]);
			}
		}
	});

	Add("PostOrder", [&](){
		for (int i = 0; i < 100; i++) {
			Test::CompleteBinaryTree<int, Test::BinaryNode> tree;
			Test::CompleteBinaryTree<int, Test::BinaryNodeWithParent> tree2;
			int count = 1 + Test::Random::Next();

			for (int j = 0; j < count; j++) {
				int v = Test::Random::Next();
				tree.Insert(v);
				tree2.Insert(v);
			}

			cout << "Run " << i << ", " << count << " elements, height " << tree.Height() << endl;

			vector<int> v1;
			vector<int> v2;
			vector<int> v3;
			vector<int> v4;
			vector<int> v5;
			vector<int> v6;

			function<function<void(int)>(vector<int> &)> f = [&](vector<int> & v)->function < void(int) > {
				function<void(int)> w = [&](int n){
					v.push_back(n);
				};

				return w;
			};

			tree.PostOrderWalk(f(v1));
			tree.PostOrderWalkWithStack(f(v2));
			tree.PostOrderWalkWithStack2(f(v3));
			tree2.PostOrderWalk(f(v4));
			tree2.PostOrderWalkWithStack(f(v5));
			tree2.PostOrderWalkWithStack2(f(v6));

			ASSERT2(v1.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v1.size()));
			ASSERT2(v2.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v2.size()));
			ASSERT2(v3.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v3.size()));
			ASSERT2(v4.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v4.size()));
			ASSERT2(v5.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v4.size()));
			ASSERT2(v6.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v4.size()));

			for (int j = 0; j < count; j++) {
				ASSERT1(v1[j] == v2[j]);
				ASSERT1(v1[j] == v3[j]);
				ASSERT1(v1[j] == v4[j]);
				ASSERT1(v1[j] == v5[j]);
				ASSERT1(v1[j] == v6[j]);
			}
		}
	});

	Add("BuildTreePreOrderInOrder", [&](){
		Test::CompleteBinaryTree<int, Test::BinaryNode> tree;
		Test::CompleteBinaryTree<int, Test::BinaryNodeWithParent> tree2;
		int count = 1 + Test::Random::Next();
		for (int i = 0; i < count; i++) {
			tree.Insert(i);
			tree2.Insert(i);
		}

		tree.Print();
		tree2.Print();

		unique_ptr<int[]> preOrder(new int[count]);
		unique_ptr<int[]> inOrder(new int[count]);

		function<function<void(int)>(unique_ptr<int[]> &, int &)> f = [&](unique_ptr<int[]> & v, int & k)->function < void(int) > {
			function<void(int)> w = [&](int n){
				v[k++] = n;
			};

			return w;
		};

		int i = 0;
		int j = 0;
		tree.PreOrderWalk(f(preOrder, i));
		tree.InOrderWalk(f(inOrder, j));

		Logger().WriteInformation("PreOrder:\n");
		for (int i = 0; i < count; i++) {
			Logger().WriteInformation("  %d", preOrder[i]);
		}
		Logger().WriteInformation("\n");

		Logger().WriteInformation("InOrder:\n");
		for (int i = 0; i < count; i++) {
			Logger().WriteInformation("  %d", inOrder[i]);
		}
		Logger().WriteInformation("\n");

		Test::CompleteBinaryTree<int, Test::BinaryNode> tree3;
		tree3.BuildTreePreOrderInOrder(preOrder.get(), count, inOrder.get(), count);
		tree3.Print();
		ASSERT1(tree == tree3);

		Test::CompleteBinaryTree<int, Test::BinaryNodeWithParent> tree4;
		tree4.BuildTreePreOrderInOrder(preOrder.get(), count, inOrder.get(), count);
		tree4.Print();
		ASSERT1(tree2 == tree4);
	});

	Add("BuildTreeInOrderPostOrder", [&](){
		Test::CompleteBinaryTree<int, Test::BinaryNode> tree;
		Test::CompleteBinaryTree<int, Test::BinaryNodeWithParent> tree2;
		int count = 1 + Test::Random::Next();
		for (int i = 0; i < count; i++) {
			tree.Insert(i);
			tree2.Insert(i);
		}

		tree.Print();
		tree2.Print();

		unique_ptr<int[]> inOrder(new int[count]);
		unique_ptr<int[]> postOrder(new int[count]);

		function<function<void(int)>(unique_ptr<int[]> &, int &)> f = [&](unique_ptr<int[]> & v, int & k)->function < void(int) > {
			function<void(int)> w = [&](int n){
				v[k++] = n;
			};

			return w;
		};

		int i = 0;
		int j = 0;
		tree.InOrderWalk(f(inOrder, i));
		tree.PostOrderWalk(f(postOrder, j));

		Logger().WriteInformation("InOrder:\n");
		for (int i = 0; i < count; i++) {
			Logger().WriteInformation("  %d", inOrder[i]);
		}
		Logger().WriteInformation("\n");

		Logger().WriteInformation("PostOrder:\n");
		for (int i = 0; i < count; i++) {
			Logger().WriteInformation("  %d", postOrder[i]);
		}
		Logger().WriteInformation("\n");

		Test::CompleteBinaryTree<int, Test::BinaryNode> tree3;
		tree3.BuildTreeInOrderPostOrder(inOrder.get(), count, postOrder.get(), count);
		tree3.Print();
		ASSERT1(tree == tree3);

		Test::CompleteBinaryTree<int, Test::BinaryNodeWithParent> tree4;
		tree4.BuildTreeInOrderPostOrder(inOrder.get(), count, postOrder.get(), count);
		tree4.Print();
		ASSERT1(tree2 == tree4);
	});

	Add("ToDoubleLinkList", [&](){
		auto check = [&](int count) {
			Test::CompleteBinaryTree<int, Test::BinaryNode> tree;
			Test::CompleteBinaryTree<int, Test::BinaryNodeWithParent> tree2;
			for (int i = 0; i < count; i++) {
				tree.Insert(i);
				tree2.Insert(i);
			}

			tree.Print();
			tree2.Print();

			Test::BinaryNode<int> * head;
			Test::BinaryNode<int> * tail;
			Test::BinaryNodeWithParent<int> * head2;
			Test::BinaryNodeWithParent<int> * tail2;
			tree.ToDoubleLinkList(head, tail);
			tree2.ToDoubleLinkList(head2, tail2);

			auto print = [&](Test::BinaryNode<int> * head, Test::BinaryNode<int> * tail) -> int {
				if (head == nullptr || tail == nullptr) return 0;
				int c = 0;
				Logger().WriteInformation("head");
				do {
					Logger().WriteInformation(" <=> %d", head->content);
					c++;
					head = head->right;
				} while (head != nullptr);
				Logger().WriteInformation(" <=> tail\n");
				return c;
			};

			int c = print(head, tail);
			int c2 = print(head2, tail2);
			ASSERT1(c == count);
			ASSERT1(c2 == count);

			if (c > 0 && c2 > 0) {
				Test::BinaryNode<int> * p = head;
				Test::BinaryNodeWithParent<int> * p2 = head2;
				do {
					ASSERT1(p->content == p2->content);
					p = p->right;
					p2 = (Test::BinaryNodeWithParent<int> *)p2->right;
				} while (p != nullptr && p2 != nullptr);

				do {
					p = head;
					p2 = head2;
					head = head->right;
					head2 = (Test::BinaryNodeWithParent<int> *)head2->right;
					delete p;
					delete p2;
				} while (head != nullptr && head2 != nullptr);
			}
		};

		for (int i = 1; i <= 10; i++) {
			check(i);
		}

		for (int i = 1; i <= 100; i++) {
			int count = 1 + Test::Random::Next();
			check(count);
		}
	});

	Add("FromSingleLinkList", [&](){
		auto initList = [&](Test::SingleNode<int> * & list, int count) {
			list = new Test::SingleNode<int>(0);
			Test::SingleNode<int> * p = list;
			for (int i = 1; i < count; i++) {
				p->Next() = new Test::SingleNode<int>(i);
				p = p->Next();
			}
		};

		auto check = [&](int count) {
			Logger().WriteInformation("Create a binary tree from a list of %d nodes:\n", count);
			Test::SingleNode<int> * list;
			Test::SingleNode<int> * list2;
			initList(list, count);
			initList(list2, count);

			Test::BinaryTree<int, Test::BinaryNode> tree;
			tree.FromSingleLinkList(list);
			tree.Print2();
			Test::BinaryTree<int, Test::BinaryNode> tree2;
			tree2.FromSingleLinkList2(list2);
			tree2.Print2();

			ASSERT1(tree == tree2);
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

	Add("GetBoundaryValues1", [&](){
		auto print = [&](vector<int> & v) {
			for_each(v.begin(), v.end(), [&](int i){
				Logger().WriteInformation("  %d", i);
			});
			Logger().WriteInformation("\n");
		};

		auto check = [&](int count) {
			Logger().WriteInformation("Get boundary values of a binary tree of %d nodes:\n", count);

			Test::BinaryTree<int, Test::BinaryNode> tree;
			for (int i = 0; i < count; i++) {
				int v = Test::Random::Next();
				tree.Insert(v);
			}

			vector<int> values;
			tree.GetBoundaryValues(values);
			tree.Print();
			print(values);
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
		Test::BinaryNode<int> * n0 = new Test::BinaryNode<int>(0);
		Test::BinaryNode<int> * n1 = new Test::BinaryNode<int>(1);
		Test::BinaryNode<int> * n2 = new Test::BinaryNode<int>(2);
		Test::BinaryNode<int> * n3 = new Test::BinaryNode<int>(3);
		Test::BinaryNode<int> * n4 = new Test::BinaryNode<int>(4);
		Test::BinaryNode<int> * n5 = new Test::BinaryNode<int>(5);
		Test::BinaryNode<int> * n6 = new Test::BinaryNode<int>(6);
		Test::BinaryNode<int> * n7 = new Test::BinaryNode<int>(7);
		Test::BinaryNode<int> * n8 = new Test::BinaryNode<int>(8);
		Test::BinaryNode<int> * n9 = new Test::BinaryNode<int>(9);
		Test::BinaryNode<int> * n10 = new Test::BinaryNode<int>(10);
		Test::BinaryNode<int> * n11 = new Test::BinaryNode<int>(11);
		Test::BinaryNode<int> * n12 = new Test::BinaryNode<int>(12);
		Test::BinaryNode<int> * n13 = new Test::BinaryNode<int>(13);
		Test::BinaryNode<int> * n14 = new Test::BinaryNode<int>(14);
		Test::BinaryNode<int> * n15 = new Test::BinaryNode<int>(15);
		Test::BinaryNode<int> * n16 = new Test::BinaryNode<int>(16);
		n0->left = n1;
		n0->right = n9;
		n1->right = n2;
		n2->left = n3;
		n2->right = n5;
		n3->right = n4;
		n5->left = n6;
		n5->right = n8;
		n6->left = n7;
		n9->left = n10;
		n10->left = n11;
		n10->right = n15;
		n11->left = n12;
		n11->right = n13;
		n13->right = n14;
		n15->left = n16;

		Test::BinaryTree<int, Test::BinaryNode> tree;
		tree.Root(n0);

		vector<int> expect = { 0, 1, 2, 3, 4, 7, 8, 12, 14, 16, 15, 10, 9 };

		auto print = [&](vector<int> & v) {
			for_each(v.begin(), v.end(), [&](int i){
				Logger().WriteInformation("  %d", i);
			});
			Logger().WriteInformation("\n");
		};

		vector<int> values;
		tree.GetBoundaryValues(values);
		tree.Print();
		print(values);
		print(expect);

		ASSERT1(values.size() == expect.size());
		for (unsigned int i = 0; i < expect.size(); i++) {
			ASSERT1(values[i] == expect[i]);
		}
	});

	Add("Serialize", [&](){
		auto check = [&](int count) {
			Logger().WriteInformation("Serialize/deserialize a binary tree of %d nodes:\n", count);

			Test::BinaryTree<int, Test::BinaryNode> tree;
			for (int i = 0; i < count; i++) {
				int v = Test::Random::Next();
				tree.Insert(v);
			}

			stringstream ss;
			tree.Serialize(ss);
			tree.Print();
			Logger().WriteInformation("%s\n", ss.str().c_str());
			Test::BinaryTree<int, Test::BinaryNode> tree2;
			tree2.Deserialize(ss);
			tree2.Print();
			ASSERT1(tree == tree2);
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

	Add("Print1", [&](){
		auto check = [&](int count) {
			Logger().WriteInformation("Print a binary tree of %d nodes:\n", count);

			Test::BinaryTree<int, Test::BinaryNode> tree;
			for (int i = 0; i < count; i++) {
				tree.Insert(i);
			}

			tree.Print();
			tree.Print2();
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

	Add("Print2", [&](){
		auto check = [&](int count) {
			Logger().WriteInformation("Print a binary tree of %d nodes:\n", count);

			Test::BinaryTree<int, Test::BinaryNode> tree;
			for (int i = 0; i < count; i++) {
				int v = Test::Random::Next();
				tree.Insert(v);
			}

			tree.Print();
			tree.Print2();
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

	Add("PrintZigZag", [&](){
		auto check = [&](int count) {
			Logger().WriteInformation("Print a binary tree of %d nodes:\n", count);

			Test::BinaryTree<int, Test::BinaryNode> tree;
			for (int i = 0; i < count; i++) {
				tree.Insert(i);
			}

			tree.Print2();
			tree.Root()->PrintZigZag();
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

	Add("LevelOrderWalk1", [&](){
		auto print = [&](vector<int> & v) {
			for_each(v.begin(), v.end(), [&](int c){
				Logger().WriteInformation("  %d", c);
			});
			Logger().WriteInformation("\n");
		};

		auto check = [&](int count) {
			Logger().WriteInformation("Level order walk a binary tree of %d nodes:\n", count);

			Test::BinaryTree<int, Test::BinaryNode> tree;
			for (int i = 0; i < count; i++) {
				tree.Insert(i);
			}

			Test::BinaryTree<int, Test::BinaryNodeWithRightSibling> tree2;
			Test::BinaryNodeWithRightSibling<int> * node2 = Test::BinaryNodeWithRightSibling<int>::Clone(tree.Root());
			node2->SetRightSibling();
			tree2.Root(node2);

			// Test::BinaryTree<int, Test::BinaryNodeWithRightSibling> tree3;
			// Test::BinaryNodeWithRightSibling<int> * node3 = Test::BinaryNodeWithRightSibling<int>::Clone(tree.Root());
			// node3->SetRightSibling2();
			// tree3.Root(node3);

			tree.Print2();
			tree2.Print2();
			// tree3.Print2();
			vector<int> v1;
			vector<int> v2;
			vector<int> v3;
			// vector<int> v4;

			auto visit = [&](vector<int> & v) -> function<void(int)> {
				function<void(int)> f = [&](int c) {
					v.push_back(c);
				};
				return f;
			};

			tree.LevelOrderWalk(visit(v1));
			tree.LevelOrderWalk2(visit(v2));
			tree2.LevelOrderWalk(visit(v3));
			// tree3.LevelOrderWalk(visit(v4));
			print(v1);
			print(v2);
			print(v3);
			// print(v4);

			ASSERT1(v1.size() == v2.size());
			ASSERT1(v1.size() == v3.size());
			// ASSERT1(v1.size() == v4.size());
			for (unsigned int i = 0; i < v1.size(); i++) {
				ASSERT1(v1[i] == v2[i]);
				ASSERT1(v1[i] == v3[i]);
				// ASSERT1(v1[i] == v4[i]);
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
		auto print = [&](vector<int> & v) {
			for_each(v.begin(), v.end(), [&](int c){
				Logger().WriteInformation("  %d", c);
			});
			Logger().WriteInformation("\n");
		};

		auto check = [&](int count) {
			Logger().WriteInformation("Level order walk a binary tree of %d nodes:\n", count);

			Test::CompleteBinaryTree<int, Test::BinaryNode> tree;
			for (int i = 0; i < count; i++) {
				tree.Insert(i);
			}

			Test::BinaryTree<int, Test::BinaryNodeWithRightSibling> tree2;
			Test::BinaryNodeWithRightSibling<int> * node2 = Test::BinaryNodeWithRightSibling<int>::Clone(tree.Root());
			node2->SetRightSibling();
			tree2.Root(node2);

			Test::BinaryTree<int, Test::BinaryNodeWithRightSibling> tree3;
			Test::BinaryNodeWithRightSibling<int> * node3 = Test::BinaryNodeWithRightSibling<int>::Clone(tree.Root());
			node3->SetRightSibling2();
			tree3.Root(node3);

			tree.Print2();
			tree2.Print2();
			tree3.Print2();
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

			tree.LevelOrderWalk(visit(v1));
			tree.LevelOrderWalk2(visit(v2));
			tree2.LevelOrderWalk(visit(v3));
			tree3.LevelOrderWalk(visit(v4));
			print(v1);
			print(v2);
			print(v3);
			print(v4);

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
}