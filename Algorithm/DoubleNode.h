#pragma once
#include "Node2.h"
namespace Test {
	template<class T> class DoubleNode : public Node2<T> {
	public:
		DoubleNode(const T & v) : Node2(v) {}

		DoubleNode * & Prev(void) { return (DoubleNode * &)this->first; }
		void Prev(DoubleNode * prev) { this->first = prev; }
		DoubleNode * & Next(void) { return (DoubleNode * &)this->second; }
		void Next(DoubleNode * next) { this->second = next; }
	};
}