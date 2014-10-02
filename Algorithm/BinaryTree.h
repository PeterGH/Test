#pragma once
#include <functional>
#include <ppl.h>
#include "BinaryIterator.h"
#include "InOrderBinaryIterator.h"
#include "SingleNode.h"
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
			if (node == nullptr || node->Value() == content) return node;
			N<T> * left = Search((N<T> *)node->Left(), content);
			if (left != nullptr) return left;
			else return Search((N<T> *)node->Right(), content);
		}

		static N<T> * LowestCommonAncestor(N<T> * node, N<T> * first, N<T> * second)
		{
			if (node == nullptr || first == nullptr || second == nullptr) return nullptr;
			if (node == first || node == second) return node;

			function<int(N<T> *, N<T> *, N<T> *)> hits = [&](N<T> * n, N<T> * f, N<T> * s) -> int {
				if (n == nullptr) return 0;
				int h = hits((N<T> *)n->Left(), f, s) + hits((N<T> *)n->Right(), f, s);
				if (n == f || n == s) return 1 + h;
				else return h;
			};

			int h = hits((N<T> *)node->Left(), first, second);
			if (h == 1) return node;
			else if (h == 2) return LowestCommonAncestor((N<T> *)node->Left(), first, second);
			else return LowestCommonAncestor((N<T> *)node->Right(), first, second);
		}

		static N<T> * LowestCommonAncestor2(N<T> * node, N<T> * first, N<T> * second)
		{
			if (node == nullptr || first == nullptr || second == nullptr) return nullptr;
			if (node == first || node == second) return node;
			N<T> * left = LowestCommonAncestor2((N<T> *)node->Left(), first, second);
			N<T> * right = LowestCommonAncestor2((N<T> *)node->Right(), first, second);
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

			node->Left() = BuildTreePreOrderInOrderInternal(preOrder+1, index, inOrder, index);
			node->Right() = BuildTreePreOrderInOrderInternal(preOrder+index+1, preLength-1-index, inOrder+index+1, inLength-1-index);

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

			node->Left() = BuildTreeInOrderPostOrderInternal(inOrder, index, postOrder, index);
			node->Right() = BuildTreeInOrderPostOrderInternal(inOrder+index+1, inLength-1-index, postOrder+index, postLength-1-index);

			return node;
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
			while (p->Left() != nullptr && p->Right() != nullptr) {
				if (r == 0) {
					r = Random::Next();
				}
				if ((r & 0x1) == 0) {
					p = (N<T> *)p->Left();
				} else {
					p = (N<T> *)p->Right();
				}
				r = r >> 1;
			}

			if (p->Left() == nullptr) {
				p->Left() = new N<T>(content);
			} else {
				p->Right() = new N<T>(content);
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
			return node->Value();
		}

		virtual const T & LowestCommonAncestor2(const T & first, const T & second)
		{
			N<T> * firstNode = this->Search(first);
			N<T> * secondNode = this->Search(second);
			N<T> * node = LowestCommonAncestor2(this->root, firstNode, secondNode);
			if (node == nullptr) {
				throw new invalid_argument(String::Format("%d and %d have no common ancestor.", first, second));
			}
			return node->Value();
		}

		static N<T> * Min(N<T> * node)
		{
			if (node == nullptr) return node;
			N<T> * left = Min((N<T> *)node->Left());
			N<T> * right = Min((N<T> *)node->Right());
			N<T> * min = node;
			if (left != nullptr && left->Value() < min->Value()) {
				min = left;
			}
			if (right != nullptr && right->Value() < min->Value()) {
				min = right;
			}
			return min;
		}

		static N<T> * Max(N<T> * node)
		{
			if (node == nullptr) return node;
			N<T> * left = Max((N<T> *)node->Left());
			N<T> * right = Max((N<T> *)node->Right());
			N<T> * max = node;
			if (left != nullptr && left->Value() > max->Value()) {
				max = left;
			}
			if (right != nullptr && right->Value() > max->Value()) {
				max = right;
			}
			return max;
		}

		virtual T & Min(void)
		{
			if (this->root != nullptr) return Min(this->root)->Value();
			else throw runtime_error("Tree is empty");
		}

		virtual T & Max(void)
		{
			if (this->root != nullptr) return Max(this->root)->Value();
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

		void PreOrderWalkWithStack3(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->PreOrderWalkWithStack3(f);
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

		void LevelOrderWalk(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->LevelOrderWalk(f);
			}
		}

		void LevelOrderWalk2(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->LevelOrderWalk2(f);
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

		void Print2(void)
		{
			if (this->root != nullptr) this->root->Print2();
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
				this->root->DeleteTree();
				delete this->root;
				this->root = nullptr;
			}

			this->root = BuildTreePreOrderInOrderInternal(preOrder, preLength, inOrder, inLength);
		}

		void BuildTreePreOrderInOrder2(T * preOrder, int preLength, T * inOrder, int inLength)
		{
			if (this->root != nullptr) {
				this->root->DeleteTree();
				delete this->root;
				this->root = nullptr;
			}

			if (preOrder == nullptr || preLength <= 0 || inOrder == nullptr || inLength <= 0 || preLength != inLength) return;

			stack<N<T> *> path;

			int i = 0;
			int j = 0;
			int f = 0;

			this->root = new N<T>(preOrder[i]);
			path.push(this->root);
			N<T> * t = this->root;
			i++;

			while (i < preLength) {
				if (!path.empty() && path.top()->Value() == inOrder[j]) {
					t = path.top();
					path.pop();
					f = 1;
					j++;
				} else {
					if (f == 0) {
						t->Left() = new N<T>(preOrder[i]);
						t = (N<T>*)t->Left();
					} else {
						f = 0;
						t->Right() = new N<T>(preOrder[i]);
						t = (N<T>*)t->Right();
					}
					path.push(t);
					i++;
				}
			}
		}

		void BuildTreeInOrderPostOrder(T * inOrder, int inLength, T * postOrder, int postLength)
		{
			if (this->root != nullptr) {
				this->root->DeleteTree();
				delete this->root;
				this->root = nullptr;
			}

			this->root = BuildTreeInOrderPostOrderInternal(inOrder, inLength, postOrder, postLength);
		}

		void BuildTreeInOrderPostOrder2(T * inOrder, int inLength, T * postOrder, int postLength)
		{
			if (this->root != nullptr) {
				this->root->DeleteTree();
				delete this->root;
				this->root = nullptr;
			}

			if (inOrder == nullptr || inLength <= 0 || postOrder == nullptr || postLength <= 0 || inLength != postLength) return;

			stack<N<T> *> path;

			int i = postLength - 1;
			int j = inLength - 1;
			int f = 0;

			this->root = new N<T>(postOrder[i]);
			path.push(this->root);
			N<T> * t = this->root;
			i--;

			while (i >= 0) {
				if (!path.empty() && path.top()->Value() == inOrder[j]) {
					t = path.top();
					path.pop();
					f = 1;
					j--;
				} else {
					if (f == 0) {
						t->Right() = new N<T>(postOrder[i]);
						t = (N<T>*)t->Right();
					} else {
						f = 0;
						t->Left() = new N<T>(postOrder[i]);
						t = (N<T>*)t->Left();
					}
					path.push(t);
					i--;
				}
			}
		}

		static int Compare(N<T> * first, N<T> * second)
		{
			if (first == nullptr && second == nullptr) return 0;
			if (first == nullptr && second != nullptr) return -1;
			if (first != nullptr && second == nullptr) return 1;
			if (first->Value() < second->Value()) return -1;
			if (first->Value() > second->Value()) return 1;
			int v = Compare((N<T> *)first->Left(), (N<T> *)second->Left());
			if (v == 0) return Compare((N<T> *)first->Right(), (N<T> *)second->Right());
			return v;
		}

		static int Compare2(N<T> * first, N<T> * second)
		{
			if (first == nullptr && second == nullptr) return 0;
			if (first == nullptr && second != nullptr) return -1;
			if (first != nullptr && second == nullptr) return 1;
			if (first->Value() < second->Value()) return -1;
			if (first->Value() > second->Value()) return 1;

			deque<N<T> *> q;
			q.push_front(first);
			q.push_back(second);

			while (!q.empty()) {
				first = q.front();
				q.pop_front();
				second = q.back();
				q.pop_back();

				if (first->Right() == nullptr && second->Right() != nullptr) return -1;
				if (first->Right() != nullptr && second->Right() == nullptr) return 1;
				if (first->Right() != nullptr && second->Right() != nullptr) {
					if (first->Right()->Value() < second->Right()->Value()) return -1;
					if (first->Right()->Value() > second->Right()->Value()) return 1;
					q.push_front(first->Right());
					q.push_back(second->Right());
				}

				if (first->Left() == nullptr && second->Left() != nullptr) return -1;
				if (first->Left() != nullptr && second->Left() == nullptr) return 1;
				if (first->Left() != nullptr && second->Left() != nullptr) {
					if (first->Left()->Value() < second->Left()->Value()) return -1;
					if (first->Left()->Value() > second->Left()->Value()) return 1;
					q.push_front(first->Left());
					q.push_back(second->Left());
				}
			}
			return 0;
		}

		bool operator==(const BinaryTree & other) const { return Compare(this->root, other.root) == 0; }

		// http://leetcode.com/2010/11/convert-binary-search-tree-bst-to.html
		// Flatten a binary tree into a doubly-link-list.
		// Return head and tail, head->Left() = nullptr, tail->Right() = nullptr,
		// i.e., the list is not circular.
		N<T> * ToDoubleLinkList(N<T> * & head, N<T> * & tail)
		{
			function<void(N<T> *, N<T> * &, N<T> * &)> convert = [&](N<T> * node, N<T> * & min, N<T> * & max) {
				min = nullptr;
				max = nullptr;
				if (node == nullptr) return;

				N<T> * leftMin = nullptr;
				N<T> * leftMax = nullptr;
				convert((N<T> *)node->Left(), leftMin, leftMax);

				N<T> * rightMin = nullptr;
				N<T> * rightMax = nullptr;
				convert((N<T> *)node->Right(), rightMin, rightMax);

				if (leftMax == nullptr) {
					leftMin = node;
					leftMax = node;
				} else {
					leftMax->Right() = node;
					node->Left() = leftMax;
				}

				if (rightMin == nullptr) {
					rightMin = node;
					rightMax = node;
				} else {
					rightMin->Left() = node;
					node->Right() = rightMin;
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

		void FromSingleLinkList(SingleNode<T> * list)
		{
			if (list == nullptr) return;

			function<N<T> * (SingleNode<T> *)> convert = [&](SingleNode<T> * head) -> N<T> * {
				if (head == nullptr) return nullptr;

				if (head->Next() == nullptr) {
					N<T> * tree = new N<T>(head->Value());
					delete head;
					return tree;
				}

				SingleNode<T> * first = head;
				SingleNode<T> * second = head->Next();
				while (second->Next() != nullptr && second->Next()->Next() != nullptr) {
					first = first->Next();
					second = second->Next();
					second = second->Next();
				}

				SingleNode<T> * node = first->Next();
				first->Next() = nullptr;
				first = node->Next();
				node->Next() = nullptr;

				N<T> * tree = new N<T>(node->Value());

				parallel_invoke(
					[&convert, &tree, head] { tree->Left() = convert(head); },
					[&convert, &tree, first] { tree->Right() = convert(first); });

				delete node;

				return tree;
			};

			this->root = convert(list);
		}

		void FromSingleLinkList2(SingleNode<T> * list)
		{
			if (list == nullptr) return;

			function<N<T> * (SingleNode<T> * &, int, int)> convert = [&](SingleNode<T> * & head, int begin, int end) -> N<T> * {
				if (head == nullptr || begin > end) return nullptr;

				// Choose the median one if there are odd numbers in [begin, end]
				// Choose the upper median if there are even numbers in [begin, end]
				int middle = begin + ((1 + end - begin) >> 1);

				N<T> * left = convert(head, begin, middle - 1);
				N<T> * node = new N<T>(head->Value());
				node->Left() = left;

				SingleNode<T> * p = head;
				head = head->Next();
				delete p;

				node->Right() = convert(head, middle + 1, end);

				return node;
			};

			SingleNode<T> * p = list;
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

			values.push_back(this->root->Value());

			function<void(N<T> *, bool)> searchLeft = [&](N<T> * node, bool include) {
				if (node == nullptr) return;

				if (include
					|| node->Left() == nullptr && node->Right() == nullptr) {
					values.push_back(node->Value());
				}

				if (node->Left() != nullptr) {
					searchLeft(node->Left(), include);
				}

				if (node->Right() != nullptr) {
					// include the right child only if
					// its parent is included and has no left child
					searchLeft(node->Right(), include && node->Left() == nullptr);
				}
			};

			function<void(N<T>*, bool)> searchRight = [&](N<T> * node, bool include) {
				if (node == nullptr) return;

				if (node->Left() != nullptr) {
					// include the left child only if
					// its parent is included and has no right child
					searchRight(node->Left(), include && node->Right() == nullptr);
				}

				if (node->Right() != nullptr) {
					searchRight(node->Right(), include);
				}

				if (include
					|| node->Left() == nullptr && node->Right() == nullptr) {
					values.push_back(node->Value());
				}
			};

			searchLeft(this->root->Left(), true);
			searchRight(this->root->Right(), true);
		}

		virtual void Serialize(ostream & output)
		{
			function<void(N<T> *)> serialize = [&](N<T> * node){
				if (node == nullptr) {
					output << '#';
				} else {
					output << node->Value() << ' ';
					serialize((N<T> *)node->Left());
					serialize((N<T> *)node->Right());
				}
			};

			serialize(this->root);
		}

		virtual void Deserialize(istream & input)
		{
			function<void(N<T> * &)> deserialize = [&](N<T> * & node) {
				char c = input.peek();
				if (c == ' ') {
					// Two cases: ' '#, or ' 'number
					// Skip ' ' using seekg. Using input >> c does not work
					// because the >> operator actually skips ' ' and reads
					// next charactor, which is either '#' or a digit.
					input.seekg(1, ios_base::cur);
					c = input.peek();
				}

				if (c == '#') {
					input >> c;
					return;
				}

				T value;
				// The istream >> operator reads a value and leaves
				// the next ' ' character in the stream.
				input >> value;
				node = new N<T>(value);
				deserialize((N<T> * &)node->Left());
				deserialize((N<T> * &)node->Right());
			};

			deserialize(this->root);
		}
	};
}