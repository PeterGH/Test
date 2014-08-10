#pragma once

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

namespace Test {
	template<class T> class Node {
	protected:
		T value;
	public:
		Node(const T & v) : value(v) {}

		virtual ~Node(void)
		{
#ifdef DEBUG
			cout << "Deleting " << this->value << endl;
#endif
		}

		T & Value(void) { return this->value; }
		void Value(const T & v) { this->value = v; }
	};
}