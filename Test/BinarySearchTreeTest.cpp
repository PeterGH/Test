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

		cout << "Min: " << tree.Min() << endl;
		cout << "Max: " << tree.Max() << endl;

		function<void(int)> p = [](int n){cout << n << " "; };
		cout << "PreOrder:";
		tree.PreOrderWalk(p);
		cout << endl;

		cout << "InOrder:";
		tree.InOrderWalk(p);
		cout << endl;

		cout << "PostOrder:";
		tree.PostOrderWalk(p);
		cout << endl;

		int v = tree.Successor(34);
		cout << "Successor of 34: " << v << endl;
		ASSERT1(v == 35);

		v = tree.Predecessor(42);
		cout << "Predecessor of 42: " << v << endl;
		ASSERT1(v == 35);
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
}