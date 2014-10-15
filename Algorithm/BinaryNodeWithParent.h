#pragma once
#include <set>
#include "BinaryNode.h"
using namespace std;
namespace Test {
	template<class T> class BinaryNodeWithParent : public BinaryNode<T> {
	public:
		BinaryNodeWithParent(const T & v) : BinaryNode<T>(v)
		{
			this->Neighbor(2) = nullptr;
		}

		virtual ~BinaryNodeWithParent(void) {}

		// Get the reference of parent pointer
		BinaryNodeWithParent * & Parent(void) { return (BinaryNodeWithParent * &)this->Neighbor(2); }
		// Set the parent pointer
		virtual void Parent(BinaryNode * parent) { this->Neighbor(2) = parent; }

		// Non-recursive without stack
		static void PreOrderWalkWithOutStack(BinaryNodeWithParent * node, function<void(T)> f);
		void PreOrderWalkWithOutStack(function<void(T)> f) { PreOrderWalkWithOutStack(this, f); }

		// Non-recursive without stack
		static void InOrderWalkWithOutStack(BinaryNodeWithParent * node, function<void(T)> f);
		void InOrderWalkWithOutStack(function<void(T)> f) { InOrderWalkWithOutStack(this, f); }

		// Non-recursive without stack
		static void PostOrderWalkWithOutStack(BinaryNodeWithParent * node, function<void(T)> f);
		void PostOrderWalkWithOutStack(function<void(T)> f) { PostOrderWalkWithOutStack(this, f); }

		static BinaryNodeWithParent<T> * LowestCommonAncestor(BinaryNodeWithParent<T> * first, BinaryNodeWithParent<T> * second);
		static BinaryNodeWithParent<T> * LowestCommonAncestor2(BinaryNodeWithParent<T> * first, BinaryNodeWithParent<T> * second);

		// Count height of tree rooted at node
		// Non-recursive
		static int Height2(BinaryNodeWithParent * node);
		int Height2(void) { return Height2(this); }

		// Count the distance of node from the root
		static int Depth(BinaryNodeWithParent * node);
		int Depth(void) { return Depth(this); }

		static BinaryNodeWithParent * Clone2(BinaryNode * node);
		BinaryNodeWithParent * Clone2(void) { return Clone2(this); }
	};

	// Non-recursive without stack
	template<class T> void BinaryNodeWithParent<T>::PreOrderWalkWithOutStack(BinaryNodeWithParent * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		BinaryNodeWithParent * prev = node;
		while (node != nullptr) {
			if (prev == node->Right()) {
				prev = node;
				node = node->Parent();
			} else if (node->Left() != nullptr && node->Left() != prev) {
				f(node->Value());
				prev = node;
				node = (BinaryNodeWithParent<T> *)node->Left();
			} else {
				if (node->Left() == nullptr) f(node->Value());
				prev = node;
				if (node->Right() == nullptr) node = node->Parent();
				else node = (BinaryNodeWithParent<T> *)node->Right();
			}
		}
	}

	// Non-recursive without stack
	template<class T> void BinaryNodeWithParent<T>::InOrderWalkWithOutStack(BinaryNodeWithParent * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		BinaryNodeWithParent * prev = node;
		while (node != nullptr) {
			if (prev == node->Right()) {
				prev = node;
				node = node->Parent();
			} else if (node->Left() != nullptr && node->Left() != prev) {
				prev = node;
				node = (BinaryNodeWithParent<T> *)node->Left();
			} else {
				f(node->Value());
				prev = node;
				if (node->Right() == nullptr) node = node->Parent();
				else node = (BinaryNodeWithParent<T> *)node->Right();
			}
		}
	}

	template<class T> void BinaryNodeWithParent<T>::PostOrderWalkWithOutStack(BinaryNodeWithParent * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		BinaryNodeWithParent * prev = node;
		while (node != nullptr) {
			if (prev == node->Right()) {
				f(node->Value());
				prev = node;
				node = node->Parent();
			} else if (node->Left() != nullptr && node->Left() != prev) {
				prev = node;
				node = (BinaryNodeWithParent<T> *)node->Left();
			} else {
				prev = node;
				if (node->Right() == nullptr) {
					f(node->Value());
					node = node->Parent();
				} else {
					node = (BinaryNodeWithParent<T> *)node->Right();
				}
			}
		}
	}

