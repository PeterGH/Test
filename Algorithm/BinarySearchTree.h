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
				if (newNode->Value() < current->Value()) current = (BinaryNodeWithParent<T> *)current->Left();
				else current = (BinaryNodeWithParent<T> *)current->Right();
			}

			newNode->Parent() = parent;

			if (parent == nullptr) {
				// This means node is NULL, i.e. it is an empty tree.
				// Return the new node as it is the first node of a tree.
				return newNode;
			} else if (newNode->Value() < parent->Value()) {
				parent->Left() = newNode;
			} else {
				parent->Right() = newNode;
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
			if (node == nullptr || node->Value() == content) return node;
			if (content < node->Value()) return SearchRecursively((BinaryNodeWithParent<T> *)node->Left(), content);
			else return SearchRecursively((BinaryNodeWithParent<T> *)node->Right(), content);
		}

		static BinaryNodeWithParent<T> * SearchIteratively(BinaryNodeWithParent<T> * node, const T & content)
		{
			if (node == nullptr || node->Value() == content) return node;
			while (node != nullptr && content != node->Value()) {
				if (content < node->Value())
					node = (BinaryNodeWithParent<T> *)node->Left();
				else
					node = (BinaryNodeWithParent<T> *)node->Right();
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
					*p = (*p)->Parent();
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
				l = l->Parent();
			}

			while (h != nullptr && l != nullptr) {
				if (h == l) return h;
				h = h->Parent();
				l = l->Parent();
			}

			return nullptr;
		}

		static BinaryNodeWithParent<T> * LowestCommonAncestor3(BinaryNodeWithParent<T> * node, const T & first, const T & second)
		{
			if (node == nullptr) return nullptr;

			while (node != nullptr) {
				if (node->Value() > std::max(first, second))
					node = (BinaryNodeWithParent<T> *)node->Left();
				else if (node->Value() < std::min(first, second))
					node = (BinaryNodeWithParent<T> *)node->Right();
				else
					break;
			}

			return node;
		}

		static BinaryNodeWithParent<T> * Min(BinaryNodeWithParent<T> * node)
		{
			if (node == nullptr) return node;
			while (node->Left() != nullptr) node = (BinaryNodeWithParent<T> *)node->Left();
			return node;
		}

		static BinaryNodeWithParent<T> * Max(BinaryNodeWithParent<T> * node)
		{
			if (node == nullptr) return node;
			while (node->Right() != nullptr) node = (BinaryNodeWithParent<T> *)node->Right();
			return node;
		}

		static BinaryNodeWithParent<T> * Successor(BinaryNodeWithParent<T> * node)
		{
			if (node == nullptr) return node;

			//  (A)
			//  / \
			// () (B)
			// The successor of A is the minimum node of subtree B
			if (node->Right() != nullptr) return Min((BinaryNodeWithParent<T> *)node->Right());

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
			BinaryNodeWithParent<T> * parent = node->Parent();
			while (parent != nullptr && node == parent->Right()) {
				node = parent;
				parent = parent->Parent();
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
			if (node->Left() != nullptr) return Max((BinaryNodeWithParent<T> *)node->Left());

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
			BinaryNodeWithParent<T> * parent = node->Parent();
			while (parent != nullptr && node == parent->Left()) {
				node = parent;
				parent = parent->Parent();
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

			if (dst->Parent() == nullptr) {
				// src becomes the new root
				if (src != nullptr) src->Parent() = nullptr;
				return dst;
			}

			if (dst == dst->Parent()->Left())
				dst->Parent()->Left() = src;
			else
				dst->Parent()->Right() = src;

			if (src != nullptr) src->Parent() = dst->Parent();

			return dst;
		}

		// Delete a node. If *node is the root then update it afte being deleted.
		static void Delete(BinaryNodeWithParent<T> ** node)
		{
			if (node == nullptr || *node == nullptr) return;

			if ((*node)->Left() == nullptr) {
				//   ()
				//    |
				//   (A)
				//   /  \
				// NULL (B)
				BinaryNodeWithParent<T> * r = (BinaryNodeWithParent<T> *)(*node)->Right();
				Transplant((*node), r);

				(*node)->Right() = nullptr;
				delete (*node);
				*node = nullptr;
				if (r != nullptr && r->Parent() == nullptr) {
					// r is the new root
					*node = r;
				}

				return;
			}

			if ((*node)->Right() == nullptr) {
				//   ()
				//    |
				//   (A)
				//   /  \
				// (B) NULL
				BinaryNodeWithParent<T> * l = (BinaryNodeWithParent<T> *)(*node)->Left();
				Transplant((*node), l);

				(*node)->Left() = nullptr;
				delete (*node);
				*node = nullptr;
				if (l != nullptr && l->Parent() == nullptr) {
					// l is the new root
					*node = l;
				}

				return;
			}

			BinaryNodeWithParent<T> * successor = Min((BinaryNodeWithParent<T> *)(*node)->Right());

			if (successor->Parent() != (*node)) {
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
				Transplant(successor, (BinaryNodeWithParent<T> *)successor->Right());
				//     ()
				//     |
				//    (A)
				//    / \
				//   () (D)
				//        \
				//         ()
				//        /
				//      (C)           (B)
				successor->Right() = (*node)->Right();
				((BinaryNodeWithParent<T> *)successor->Right())->Parent() = successor;
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
			successor->Left() = (*node)->Left();
			((BinaryNodeWithParent<T> *)successor->Left())->Parent() = successor;

			(*node)->Left() = nullptr;
			(*node)->Right() = nullptr;
			delete (*node);
			*node = nullptr;

			if (successor->Parent() == nullptr) {
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
				this->root->Parent() = nullptr;
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
			return node->Value();
		}

		virtual const T & LowestCommonAncestor2(const T & first, const T & second)
		{
			BinaryNodeWithParent<T> * firstNode = this->Search(first);
			BinaryNodeWithParent<T> * secondNode = this->Search(second);
			BinaryNodeWithParent<T> * node = LowestCommonAncestor2(firstNode, secondNode);
			if (node == nullptr) {
				throw new invalid_argument(String::Format("%d and %d have no common ancestor.", first, second));
			}
			return node->Value();
		}

		virtual const T & LowestCommonAncestor3(const T & first, const T & second)
		{
			BinaryNodeWithParent<T> * node = LowestCommonAncestor3(this->root, first, second);
			if (node == nullptr) {
				throw new invalid_argument(String::Format("%d and %d have no common ancestor.", first, second));
			}
			return node->Value();
		}

		T & Min(void)
		{
			if (this->root != nullptr) return Min(this->root)->Value();
			else throw runtime_error("Tree is empty");
		}

		T & Max(void)
		{
			if (this->root != nullptr) return Max(this->root)->Value();
			else throw runtime_error("Tree is empty");
		}

		T Successor(T content)
		{
			if (this->root != nullptr) {
				BinaryNodeWithParent<T> * p = SearchIteratively(this->root, content);
				if (p != nullptr && ((p = Successor(p)) != nullptr)) return p->Value();
			}

			throw runtime_error("No successor is found");
		}

		T Predecessor(T content)
		{
			if (this->root != nullptr) {
				BinaryNodeWithParent<T> * p = SearchIteratively(this->root, content);
				if (p != nullptr && ((p = Predecessor(p)) != nullptr)) return p->Value();
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
			T min = BinaryTree<T, BinaryNode>::Min(node)->Value();
			T max = BinaryTree<T, BinaryNode>::Max(node)->Value();
			function<bool(BinaryNode<T> *, T, T)> verify = [&](BinaryNode<T> * c, T l, T h) -> bool {
				if (c == nullptr) return true;
				if (c->Value() < l || c->Value() > h) return false;
				if (c->Left() != nullptr && c->Left()->Value() >= c->Value()) return false;
				if (c->Right() != nullptr && c->Right()->Value() < c->Value()) return false;
				return verify(c->Left(), l, c->Value()) && verify(c->Right(), c->Value(), h);
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
					if (p->Value() <= v) return p;
					if (p->Left() != nullptr) p = (BinaryNodeWithParent<T> *)p->Left();
					else p = (BinaryNodeWithParent<T> *)p->Right();
				}
				return p;
			};

			function<BinaryNodeWithParent<T> * (BinaryNodeWithParent<T> *, T)>
				firstNodeGreaterThan = [&](BinaryNodeWithParent<T> * n, T v) -> BinaryNodeWithParent<T> * {
				BinaryNodeWithParent<T> * p = n;
				while (p != nullptr) {
					if (p->Value() > v) return p;
					if (p->Right() != nullptr) p = (BinaryNodeWithParent<T> *)p->Right();
					else p = (BinaryNodeWithParent<T> *)p->Left();
				}
				return p;
			};

			function<void(BinaryNodeWithParent<T> * &, int &, BinaryNodeWithParent<T> *, int)>
				mergeLeft = [&](BinaryNodeWithParent<T> * & node, int & count, BinaryNodeWithParent<T> * left, int leftCount) {
				BinaryNodeWithParent<T> * clone = left->Clone();
				BinaryNodeWithParent<T> * invalid = firstNodeGreaterThan(clone, node->Value());
				int invalidSize = invalid == nullptr ? 0 : invalid->Size();
				node->Left() = clone;
				clone->Parent() = node;
				count += (leftCount - invalidSize);
				if (invalid != nullptr) {
					BinaryNodeWithParent<T> * p = invalid->Parent();
					p->Right() = nullptr;
					deleteTree(invalid);
				}
			};

			function<void(BinaryNodeWithParent<T> * &, int &, BinaryNodeWithParent<T> *, int)>
				mergeRight = [&](BinaryNodeWithParent<T> * & node, int & count, BinaryNodeWithParent<T> * right, int rightCount) {
				BinaryNodeWithParent<T> * clone = right->Clone();
				BinaryNodeWithParent<T> * invalid = firstNodeLessThanOrEqual(clone, node->Value());
				int invalidSize = invalid == nullptr ? 0 : invalid->Size();
				node->Right() = clone;
				clone->Parent() = node;
				count += (rightCount - invalidSize);
				if (invalid != nullptr) {
					BinaryNodeWithParent<T> * p = invalid->Parent();
					p->Left() = nullptr;
					deleteTree(invalid);
				}
			};

			function<void(BinaryNode<T> *, BinaryNodeWithParent<T> * &, int &, BinaryNodeWithParent<T> * &, int &)>
				search = [&](
				BinaryNode<T> * node,          // current node from input binary tree
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
				search(node->Left(), left, leftCount, leftLast, leftLastCount);

				BinaryNodeWithParent<T> * right;
				int rightCount;
				BinaryNodeWithParent<T> * rightLast;
				int rightLastCount;
				search(node->Right(), right, rightCount, rightLast, rightLastCount);

				current = new BinaryNodeWithParent<T>(node->Value());
				currentCount = 1;

				if (left != nullptr && left->Value() <= current->Value()) {
					mergeLeft(current, currentCount, left, leftCount);
				}

				if (right != nullptr && right->Value() > current->Value()) {
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
				cout << node->Value() << " current count " << currentCount << endl;
				current->Print();
				cout << node->Value() << " last count " << lastCount << endl;
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

			function<void(BinaryNode<T> *, T, T, BinaryNodeWithParent<T> * &, int &, BinaryNodeWithParent<T> * &, int &)>
				search = [&](
				BinaryNode<T> * node,          // current node from input binary tree
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

				if (min < node->Value() && node->Value() <= max) {
					BinaryNodeWithParent<T> * left;
					int leftCount;
					BinaryNodeWithParent<T> * leftLast;
					int leftLastCount;
					search(node->Left(), min, node->Value(), left, leftCount, leftLast, leftLastCount);

					BinaryNodeWithParent<T> * right;
					int rightCount;
					BinaryNodeWithParent<T> * rightLast;
					int rightLastCount;
					search(node->Right(), node->Value(), max, right, rightCount, rightLast, rightLastCount);

					current = new BinaryNodeWithParent<T>(node->Value());
					currentCount = 1;

					if (left != nullptr) {
						current->Left() = left;
						left->Parent() = current;
						currentCount += leftCount;
					}

					if (right != nullptr) {
						current->Right() = right;
						right->Parent() = current;
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

					if (left != current->Left() && left != last) {
						deleteTree(left);
					}

					if (right != current->Right() && right != last) {
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

			function<void(BinaryNode<T> *, BinaryNodeWithParent<T> * &, int &, T &, T &, BinaryNodeWithParent<T> * &, int &, T &, T &)>
				search = [&](
				BinaryNode<T> * node,          // current node from input binary tree
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
				search(node->Left(), left, leftCount, leftMin, leftMax, leftLast, leftLastCount, leftLastMin, leftLastMax);

				BinaryNodeWithParent<T> * right;
				int rightCount;
				T rightMin;
				T rightMax;
				BinaryNodeWithParent<T> * rightLast;
				int rightLastCount;
				T rightLastMin;
				T rightLastMax;
				search(node->Right(), right, rightCount, rightMin, rightMax, rightLast, rightLastCount, rightLastMin, rightLastMax);

				current = new BinaryNodeWithParent<T>(node->Value());
				currentCount = 1;
				currentMin = node->Value();
				currentMax = node->Value();

				if (left != nullptr && leftMax <= node->Value()) {
					current->Left() = left;
					left->Parent() = current;
					currentCount += leftCount;
					currentMin = leftMin;
				} else {
					// When leftMax > node->Value(), it is possible part
					// of left tree and node can form a valid search tree.
				}

				if (right != nullptr && node->Value() < rightMin) {
					current->Right() = right;
					right->Parent() = current;
					currentCount += rightCount;
					currentMax = rightMax;
				} else {
					// When node->Value() >= rightMin, it is possible part
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
				cout << node->Value() << " current" << endl;
				current->Print();
				cout << node->Value() << " last" << endl;
				last->Print();
#endif

				if (left != current->Left() && left != last) {
					deleteTree(left);
				}

				if (right != current->Right() && right != last) {
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

				BinaryNode<T> * leftChild = node->Left();
				BinaryNodeWithParent<T> * left;
				int leftCount;
				T leftMin;
				T leftMax;
				search(leftChild, left, leftCount, leftMin, leftMax);

				BinaryNode<T> * rightChild = node->Right();
				BinaryNodeWithParent<T> * right;
				int rightCount;
				T rightMin;
				T rightMax;
				search(rightChild, right, rightCount, rightMin, rightMax);

				if ((left == nullptr || (leftChild == node->Left() && leftMax <= node->Value()))
					&& (right == nullptr || (rightChild == node->Right() && rightMin > node->Value()))) {
					current = new BinaryNodeWithParent<T>(node->Value());
					current->Left() = left;
					if (left != nullptr) left->Parent() = current;
					current->Right() = right;
					if (right != nullptr) right->Parent() = current;
					currentCount = 1 + leftCount + rightCount;
					currentMin = left == nullptr ? node->Value() : leftMin;
					currentMax = right == nullptr ? node->Value() : rightMax;
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
				min = node->Value();
				max = node->Value();
				if (subtrees.find(node) != subtrees.end()) {
					count = subtrees[node];
					return true;
				}

				T leftMin;
				T leftMax;
				int leftCount;
				bool leftTrue = isSearchTree(node->Left(), leftMin, leftMax, leftCount);

				T rightMin;
				T rightMax;
				int rightCount;
				bool rightTrue = isSearchTree(node->Right(), rightMin, rightMax, rightCount);

				if (!leftTrue
					|| !rightTrue
					|| (node->Left() != nullptr && leftMax > node->Value())
					|| (node->Right() != nullptr && rightMin <= node->Value())) {
					return false;
				}

				min = node->Left() == nullptr ? node->Value() : leftMin;
				max = node->Right() == nullptr ? node->Value() : rightMax;
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
				search(node->Left(), left, leftCount);

				BinaryNodeWithParent<T> * right;
				int rightCount;
				search(node->Right(), right, rightCount);

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

		// http://leetcode.com/2010/09/saving-binary-search-tree-to-file.html
		// Complexity n*log(n)
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

		// http://leetcode.com/2010/09/saving-binary-search-tree-to-file.html
		// Linear time implemenation
		void Deserialize2(istream & input, T min, T max)
		{
			function<void(T, T, T &, BinaryNodeWithParent<T> * &)>
			deserialize = [&](T l, T h, T & value, BinaryNodeWithParent<T> * & node) {
				if (l < value && value <= h) {
					T v = value;
					node = new BinaryNodeWithParent<T>(v);
					input >> value;
					if (input.good() && !input.eof()) {
						deserialize(l, v, value, (BinaryNodeWithParent<T> * &)node->Left());
						deserialize(v, h, value, (BinaryNodeWithParent<T> * &)node->Right());
					}
				}
			};

			T value;
			input >> value;
			if (input.good() && !input.eof()) {
				deserialize(min, max, value, this->root);
			}
		}
	};
}