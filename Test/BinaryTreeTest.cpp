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

			function<function<void(int)>(vector<int> &)> f = [&](vector<int> & v)->function < void(int) > {
				function<void(int)> w = [&](int n){
					v.push_back(n);
				};

				return w;
			};

			tree.PreOrderWalk(f(v1));
			tree.PreOrderWalkWithStack(f(v2));
			tree.PreOrderWalkWithStack2(f(v3));
			tree2.PreOrderWalk(f(v4));
			tree2.PreOrderWalkWithStack(f(v5));
			tree2.PreOrderWalkWithStack2(f(v6));

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
		auto initList = [&](Test::Node1<int> * & list, int count) {
			list = new Test::Node1<int>(0);
			Test::Node1<int> * p = list;
			for (int i = 1; i < count; i++) {
				p->Next() = new Test::Node1<int>(i);
				p = p->Next();
			}
		};

		auto check = [&](int count) {
			Logger().WriteInformation("Create a binary tree from a list of %d nodes:\n", count);
			Test::Node1<int> * list;
			Test::Node1<int> * list2;
			initList(list, count);
			initList(list2, count);

			Test::BinaryTree<int, Test::BinaryNode> tree;
			tree.FromSingleLinkList(list);
			tree.Print();
			Test::BinaryTree<int, Test::BinaryNode> tree2;
			tree2.FromSingleLinkList2(list2);
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
}