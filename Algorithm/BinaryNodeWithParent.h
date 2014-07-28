#pragma once
#include "BinaryNode.h"
#include <set>
using namespace std;
namespace Test {
	template<class T> class BinaryNodeWithParent : public BinaryNode<T> {
	public:
		BinaryNodeWithParent * parent;

		BinaryNodeWithParent(const T & content) : BinaryNode(content), parent(nullptr) {}

		virtual ~BinaryNodeWithParent(void)
		{
			// Base destructor is called implicitly
			// BinaryNode::~BinaryNode();
			this->parent = nullptr;
		}

		// Non-recursive without stack
		static void PreOrderWalkWithOutStack(BinaryNodeWithParent * node, function<void(T)> f)
		{
			if (node == nullptr || f == nullptr) return;
			BinaryNodeWithParent * prev = node;
			while (node != nullptr) {
				if (prev == node->right) {
					prev = node;
					node = node->parent;
				} else if (node->left != nullptr && prev != node->left) {
					f(node->content);
					prev = node;
					node = (BinaryNodeWithParent<T> *)node->left;
				} else {
					if (node->left == nullptr) {
						f(node->content);
					}
					
					prev = node;
					if (node->right != nullptr) {
						node = (BinaryNodeWithParent<T> *)node->right;
					} else {
						node = node->parent;
					}
				}
			}
		}

		void PreOrderWalkWithOutStack(function<void(T)> f) { PreOrderWalkWithOutStack(this, f); }

		// Non-recursive without stack
		static void InOrderWalkWithOutStack(BinaryNodeWithParent * node, function<void(T)> f)
		{
			if (node == nullptr || f == nullptr) return;
			BinaryNodeWithParent * prev = node;
			while (node != nullptr) {
				if (prev == node->right) {
					prev = node;
					node = node->parent;
				} else if (node->left != nullptr && prev != node->left) {
					prev = node;
					node = (BinaryNodeWithParent<T> *)node->left;
				} else {
					f(node->content);
					prev = node;
					if (node->right != nullptr) {
						node = (BinaryNodeWithParent<T> *)node->right;
					} else {
						node = node->parent;
					}
				}
			}
		}

		void InOrderWalkWithOutStack(function<void(T)> f) { InOrderWalkWithOutStack(this, f); }

		// Non-recursive without stack
		static void PostOrderWalkWithOutStack(BinaryNodeWithParent * node, function<void(T)> f)
		{
			if (node == nullptr || f == nullptr) return;
			BinaryNodeWithParent * prev = node;
			while (node != nullptr) {
				if (prev == node->right) {
					f(node->content);
					prev = node;
					node = node->parent;
				} else if (node->left != nullptr && prev != node->left) {
					prev = node;
					node = (BinaryNodeWithParent<T> *)node->left;
				} else {
					prev = node;
					if (node->right != nullptr) {
						node = (BinaryNodeWithParent<T> *)node->right;
					} else {
						f(node->content);
						node = node->parent;
					}
				}
			}
		}

		void PostOrderWalkWithOutStack(function<void(T)> f) { PostOrderWalkWithOutStack(this, f); }

		// Count height of tree rooted at node
		// Non-recursive
		static int Height2(BinaryNodeWithParent * node)
		{
			if (node == nullptr) return 0;
			BinaryNodeWithParent * prev = node;
			// Track the maximum height while traversing the tree
			int max = 0;
			// Track the height of current node
			int h = 0;
			while (node != nullptr) {
				if (prev == node->right) {
					// h is the height of right
					// Minus one to get the height of node
					h--;
					prev = node;
					node = node->parent;
				} else if (node->left != nullptr && prev != node->left) {
					// h is the height of parent
					// Plus one to get the height of node
					h++;
					if (h > max) max = h;
					prev = node;
					node = (BinaryNodeWithParent *)node->left;
				} else {
					if (prev == node->left) {
						// h is the height of left
						// Minus one to get the height of node
						h--;
					} else if (node->left == nullptr) {
						// h is the height of parent
						// Plus one to get the height of node
						h++;
						if (h > max) max = h;
					}
					
					prev = node;
					if (node->right == nullptr) {
						node = node->parent;
					} else {
						node = (BinaryNodeWithParent *)node->right;
					}
				}
			}
			
			return max;
		}

		int Height(void) { return Height2(this); }

		// Count the distance of node from the root
		static int Depth(BinaryNodeWithParent * node)
		{
			int d = 0;
			while (node != nullptr) {
				d++;
				node = node->parent;
			}
			return d;
		}

		int Depth(void) { return Depth(this); }
	};
}