#include "NodeTest.h"

void NodeTest::Init(void)
{
	Add("Node", [&](){
		{
			Node<int> node(1);
			ASSERT1(0 == node.CountNeighbors());
			ASSERT1(nullptr == node.Neighbor(0));
			ASSERT1(1 == node.CountNeighbors());
			ASSERT1(nullptr == node.Neighbor(0));
			ASSERT1(1 == node.CountNeighbors());
		}
		{
			Node<int> * p = new Node<int>(2);
			ASSERT1(0 == p->CountNeighbors());
			ASSERT1(nullptr == p->Neighbor(0));
			ASSERT1(1 == p->CountNeighbors());
			ASSERT1(nullptr == p->Neighbor(0));
			ASSERT1(1 == p->CountNeighbors());
			ASSERT1(nullptr == p->Neighbor(1));
			ASSERT1(2 == p->CountNeighbors());
			delete p;
		}
	});

	Add("SingleNode1", [&](){
		SingleNode<int> node(1);
		cout << &node << endl;
		cout << "Count: " << node.CountNeighbors() << endl;
		ASSERT1(1 == node.CountNeighbors());
		cout << "Middle: " << node.Middle()->Value() << endl;
		ASSERT1(1 == node.Middle()->Value());
		SingleNode<int> * r = node.Reverse();
		cout << "Reverse: " << r << endl;
		ASSERT1(1 == r->Value());
		r = nullptr;
		r = new SingleNode<int>(2);
		cout << r << endl;
		delete r;
	});

	Add("SingleNode2", [&](){
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			SingleNode<int> * n2 = new SingleNode<int>(2);
			SingleNode<int> * n3 = new SingleNode<int>(3);
			SingleNode<int> * n4 = new SingleNode<int>(4);
			n1->Next() = n2;
			n2->Next() = n3;
			n3->Next() = n4;

			cout << n1 << endl;

			cout << "Middle: " << n1->Middle()->Value() << endl;
			ASSERT1(2 == n1->Middle()->Value());

			n1->DeleteList();
			delete n1;
		}
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			SingleNode<int> * n2 = new SingleNode<int>(2);
			SingleNode<int> * n3 = new SingleNode<int>(3);
			SingleNode<int> * n4 = new SingleNode<int>(4);
			n1->Next(n2);
			n2->Next(n3);
			n3->Next(n4);

			cout << n1 << endl;

			n1->DeleteList();
			delete n1;
		}
	});

	Add("SingleNode3", [&](){
		{
			SingleNode<int> * n1 = new SingleNode<int>(1);
			SingleNode<int> * n2 = new SingleNode<int>(2);
			SingleNode<int> * n3 = new SingleNode<int>(3);
			SingleNode<int> * n4 = new SingleNode<int>(4);
			n1->Next() = n2;
			n2->Next() = n3;
			n3->Next() = n4;
			n4->Next() = n1;

			cout << n1 << endl;

			cout << "Middle: " << n1->Middle()->Value() << endl;

			n1->DeleteList();
			delete n1;
		}
	});

	Add("SingleNode4", [&](){
		{
			SingleNode<int> n1(0);
			for (int i = 1; i < 10; i++) {
				n1.InsertAtEnd(new SingleNode<int>(i));
				cout << &n1 << endl;
				int m = n1.Middle()->Value();
				cout << "Middle: " << m << endl;
				ASSERT1(m == i >> 1);
			}
			n1.DeleteList();
		}
		{
			SingleNode<int> n1(0);
			for (int i = 9; i > 0; i--) {
				n1.InsertAfter(new SingleNode<int>(i));
				cout << &n1 << endl;
			}
			int m = n1.Middle()->Value();
			cout << "Middle: " << m << endl;
			ASSERT1(m == 4);
			n1.DeleteList();
		}
	});

	Add("SingleNode5", [&](){
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			for (int i = 1; i < 10; i++) {
				n->InsertAtEnd(new SingleNode<int>(i));
				cout << n << endl;
				n = n->Reverse();
				cout << "Reverse: " << endl << n << endl;
			}
			n->DeleteList();
			delete n;
		}
	});

	Add("SingleNodeReorder", [&](){
		auto check = [&](SingleNode<int> * node) {
			size_t len = node->Length();
			cout << node << endl;
			SingleNode<int>::Reorder(node);
			size_t len2 = node->Length();
			cout << node << endl;
			ASSERT1(len == len2);
			size_t i = 0;
			SingleNode<int> * p = node;
			while (p != nullptr) {
				ASSERT1(p->Value() == i);
				p = p->Next();
				i++;
			}
			node->DeleteList();
			delete node;
		};
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			check(n);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			n->InsertAtEnd(new SingleNode<int>(1));
			check(n);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			n->InsertAtEnd(new SingleNode<int>(2));
			n->InsertAtEnd(new SingleNode<int>(1));
			check(n);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			n->InsertAtEnd(new SingleNode<int>(2));
			n->InsertAtEnd(new SingleNode<int>(3));
			n->InsertAtEnd(new SingleNode<int>(1));
			check(n);
		}
		{
			for (int i = 5; i < 100; i++) {
				Logger().WriteInformation("Reorder a list of %d nodes\n", i);
				SingleNode<int> * n = new SingleNode<int>(0);
				int j = (i + 1) >> 1;
				for (int k = 1; k < j; k++) {
					n->InsertAtEnd(new SingleNode<int>(2 * k));
				}
				j = i >> 1;
				for (int k = j; k > 0; k--) {
					n->InsertAtEnd(new SingleNode<int>(2 * k - 1));
				}
				check(n);
			}
		}
	});

	Add("SingleNodeCycle", [&](){
		auto check = [&](SingleNode<int> * node, int beginning){
			bool hasCycle = SingleNode<int>::HasCycle(node);
			if (hasCycle) {
				SingleNode<int> * cycle = SingleNode<int>::FindCycle(node);
				Logger().WriteInformation("Has cycle at %d\n", cycle->Value());
				int v = cycle->Value();
				if (cycle != node) {
					SingleNode<int> * p = node;
					while (p->Next() != cycle) {
						p = p->Next();
					}
					p->Next() = nullptr;
					node->DeleteList();
					delete node;
				}
				cycle->DeleteList();
				delete cycle;
				ASSERT1(beginning == v);
			} else {
				Logger().WriteInformation("No cycle\n");
				node->DeleteList();
				delete node;
				ASSERT1(beginning == -1);
			}
		};
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			check(n, -1);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			n->Next() = n;
			check(n, 0);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			n->InsertAtEnd(new SingleNode<int>(1));
			check(n, -1);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			n->Next() = n;
			n->InsertAtEnd(new SingleNode<int>(1));
			check(n, 0);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			SingleNode<int> * c = new SingleNode<int>(1);
			c->Next() = c;
			n->Next() = c;
			check(n, 1);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			n->InsertAtEnd(new SingleNode<int>(1));
			n->InsertAtEnd(new SingleNode<int>(2));
			check(n, -1);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			n->Next() = n;
			n->InsertAtEnd(new SingleNode<int>(1));
			n->InsertAtEnd(new SingleNode<int>(2));
			check(n, 0);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			SingleNode<int> * c = new SingleNode<int>(1);
			c->Next() = c;
			c->InsertAtEnd(new SingleNode<int>(2));
			n->Next() = c;
			check(n, 1);
		}
		{
			SingleNode<int> * n = new SingleNode<int>(0);
			n->InsertAtEnd(new SingleNode<int>(1));
			SingleNode<int> * c = new SingleNode<int>(2);
			c->Next() = c;
			n->Next() = c;
			check(n, 2);
		}
		{
			for (int i = 4; i < 100; i++) {
				Logger().WriteInformation("Test %d nodes\n", i);
				for (int j = 0; j < i; j++) {
					SingleNode<int> * n;
					SingleNode<int> * c = new SingleNode<int>(j);
					c->Next() = c;
					for (int k = j+1; k < i; k++) {
						c->InsertAtEnd(new SingleNode<int>(k));
					}
					if (j == 0) {
						n = c;
					} else {
						n = new SingleNode<int>(0);
						SingleNode<int> * p = n;
						for (int k = 1; k < j; k++) {
							p = new SingleNode<int>(k);
							n->InsertAtEnd(p);
						}
						p->Next() = c;
					}
					check(n, j);
				}
			}
		}
	});

	Add("DoubleNode", [&](){
		{
			Test::DoubleNode<int> node(1);
		}
		{
			Test::DoubleNode<int> * p = new Test::DoubleNode<int>(2);
			delete p;
		}
		{
			Test::DoubleNode<int> * n1 = new Test::DoubleNode<int>(1);
			Test::DoubleNode<int> * n2 = new Test::DoubleNode<int>(2);
			Test::DoubleNode<int> * n3 = new Test::DoubleNode<int>(3);
			Test::DoubleNode<int> * n4 = new Test::DoubleNode<int>(4);
			n1->Next() = n2;
			n2->Prev() = n1;
			n2->Next() = n3;
			n3->Prev() = n2;
			n3->Next() = n4;
			n4->Prev() = n3;

			Test::DoubleNode<int> * p = n1;
			Logger().WriteInformation("Head");
			do {
				Logger().WriteInformation(" -> %d", p->Value());
				p = p->Next();
			} while (p != nullptr);
			Logger().WriteInformation("\n");

			p = n4;
			Logger().WriteInformation("Tail");
			do {
				Logger().WriteInformation(" -> %d", p->Value());
				p = p->Prev();
			} while (p != nullptr);
			Logger().WriteInformation("\n");

			p = n1;
			Test::DoubleNode<int> * c = n1;
			do {
				Logger().WriteInformation("Value %d\n", c->Value());
				p = c;
				c = p->Next();
				delete p;
			} while (c != nullptr);
		}
		{
			Test::DoubleNode<int> * n1 = new Test::DoubleNode<int>(1);
			Test::DoubleNode<int> * n2 = new Test::DoubleNode<int>(2);
			Test::DoubleNode<int> * n3 = new Test::DoubleNode<int>(3);
			Test::DoubleNode<int> * n4 = new Test::DoubleNode<int>(4);
			n1->Next(n2);
			n2->Prev(n1);
			n2->Next(n3);
			n3->Prev(n2);
			n3->Next(n4);
			n4->Prev(n3);

			Test::DoubleNode<int> * p = n1;
			Logger().WriteInformation("Head");
			do {
				Logger().WriteInformation(" -> %d", p->Value());
				p = p->Next();
			} while (p != nullptr);
			Logger().WriteInformation("\n");

			p = n4;
			Logger().WriteInformation("Tail");
			do {
				Logger().WriteInformation(" -> %d", p->Value());
				p = p->Prev();
			} while (p != nullptr);
			Logger().WriteInformation("\n");

			p = n1;
			Test::DoubleNode<int> * c = n1;
			do {
				Logger().WriteInformation("Value %d\n", c->Value());
				p = c;
				c = p->Next();
				delete p;
			} while (c != nullptr);
		}
	});

	Add("DoubleNodeClone", [&](){
		{
			Test::DoubleNode<int> node(1);
			Test::DoubleNode<int> * copy = (Test::DoubleNode<int> *)Test::DoubleNode<int>::Clone(&node);
			ASSERT1(copy->Value() == 1);
			ASSERT1(copy->Prev() == nullptr);
			ASSERT1(copy->Next() == nullptr);
			delete copy;
		}
		{
			Test::DoubleNode<int> node(1);
			node.Prev() = &node;
			node.Next() = &node;
			Test::DoubleNode<int> * copy = (Test::DoubleNode<int> *)Test::DoubleNode<int>::Clone(&node);
			ASSERT1(copy->Value() == 1);
			ASSERT1(copy->Prev() == copy);
			ASSERT1(copy->Next() == copy);
			delete copy;
		}
		{
			Test::DoubleNode<int> * n1 = new Test::DoubleNode<int>(1);
			Test::DoubleNode<int> * n2 = new Test::DoubleNode<int>(2);
			Test::DoubleNode<int> * n3 = new Test::DoubleNode<int>(3);
			Test::DoubleNode<int> * n4 = new Test::DoubleNode<int>(4);
			n1->Next() = n2;
			n2->Prev() = n1;
			n2->Next() = n3;
			n3->Prev() = n2;
			n3->Next() = n4;
			n4->Prev() = n3;

			Test::DoubleNode<int> * copy = (Test::DoubleNode<int> *)Test::DoubleNode<int>::Clone(n1);

			Test::DoubleNode<int> * p = n1;
			Logger().WriteInformation("Head");
			do {
				Logger().WriteInformation(" -> %d", p->Value());
				p = p->Next();
			} while (p != nullptr);
			Logger().WriteInformation("\n");

			p = copy;
			Logger().WriteInformation("Head");
			do {
				Logger().WriteInformation(" -> %d", p->Value());
				p = p->Next();
			} while (p != nullptr);
			Logger().WriteInformation("\n");

			p = n1;
			Test::DoubleNode<int> * c = n1;
			do {
				Logger().WriteInformation("Value %d\n", c->Value());
				p = c;
				c = p->Next();
				delete p;
			} while (c != nullptr);

			p = copy;
			c = copy;
			do {
				Logger().WriteInformation("Value %d\n", c->Value());
				p = c;
				c = p->Next();
				delete p;
			} while (c != nullptr);
		}
		{
			Test::DoubleNode<int> * n1 = new Test::DoubleNode<int>(1);
			Test::DoubleNode<int> * n2 = new Test::DoubleNode<int>(2);
			Test::DoubleNode<int> * n3 = new Test::DoubleNode<int>(3);
			Test::DoubleNode<int> * n4 = new Test::DoubleNode<int>(4);
			n1->Next() = n2;
			n2->Prev() = n1;
			n2->Next() = n3;
			n3->Prev() = n1;
			n3->Next() = n4;
			n4->Prev() = n1;

			Test::DoubleNode<int> * copy = (Test::DoubleNode<int> *)Test::DoubleNode<int>::Clone(n1);

			Test::DoubleNode<int> * p = n1;
			Logger().WriteInformation("Head");
			do {
				Logger().WriteInformation(" -> %d", p->Value());
				p = p->Next();
			} while (p != nullptr);
			Logger().WriteInformation("\n");

			p = copy;
			Logger().WriteInformation("Head");
			do {
				Logger().WriteInformation(" -> %d", p->Value());
				p = p->Next();
			} while (p != nullptr);
			Logger().WriteInformation("\n");

			ASSERT1(copy->Prev() == nullptr);
			ASSERT1(copy->Value() == 1);
			ASSERT1(copy->Next()->Value() == 2);
			ASSERT1(copy->Next()->Prev() == copy);
			ASSERT1(copy->Next()->Next()->Value() == 3);
			ASSERT1(copy->Next()->Next()->Prev() == copy);
			ASSERT1(copy->Next()->Next()->Next()->Value() == 4);
			ASSERT1(copy->Next()->Next()->Next()->Prev() == copy);
			ASSERT1(copy->Next()->Next()->Next()->Next() == nullptr);

			p = n1;
			Test::DoubleNode<int> * c = n1;
			do {
				Logger().WriteInformation("Value %d\n", c->Value());
				p = c;
				c = p->Next();
				delete p;
			} while (c != nullptr);

			p = copy;
			c = copy;
			do {
				Logger().WriteInformation("Value %d\n", c->Value());
				p = c;
				c = p->Next();
				delete p;
			} while (c != nullptr);
		}
		{
			Test::DoubleNode<int> * n1 = new Test::DoubleNode<int>(1);
			Test::DoubleNode<int> * n2 = new Test::DoubleNode<int>(2);
			Test::DoubleNode<int> * n3 = new Test::DoubleNode<int>(3);
			Test::DoubleNode<int> * n4 = new Test::DoubleNode<int>(4);
			n1->Prev() = n4;
			n1->Next() = n2;
			n2->Prev() = n4;
			n2->Next() = n3;
			n3->Prev() = n4;
			n3->Next() = n4;
			n4->Prev() = n4;
			n4->Next() = nullptr;

			Test::DoubleNode<int> * copy = (Test::DoubleNode<int> *)Test::DoubleNode<int>::Clone(n1);

			Test::DoubleNode<int> * p = n1;
			Logger().WriteInformation("Head");
			do {
				Logger().WriteInformation(" -> %d", p->Value());
				p = p->Next();
			} while (p != nullptr);
			Logger().WriteInformation("\n");

			p = copy;
			Logger().WriteInformation("Head");
			do {
				Logger().WriteInformation(" -> %d", p->Value());
				p = p->Next();
			} while (p != nullptr);
			Logger().WriteInformation("\n");

			ASSERT1(copy->Prev() == copy->Next()->Next()->Next());
			ASSERT1(copy->Value() == 1);
			ASSERT1(copy->Next()->Value() == 2);
			ASSERT1(copy->Next()->Prev() == copy->Next()->Next()->Next());
			ASSERT1(copy->Next()->Next()->Value() == 3);
			ASSERT1(copy->Next()->Next()->Prev() == copy->Next()->Next()->Next());
			ASSERT1(copy->Next()->Next()->Next()->Value() == 4);
			ASSERT1(copy->Next()->Next()->Next()->Prev() == copy->Next()->Next()->Next());
			ASSERT1(copy->Next()->Next()->Next()->Next() == nullptr);

			p = n1;
			Test::DoubleNode<int> * c = n1;
			do {
				Logger().WriteInformation("Value %d\n", c->Value());
				p = c;
				c = p->Next();
				delete p;
			} while (c != nullptr);

			p = copy;
			c = copy;
			do {
				Logger().WriteInformation("Value %d\n", c->Value());
				p = c;
				c = p->Next();
				delete p;
			} while (c != nullptr);
		}
	});
}