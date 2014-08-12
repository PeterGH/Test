#include "BinarySearchTreeTest.h"

void BinarySearchTreeTest::Init(void)
{
	Add("Insert", [&](){
		int I[] = { 3, 43, 42, 1, 3, 3556, 7, 34, 8, 8769, 96656532, 1, 445, 35, 64, 70 };
		int L = sizeof(I) / sizeof(I[0]);

		//    3
		//   /  \
		//  /    \
		// 1      43
		//  \    /  \
		//   1  42  3556
		//     /     /  \
		//    3    445 8769
		//     \   /      \
		//      7 64    96656532
		//       \  \
		//       34  70
		//       / \
		//      8  35
		Test::BinarySearchTree<int> tree;
		for (int i = 0; i < L; i++) {
			tree.Insert(I[i]);
		}

		tree.Print();

		ASSERT1(tree.Verify() == true);

		cout << "Height: " << tree.Height() << endl;
		cout << "Min: " << tree.Min() << endl;
		cout << "Max: " << tree.Max() << endl;

		function<void(int)> p = [](int n){cout << " " << n; };
		cout << "PreOrder:";
		tree.PreOrderWalk(p);
		cout << endl;
		cout << "PreOrderWithStack:";
		tree.PreOrderWalkWithStack(p);
		cout << endl;
		cout << "PreOrderWithStack2:";
		tree.PreOrderWalkWithStack2(p);
		cout << endl;
		cout << "PreOrderWithOutStack:";
		tree.PreOrderWalkWithOutStack(p);
		cout << endl;
		cout << "PreOrderIterator:";
		for (Test::PreOrderBinaryIterator<int, Test::BinaryNodeWithParent> it = tree.PreOrderBegin(); it != tree.PreOrderEnd(); it++) {
			cout << " " << *it;
		}
		cout << endl;
		cout << "PreOrderWithOutStackIterator:";
		for (Test::PreOrderBinaryIteratorWithOutStack<int> it = tree.PreOrderWithOutStackBegin(); it != tree.PreOrderWithOutStackEnd(); it++) {
			cout << " " << *it;
		}
		cout << endl;

		cout << "InOrder:";
		tree.InOrderWalk(p);
		cout << endl;
		cout << "InOrderWithStack:";
		tree.InOrderWalkWithStack(p);
		cout << endl;
		cout << "InOrderWithStack2:";
		tree.InOrderWalkWithStack2(p);
		cout << endl;
		cout << "InOrderWithOutStack:";
		tree.InOrderWalkWithOutStack(p);
		cout << endl;
		cout << "InOrderIterator:";
		for (Test::InOrderBinaryIterator<int, Test::BinaryNodeWithParent> it = tree.InOrderBegin(); it != tree.InOrderEnd(); it++) {
			cout << " " << *it;
		}
		cout << endl;
		cout << "InOrderWithOutStackIterator:";
		for (Test::InOrderBinaryIteratorWithOutStack<int> it = tree.InOrderWithOutStackBegin(); it != tree.InOrderWithOutStackEnd(); it++) {
			cout << " " << *it;
		}
		cout << endl;

		cout << "PostOrder:";
		tree.PostOrderWalk(p);
		cout << endl;
		cout << "PostOrderWithStack:";
		tree.PostOrderWalkWithStack(p);
		cout << endl;
		cout << "PostOrderWithStack2:";
		tree.PostOrderWalkWithStack2(p);
		cout << endl;
		cout << "PostOrderWithOutStack:";
		tree.PostOrderWalkWithOutStack(p);
		cout << endl;
		cout << "PostOrderIterator:";
		for (Test::PostOrderBinaryIterator<int, Test::BinaryNodeWithParent> it = tree.PostOrderBegin(); it != tree.PostOrderEnd(); it++) {
			cout << " " << *it;
		}
		cout << endl;
		cout << "PostOrderWithOutStackIterator:";
		for (Test::PostOrderBinaryIteratorWithOutStack<int> it = tree.PostOrderWithOutStackBegin(); it != tree.PostOrderWithOutStackEnd(); it++) {
			cout << " " << *it;
		}
		cout << endl;

		int v = tree.Successor(34);
		cout << "Successor of 34: " << v << endl;
		ASSERT1(v == 35);

		v = tree.Predecessor(42);
		cout << "Predecessor of 42: " << v << endl;
		ASSERT1(v == 35);

		v = tree.Search(3)->content;
		ASSERT1(v == 3);

		v = tree.Search(42)->content;
		ASSERT1(v == 42);

		v = tree.Search(8)->content;
		ASSERT1(v == 8);

		Test::BinaryNodeWithParent<int> * pn = tree.Search(0);
		ASSERT1(pn == nullptr);
	});

	Add("LCA", [&](){
		Test::BinarySearchTree<int> tree;
		vector<int> inserted;
		int count = 1 + Test::Random::Next();
		for (int j = 0; j < count; j++) {
			int v = Test::Random::Next();
			tree.Insert(v);
			inserted.push_back(v);
		}

		tree.Print();

		for (int i = 0; i < count - 1; i++) {
			for (int j = i + 1; j < count; j++) {
				int a = tree.LowestCommonAncestor(inserted[i], inserted[j]);
				int b = tree.LowestCommonAncestor2(inserted[i], inserted[j]);
				int c = tree.LowestCommonAncestor3(inserted[i], inserted[j]);
				Logger().WriteInformation("(%d, %d): %d and %d lowest common ancestor is (%d, %d, %d)\n", i, j, inserted[i], inserted[j], a, b, c);
				ASSERT1(a == b);
				ASSERT1(a == c);
			}
		}
	});

	Add("PreOrder", [&](){
		for (int i = 0; i < 100; i++) {
			Test::BinarySearchTree<int> tree;
			int count = 1 + Test::Random::Next();

			for (int j = 0; j < count; j++) {
				int v = Test::Random::Next();
				tree.Insert(v);
			}

			cout << "Run " << i << ", " << count << " elements, height " << tree.Height() << endl;

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

			tree.PreOrderWalk(f(v1));
			tree.PreOrderWalkWithStack(f(v2));
			tree.PreOrderWalkWithStack2(f(v3));
			tree.PreOrderWalkWithStack3(f(v4));
			tree.PreOrderWalkWithOutStack(f(v5));

			for (Test::PreOrderBinaryIterator<int, Test::BinaryNodeWithParent> it = tree.PreOrderBegin(); it != tree.PreOrderEnd(); it++) {
				v6.push_back(*it);
			}

			for (Test::PreOrderBinaryIteratorWithOutStack<int> it = tree.PreOrderWithOutStackBegin(); it != tree.PreOrderWithOutStackEnd(); it++) {
				v7.push_back(*it);
			}

			ASSERT2(v1.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v1.size()));
			ASSERT2(v2.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v2.size()));
			ASSERT2(v3.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v3.size()));
			ASSERT2(v4.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v4.size()));
			ASSERT2(v5.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v5.size()));
			ASSERT2(v6.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v6.size()));
			ASSERT2(v7.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v7.size()));

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

	Add("InOrder", [&](){
		for (int i = 0; i < 100; i++) {
			Test::BinarySearchTree<int> tree;
			int count = 1 + Test::Random::Next();

			for (int j = 0; j < count; j++) {
				int v = Test::Random::Next();
				tree.Insert(v);
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
			tree.InOrderWalkWithOutStack(f(v4));

			for (Test::InOrderBinaryIterator<int, Test::BinaryNodeWithParent> it = tree.InOrderBegin(); it != tree.InOrderEnd(); it++) {
				v5.push_back(*it);
			}

			for (Test::InOrderBinaryIteratorWithOutStack<int> it = tree.InOrderWithOutStackBegin(); it != tree.InOrderWithOutStackEnd(); it++) {
				v6.push_back(*it);
			}

			ASSERT2(v1.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v1.size()));
			ASSERT2(v2.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v2.size()));
			ASSERT2(v3.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v3.size()));
			ASSERT2(v4.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v4.size()));
			ASSERT2(v5.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v5.size()));
			ASSERT2(v6.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v6.size()));

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
			Test::BinarySearchTree<int> tree;
			int count = 1 + Test::Random::Next();

			for (int j = 0; j < count; j++) {
				int v = Test::Random::Next();
				tree.Insert(v);
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
			tree.PostOrderWalkWithOutStack(f(v4));

			for (Test::PostOrderBinaryIterator<int, Test::BinaryNodeWithParent> it = tree.PostOrderBegin(); it != tree.PostOrderEnd(); it++) {
				v5.push_back(*it);
			}

			for (Test::PostOrderBinaryIteratorWithOutStack<int> it = tree.PostOrderWithOutStackBegin(); it != tree.PostOrderWithOutStackEnd(); it++) {
				v6.push_back(*it);
			}

			ASSERT2(v1.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v1.size()));
			ASSERT2(v2.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v2.size()));
			ASSERT2(v3.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v3.size()));
			ASSERT2(v4.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v4.size()));
			ASSERT2(v5.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v5.size()));
			ASSERT2(v6.size() == count, Test::String::Format("Expect %d elements, actual visited %d", count, v6.size()));

			for (int j = 0; j < count; j++) {
				ASSERT1(v1[j] == v2[j]);
				ASSERT1(v1[j] == v3[j]);
				ASSERT1(v1[j] == v4[j]);
				ASSERT1(v1[j] == v5[j]);
				ASSERT1(v1[j] == v6[j]);
			}
		}
	});

	Add("Delete 1", [&]() {
		int I[] = { 3, 43, 42, 1, 3, 3556, 7, 34, 8, 8769, 96656532, 1, 445, 35, 64, 70 };
		int L = sizeof(I) / sizeof(I[0]);

		//    3
		//   /  \
		//  /    \
		// 1      43
		//  \    /  \
		//   1  42  3556
		//     /     /  \
		//    3    445 8769
		//     \   /      \
		//      7 64    96656532
		//       \  \
		//       34  70
		//       / \
		//      8  35
		Test::BinarySearchTree<int> tree;
		for (int i = 0; i < L; i++) {
			tree.Insert(I[i]);
		}

		tree.Print();
		ASSERT1(tree.Verify() == true);

		int v;
		for (int i = 0; i < L; i += 2) {
			v = tree.Min();
			cout << "Delete min " << v << endl;
			tree.Delete(v);
			tree.Print();
			ASSERT1(tree.Verify() == true);

			v = tree.Max();
			cout << "Delete max " << v << endl;
			tree.Delete(v);
			tree.Print();
			ASSERT1(tree.Verify() == true);
		}
	});

	Add("Delete 2", [&]() {
		int I[] = { 3, 43, 42, 1, 3, 3556, 7, 34, 8, 8769, 96656532, 1, 445, 35, 64, 70 };
		int L = sizeof(I) / sizeof(I[0]);

		//    3
		//   /  \
		//  /    \
		// 1      43
		//  \    /  \
		//   1  42  3556
		//     /     /  \
		//    3    445 8769
		//     \   /      \
		//      7 64    96656532
		//       \  \
		//       34  70
		//       / \
		//      8  35
		Test::BinarySearchTree<int> tree;
		for (int i = 0; i < L; i++) {
			tree.Insert(I[i]);
		}

		tree.Print();
		ASSERT1(tree.Verify() == true);

		for (int i = 0; i < L; i++) {
			cout << "Delete " << I[i] << endl;
			tree.Delete(I[i]);
			tree.Print();
			ASSERT1(tree.Verify() == true);
		}
	});

	Add("Height", [&](){
		for (int i = 0; i < 100; i++) {
			Test::BinarySearchTree<int> tree;
			int count = 1 + Test::Random::Next();

			for (int j = 0; j < count; j++) {
				int v = Test::Random::Next();
				tree.Insert(v);
			}

			int h = tree.Height();
			cout << "Run " << i << ", " << count << " elements, height " << h << endl;
		}
	});

	Add("Verify", [&](){
		{
			Test::BinaryNode<int> * n1 = new Test::BinaryNode<int>(80);
			Test::BinaryNode<int> * n2 = new Test::BinaryNode<int>(70);
			Test::BinaryNode<int> * n3 = new Test::BinaryNode<int>(100);
			n1->left = n2;
			n2->right = n3;
			Test::BinaryTree<int, Test::BinaryNode> tree;
			tree.Root(n1);
			tree.Print();
			ASSERT1(Test::BinarySearchTree<int>::Verify(n1) == false);
		}
		{
			Test::BinaryNode<int> * n1 = new Test::BinaryNode<int>(80);
			Test::BinaryNode<int> * n2 = new Test::BinaryNode<int>(80);
			Test::BinaryNode<int> * n3 = new Test::BinaryNode<int>(70);
			n1->left = n2;
			n2->right = n3;
			Test::BinaryTree<int, Test::BinaryNode> tree;
			tree.Root(n1);
			tree.Print();
			ASSERT1(Test::BinarySearchTree<int>::Verify(n1) == false);
		}
		{
			Test::BinaryNode<int> * n1 = new Test::BinaryNode<int>(80);
			Test::BinaryNode<int> * n2 = new Test::BinaryNode<int>(80);
			Test::BinaryNode<int> * n3 = new Test::BinaryNode<int>(70);
			n1->left = n3;
			n1->right = n2;
			Test::BinaryTree<int, Test::BinaryNode> tree;
			tree.Root(n1);
			tree.Print();
			ASSERT1(Test::BinarySearchTree<int>::Verify(n1) == true);
		}
	});

	Add("BuildTreePreOrderInOrder", [&](){
		Test::BinarySearchTree<int> tree;
		set<int> values;
		int count = 1 + Test::Random::Next();
		for (int i = 0; i < count; i++) {
			int v = Test::Random::Next();
			if (values.find(v) == values.end()) {
				tree.Insert(v);
				values.insert(v);
			}
		}

		count = values.size();

		tree.Print();

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

		Test::BinarySearchTree<int> tree2;
		tree2.BuildTreePreOrderInOrder(preOrder.get(), count, inOrder.get(), count);
		tree2.Print();
		ASSERT1(true == tree2.Verify());
		ASSERT1(tree == tree2);
	});

	Add("BuildTreeInOrderPostOrder", [&](){
		Test::BinarySearchTree<int> tree;
		set<int> values;
		int count = 1 + Test::Random::Next();
		for (int i = 0; i < count; i++) {
			int v = Test::Random::Next();
			if (values.find(v) == values.end()) {
				tree.Insert(v);
				values.insert(v);
			}
		}

		count = values.size();

		tree.Print();

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

		Test::BinarySearchTree<int> tree2;
		tree2.BuildTreeInOrderPostOrder(inOrder.get(), count, postOrder.get(), count);
		tree2.Print();
		ASSERT1(true == tree2.Verify());
		ASSERT1(tree == tree2);
	});

	Add("ToDoubleLinkList", [&](){
		auto check = [&](int count) {
			vector<int> items;
			Test::BinarySearchTree<int> tree;
			for (int i = 0; i < count; i++) {
				int e = Test::Random::Next();
				items.push_back(e);
				tree.Insert(e);
			}

			tree.Print();

			Test::BinaryNodeWithParent<int> * head;
			Test::BinaryNodeWithParent<int> * tail;
			tree.ToDoubleLinkList(head, tail);

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
			ASSERT1(c == count);

			if (c > 0) {
				sort(items.begin(), items.end());
				vector<int>::iterator it = items.begin();
				Test::BinaryNodeWithParent<int> * p = head;
				do {
					ASSERT1(*it == p->content);
					it++;
					p = (Test::BinaryNodeWithParent<int> *)p->right;
				} while (it != items.end() && p != nullptr);

				do {
					p = head;
					head = (Test::BinaryNodeWithParent<int> *)head->right;
					delete p;
				} while (head != nullptr);
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

	Add("MaxTreeFromBinaryTree1", [&](){
		auto check = [&](int count) {
			Logger().WriteInformation("Search a max binary search tree from a binary tree of %d nodes:\n", count);

			Test::BinaryTree<int, Test::BinaryNode> tree;
			for (int i = 0; i < count; i++) {
				int v = Test::Random::Next();
				tree.Insert(v);
			}

			Test::BinarySearchTree<int> searchTree;
			Test::BinarySearchTree<int> searchTree2;
			// Test::BinarySearchTree<int> searchTree3;
			searchTree.MaxTreeFromBinaryTree(&tree);
			searchTree2.MaxTreeFromBinaryTree2(&tree);
			// searchTree3.MaxTreeFromBinaryTree3(&tree);
			tree.Print();
			searchTree.Print();
			searchTree2.Print();
			// searchTree3.Print();
			ASSERT1(searchTree.Verify());
			ASSERT1(searchTree2.Verify());
			// ASSERT1(searchTree3.Verify());
			ASSERT1(searchTree == searchTree2);
			// ASSERT1(searchTree == searchTree3);
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

	Add("MaxTreeFromBinaryTree2", [&](){
		Logger().WriteInformation("Search a max binary search tree from a binary tree:\n");
		Test::BinaryNode<int> * n1 = new Test::BinaryNode<int>(80);
		Test::BinaryNode<int> * n2 = new Test::BinaryNode<int>(70);
		Test::BinaryNode<int> * n3 = new Test::BinaryNode<int>(100);
		Test::BinaryNode<int> * n4 = new Test::BinaryNode<int>(90);
		Test::BinaryNode<int> * n5 = new Test::BinaryNode<int>(60);
		Test::BinaryNode<int> * n6 = new Test::BinaryNode<int>(85);
		Test::BinaryNode<int> * n7 = new Test::BinaryNode<int>(75);
		n1->left = n2;
		n1->right = n3;
		n3->left = n4;
		n4->left = n5;
		n5->right = n6;
		n2->right = n7;

		Test::BinaryTree<int, Test::BinaryNode> tree;
		tree.Root(n1);

		Test::BinarySearchTree<int> searchTree;
		Test::BinarySearchTree<int> searchTree2;
		// Test::BinarySearchTree<int> searchTree3;
		searchTree.MaxTreeFromBinaryTree(&tree);
		searchTree2.MaxTreeFromBinaryTree2(&tree);
		// searchTree2.MaxTreeFromBinaryTree2(&tree);
		tree.Print();
		searchTree.Print();
		searchTree2.Print();
		// searchTree3.Print();
		ASSERT1(searchTree.Verify());
		ASSERT1(searchTree2.Verify());
		// ASSERT1(searchTree3.Verify());
		ASSERT1(searchTree == searchTree2);
		// ASSERT1(searchTree == searchTree3);
	});

	Add("MaxTreeFromCompleteBinaryTree", [&](){
		auto check = [&](int count) {
			Logger().WriteInformation("Search a max binary search tree from a complete binary tree of %d nodes:\n", count);

			Test::CompleteBinaryTree<int, Test::BinaryNode> tree;
			for (int i = 0; i < count; i++) {
				int v = Test::Random::Next();
				tree.Insert(v);
			}

			Test::BinarySearchTree<int> searchTree;
			Test::BinarySearchTree<int> searchTree2;
			// Test::BinarySearchTree<int> searchTree3;
			searchTree.MaxTreeFromBinaryTree(&tree);
			searchTree2.MaxTreeFromBinaryTree2(&tree);
			// searchTree3.MaxTreeFromBinaryTree3(&tree);
			tree.Print();
			searchTree.Print();
			searchTree2.Print();
			// searchTree3.Print();
			ASSERT1(searchTree.Verify());
			ASSERT1(searchTree2.Verify());
			// ASSERT1(searchTree3.Verify());
			ASSERT1(searchTree == searchTree2);
			// ASSERT1(searchTree == searchTree3);
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

	Add("MaxTreeFromBinarySearchTree", [&](){
		auto check = [&](int count) {
			Logger().WriteInformation("Search a max binary search tree from a binary search tree of %d nodes:\n", count);

			Test::BinarySearchTree<int> tree;
			for (int i = 0; i < count; i++) {
				int v = Test::Random::Next();
				tree.Insert(v);
			}

			Test::BinarySearchTree<int> searchTree;
			Test::BinarySearchTree<int> searchTree2;
			Test::BinarySearchTree<int> searchTree3;
			searchTree.MaxTreeFromBinaryTree((Test::BinaryTree<int, Test::BinaryNode> *)&tree);
			searchTree2.MaxTreeFromBinaryTree2((Test::BinaryTree<int, Test::BinaryNode> *)&tree);
			searchTree3.MaxTreeFromBinaryTree3((Test::BinaryTree<int, Test::BinaryNode> *)&tree);
			tree.Print();
			searchTree.Print();
			searchTree2.Print();
			searchTree3.Print();
			ASSERT1(searchTree.Verify());
			ASSERT1(searchTree2.Verify());
			ASSERT1(searchTree3.Verify());
			ASSERT1(tree == searchTree);
			ASSERT1(tree == searchTree2);
			ASSERT1(tree == searchTree3);
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

	Add("MaxSubTreeFromBinaryTree1", [&](){
		auto check = [&](int count) {
			Logger().WriteInformation("Search a max binary search sub tree from a binary tree of %d nodes:\n", count);

			Test::BinaryTree<int, Test::BinaryNode> tree;
			for (int i = 0; i < count; i++) {
				int v = Test::Random::Next();
				tree.Insert(v);
			}

			Test::BinarySearchTree<int> searchTree;
			Test::BinarySearchTree<int> searchTree2;
			searchTree.MaxSubTreeFromBinaryTree(&tree);
			searchTree2.MaxSubTreeFromBinaryTree2(&tree);
			tree.Print();
			searchTree.Print();
			searchTree2.Print();
			ASSERT1(searchTree.Verify());
			ASSERT1(searchTree2.Verify());
			ASSERT1(searchTree == searchTree2);
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

	Add("MaxSubTreeFromBinaryTree2", [&](){
		Logger().WriteInformation("Search a max binary search sub tree from a binary tree:\n");
		Test::BinaryNode<int> * n1 = new Test::BinaryNode<int>(80);
		Test::BinaryNode<int> * n2 = new Test::BinaryNode<int>(70);
		Test::BinaryNode<int> * n3 = new Test::BinaryNode<int>(100);
		Test::BinaryNode<int> * n4 = new Test::BinaryNode<int>(90);
		Test::BinaryNode<int> * n5 = new Test::BinaryNode<int>(60);
		Test::BinaryNode<int> * n6 = new Test::BinaryNode<int>(85);
		Test::BinaryNode<int> * n7 = new Test::BinaryNode<int>(75);
		n1->left = n2;
		n1->right = n3;
		n3->left = n4;
		n4->left = n5;
		n5->right = n6;
		n2->right = n7;

		Test::BinaryTree<int, Test::BinaryNode> tree;
		tree.Root(n1);

		Test::BinarySearchTree<int> searchTree;
		Test::BinarySearchTree<int> searchTree2;
		searchTree.MaxSubTreeFromBinaryTree(&tree);
		searchTree2.MaxSubTreeFromBinaryTree2(&tree);
		tree.Print();
		searchTree.Print();
		searchTree2.Print();
		ASSERT1(searchTree.Verify());
		ASSERT1(searchTree2.Verify());
		ASSERT1(searchTree == searchTree2);
	});

	Add("MaxSubTreeFromCompleteBinaryTree", [&](){
		auto check = [&](int count) {
			Logger().WriteInformation("Search a max binary search sub tree from a complete binary tree of %d nodes:\n", count);

			Test::CompleteBinaryTree<int, Test::BinaryNode> tree;
			for (int i = 0; i < count; i++) {
				int v = Test::Random::Next();
				tree.Insert(v);
			}

			Test::BinarySearchTree<int> searchTree;
			Test::BinarySearchTree<int> searchTree2;
			searchTree.MaxSubTreeFromBinaryTree(&tree);
			searchTree2.MaxSubTreeFromBinaryTree2(&tree);
			tree.Print();
			searchTree.Print();
			searchTree2.Print();
			ASSERT1(searchTree.Verify());
			ASSERT1(searchTree2.Verify());
			ASSERT1(searchTree == searchTree2);
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

	Add("MaxSubTreeFromBinarySearchTree", [&](){
		auto check = [&](int count) {
			Logger().WriteInformation("Search a max binary search sub tree from a binary search tree of %d nodes:\n", count);

			Test::BinarySearchTree<int> tree;
			for (int i = 0; i < count; i++) {
				int v = Test::Random::Next();
				tree.Insert(v);
			}

			Test::BinarySearchTree<int> searchTree;
			Test::BinarySearchTree<int> searchTree2;
			searchTree.MaxSubTreeFromBinaryTree((Test::BinaryTree<int, Test::BinaryNode> *)&tree);
			searchTree2.MaxSubTreeFromBinaryTree2((Test::BinaryTree<int, Test::BinaryNode> *)&tree);
			tree.Print();
			searchTree.Print();
			searchTree2.Print();
			ASSERT1(searchTree.Verify());
			ASSERT1(searchTree2.Verify());
			ASSERT1(tree == searchTree);
			ASSERT1(tree == searchTree2);
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

	Add("Serialize", [&](){
		auto check = [&](int count) {
			Logger().WriteInformation("Serialize/deserialize a binary search tree of %d nodes:\n", count);

			Test::BinarySearchTree<int> tree;
			for (int i = 0; i < count; i++) {
				int v = Test::Random::Next();
				tree.Insert(v);
			}

			tree.Print();

			stringstream ss;
			stringstream ss2;
			tree.Serialize(ss);
			tree.Serialize(ss2);
			Logger().WriteInformation("%s\n", ss.str().c_str());
			Test::BinarySearchTree<int> tree2;
			tree2.Deserialize(ss);
			tree2.Print();
			Test::BinarySearchTree<int> tree3;
			tree3.Deserialize2(ss2, INT_MIN, INT_MAX);
			tree3.Print();
			ASSERT1(tree == tree2);
			ASSERT1(tree == tree3);
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