	template<class T> BinaryNodeWithParent<T> * BinaryNodeWithParent<T>::LowestCommonAncestor(BinaryNodeWithParent<T> * first, BinaryNodeWithParent<T> * second)
	{
		if (first == nullptr || second == nullptr) return nullptr;
		set<BinaryNodeWithParent<T> *> visited;
		pair<set<BinaryNodeWithParent<T> *>::iterator, bool> result;
		auto checkAndMoveUp = [&](BinaryNodeWithParent<T> ** p) -> bool {
			if (*p != nullptr) {
				// set.insert returns a pair, where the second value is a bool indicating
				// whether the first value points to a new element or an existing element.
				result = visited.insert(*p);
				if (!result.second) {
					// Insert failed because the same element already exists
					return true;
				}
				*p = (*p)->Parent();
			}
			return false;
		};

		while (first != nullptr || second != nullptr) {
			if (checkAndMoveUp(&first)) return first;
			if (checkAndMoveUp(&second)) return second;
		}
		return nullptr;
	}

	template<class T> BinaryNodeWithParent<T> * BinaryNodeWithParent<T>::LowestCommonAncestor2(BinaryNodeWithParent<T> * first, BinaryNodeWithParent<T> * second)
	{
		if (first == nullptr || second == nullptr) return nullptr;
		int df = first->Depth();
		int ds = second->Depth();
		int dd = df > ds ? df - ds : ds - df;
		BinaryNodeWithParent<T> * h = df < ds ? first : second;
		BinaryNodeWithParent<T> * l = df < ds ? second : first;
		for (int i = 0; i < dd; i++) {
			l = l->Parent();
		}
		while (h != nullptr && l != nullptr) {
			if (h == l) return h;
			h = h->Parent();
			l = l->Parent();
		}
		return nullptr;
	}

	// Count height of tree rooted at node
	// Non-recursive
	template<class T> int BinaryNodeWithParent<T>::Height2(BinaryNodeWithParent * node)
	{
		if (node == nullptr) return 0;
		BinaryNodeWithParent * prev = node;
		// Track the maximum height while traversing the tree
		int max = 0;
		// Track the height of current node
		int h = 0;
		while (node != nullptr) {
			if (prev == node->Right()) {
				// h is the height of right
				// Minus one to get the height of node
				h--;
				prev = node;
				node = node->Parent();
			} else if (node->Left() != nullptr && node->Left() != prev) {
				// h is the height of node
				// Plus one to get the height of left child
				h++;
				if (h > max) max = h;
				prev = node;
				node = (BinaryNodeWithParent *)node->Left();
			} else {
				if (node->Left() == prev) {
					// h is the height of left
					// Minus one to get the height of node
					h--;
				} else if (node->Left() == nullptr) {
					// h is the height of parent
					// Plus one to get the height of node
					h++;
					if (h > max) max = h;
				}

				prev = node;
				if (node->Right() == nullptr) node = node->Parent();
				else node = (BinaryNodeWithParent *)node->Right();
			}
		}
		return max;
	}

	// Count the distance of node from the root
	template<class T> int BinaryNodeWithParent<T>::Depth(BinaryNodeWithParent * node)
	{
		int d = 0;
		while (node != nullptr) {
			d++;
			node = node->Parent();
		}
		return d;
	}

	template<class T> BinaryNodeWithParent<T> * BinaryNodeWithParent<T>::Clone2(BinaryNode<T> * node)
	{
		if (node == nullptr) return nullptr;
		BinaryNodeWithParent * newNode = new BinaryNodeWithParent(node->Value());
		BinaryNodeWithParent * left = Clone2(node->Left());
		if (left != nullptr) {
			newNode->Left() = left;
			left->Parent() = newNode;
		}
		BinaryNodeWithParent * right = Clone2(node->Right());
		if (right != nullptr) {
			newNode->Right() = right;
			right->Parent() = newNode;
		}
		return newNode;
	}

}