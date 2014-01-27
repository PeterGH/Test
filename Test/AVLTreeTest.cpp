#include "AVLTreeTest.h"

void AVLTreeTest::Init(void)
{
	Add("Insert 1", [&](){
		Test::AVLTree<int> tree;
		bool valid;
		for (int i = 0; i < 20; i ++) {
			tree.Insert(i);
			valid = tree.Verify();
			if (!valid)	tree.Print();
			ASSERT1(valid == true);
		}
	});

	Add("Insert 2", [&](){
		for (int i = 0; i < 100; i++) {
			int count = 1 + Test::Random::Next(1000);
			cout << "Run " << i << ", " << count << " elements" << endl;
			Test::AVLTree<int> tree;
			bool valid;
			int v;
			for (int j = 0; j < count; j ++) {
				v = Test::Random::Next();
				tree.Insert(v);
				valid = tree.Verify();
				if (!valid) {
					cout << "Insert " << v << endl;
					tree.Print();
				}
				ASSERT1(valid == true);
			}
		}
	});
}