#pragma once
#include <vector>
using namespace std;

namespace Test {
	template<class T> class Node {
	private:
		void Expand(size_t i)
		{
			if (i >= this->neighbor.size()) {
				this->neighbor.insert(this->neighbor.end(), i - this->neighbor.size() + 1, nullptr);
			}
		}

	protected:
		T value;
		vector<Node *> neighbor;

	public:
		Node(const T & v) : value(v) {}

		Node(const T & v, size_t n) : value(v)
		{
			this->neighbor = vector<Node *>(n, nullptr);
		}

		Node(size_t n)
		{
			this->neighbor = vector<Node *>(n, nullptr);
		}

		virtual ~Node(void)
		{
			for (size_t i = 0; i < this->neighbor.size(); i++) {
				this->neighbor[i] = nullptr;
			}
		}

		T Value(void) const { return this->value; }

		T & Value(void) { return this->value; }

		void Value(const T & v) { this->value = v; }

		Node * & Neighbor(size_t i)
		{
			Expand(i);
			return (Node * &)this->neighbor[i];
		}

		void Neighbor(size_t i, Node * n)
		{
			Expand(i);
			this->neighbor[i] = n;
		}

		size_t CountNeighbors(void) { return this->neighbor.size(); }
	};
}