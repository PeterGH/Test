#pragma once
#include "BinaryNodeWithParent.h"
#include "BinaryTree.h"

namespace Test {
	template<class T> class BinarySearchTree : public BinaryTree<T, BinaryNodeWithParent> {
	private:
		// Insert a content to the subtree at node and return node.
		// If node is NULL, then return a new node with the content.
		static BinaryNodeWithParent<T> * Insert(BinaryNodeWithParent<T> * node, BinaryNodeWithParent<T> * newNode)
		{
			BinaryNodeWithParent<T> * parent = node;
			BinaryNodeWithParent<T> * current = node;
			while (current != nullptr) {
				parent = current;
				if (newNode->content < current->content) current = (BinaryNodeWithParent<T> *)current->left;
				else current = (BinaryNodeWithParent<T> *)current->right;
			}

			newNode->parent = parent;

			if (parent == nullptr) {
				// This means node is NULL, i.e. it is an empty tree.
				// Return the new node as it is the first node of a tree.
				return newNode;
			} else if (newNode->content < parent->content) {
				parent->left = newNode;
			} else {
				parent->right = newNode;
			}

			return node;
		}

		static BinaryNodeWithParent<T> * Insert(BinaryNodeWithParent<T> * node, T & content)
		{
			BinaryNodeWithParent<T> * newNode = new BinaryNodeWithParent<T>(content);
			return Insert(node, newNode);
		}

		static BinaryNodeWithParent<T> * SearchRecursively(BinaryNodeWithParent<T> * node, T & content)
		{
			if (node == nullptr || node->content == content) return node;
			if (content < node->content) return Search(node->left, content);
			else return Search(node->right, content);
		}

		static BinaryNodeWithParent<T> * SearchIteratively(BinaryNodeWithParent<T> * node, T & content)
		{
			if (node == nullptr || node->content == content) return node;
			while (node != nullptr && content != node->content) {
				if (content < node->content)
					node = (BinaryNodeWithParent<T> *)node->left;
				else
					node = (BinaryNodeWithParent<T> *)node->right;
			}

			return node;
		}

		static BinaryNodeWithParent<T> * Min(BinaryNodeWithParent<T> * node)
		{
			if (node == nullptr) return node;
			while (node->left != nullptr) node = (BinaryNodeWithParent<T> *)node->left;
			return node;
		}

		static BinaryNodeWithParent<T> * Max(BinaryNodeWithParent<T> * node)
		{
			if (node == nullptr) return node;
			while (node->right != nullptr) node = (BinaryNodeWithParent<T> *)node->right;
			return node;
		}

		static BinaryNodeWithParent<T> * Successor(BinaryNodeWithParent<T> * node)
		{
			if (node == nullptr) return node;

			//  (A)
			//  / \
									// () (B)
			// The successor of A is the minimum node of subtree B
			if (node->right != nullptr) return Min((BinaryNodeWithParent<T> *)node->right);

			//    (B)
			//   /
			// (C)
			//   \
									//    ()
			//      \
									//      (A)
			//      / \
									//     () NULL
			// The successor of A is the lowest ancestor B whose left child C contains A in its right substree
			BinaryNodeWithParent<T> * parent = node->parent;
			while (parent != nullptr && node == parent->right) {
				node = parent;
				parent = parent->parent;
			}

			// parent could be NULL if node is the maximum node of tree, i.e.,
			//
			//  (A)
			//  / \
									// () NULL
			//
			// or
			//
			// ()
			//   \
									//   (A)
			//   / \
									//  () NULL
			return parent;
		}

		static BinaryNodeWithParent<T> * Predecessor(BinaryNodeWithParent<T> * node)
		{
			if (node == nullptr) return nullptr;

			//   (A)
			//   /
			// (B)
			// The predecessor of A is the maximum node of subtree B
			if (node->left != nullptr) return Max((BinaryNodeWithParent<T> *)node->left);

			//     (B)
			//       \
						//       (C)
			//       /
			//      ()
			//     /
			//   (A)
			//   / \
						// NULL ()
			// The predecessor of A is the lowest ancestor B whose right child C contains A in its left substree
			BinaryNodeWithParent<T> * parent = node->parent;
			while (parent != nullptr && node == parent->left) {
				node = parent;
				parent = parent->parent;
			}

			// parent could be NULL if node is the minimum node of tree, i.e.,
			//
			//   (A)
			//   / \
						// NULL ()
			//
			// or
			//
			//      ()
			//     /
			//   (A)
			//   / \
						// NULL ()
			return parent;
		}

		// Replace the subtree at dst with the subtree at src. Return dst.
		static BinaryNodeWithParent<T> * Transplant(BinaryNodeWithParent<T> * dst, BinaryNodeWithParent<T> * src)
		{
			if (dst == nullptr) return dst;

			if (dst->parent == nullptr) {
				// src becomes the new root
				if (src != nullptr) src->parent = nullptr;
				return dst;
			}

			if (dst == dst->parent->left)
				dst->parent->left = src;
			else
				dst->parent->right = src;

			if (src != nullptr) src->parent = dst->parent;

			return dst;
		}

		// Delete a node. If *node is the root then update it afte being deleted.
		static void Delete(BinaryNodeWithParent<T> ** node)
		{
			if (node == nullptr || *node == nullptr) return;

			if ((*node)->left == nullptr) {
				//   ()
				//    |
				//   (A)
				//   /  \
								// NULL (B)
				BinaryNodeWithParent<T> * r = (BinaryNodeWithParent<T> *)(*node)->right;
				Transplant((*node), r);

				(*node)->right = nullptr;
				delete (*node);
				*node = nullptr;
				if (r != nullptr && r->parent == nullptr) {
					// r is the new root
					*node = r;
				}

				return;
			}

			if ((*node)->right == nullptr) {
				//   ()
				//    |
				//   (A)
				//   /  \
								// (B) NULL
				BinaryNodeWithParent<T> * l = (BinaryNodeWithParent<T> *)(*node)->left;
				Transplant((*node), l);

				(*node)->left = nullptr;
				delete (*node);
				*node = nullptr;
				if (l != nullptr && l->parent == nullptr) {
					// l is the new root
					*node = l;
				}

				return;
			}

			BinaryNodeWithParent<T> * successor = Min((BinaryNodeWithParent<T> *)(*node)->right);

			if (successor->parent != (*node)) {
				//     ()
				//     |
				//    (A)
				//    / \
				//   ()  (D)
				//        \
				//         ()
				//        /
				//      (B)
				//      / \
				//    NULL (C)
				Transplant(successor, (BinaryNodeWithParent<T> *)successor->right);
				//     ()
				//     |
				//    (A)
				//    / \
				//   () (D)
				//        \
				//         ()
				//        /
				//      (C)           (B)
				successor->right = (*node)->right;
				((BinaryNodeWithParent<T> *)successor->right)->parent = successor;
				//     ()
				//     |
				//    (A)
				//    /
				//   () 
				//       (B)
				//         \
				//         (D)
				//           \
				//            ()
				//           /
				//         (C)
			}

			Transplant((*node), successor);
			successor->left = (*node)->left;
			((BinaryNodeWithParent<T> *)successor->left)->parent = successor;

			(*node)->left = nullptr;
			(*node)->right = nullptr;
			delete (*node);
			*node = nullptr;

			if (successor->parent == nullptr) {
				// successor is the new root
				*node = successor;
			}
		}

		// Verify if a subtree at node is a valid binary search tree.
		static bool Verify(BinaryNodeWithParent<T> * node)
		{
			if (node == nullptr) return true;
			if (node->left != nullptr && node->left->content >= node->content) return false;
			if (node->right != nullptr && node->right->content < node->content) return false;
			if (!Verify((BinaryNodeWithParent<T> *)node->left)) return false;
			return Verify((BinaryNodeWithParent<T> *)node->right);
		}

	public:

		void PreOrderWalkWithOutStack(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->PreOrderWalkWithOutStack(f);
			}
		}

