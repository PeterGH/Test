#pragma once
#include "Node1.h"
namespace Test {
	template<class T> class Node2 : public Node1<T> {
	protected:
		Node * second;
	public:
		Node2(const T & v) : Node1(v), second(nullptr) {}

		virtual ~Node2(void)
		{
			if (this->second != nullptr) {
				this->second = nullptr;
			}
		}
	};
}