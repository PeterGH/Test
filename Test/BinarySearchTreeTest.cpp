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

		for (int i = 0; i < count-1; i++) {
			for (int j = i+1; j < count; j++) {
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

			function<function<void(int)>(vector<int> &)> f = [&](vector<int> & v)->function<void(int)>{
				function<void(int)> w = [&](int n){
					v.push_back(n);
				};

				return w;
			};

			tree.PreOrderWalk(f(v1));
			tree.PreOrderWalkWithStack(f(v2));
			tree.PreOrderWalkWithStack2(f(v3));
			tree.PreOrderWalkWithOutStack(f(v4));

			for (Test::PreOrderBinaryIterator<int, Test::BinaryNodeWithParent> it = tree.PreOrderBegin(); it != tree.PreOrderEnd(); it++) {
				v5.push_back(*it);
			}

			for (Test::PreOrderBinaryIteratorWithOutStack<int> it = tree.PreOrderWithOutStackBegin(); it != tree.PreOrderWithOutStackEnd(); it++) {
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

			function<function<void(int)>(vector<int> &)> f = [&](vector<int> & v)->function<void(int)>{
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

			function<function<void(int)>(vector<int> &)> f = [&](vector<int> & v)->function<void(int)>{
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
}