#pragma once
#include <stdexcept>
#include "Node1.h"
using namespace std;
namespace Test {
	template<class T> class SingleNode : public Node1<T> {
		template<class T> friend ostream & operator<<(ostream &, SingleNode<T> *);
	public:
		SingleNode(const T & v) : Node1(v) {}

		virtual ~SingleNode(void) {}

		// Get the reference of next node pointer
		SingleNode * & Next(void) { return (SingleNode * &)this->first; }

		// Set the next node pointer
		void Next(SingleNode * next) { this->first = next; }

		// Count list nodes
		size_t Length(void);

		// Insert a node or a list after this one
		void InsertAfter(SingleNode * node);

		// Insert a node or a list at the end of this list
		void InsertAtEnd(SingleNode * node);

		// Delete the first node with value v
		void Delete(const T & v);

		// Delete the list at this node;
		void DeleteList(void);

		// Return the n-th node when this list contains (2n-1) or 2n nodes
		SingleNode * Middle(void);

		// Reverse this node and return the head of new list
		SingleNode * Reverse(void);
	};

	template<class T> size_t SingleNode<T>::Length(void)
	{
		size_t s = 1;
		SingleNode * p = this->Next();
		while (p != nullptr && p != this) {
			s++;
			p = p->Next();
		}
		return s;
	}

	template<class T> void SingleNode<T>::InsertAfter(SingleNode * node)
	{
		if (node == nullptr) throw invalid_argument("node is nullptr");

		SingleNode * p = node;
		while (p->Next() != nullptr && p->Next() != node) {
			p = p->Next();
		}

		// p->Next() == nullptr, if node is not circular
		// p->Next() == node, if node is circular

		// If node is circular, it will be broken
		p->Next() = this->Next();
		this->Next() = node;
	}

	template<class T> void SingleNode<T>::InsertAtEnd(SingleNode * node)
	{
		if (node == nullptr) throw invalid_argument("node is nullptr");

		SingleNode * p = this;
		while (p->Next() != nullptr && p->Next() != this) {
			p = p->Next();
		}

		// p->Next() == nullptr, if this list is not circular
		// p->Next() == this, if this list is circular

		SingleNode * q = node;
		while (q->Next() != nullptr && q->Next() != node) {
			q = q->Next();
		}

		// q->Next() == nullptr, if node is not circular
		// q->Next() == node, if node is circular

		// If node is circular, it will be broken
		// If this list is circular, it will be maintained
		q->Next() = p->Next();
		p->Next() = node;
	}

	template<class T> void SingleNode<T>::Delete(const T & v)
	{
		SingleNode * p = this;
		if (p->Value() == v) {
			// This node is what we are looking for, but
			// we cannot delete itself. So we copy next node value into this one,
			// which effectively "delete" this node.
			if (p->Next() == nullptr) throw invalid_argument("A SingleNode cannot delete itself");
			while (p->Next()->Next() != nullptr && p->Next()->Next() != this) {
				p->Value() = p->Next()->Value();
				p = p->Next();
			}
			p->Value() = p->Next()->Value();
			// Now p->Next() is useless and can be deleted
		} else {
			while (p->Next() != nullptr && p->Next()->Value() != v) {
				p = p->Next();
			}
			// Now p->Next() is what we are looking for
		}

		if (p->Next() != nullptr) {
			SingleNode * q = p->Next();
			p->Next() = q->Next();
			delete q;
		}
	}

	template<class T> void SingleNode<T>::DeleteList(void)
	{
		SingleNode<T> * p = this->Next();
		while (p != nullptr && p != this) {
			this->Next() = p->Next();
			delete p;
			p = this->Next();
		}
		this->Next() = p;
	}

	// The middle node is the n-th node, no matter if the list contain (2n-1) nodes or 2n nodes.
	template<class T> SingleNode<T> * SingleNode<T>::Middle(void)
	{
		SingleNode * middle;
		SingleNode * p;

		// Start from the first (1-th) node.
		middle = this;
		p = this;

		while (p->Next() != nullptr && p->Next() != this
			&& p->Next()->Next() != nullptr && p->Next()->Next() != this) {
			// p visits the (2n-1)-th node.
			p = p->Next()->Next();
			// middle visits the n-th node.
			middle = middle->Next();
		}

		return middle;
	}

	template<class T> SingleNode<T> * SingleNode<T>::Reverse(void)
	{
		if (this->Next() == nullptr || this->Next() == this) return this;
		SingleNode * p = this;
		SingleNode * m = this->Next();
		SingleNode * n = m->Next();
		while (n != nullptr && n != this) {
			m->Next() = p;
			p = m;
			m = n;
			n = n->Next();
		}
		m->Next() = p;
		this->Next() = n == this ? m : nullptr;
		return m;
	}

	template<class T> ostream & operator<<(ostream & os, SingleNode<T> * list)
	{
		SingleNode<T> * p = list;
		cout << "head";
		string s = to_string(p->Value());
		cout << "->" << s;
		int i = 6 + s.length();
		p = p->Next();
		while (p != nullptr && p != list) {
			s = to_string(p->Value());
			cout << "->" << s;
			i = i + 2 + s.length();
			p = p->Next();
		}

		if (p != list) {
			cout << "->nullptr" << endl;
		} else {
			auto printChar = [&](int n, char c) {
				string chars(n, c);
				cout << chars;
			};

			cout << "-|" << endl;
			i++;
			printChar(5, ' ');
			cout << "|";
			printChar(i-6, '_');
			cout << "|" << endl;
		}
		return os;
	}

}