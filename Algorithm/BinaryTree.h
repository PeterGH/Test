#pragma once

#include <functional>
#include <stack>
#include <vector>
#include "BitSet.h"

using namespace std;

namespace Test {

	// Implement a complete unordered binary tree.
	// Every level except the last one is fully filled.
	template<class T> class BinaryTree {
	private:
		// Total number of nodes
		int count;

	protected:
		class Node {
			template<class T> friend class BinaryTree;
			template<class T> friend class BinarySearchTree;
		private:
			T content;
			Node * parent;
			Node * left;
			Node * right;
		public:
			Node(const T & c) : content(c), parent(nullptr), left(nullptr), right(nullptr) {}

			// Delete the node itself
			// Not delete its children
			~Node(void)
			{
				auto f = [](Node * p) { if (p != nullptr) { p = nullptr; } };
				f(this->left);
				f(this->right);
				f(this->parent);
			}

			T & Content() { return this->content; }

			static void PreOrderWalk(Node * node, function<void(Node *)> f)
			{
				if (node == nullptr || f == nullptr) return;
				f(node);
				PreOrderWalk(node->left, f);
				PreOrderWalk(node->right, f);
			}

			// Recursive
			void PreOrderWalk(function<void(Node *)> f) { PreOrderWalk(this, f); }

			// Non-recursive with stack
			static void PreOrderWalk2(Node * node, function<void(Node *)> f)
			{
				if (node == nullptr || f == nullptr) return;
				stack<Node *> path;
				while (!path.empty() || node != nullptr) {
					if (node != nullptr) {
						f(node);
						path.push(node);
						node = node->left;
					} else {
						node = path.top()->right;
						path.pop();
					}
				}
			}

			// Non-recursive without stack
			static void PreOrderWalk3(Node * node, function<void(Node *)> f)
			{
				if (node == nullptr || f == nullptr) return;
				Node * prev = node;
				while (node != nullptr) {
					if (prev == node->right) {
						prev = node;
						node = node->parent;
					} else if (node->left != nullptr && prev != node->left) {
						f(node);
						prev = node;
						node = node->left;
					} else {
						if (node->left == nullptr) {
							f(node);
						}

						prev = node;
						if (node->right != nullptr) {
							node = node->right;
						} else {
							node = node->parent;
						}
					}
				}
			}

			// Recursive
			static void InOrderWalk(Node * node, function<void(Node *)> f)
			{
				if (node == nullptr || f == nullptr) return;
				InOrderWalk(node->left, f);
				f(node);
				InOrderWalk(node->right, f);
			}

			void InOrderWalk(function<void(Node *)> f) { InOrderWalk(this, f); }

			// Non-recursive with stack
			static void InOrderWalk2(Node * node, function<void(Node *)> f)
			{
				if (node == nullptr || f == nullptr) return;
				stack<Node *> path;
				while (!path.empty() || node != nullptr) {
					if (node != nullptr) {
						path.push(node);
						node = node->left;
					} else {
						node = path.top();
						path.pop();
						f(node);
						node = node->right;
					}
				}
			}

			// Non-recursive without stack
			static void InOrderWalk3(Node * node, function<void(Node *)> f)
			{
				if (node == nullptr || f == nullptr) return;
				Node * prev = node;
				while (node != nullptr) {
					if (prev == node->right) {
						prev = node;
						node = node->parent;
					} else if (node->left != nullptr && prev != node->left) {
						prev = node;
						node = node->left;
					} else {
						f(node);
						prev = node;
						if (node->right != nullptr) {
							node = node->right;
						} else {
							node = node->parent;
						}
					}
				}
			}

			// Recursive
			static void PostOrderWalk(Node * node, function<void(Node *)> f)
			{
				if (node == nullptr || f == nullptr) return;
				PostOrderWalk(node->left, f);
				PostOrderWalk(node->right, f);
				f(node);
			}

			void PostOrderWalk(function<void(Node *)> f) { PostOrderWalk(this, f); }

			// Non-recursive with stack
			static void PostOrderWalk2(Node * node, function<void(Node *)> f)
			{
				if (node == nullptr || f == nullptr) return;
				stack<Node *> path;
				Node * prev = nullptr;
				while (!path.empty() || node != nullptr) {
					if (node != nullptr) {
						path.push(node);
						node = node->left;
					} else {
						Node * top = path.top();
						if (top->right != nullptr && top->right != prev) {
							node = top->right;
						} else {
							path.pop();
							f(top);
							prev = top;
						}
					}
				}
			}

			// Non-recursive without stack
			static void PostOrderWalk3(Node * node, function<void(Node *)> f)
			{
				if (node == nullptr || f == nullptr) return;
				Node * prev = node;
				while (node != nullptr) {
					if (prev == node->right) {
						f(node);
						prev = node;
						node = node->parent;
					} else if (node->left != nullptr && prev != node->left) {
						prev = node;
						node = node->left;
					} else {
						prev = node;
						if (node->right != nullptr) {
							node = node->right;
						} else {
							f(node);
							node = node->parent;
						}
					}
				}
			}

			// Delete all the children of node
			static void Empty(Node * node)
			{
				function<void(Node *)> del = [](Node * x){ delete x; };
				PostOrderWalk(node->left, del);
				PostOrderWalk(node->right, del);
				node->left = nullptr;
				node->right = nullptr;
			}

			void Empty(void) { Empty(this); }

			static void Print(Node * node, int x, vector<int> y)
			{
				printf("%3d", node->content);

				if (node->right != nullptr) {
					// Record current x coordinate,
					// so it can be used to draw '|'
					y.push_back(x);
				}

				if (node->left != nullptr) {
					printf(" ___");
					Print(node->left, x + 1, y);
				}

				if (node->right != nullptr) {
					printf("\n");
					for (int i = 0; i < x; i++) {
						if (find(y.begin(), y.end(), i) != y.end()) {
							// Draw '|' because the parent node still has its right child not printed.
							printf("   |   ");
						} else {
							printf("       ");
						}
					}

					printf("   |___");

					// The right child is ready to print
					// Remove its coordinate because it is not needed any more
					y.pop_back();

					Print(node->right, x + 1, y);
				}
			}

			void Print(void)
			{
				vector<int> y;
				Print(this, 0, y);
				printf("\n");
			}

		} * root;

		// Delete all the nodes
		void Empty(void);

	public:
		BinaryTree(void) : root(nullptr), count(0) {}
		~BinaryTree(void) { Empty(); }

		// Get the height of node given its index (0-based)
		static int Height(int index);

		// Get the branch code of node given its index (0-based)
		static BitSet BrachCode(int index);

		// Insert the content as a new node at the next available position
		virtual void Insert(T & content);

		void PreOrderWalk(function<void(T)> f);
		void PreOrderWalk2(function<void(T)> f);
		void PreOrderWalk3(function<void(T)> f);

		void InOrderWalk(function<void(T)> f);
		void InOrderWalk2(function<void(T)> f);
		void InOrderWalk3(function<void(T)> f);

		void PostOrderWalk(function<void(T)> f);
		void PostOrderWalk2(function<void(T)> f);
		void PostOrderWalk3(function<void(T)> f);

		void Print(void);
	};

