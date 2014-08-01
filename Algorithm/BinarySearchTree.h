#pragma once
#include <functional>
#ifdef DEBUG
#include <iostream>
#endif
#include "BinaryNodeWithParent.h"
#include "BinaryTree.h"
#include "PreOrderBinaryIteratorWithOutStack.h"
#include "InOrderBinaryIteratorWithOutStack.h"
#include "PostOrderBinaryIteratorWithOutStack.h"
using namespace std;
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

		static BinaryNodeWithParent<T> * SearchRecursively(BinaryNodeWithParent<T> * node, const T & content)
		{
			if (node == nullptr || node->content == content) return node;
			if (content < node->content) return SearchRecursively((BinaryNodeWithParent<T> *)node->left, content);
			else return SearchRecursively((BinaryNodeWithParent<T> *)node->right, content);
		}

		static BinaryNodeWithParent<T> * SearchIteratively(BinaryNodeWithParent<T> * node, const T & content)
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

		static BinaryNodeWithParent<T> * LowestCommonAncestor(BinaryNodeWithParent<T> * first, BinaryNodeWithParent<T> * second)
		{
			if (first == nullptr || second == nullptr) return nullptr;

			set<BinaryNodeWithParent<T> *> visited;
			pair<set<BinaryNodeWithParent<T>*>::iterator, bool> result;

			auto checkAndMoveUp = [&](BinaryNodeWithParent<T> ** p) -> bool {
				if (*p != nullptr) {
					result = visited.insert(*p);
					if (!result.second) {
						// Insert failed because the same element already exists
						return true;
					}
					*p = (*p)->parent;
				}
				return false;
			};

			while (first != nullptr || second != nullptr) {
				if (checkAndMoveUp(&first)) {
					return first;
				}

				if (checkAndMoveUp(&second)) {
					return second;
				}
			}

			return nullptr;
		}

		static BinaryNodeWithParent<T> * LowestCommonAncestor2(BinaryNodeWithParent<T> * first, BinaryNodeWithParent<T> * second)
		{
			if (first == nullptr || second == nullptr) return nullptr;

			int df = first->Depth();
			int ds = second->Depth();

			int dd = df > ds ? df - ds : ds - df;
			BinaryNodeWithParent<T> * h = df < ds ? first : second;
			BinaryNodeWithParent<T> * l = df < ds ? second : first;
			for (int i = 0; i < dd; i++) {
				l = l->parent;
			}

			while (h != nullptr && l != nullptr) {
				if (h == l) return h;
				h = h->parent;
				l = l->parent;
			}

			return nullptr;
		}

		static BinaryNodeWithParent<T> * LowestCommonAncestor3(BinaryNodeWithParent<T> * node, const T & first, const T & second)
		{
			if (node == nullptr) return nullptr;

			while (node != nullptr) {
				if (node->content > std::max(first, second))
					node = (BinaryNodeWithParent<T> *)node->left;
				else if (node->content < std::min(first, second))
					node = (BinaryNodeWithParent<T> *)node->right;
				else
					break;
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

		BinaryNodeWithParent<T> * Search(const T & content)
		{
			return SearchRecursively((BinaryNodeWithParent<T> *)this->root, content);
		}

		virtual const T & LowestCommonAncestor(const T & first, const T & second)
		{
			BinaryNodeWithParent<T> * firstNode = this->Search(first);
			BinaryNodeWithParent<T> * secondNode = this->Search(second);
			BinaryNodeWithParent<T> * node = LowestCommonAncestor(firstNode, secondNode);
			if (node == nullptr) {
				throw new invalid_argument(String::Format("%d and %d have no common ancestor.", first, second));
			}
			return node->content;
		}

		virtual const T & LowestCommonAncestor2(const T & first, const T & second)
		{
			BinaryNodeWithParent<T> * firstNode = this->Search(first);
			BinaryNodeWithParent<T> * secondNode = this->Search(second);
			BinaryNodeWithParent<T> * node = LowestCommonAncestor2(firstNode, secondNode);
			if (node == nullptr) {
				throw new invalid_argument(String::Format("%d and %d have no common ancestor.", first, second));
			}
			return node->content;
		}

		virtual const T & LowestCommonAncestor3(const T & first, const T & second)
		{
			BinaryNodeWithParent<T> * node = LowestCommonAncestor3(this->root, first, second);
			if (node == nullptr) {
				throw new invalid_argument(String::Format("%d and %d have no common ancestor.", first, second));
			}
			return node->content;
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

		// Verify if a subtree at node is a valid binary search tree.
		static bool Verify(BinaryNode<T> * node)
		{
			if (node == nullptr) return true;
			T min = BinaryTree<T, BinaryNode>::Min(node)->content;
			T max = BinaryTree<T, BinaryNode>::Max(node)->content;
			function<bool(BinaryNode<T> *, T, T)> verify = [&](BinaryNode<T> * c, T l, T h) -> bool {
				if (c == nullptr) return true;
				if (c->content < l || c->content > h) return false;
				if (c->left != nullptr && c->left->content >= c->content) return false;
				if (c->right != nullptr && c->right->content < c->content) return false;
				return verify(c->left, l, c->content) && verify(c->right, c->content, h);
			};

			return verify(node, min, max);
		}

		bool Verify(void)
		{
			return Verify(this->root);
		}

		PreOrderBinaryIteratorWithOutStack<T> PreOrderWithOutStackBegin() const { return PreOrderBinaryIteratorWithOutStack<T>(this->root); }
		PreOrderBinaryIteratorWithOutStack<T> PreOrderWithOutStackEnd() const { return PreOrderBinaryIteratorWithOutStack<T>(); }

		InOrderBinaryIteratorWithOutStack<T> InOrderWithOutStackBegin() const { return InOrderBinaryIteratorWithOutStack<T>(this->root); }
		InOrderBinaryIteratorWithOutStack<T> InOrderWithOutStackEnd() const { return InOrderBinaryIteratorWithOutStack<T>(); }

		PostOrderBinaryIteratorWithOutStack<T> PostOrderWithOutStackBegin() const { return PostOrderBinaryIteratorWithOutStack<T>(this->root); }
		PostOrderBinaryIteratorWithOutStack<T> PostOrderWithOutStackEnd() const { return PostOrderBinaryIteratorWithOutStack<T>(); }

		// http://leetcode.com/2010/11/largest-binary-search-tree-bst-in_22.html
		void MaxTreeFromBinaryTree(BinaryTree<T, BinaryNode> * binaryTree)
		{
			function<void(BinaryNodeWithParent<T> * &)> deleteTree = [&](BinaryNodeWithParent<T> * & node) {
				node->DeleteTree();
				delete node;
			};

			function<BinaryNodeWithParent<T> * (BinaryNodeWithParent<T> *, T)>
				firstNodeLessThanOrEqual = [&](BinaryNodeWithParent<T> * n, T v) -> BinaryNodeWithParent<T> * {
				BinaryNodeWithParent<T> * p = n;
				while (p != nullptr) {
					if (p->content <= v) return p;
					if (p->left != nullptr) p = (BinaryNodeWithParent<T> *)p->left;
					else p = (BinaryNodeWithParent<T> *)p->right;
				}
				return p;
			};

			function<BinaryNodeWithParent<T> * (BinaryNodeWithParent<T> *, T)>
				firstNodeGreaterThan = [&](BinaryNodeWithParent<T> * n, T v) -> BinaryNodeWithParent<T> * {
				BinaryNodeWithParent<T> * p = n;
				while (p != nullptr) {
					if (p->content > v) return p;
					if (p->right != nullptr) p = (BinaryNodeWithParent<T> *)p->right;
					else p = (BinaryNodeWithParent<T> *)p->left;
				}
				return p;
			};

			function<void(BinaryNodeWithParent<T> * &, int &, BinaryNodeWithParent<T> *, int)>
				mergeLeft = [&](BinaryNodeWithParent<T> * & node, int & count, BinaryNodeWithParent<T> * left, int leftCount) {
				BinaryNodeWithParent<T> * clone = left->Clone();
				BinaryNodeWithParent<T> * invalid = firstNodeGreaterThan(clone, node->content);
				int invalidSize = invalid == nullptr ? 0 : invalid->Size();
				node->left = clone;
				clone->parent = node;
				count += (leftCount - invalidSize);
				if (invalid != nullptr) {
					BinaryNodeWithParent<T> * p = invalid->parent;
					p->right = nullptr;
					deleteTree(invalid);
				}
			};

			function<void(BinaryNodeWithParent<T> * &, int &, BinaryNodeWithParent<T> *, int)>
				mergeRight = [&](BinaryNodeWithParent<T> * & node, int & count, BinaryNodeWithParent<T> * right, int rightCount) {
				BinaryNodeWithParent<T> * clone = right->Clone();
				BinaryNodeWithParent<T> * invalid = firstNodeLessThanOrEqual(clone, node->content);
				int invalidSize = invalid == nullptr ? 0 : invalid->Size();
				node->right = clone;
				clone->parent = node;
				count += (rightCount - invalidSize);
				if (invalid != nullptr) {
					BinaryNodeWithParent<T> * p = invalid->parent;
					p->left = nullptr;
					deleteTree(invalid);
				}
			};

			function<void(const BinaryNode<T> *, BinaryNodeWithParent<T> * &, int &, BinaryNodeWithParent<T> * &, int &)>
				search = [&](
				const BinaryNode<T> * node,          // current node from input binary tree
				BinaryNodeWithParent<T> * & current, // root of current search tree
				int & currentCount,                  // node count of current search tree
				BinaryNodeWithParent<T> * & last,    // root of last max search tree. can be current or different.
				int & lastCount                      // node count of last max search tree.
				)
			{
				if (node == nullptr) {
					current = nullptr;
					currentCount = 0;
					last = nullptr;
					lastCount = 0;
					return;
				}

				BinaryNodeWithParent<T> * left;
				int leftCount;
				BinaryNodeWithParent<T> * leftLast;
				int leftLastCount;
				search(node->left, left, leftCount, leftLast, leftLastCount);

				BinaryNodeWithParent<T> * right;
				int rightCount;
				BinaryNodeWithParent<T> * rightLast;
				int rightLastCount;
				search(node->right, right, rightCount, rightLast, rightLastCount);

				current = new BinaryNodeWithParent<T>(node->content);
				currentCount = 1;

				if (left != nullptr && left->content <= current->content) {
					mergeLeft(current, currentCount, left, leftCount);
				}

				if (right != nullptr && right->content > current->content) {
					mergeRight(current, currentCount, right, rightCount);
				}

				if (leftLastCount >= rightLastCount) {
					last = leftLast;
					lastCount = leftLastCount;
				} else {
					last = rightLast;
					lastCount = rightLastCount;
				}

				if (currentCount >= lastCount) {
					last = current;
					lastCount = currentCount;
				}

#ifdef DEBUG
				cout << node->content << " current count " << currentCount << endl;
				current->Print();
				cout << node->content << " last count " << lastCount << endl;
				last->Print();
#endif

				if (left != last) {
					deleteTree(left);
				}

				if (right != last) {
					deleteTree(right);
				}

				if (leftLast != last && leftLast != left) {
					deleteTree(leftLast);
				}

				if (rightLast != last && rightLast != right) {
					deleteTree(rightLast);
				}
			};

			BinaryNodeWithParent<T> * node;
			int count;
			BinaryNodeWithParent<T> * last;
			int lastCount;
			search(binaryTree->Root(), node, count, last, lastCount);

			if (node != last) {
				if (count >= lastCount) {
					this->root = node;
					deleteTree(last);
				} else {
					this->root = last;
					deleteTree(node);
				}
			} else {
				this->root = node;
			}
		}

		// http://leetcode.com/2010/11/largest-binary-search-tree-bst-in_22.html
		void MaxTreeFromBinaryTree2(BinaryTree<T, BinaryNode> * binaryTree)
		{
			function<void(BinaryNodeWithParent<T> * &)> deleteTree = [&](BinaryNodeWithParent<T> * & node) {
				node->DeleteTree();
				delete node;
			};

			T binaryTreeMin = binaryTree->Min();
			T binaryTreeMax = binaryTree->Max();

			function<void(const BinaryNode<T> *, T, T, BinaryNodeWithParent<T> * &, int &, BinaryNodeWithParent<T> * &, int &)>
				search = [&](
				const BinaryNode<T> * node,          // current node from input binary tree
				T min,                               // lower bound of node value
				T max,                               // upper bound of node value
				BinaryNodeWithParent<T> * & current, // root of current search tree
				int & currentCount,                  // node count of current search tree
				BinaryNodeWithParent<T> * & last,    // root of last max search tree. can be current or different.
				int & lastCount                      // node count of last max search tree.
				)
			{
				if (node == nullptr) {
					current = nullptr;
					currentCount = 0;
					last = nullptr;
					lastCount = 0;
					return;
				}

				if (min < node->content && node->content <= max) {
					BinaryNodeWithParent<T> * left;
					int leftCount;
					BinaryNodeWithParent<T> * leftLast;
					int leftLastCount;
					search(node->left, min, node->content, left, leftCount, leftLast, leftLastCount);

					BinaryNodeWithParent<T> * right;
					int rightCount;
					BinaryNodeWithParent<T> * rightLast;
					int rightLastCount;
					search(node->right, node->content, max, right, rightCount, rightLast, rightLastCount);

					current = new BinaryNodeWithParent<T>(node->content);
					currentCount = 1;

					if (left != nullptr) {
						current->left = left;
						left->parent = current;
						currentCount += leftCount;
					}

					if (right != nullptr) {
						current->right = right;
						right->parent = current;
						currentCount += rightCount;
					}

					if (leftLastCount >= rightLastCount) {
						last = leftLast;
						lastCount = leftLastCount;
					} else {
						last = rightLast;
						lastCount = rightLastCount;
					}

					if (currentCount >= lastCount) {
						last = current;
						lastCount = currentCount;
					}

					if (left != current->left && left != last) {
						deleteTree(left);
					}

					if (right != current->right && right != last) {
						deleteTree(right);
					}

					if (leftLast != last && leftLast != left) {
						deleteTree(leftLast);
					}

					if (rightLast != last && rightLast != right) {
						deleteTree(rightLast);
					}
				} else {
					search(node, binaryTreeMin - 1, binaryTreeMax + 1, current, currentCount, last, lastCount);
					current = nullptr;
					currentCount = 0;
				}
			};

			BinaryNodeWithParent<T> * node;
			int count;
			BinaryNodeWithParent<T> * last;
			int lastCount;
			search(binaryTree->Root(), binaryTreeMin - 1, binaryTreeMax + 1, node, count, last, lastCount);

			if (node != last) {
				if (count >= lastCount) {
					this->root = node;
					deleteTree(last);
				} else {
					this->root = last;
					deleteTree(node);
				}
			} else {
				this->root = node;
			}
		}

		// http://leetcode.com/2010/11/largest-binary-search-tree-bst-in_22.html
		// This implementation has a bug.
		void MaxTreeFromBinaryTree3(BinaryTree<T, BinaryNode> * binaryTree)
		{
			function<void(BinaryNodeWithParent<T> * &)> deleteTree = [&](BinaryNodeWithParent<T> * & node) {
				node->DeleteTree();
				delete node;
			};

			function<void(const BinaryNode<T> *, BinaryNodeWithParent<T> * &, int &, T &, T &, BinaryNodeWithParent<T> * &, int &, T &, T &)>
				search = [&](
				const BinaryNode<T> * node,          // current node from input binary tree
				BinaryNodeWithParent<T> * & current, // root of current search tree
				int & currentCount,                  // node count of current search tree
				T & currentMin,                      // min of current search tree
				T & currentMax,                      // max of current search tree
				BinaryNodeWithParent<T> * & last,    // root of last max search tree. can be current or different.
				int & lastCount,                     // node count of last max search tree.
				T & lastMin,                         // min of last search tree
				T & lastMax                          // max of last search tree
				)
			{
				if (node == nullptr) {
					current = nullptr;
					currentCount = 0;
					last = nullptr;
					lastCount = 0;
					return;
				}

				BinaryNodeWithParent<T> * left;
				int leftCount;
				T leftMin;
				T leftMax;
				BinaryNodeWithParent<T> * leftLast;
				int leftLastCount;
				T leftLastMin;
				T leftLastMax;
				search(node->left, left, leftCount, leftMin, leftMax, leftLast, leftLastCount, leftLastMin, leftLastMax);

				BinaryNodeWithParent<T> * right;
				int rightCount;
				T rightMin;
				T rightMax;
				BinaryNodeWithParent<T> * rightLast;
				int rightLastCount;
				T rightLastMin;
				T rightLastMax;
				search(node->right, right, rightCount, rightMin, rightMax, rightLast, rightLastCount, rightLastMin, rightLastMax);

				current = new BinaryNodeWithParent<T>(node->content);
				currentCount = 1;
				currentMin = node->content;
				currentMax = node->content;

				if (left != nullptr && leftMax <= node->content) {
					current->left = left;
					left->parent = current;
					currentCount += leftCount;
					currentMin = leftMin;
				} else {
					// When leftMax > node->content, it is possible part
					// of left tree and node can form a valid search tree.
				}

				if (right != nullptr && node->content < rightMin) {
					current->right = right;
					right->parent = current;
					currentCount += rightCount;
					currentMax = rightMax;
				} else {
					// When node->content >= rightMin, it is possible part
					// of right tree and node can form a valid search tree.
				}

				if (leftLastCount >= rightLastCount) {
					last = leftLast;
					lastCount = leftLastCount;
					lastMin = leftLastMin;
					lastMax = leftLastMax;
				} else {
					last = rightLast;
					lastCount = rightLastCount;
					lastMin = rightLastMin;
					lastMax = rightLastMax;
				}

				if (currentCount >= lastCount) {
					last = current;
					lastCount = currentCount;
					lastMin = currentMin;
					lastMax = currentMax;
				}

#ifdef DEBUG
				cout << node->content << " current" << endl;
				current->Print();
				cout << node->content << " last" << endl;
				last->Print();
#endif

				if (left != current->left && left != last) {
					deleteTree(left);
				}

				if (right != current->right && right != last) {
					deleteTree(right);
				}

				if (leftLast != last && leftLast != left) {
					deleteTree(leftLast);
				}

				if (rightLast != last && rightLast != right) {
					deleteTree(rightLast);
				}
			};

			BinaryNodeWithParent<T> * node;
			int count;
			T min;
			T max;
			BinaryNodeWithParent<T> * last;
			int lastCount;
			T lastMin;
			T lastMax;
			search(binaryTree->Root(), node, count, min, max, last, lastCount, lastMin, lastMax);

			if (node != last) {
				if (count >= lastCount) {
					this->root = node;
					deleteTree(last);
				} else {
					this->root = last;
					deleteTree(node);
				}
			} else {
				this->root = node;
			}
		}

		// http://leetcode.com/2010/11/largest-binary-search-tree-bst-in.html
		void MaxSubTreeFromBinaryTree(BinaryTree<T, BinaryNode> * binaryTree)
		{
			function<void(BinaryNodeWithParent<T> * &)> deleteTree = [&](BinaryNodeWithParent<T> * & node) {
				node->DeleteTree();
				delete node;
			};

			function<void(BinaryNode<T> * &, BinaryNodeWithParent<T> * &, int &, T &, T &)>
				search = [&](
				BinaryNode<T> * & node,              // current node from input binary tree
				BinaryNodeWithParent<T> * & current, // root of current search tree
				int & currentCount,                  // node count of current search tree
				T & currentMin,                      // min of current search tree
				T & currentMax                       // max of current search tree
				)
			{
				if (node == nullptr) {
					current = nullptr;
					currentCount = 0;
					return;
				}

				BinaryNode<T> * leftChild = node->left;
				BinaryNodeWithParent<T> * left;
				int leftCount;
				T leftMin;
				T leftMax;
				search(leftChild, left, leftCount, leftMin, leftMax);

				BinaryNode<T> * rightChild = node->right;
				BinaryNodeWithParent<T> * right;
				int rightCount;
				T rightMin;
				T rightMax;
				search(rightChild, right, rightCount, rightMin, rightMax);

				if ((left == nullptr || (leftChild == node->left && leftMax <= node->content))
					&& (right == nullptr || (rightChild == node->right && rightMin > node->content))) {
					current = new BinaryNodeWithParent<T>(node->content);
					current->left = left;
					if (left != nullptr) left->parent = current;
					current->right = right;
					if (right != nullptr) right->parent = current;
					currentCount = 1 + leftCount + rightCount;
					currentMin = left == nullptr ? node->content : leftMin;
					currentMax = right == nullptr ? node->content : rightMax;
				} else {
					if (leftCount >= rightCount) {
						node = leftChild;
						current = left;
						currentCount = leftCount;
						currentMin = leftMin;
						currentMax = leftMax;
						if (right != nullptr) deleteTree(right);
					} else {
						node = rightChild;
						current = right;
						currentCount = rightCount;
						currentMin = rightMin;
						currentMax = rightMax;
						if (left != nullptr) deleteTree(left);
					}
				}
			};

			BinaryNode<T> * r = binaryTree->Root();
			BinaryNodeWithParent<T> * node;
			int count;
			T min;
			T max;
			search(r, node, count, min, max);

			this->root = node;
		}

		// http://leetcode.com/2010/11/largest-binary-search-tree-bst-in.html
		void MaxSubTreeFromBinaryTree2(BinaryTree<T, BinaryNode> * binaryTree)
		{
			function<void(BinaryNodeWithParent<T> * &)> deleteTree = [&](BinaryNodeWithParent<T> * & node) {
				node->DeleteTree();
				delete node;
			};

			// Record subtrees already verified to avoid re-verification
			map<BinaryNode<T> *, int> subtrees;

			function<bool(BinaryNode<T> *, T &, T &, int &)> isSearchTree = [&](BinaryNode<T> * node, T & min, T & max, int & count) -> bool {
				count = 0;
				if (node == nullptr) return true;
				min = node->content;
				max = node->content;
				if (subtrees.find(node) != subtrees.end()) {
					count = subtrees[node];
					return true;
				}

				T leftMin;
				T leftMax;
				int leftCount;
				bool leftTrue = isSearchTree(node->left, leftMin, leftMax, leftCount);

				T rightMin;
				T rightMax;
				int rightCount;
				bool rightTrue = isSearchTree(node->right, rightMin, rightMax, rightCount);

				if (!leftTrue
					|| !rightTrue
					|| (node->left != nullptr && leftMax > node->content)
					|| (node->right != nullptr && rightMin <= node->content)) {
					return false;
				}

				min = node->left == nullptr ? node->content : leftMin;
				max = node->right == nullptr ? node->content : rightMax;
				count += (1 + leftCount + rightCount);
				subtrees[node] = count;

				return true;
			};

			function<void(BinaryNode<T> *, BinaryNodeWithParent<T> * &, int &)>
				search = [&](
				BinaryNode<T> * node,                // current node from input binary tree
				BinaryNodeWithParent<T> * & current, // root of current search tree
				int & currentCount                   // node count of current search tree
				)
			{
				if (node == nullptr) {
					current = nullptr;
					currentCount = 0;
					return;
				}

				T min;
				T max;
				if (isSearchTree(node, min, max, currentCount)) {
					current = BinaryNodeWithParent<T>::Clone(node);
					return;
				}

				BinaryNodeWithParent<T> * left;
				int leftCount;
				search(node->left, left, leftCount);

				BinaryNodeWithParent<T> * right;
				int rightCount;
				search(node->right, right, rightCount);

				if (leftCount >= rightCount) {
					current = left;
					currentCount = leftCount;
					if (right != nullptr) deleteTree(right);
				} else {
					current = right;
					currentCount = rightCount;
					if (left != nullptr) deleteTree(left);
				}
			};

			BinaryNode<T> * r = binaryTree->Root();
			BinaryNodeWithParent<T> * node;
			int count;
			search(r, node, count);

			this->root = node;
		}

		void Serialize(ostream & output)
		{
			function<void(T)> serialize = [&](T v){
				output << v << ' ';
			};

			this->PreOrderWalk(serialize);
		}

		void Deserialize(istream & input)
		{
			T value;
			while (true) {
				input >> value;
				if (input.good() && !input.eof()) {
					this->Insert(value);
				} else {
					break;
				}
			}
		}
	};
}