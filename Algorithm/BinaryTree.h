#pragma once
#include <functional>
#include "BinaryIterator.h"
#include "PreOrderBinaryIterator.h"
#include "InOrderBinaryIterator.h"
#include "PostOrderBinaryIterator.h"
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

		virtual ~BinaryTree(void)
		{
			if (this->root != nullptr) {
				delete this->root;
				this->root = nullptr;
			}
		}

		virtual void Insert(T & content) {}

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
	};
}