	template<class T> void BinaryTree<T>::Empty(void)
	{
		if (this->root != nullptr) {
			Node::Empty(this->root);
			delete this->root;
			this->root = nullptr;
			this->count = 0;
		}
	}

	//         0
	//    1          2
	//  3   4     5     6
	// 7 8 9 10 11 12 13 14
	// Given height H, the number of nodes are in [2^(H - 1), 2^H - 1]
	// The indices of nodes at height H are in [2^(H - 1) - 1, 2^H - 2]
	// Given node index I, its children are 2*I+1 and 2*I+2

	template<class T> int BinaryTree<T>::Height(int index)
	{
		unsigned int c = (unsigned int)(index + 1);
		int h = 0;
		while (c > 0) {
			h++;
			c = c >> 1;
		}

		return h;
	}

	// Encode the link from a node to its left child as 0.
	// Encode the link from a node to its right child as 1.
	// The the path from the root to and node can be represented with a bit set.
	template<class T> BitSet BinaryTree<T>::BrachCode(int index)
	{
		int h = Height(index);
		BitSet branch(h);
		unsigned int c = (unsigned int)index;
		while (c > 0) {
			if (c % 2 == 1) {
				// index is an odd number, meaning it is the left child of its parent
				// Encode it as 0
				branch.Reset(h - 1);
			} else {
				// index is an even number, meaning it is the right child of its parent
				// Encode it as 1
				branch.Set(h - 1);
			}

			c = (c - 1) >> 1;
			h--;
		}

		return branch;
	}

