#pragma once
#include "Node.h"
namespace Test {
	template<class T> class Node1 : public Node<T> {
	protected:
		Node * first;
	public:
		Node1(const T & v) : Node(v), first(nullptr) {}

		virtual ~Node1(void)
		{
			if (this->first != nullptr) {
				this->first = nullptr;
			}
		}

		Node1 * & Next(void) { return (Node1 * &)this->first; }
		void Next(Node1 * next) { this->first = next; }
	};
}