#pragma once
#include <functional>
#include <ppl.h>
#include "BinaryIterator.h"
#include "InOrderBinaryIterator.h"
#include "Node1.h"
#include "PostOrderBinaryIterator.h"
#include "PreOrderBinaryIterator.h"
#include "Random.h"
using namespace concurrency;
using namespace std;

namespace Test {

	template<class T, template<class T> class N> class BinaryTree {
	protected:
		N<T> * root;

		static N<T> * Search(N<T> * node, const T & content)
		{
			if (node == nullptr || node->content == content) return node;
			N<T> * left = Search((N<T> *)node->left, content);
			if (left != nullptr) return left;
			else return Search((N<T> *)node->right, content);
		}

		static N<T> * LowestCommonAncestor(N<T> * node, N<T> * first, N<T> * second)
		{
			if (node == nullptr || first == nullptr || second == nullptr) return nullptr;
			if (node == first || node == second) return node;

			function<int(N<T> *, N<T> *, N<T> *)> hits = [&](N<T> * n, N<T> * f, N<T> * s) -> int {
				if (n == nullptr) return 0;
				int h = hits((N<T> *)n->left, f, s) + hits((N<T> *)n->right, f, s);
				if (n == f || n == s) return 1 + h;
				else return h;
			};

			int h = hits((N<T> *)node->left, first, second);
			if (h == 1) return node;
			else if (h == 2) return LowestCommonAncestor((N<T> *)node->left, first, second);
			else return LowestCommonAncestor((N<T> *)node->right, first, second);
		}

		static N<T> * LowestCommonAncestor2(N<T> * node, N<T> * first, N<T> * second)
		{
			if (node == nullptr || first == nullptr || second == nullptr) return nullptr;
			if (node == first || node == second) return node;
			N<T> * left = LowestCommonAncestor2((N<T> *)node->left, first, second);
			N<T> * right = LowestCommonAncestor2((N<T> *)node->right, first, second);
			if (left != nullptr && right != nullptr) return node;
			if (left != nullptr) return left;
			else return right;
		}

		static N<T> * BuildTreePreOrderInOrderInternal(T * preOrder, int preLength, T * inOrder, int inLength)
		{
			if (inOrder == nullptr || preOrder == nullptr || inLength <= 0 || preLength <= 0 || inLength != preLength) return nullptr;

			T value = preOrder[0];

			int index = -1;
			for (int i = 0; i < inLength; i++) {
				if (inOrder[i] == value) {
					index = i;
					break;
				}
			}

			if (index == -1) return nullptr;

			N<T> * node = new N<T>(value);

			node->left = BuildTreePreOrderInOrderInternal(preOrder+1, index, inOrder, index);
			node->right = BuildTreePreOrderInOrderInternal(preOrder+index+1, preLength-1-index, inOrder+index+1, inLength-1-index);

			return node;
		}

		static N<T> * BuildTreeInOrderPostOrderInternal(T * inOrder, int inLength, T * postOrder, int postLength)
		{
			if (inOrder == nullptr || postOrder == nullptr || inLength <= 0 || postLength <= 0 || inLength != postLength) return nullptr;

			T value = postOrder[postLength-1];

			int index = -1;
			for (int i = 0; i < inLength; i++) {
				if (inOrder[i] == value) {
					index = i;
					break;
				}
			}

			if (index == -1) return nullptr;

			N<T> * node = new N<T>(value);

			node->left = BuildTreeInOrderPostOrderInternal(inOrder, index, postOrder, index);
			node->right = BuildTreeInOrderPostOrderInternal(inOrder+index+1, inLength-1-index, postOrder+index, postLength-1-index);

			return node;
		}

		static int Compare(N<T> * first, N<T> * second)
		{
			if (first == nullptr && second == nullptr) return 0;
			if (first == nullptr && second != nullptr) return -1;
			if (first != nullptr && second == nullptr) return 1;
			if (first->content < second->content) return -1;
			if (first->content > second->content) return 1;
			int v = Compare((N<T> *)first->left, (N<T> *)second->left);
			if (v == 0) return Compare((N<T> *)first->right, (N<T> *)second->right);
			return v;
		}

	public:
		BinaryTree(void) : root(nullptr) {}

		void DeleteTree(void)
		{
			if (this->root != nullptr) {
				this->root->DeleteTree();
				delete this->root;
				this->root = nullptr;
			}
		}

		virtual ~BinaryTree(void)
		{
			this->DeleteTree();
		}

		N<T> * Root(void) { return this->root; }

		N<T> * Root(N<T> * other)
		{
			N<T> * p = this->root;
			this->root = other;
			return p;
		}

		// Insert a new node below a random leaf node
		virtual void Insert(T & content)
		{
			if (this->root == nullptr) {
				this->root = new N<T>(content);
				return;
			}

			N<T> * p = this->root;
			unsigned int r = 0;
			while (p->left != nullptr && p->right != nullptr) {
				if (r == 0) {
					r = Random::Next();
				}
				if ((r & 0x1) == 0) {
					p = (N<T> *)p->left;
				} else {
					p = (N<T> *)p->right;
				}
				r = r >> 1;
			}

			if (p->left == nullptr) {
				p->left = new N<T>(content);
			} else {
				p->right = new N<T>(content);
			}
		}

		virtual N<T> * Search(const T & content)
		{
			return Search(this->root, content);
		}

		virtual const T & LowestCommonAncestor(const T & first, const T & second)
		{
			N<T> * firstNode = this->Search(first);
			N<T> * secondNode = this->Search(second);
			N<T> * node = LowestCommonAncestor(this->root, firstNode, secondNode);
			if (node == nullptr) {
				throw new invalid_argument(String::Format("%d and %d have no common ancestor.", first, second));
			}
			return node->content;
		}

		virtual const T & LowestCommonAncestor2(const T & first, const T & second)
		{
			N<T> * firstNode = this->Search(first);
			N<T> * secondNode = this->Search(second);
			N<T> * node = LowestCommonAncestor2(this->root, firstNode, secondNode);
			if (node == nullptr) {
				throw new invalid_argument(String::Format("%d and %d have no common ancestor.", first, second));
			}
			return node->content;
		}

		static N<T> * Min(N<T> * node)
		{
			if (node == nullptr) return node;
			N<T> * left = Min((N<T> *)node->left);
			N<T> * right = Min((N<T> *)node->right);
			N<T> * min = node;
			if (left != nullptr && left->content < min->content) {
				min = left;
			}
			if (right != nullptr && right->content < min->content) {
				min = right;
			}
			return min;
		}

		static N<T> * Max(N<T> * node)
		{
			if (node == nullptr) return node;
			N<T> * left = Max((N<T> *)node->left);
			N<T> * right = Max((N<T> *)node->right);
			N<T> * max = node;
			if (left != nullptr && left->content > max->content) {
				max = left;
			}
			if (right != nullptr && right->content > max->content) {
				max = right;
			}
			return max;
		}

		virtual T & Min(void)
		{
			if (this->root != nullptr) return Min(this->root)->content;
			else throw runtime_error("Tree is empty");
		}

		virtual T & Max(void)
		{
			if (this->root != nullptr) return Max(this->root)->content;
			else throw runtime_error("Tree is empty");
		}

		void PreOrderWalk(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->PreOrderWalk(f);
			}
		}