	template<class T> void BinaryTree<T>::Insert(T & content)
	{
		Node * node = new Node(content);
		if (this->root == nullptr) {
			this->root = node;
			this->root->parent = nullptr;
			this->count = 1;
		} else {
			// this->count equals to the index for the new node
			int height = Height(this->count);
			BitSet branch = BrachCode(this->count);

			Node * current = this->root;
			for (int h = 1; h < height; h++) {
				if (!branch.Test(h)) {
					if (current->left != nullptr) current = current->left;
					else current->left = node;
				} else if (branch.Test(h)) {
					if (current->right != nullptr) current = current->right;
					else current->right = node;
				}
			}

			this->count++;
		}
	}

	template<class T> void BinaryTree<T>::PreOrderWalk(function<void(T)> f)
	{
		if (this->root != nullptr) {
			auto fNode = [=](Node * x){ f(x->Content()); };
			Node::PreOrderWalk(this->root, fNode);
		}
	}

	template<class T> void BinaryTree<T>::PreOrderWalk2(function<void(T)> f)
	{
		if (this->root != nullptr) {
			auto fNode = [=](Node * x){ f(x->Content()); };
			Node::PreOrderWalk2(this->root, fNode);
		}
	}

	template<class T> void BinaryTree<T>::PreOrderWalk3(function<void(T)> f)
	{
		if (this->root != nullptr) {
			auto fNode = [=](Node * x){ f(x->Content()); };
			Node::PreOrderWalk3(this->root, fNode);
		}
	}

	template<class T> void BinaryTree<T>::InOrderWalk(function<void(T)> f)
	{
		if (this->root != nullptr) {
			auto fNode = [=](Node * x){ f(x->Content()); };
			Node::InOrderWalk(this->root, fNode);
		}
	}

	template<class T> void BinaryTree<T>::InOrderWalk2(function<void(T)> f)
	{
		if (this->root != nullptr) {
			auto fNode = [=](Node * x){ f(x->Content()); };
			Node::InOrderWalk2(this->root, fNode);
		}
	}

	template<class T> void BinaryTree<T>::InOrderWalk3(function<void(T)> f)
	{
		if (this->root != nullptr) {
			auto fNode = [=](Node * x){ f(x->Content()); };
			Node::InOrderWalk3(this->root, fNode);
		}
	}

	template<class T> void BinaryTree<T>::PostOrderWalk(function<void(T)> f)
	{
		if (this->root != nullptr) {
			auto fNode = [=](Node * x){ f(x->Content()); };
			Node::PostOrderWalk(this->root, fNode);
		}
	}

	template<class T> void BinaryTree<T>::PostOrderWalk2(function<void(T)> f)
	{
		if (this->root != nullptr) {
			auto fNode = [=](Node * x){ f(x->Content()); };
			Node::PostOrderWalk2(this->root, fNode);
		}
	}

	template<class T> void BinaryTree<T>::PostOrderWalk3(function<void(T)> f)
	{
		if (this->root != nullptr) {
			auto fNode = [=](Node * x){ f(x->Content()); };
			Node::PostOrderWalk3(this->root, fNode);
		}
	}

	template<class T> void BinaryTree<T>::Print(void)
	{
		if (this->root != nullptr) this->root->Print();
	}
}