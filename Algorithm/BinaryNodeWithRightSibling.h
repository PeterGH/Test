#pragma once
#include "BinaryNode.h"
namespace Test {
	template<class T> class BinaryNodeWithRightSibling : public BinaryNode<T> {
	public:
		BinaryNodeWithRightSibling * rightSibling;

		BinaryNodeWithRightSibling(const T & content) : BinaryNode(content), rightSibling(nullptr) {}

		virtual ~BinaryNodeWithRightSibling(void)
		{
			this->rightSibling = nullptr;
		}

		// This works for both complete and incomplete binary trees
		static void SetRightSibling(BinaryNodeWithRightSibling * node)
		{
			if (node == nullptr) return;

			while (node != nullptr) {
				// Track nodes at current level, which is already done with rightSibling setting
				BinaryNodeWithRightSibling * current = node;
				// Track the beginning of next level, which is to set with rightSibling
				node = (BinaryNodeWithRightSibling *)current->left;
				// Find the beginning
				while (node == nullptr && current != nullptr) {
					node = (BinaryNodeWithRightSibling *)current->left;
					if (node == nullptr) {
						// Current has no left child
						node = (BinaryNodeWithRightSibling *)current->right;
					}
					if (node == nullptr) {
						// Current has no left and right children
						current = current->rightSibling;
					}
				}

				if (node == nullptr) {
					// No more nodes in the next level
					return;
				}

				BinaryNodeWithRightSibling * prev = node;
				if (prev == current->left) {
					if (current->right != nullptr) {
						prev->rightSibling = (BinaryNodeWithRightSibling *)current->right;
						prev = (BinaryNodeWithRightSibling *)current->right;
					}
				}

				current = current->rightSibling;
				while (current != nullptr) {
					if (current->left != nullptr) {
						prev->rightSibling = (BinaryNodeWithRightSibling *)current->left;
						prev = (BinaryNodeWithRightSibling *)current->left;
					}
					if (current->right != nullptr) {
						prev->rightSibling = (BinaryNodeWithRightSibling *)current->right;
						prev = (BinaryNodeWithRightSibling *)current->right;
					}
					current = current->rightSibling;
				}
			}
		}

		void SetRightSibling(void) { SetRightSibling(this); }

		// DFS
		// This works for complete binary tree only
		static void SetRightSibling2(BinaryNodeWithRightSibling * node)
		{
			if (node == nullptr) return;

			BinaryNodeWithRightSibling * p = (BinaryNodeWithRightSibling *)node->left;
			if (p != nullptr) {
				p->rightSibling = (BinaryNodeWithRightSibling *)node->right;
			}

			if (node->right != nullptr) {
				p = (BinaryNodeWithRightSibling *)node->right;
			}

			if (p != nullptr) {
				// For incomplete binary tree, the following search will fail,
				// because not all rightSibling of nodes at current level are set yet.
				BinaryNodeWithRightSibling * current = node->rightSibling;
				while (current != nullptr) {
					if (current->left != nullptr) {
						p->rightSibling = (BinaryNodeWithRightSibling *)current->left;
						break;
					}
					if (current->right != nullptr) {
						p->rightSibling = (BinaryNodeWithRightSibling *)current->right;
						break;
					}
					current = current->rightSibling;
				}
			}

			SetRightSibling2((BinaryNodeWithRightSibling *)node->left);
			SetRightSibling2((BinaryNodeWithRightSibling *)node->right);
		}

		void SetRightSibling2(void) { SetRightSibling2(this); }

		static BinaryNodeWithRightSibling * Clone(BinaryNode * node)
		{
			if (node == nullptr) return nullptr;
			BinaryNodeWithRightSibling * newNode = new BinaryNodeWithRightSibling(node->content);
			BinaryNodeWithRightSibling * left = Clone(node->left);
			if (left != nullptr) {
				newNode->left = left;
			}
			BinaryNodeWithRightSibling * right = Clone(node->right);
			if (right != nullptr) {
				newNode->right = right;
			}

			return newNode;
		}

		BinaryNodeWithRightSibling * Clone(void) { return Clone(this); }

		// Visit level by level, left to right
		// Breadth-first search
		static void LevelOrderWalk(BinaryNodeWithRightSibling * node, function<void(T)> f)
		{
			if (node == nullptr || f == nullptr) return;
			while (node != nullptr) {
				BinaryNodeWithRightSibling * p = node;
				while (p != nullptr) {
					f(p->content);
					p = p->rightSibling;
				}

				while (p == nullptr && node != nullptr) {
					p = (BinaryNodeWithRightSibling *)node->left;
					if (p == nullptr) {
						p = (BinaryNodeWithRightSibling *)node->right;
					}
					if (p == nullptr) {
						node = node->rightSibling;
					}
				}

				node = p;
			}
		}

		virtual void LevelOrderWalk(function<void(T)> f) { LevelOrderWalk(this, f); }
	};
}