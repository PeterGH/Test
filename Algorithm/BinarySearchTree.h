#pragma once

#include "BinaryTree.h"

namespace Test {
	template<class T> class BinarySearchTree : public BinaryTree<T> {
	private:
		// Insert a content to the subtree at node and return node.
		// If node is NULL, then return a new node with the content.
		static Node * Insert(Node * node, Node * newNode);
		static Node * Insert(Node * node, T & content);

		static Node * Search(Node * node, T & content);
		static Node * Search2(Node * node, T & content);

		static Node * Min(Node * node);

		static Node * Max(Node * node);

		static Node * Successor(Node * node);

		static Node * Predecessor(Node * node);

		// Replace the subtree at dst with the subtree at src. Return dst.
		static Node * Transplant(Node * dst, Node * src);

		// Delete a node. If *node is the root then update it afte being deleted.
		static void Delete(Node ** node);

		// Verify if a subtree at node is a valid binary search tree.
		static bool Verify(Node * node);

	public:

		virtual void Insert(T & content);

		T & Min(void);

		T & Max(void);

		T Successor(T content);

		T Predecessor(T content);

		void Delete(T content);

		bool Verify(void);
	};

	template<class T> typename BinaryTree<T>::Node * BinarySearchTree<T>::Insert(Node * node, Node * newNode)
	{
		Node * parent = node;
		Node * current = node;
		while (current != nullptr) {
			parent = current;
			if (newNode->content < current->content) current = current->left;
			else current = current->right;
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

	template<class T> typename BinaryTree<T>::Node * BinarySearchTree<T>::Insert(Node * node, T & content)
	{
		Node * newNode = new Node(content);
		return Insert(node, newNode);
	}

	template<class T> typename BinaryTree<T>::Node * BinarySearchTree<T>::Search(Node * node, T & content)
	{
		if (node == nullptr || node->content == content) return node;
		if (content < node->content) return Search(node->left, content);
		else return Search(node->right, content);
	}

	template<class T> typename BinaryTree<T>::Node * BinarySearchTree<T>::Search2(Node * node, T & content)
	{
		if (node == nullptr || node->content == content) return node;
		while (node != nullptr && content != node->content) {
			if (content < node->content)
				node = node->left;
			else
				node = node->right;
		}

		return node;
	}

	template<class T> typename BinaryTree<T>::Node * BinarySearchTree<T>::Min(Node * node)
	{
		if (node == nullptr) return node;
		while (node->left != nullptr) node = node->left;
		return node;
	}

	template<class T> typename BinaryTree<T>::Node * BinarySearchTree<T>::Max(Node * node)
	{
		if (node == nullptr) return node;
		while (node->right != nullptr) node = node->right;
		return node;
	}

	template<class T> typename BinaryTree<T>::Node * BinarySearchTree<T>::Successor(Node * node)
	{
		if (node == nullptr) return node;

		//  (A)
		//  / \
		// () (B)
		// The successor of A is the minimum node of subtree B
		if (node->right != nullptr) return Min(node->right);

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
		Node * parent = node->parent;
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

	template<class T> typename BinaryTree<T>::Node * BinarySearchTree<T>::Predecessor(Node * node)
	{
		if (node == nullptr) return nullptr;

		//   (A)
		//   /
		// (B)
		// The predecessor of A is the maximum node of subtree B	
		if (node->left != nullptr) return Max(node->left);

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
		Node * parent = node->parent;
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

	template<class T> typename BinaryTree<T>::Node * BinarySearchTree<T>::Transplant(Node * dst, Node * src)
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

	template<class T> void BinarySearchTree<T>::Delete(Node ** node)
	{
		if (node == nullptr || *node == nullptr) return;

		if ((*node)->left == nullptr) {
			//   () 
			//    |
			//   (A)
			//   /  \
			// NULL (B)
			Node * r = (*node)->right;
			Transplant((*node), r);

			// delete node will not delete its children
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
			Node * l = (*node)->left;
			Transplant((*node), l);

			// delete node will not delete its children
			delete (*node);
			*node = nullptr;
			if (l != nullptr && l->parent == nullptr) {
				// l is the new root
				*node = l;
			}
			
			return;
		}

		Node * successor = Min((*node)->right);

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
			Transplant(successor, successor->right);
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
			successor->right->parent = successor;
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
		successor->left->parent = successor;
		delete (*node);
		*node = nullptr;
		if (successor->parent == nullptr) {
			// successor is the new root
			*node = successor;
		}
	}

	template<class T> bool BinarySearchTree<T>::Verify(Node * node)
	{
		if (node == nullptr) return true;
		if (node->left != nullptr && node->left->content >= node->content) return false;
		if (node->right != nullptr && node->right->content < node->content) return false;
		if (!Verify(node->left)) return false;
		return Verify(node->right);
	}

	template<class T> void BinarySearchTree<T>::Insert(T & content)
	{
		if (this->root == nullptr) {
			this->root = new Node(content);
			this->root->parent = nullptr;
		} else {
			Insert(this->root, content);
		}
	}

	template<class T> T & BinarySearchTree<T>::Min(void)
	{
		if (this->root != nullptr) return Min(this->root)->Content();
		else throw runtime_error("Tree is empty");
	}

	template<class T> T & BinarySearchTree<T>::Max(void)
	{
		if (this->root != nullptr) return Max(this->root)->Content();
		else throw runtime_error("Tree is empty");
	}

	template<class T> T BinarySearchTree<T>::Successor(T content)
	{
		if (this->root != nullptr) {
			Node * p = Search2(this->root, content);
			if (p != nullptr && ((p = Successor(p)) != nullptr)) return p->Content();
		}

		throw runtime_error("No successor is found");
	}

	template<class T> T BinarySearchTree<T>::Predecessor(T content)
	{
		if (this->root != nullptr) {
			Node * p = Search2(this->root, content);
			if (p != nullptr && ((p = Predecessor(p)) != nullptr)) return p->Content();
		}

		throw runtime_error("No successor is found");
	}

	template<class T> void BinarySearchTree<T>::Delete(T content)
	{
		if (this->root != nullptr) {
			Node * p = Search2(this->root, content);
			if (p != nullptr) {
				if (p == this->root) Delete(&(this->root));
				else Delete(&p);
			}
		}
	}

	template<class T> bool BinarySearchTree<T>::Verify(void)
	{
		return Verify(this->root);
	}
}