		void InOrderWalkWithOutStack(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->InOrderWalkWithOutStack(f);
			}
		}

		void PostOrderWalkWithOutStack(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->PostOrderWalkWithOutStack(f);
			}
		}

		virtual void Insert(T & content)
		{
			if (this->root == nullptr) {
				this->root = new BinaryNodeWithParent<T>(content);
				this->root->parent = nullptr;
			} else {
				Insert(this->root, content);
			}
		}

		T & Min(void)
		{
			if (this->root != nullptr) return Min(this->root)->content;
			else throw runtime_error("Tree is empty");
		}

		T & Max(void)
		{
			if (this->root != nullptr) return Max(this->root)->content;
			else throw runtime_error("Tree is empty");
		}

		T Successor(T content)
		{
			if (this->root != nullptr) {
				BinaryNodeWithParent<T> * p = SearchIteratively(this->root, content);
				if (p != nullptr && ((p = Successor(p)) != nullptr)) return p->content;
			}

			throw runtime_error("No successor is found");
		}

		T Predecessor(T content)
		{
			if (this->root != nullptr) {
				BinaryNodeWithParent<T> * p = SearchIteratively(this->root, content);
				if (p != nullptr && ((p = Predecessor(p)) != nullptr)) return p->content;
			}

			throw runtime_error("No successor is found");
		}

		void Delete(T content)
		{
			if (this->root != nullptr) {
				BinaryNodeWithParent<T> * p = SearchIteratively(this->root, content);
				if (p != nullptr) {
					if (p == this->root) Delete(&(this->root));
					else Delete(&p);
				}
			}
		}

		bool Verify(void)
		{
			return Verify(this->root);
		}
	};
}