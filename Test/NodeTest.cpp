#include "NodeTest.h"

void NodeTest::Init(void)
{
	Add("Node", [&](){
		{
			Test::Node<int> node(1);
		}
		{
			Test::Node<int> * p = new Test::Node<int>(2);
			delete p;
		}
	});

	Add("SingleNode", [&](){
		{
			Test::SingleNode<int> node(1);
			cout << &node << endl;
			cout << "Middle: " << node.Middle()->Value() << endl;
			Test::SingleNode<int> * r = node.Reverse();
			cout << "Reverse: " << r << endl;
		}
		{
			Test::SingleNode<int> * p = new Test::SingleNode<int>(2);
			cout << p << endl;
			delete p;
		}
		{
			Test::SingleNode<int> * n1 = new Test::SingleNode<int>(1);
			Test::SingleNode<int> * n2 = new Test::SingleNode<int>(2);
			Test::SingleNode<int> * n3 = new Test::SingleNode<int>(3);
			Test::SingleNode<int> * n4 = new Test::SingleNode<int>(4);
			n1->Next() = n2;
			n2->Next() = n3;
			n3->Next() = n4;

			cout << n1 << endl;

			cout << "Middle: " << n1->Middle()->Value() << endl;

			n1->DeleteList();
			delete n1;
		}
		{
			Test::SingleNode<int> * n1 = new Test::SingleNode<int>(1);
			Test::SingleNode<int> * n2 = new Test::SingleNode<int>(2);
			Test::SingleNode<int> * n3 = new Test::SingleNode<int>(3);
			Test::SingleNode<int> * n4 = new Test::SingleNode<int>(4);
			n1->Next(n2);
			n2->Next(n3);
			n3->Next(n4);

			cout << n1 << endl;

			n1->DeleteList();
			delete n1;
		}
		{
			Test::SingleNode<int> * n1 = new Test::SingleNode<int>(1);
			Test::SingleNode<int> * n2 = new Test::SingleNode<int>(2);
			Test::SingleNode<int> * n3 = new Test::SingleNode<int>(3);
			Test::SingleNode<int> * n4 = new Test::SingleNode<int>(4);
			n1->Next() = n2;
			n2->Next() = n3;
			n3->Next() = n4;
			n4->Next() = n1;

			cout << n1 << endl;

			cout << "Middle: " << n1->Middle()->Value() << endl;

			n1->DeleteList();
			delete n1;
		}
		{
			Test::SingleNode<int> n1(0);
			for (int i = 1; i < 10; i++) {
				n1.InsertAtEnd(new Test::SingleNode<int>(i));
				cout << &n1 << endl;
				int m = n1.Middle()->Value();
				cout << "Middle: " << m << endl;
				ASSERT1(m == i >> 1);
			}
			n1.DeleteList();
		}
		{
			Test::SingleNode<int> n1(0);
			n1.Next() = &n1;
			for (int i = 1; i < 10; i++) {
				n1.InsertAtEnd(new Test::SingleNode<int>(i));
				cout << &n1 << endl;
				int m = n1.Middle()->Value();
				cout << "Middle: " << m << endl;
				ASSERT1(m == i >> 1);
			}
			n1.DeleteList();
		}
		{
			Test::SingleNode<int> n1(0);
			for (int i = 9; i > 0; i--) {
				n1.InsertAfter(new Test::SingleNode<int>(i));
				cout << &n1 << endl;
			}
			int m = n1.Middle()->Value();
			cout << "Middle: " << m << endl;
			ASSERT1(m == 4);
			n1.DeleteList();
		}
		{
			Test::SingleNode<int> n1(0);
			n1.Next() = &n1;
			for (int i = 9; i > 0; i--) {
				n1.InsertAfter(new Test::SingleNode<int>(i));
				cout << &n1 << endl;
			}
			int m = n1.Middle()->Value();
			cout << "Middle: " << m << endl;
			ASSERT1(m == 4);
			n1.DeleteList();
		}
		{
			Test::SingleNode<int> * n = new Test::SingleNode<int>(0);
			for (int i = 1; i < 10; i++) {
				n->InsertAtEnd(new Test::SingleNode<int>(i));
				cout << n << endl;
				n = n->Reverse();
				cout << "Reverse: " << endl << n << endl;
			}
			n->DeleteList();
			delete n;
		}
		{
			Test::SingleNode<int> * n = new Test::SingleNode<int>(0);
			n->Next() = n;
			for (int i = 1; i < 10; i++) {
				n->InsertAtEnd(new Test::SingleNode<int>(i));
				cout << n << endl;
				n = n->Reverse();
				cout << "Reverse: " << endl << n << endl;
			}
			n->DeleteList();
			delete n;
		}
	});

	Add("SingleNodeReorder", [&](){
		auto check = [&](Test::SingleNode<int> * node) {
			size_t len = node->Length();
			cout << node << endl;
			Test::SingleNode<int>::Reorder(node);
			size_t len2 = node->Length();
			cout << node << endl;
			ASSERT1(len == len2);
			size_t i = 0;
			Test::SingleNode<int> * p = node;
			while (p != nullptr) {
				ASSERT1(p->Value() == i);
				p = p->Next();
				i++;
			}
			node->DeleteList();
			delete node;
		};
		{
			Test::SingleNode<int> * n = new Test::SingleNode<int>(0);
			check(n);
		}
		{
			Test::SingleNode<int> * n = new Test::SingleNode<int>(0);
			n->InsertAtEnd(new Test::SingleNode<int>(1));
			check(n);
		}
		{
			Test::SingleNode<int> * n = new Test::SingleNode<int>(0);
			n->InsertAtEnd(new Test::SingleNode<int>(2));
			n->InsertAtEnd(new Test::SingleNode<int>(1));
			check(n);
		}
		{
			Test::SingleNode<int> * n = new Test::SingleNode<int>(0);
			n->InsertAtEnd(new Test::SingleNode<int>(2));
			n->InsertAtEnd(new Test::SingleNode<int>(3));
			n->InsertAtEnd(new Test::SingleNode<int>(1));
			check(n);
		}
		{
			for (int i = 5; i < 100; i++) {
				Logger().WriteInformation("Reorder a list of %d nodes\n", i);
				Test::SingleNode<int> * n = new Test::SingleNode<int>(0);
				int j = (i + 1) >> 1;
				for (int k = 1; k < j; k++) {
					n->InsertAtEnd(new Test::SingleNode<int>(2 * k));
				}
				j = i >> 1;
				for (int k = j; k > 0; k--) {
					n->InsertAtEnd(new Test::SingleNode<int>(2 * k - 1));
				}
				check(n);
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
}