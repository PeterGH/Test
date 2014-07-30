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

	Add("Node1", [&](){
		{
			Test::Node1<int> node(1);
		}
		{
			Test::Node1<int> * p = new Test::Node1<int>(2);
			delete p;
		}
		{
			Test::Node1<int> * n1 = new Test::Node1<int>(1);
			Test::Node1<int> * n2 = new Test::Node1<int>(2);
			Test::Node1<int> * n3 = new Test::Node1<int>(3);
			Test::Node1<int> * n4 = new Test::Node1<int>(4);
			n1->Next() = n2;
			n2->Next() = n3;
			n3->Next() = n4;

			Test::Node1<int> * p = n1;
			Test::Node1<int> * c = n1;
			do {
				Logger().WriteInformation("Value %d\n", c->Value());
				p = c;
				c = p->Next();
				delete p;
			} while (c != nullptr);
		}
		{
			Test::Node1<int> * n1 = new Test::Node1<int>(1);
			Test::Node1<int> * n2 = new Test::Node1<int>(2);
			Test::Node1<int> * n3 = new Test::Node1<int>(3);
			Test::Node1<int> * n4 = new Test::Node1<int>(4);
			n1->Next(n2);
			n2->Next(n3);
			n3->Next(n4);

			Test::Node1<int> * p = n1;
			Test::Node1<int> * c = n1;
			do {
				Logger().WriteInformation("Value %d\n", c->Value());
				p = c;
				c = p->Next();
				delete p;
			} while (c != nullptr);
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