#include "BinaryTreeTest.h"

void BinaryTreeTest::Init(void)
{
	Add("BinaryNodeInsert", [&](){
		Test::CompleteBinaryTree<int, Test::BinaryNode> tree;

		for (int i = 0; i < 20; i++) {
			tree.Insert(i);
		}

		tree.Print();

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
	});

	Add("BinaryNodeWithParentInsert", [&](){
		Test::CompleteBinaryTree<int, Test::BinaryNodeWithParent> tree;

		for (int i = 0; i < 20; i++) {
			tree.Insert(i);
		}

		tree.Print();

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

			function<function<void(int)>(vector<int> &)> f = [&](vector<int> & v)->function<void(int)>{
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

			function<function<void(int)>(vector<int> &)> f = [&](vector<int> & v)->function<void(int)>{
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

			function<function<void(int)>(vector<int> &)> f = [&](vector<int> & v)->function<void(int)>{
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
}