		void PreOrderWalkWithStack(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->PreOrderWalkWithStack(f);
			}
		}

		void PreOrderWalkWithStack2(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->PreOrderWalkWithStack2(f);
			}
		}

		void InOrderWalk(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->InOrderWalk(f);
			}
		}

		void InOrderWalkWithStack(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->InOrderWalkWithStack(f);
			}
		}

		void InOrderWalkWithStack2(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->InOrderWalkWithStack2(f);
			}
		}

		void PostOrderWalk(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->PostOrderWalk(f);
			}
		}

		void PostOrderWalkWithStack(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->PostOrderWalkWithStack(f);
			}
		}

		void PostOrderWalkWithStack2(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->PostOrderWalkWithStack2(f);
			}
		}

		int Height(void)
		{
			if (this->root == nullptr) return 0;
			return this->root->Height();
		}

		void Print(void)
		{
			if (this->root != nullptr) this->root->Print();
		}

		PreOrderBinaryIterator<T, N> PreOrderBegin() const { return PreOrderBinaryIterator<T, N>(this->root); }
		PreOrderBinaryIterator<T, N> PreOrderEnd() const { return PreOrderBinaryIterator<T, N>(); }

		InOrderBinaryIterator<T, N> InOrderBegin() const { return InOrderBinaryIterator<T, N>(this->root); }
		InOrderBinaryIterator<T, N> InOrderEnd() const { return InOrderBinaryIterator<T, N>(); }

		PostOrderBinaryIterator<T, N> PostOrderBegin() const { return PostOrderBinaryIterator<T, N>(this->root); }
		PostOrderBinaryIterator<T, N> PostOrderEnd() const { return PostOrderBinaryIterator<T, N>(); }

		void BuildTreePreOrderInOrder(T * preOrder, int preLength, T * inOrder, int inLength)
		{
			if (this->root != nullptr) {
				delete this->root;
				this->root = nullptr;
			}

			this->root = BuildTreePreOrderInOrderInternal(preOrder, preLength, inOrder, inLength);
		}

		void BuildTreeInOrderPostOrder(T * inOrder, int inLength, T * postOrder, int postLength)
		{
			if (this->root != nullptr) {
				delete this->root;
				this->root = nullptr;
			}

			this->root = BuildTreeInOrderPostOrderInternal(inOrder, inLength, postOrder, postLength);
		}

		bool operator==(const BinaryTree & other) const { return Compare(this->root, other.root) == 0; }

		// http://leetcode.com/2010/11/convert-binary-search-tree-bst-to.html
		// Flatten a binary tree into a doubly-link-list.
		// Return head and tail, head->left = nullptr, tail->right = nullptr,
		// i.e., the list is not circular.
		N<T> * ToDoubleLinkList(N<T> * & head, N<T> * & tail)
		{
			function<void(N<T> *, N<T> * &, N<T> * &)> convert = [&](N<T> * node, N<T> * & min, N<T> * & max) {
				min = nullptr;
				max = nullptr;
				if (node == nullptr) return;

				N<T> * leftMin = nullptr;
				N<T> * leftMax = nullptr;
				convert((N<T> *)node->left, leftMin, leftMax);

				N<T> * rightMin = nullptr;
				N<T> * rightMax = nullptr;
				convert((N<T> *)node->right, rightMin, rightMax);

				if (leftMax == nullptr) {
					leftMin = node;
					leftMax = node;
				} else {
					leftMax->right = node;
					node->left = leftMax;
				}

				if (rightMin == nullptr) {
					rightMin = node;
					rightMax = node;
				} else {
					rightMin->left = node;
					node->right = rightMin;
				}

				min = leftMin;
				max = rightMax;
			};

			head = nullptr;
			tail = nullptr;
			convert(this->root, head, tail);

			this->root = nullptr;

			return head;
		}

		void FromSingleLinkList(Node1<T> * list)
		{
			if (list == nullptr) return;

			function<N<T> * (Node1<T> *)> convert = [&](Node1<T> * head) -> N<T> * {
				if (head == nullptr) return nullptr;

				if (head->Next() == nullptr) {
					N<T> * tree = new N<T>(head->Value());
					delete head;
					return tree;
				}

				Node1<T> * first = head;
				Node1<T> * second = head->Next();
				while (second->Next() != nullptr && second->Next()->Next() != nullptr) {
					first = first->Next();
					second = second->Next();
					second = second->Next();
				}

				Node1<T> * node = first->Next();
				first->Next() = nullptr;
				first = node->Next();
				node->Next() = nullptr;

				N<T> * tree = new N<T>(node->Value());

				parallel_invoke(
					[&convert, &tree, head] { tree->left = convert(head); },
					[&convert, &tree, first] { tree->right = convert(first); });

				delete node;

				return tree;
			};

			this->root = convert(list);
		}

		void FromSingleLinkList2(Node1<T> * list)
		{
			if (list == nullptr) return;

			function<N<T> * (Node1<T> * &, int, int)> convert = [&](Node1<T> * & head, int begin, int end) -> N<T> * {
				if (head == nullptr || begin > end) return nullptr;

				// Choose the median one if there are odd numbers in [begin, end]
				// Choose the upper median if there are even numbers in [begin, end]
				int middle = begin + ((1 + end - begin) >> 1);

				N<T> * left = convert(head, begin, middle - 1);
				N<T> * node = new N<T>(head->Value());
				node->left = left;

				Node1<T> * p = head;
				head = head->Next();
				delete p;

				node->right = convert(head, middle + 1, end);

				return node;
			};

			Node1<T> * p = list;
			int i = 0;
			while (p != nullptr) {
				p = p->Next();
				i++;
			}

			this->root = convert(list, 0, i-1);
		}

		// http://leetcode.com/2010/10/print-edge-nodes-boundary-of-binary.html
		// The boundary values include left-most nodes, leaf nodes and right-most nodes.
		// A left-most node may be the right child of its parent if its parent is left-most and has no left child.
		// Same goes to the right-most nodes.
		void GetBoundaryValues(vector<T> & values)
		{
			if (this->root == nullptr) return;

			values.push_back(this->root->content);

			function<void(N<T> *, bool)> searchLeft = [&](N<T> * node, bool include) {
				if (node == nullptr) return;

				if (include
					|| node->left == nullptr && node->right == nullptr) {
					values.push_back(node->content);
				}

				if (node->left != nullptr) {
					searchLeft(node->left, include);
				}

				if (node->right != nullptr) {
					// include the right child only if
					// its parent is included and has no left child
					searchLeft(node->right, include && node->left == nullptr);
				}
			};

			function<void(N<T>*, bool)> searchRight = [&](N<T> * node, bool include) {
				if (node == nullptr) return;

				if (node->left != nullptr) {
					// include the left child only if
					// its parent is included and has no right child
					searchRight(node->left, include && node->right == nullptr);
				}

				if (node->right != nullptr) {
					searchRight(node->right, include);
				}

				if (include
					|| node->left == nullptr && node->right == nullptr) {
					values.push_back(node->content);
				}
			};

			searchLeft(this->root->left, true);
			searchRight(this->root->right, true);
		}
	};
}