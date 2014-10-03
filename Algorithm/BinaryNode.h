#pragma once
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include "Node.h"
#include "String.h"
using namespace std;

namespace Test {
	template<class T> class BinaryNode : public Node<T> {
	public:
		BinaryNode(const T & v) : Node<T>(v, 2) {}
		virtual ~BinaryNode(void) {}

		// Delete a rooted binary tree
		static void DeleteTree(BinaryNode * node);
		void DeleteTree(void) {	DeleteTree(this); }

		// Create a complete binary tree
		static BinaryNode * ToCompleteTree(vector<T> values);
		// Fill missing nodes to make a complete tree
		static BinaryNode * FillToComplete(BinaryNode * node, vector<T> values);
		static bool IsCompleteTree(BinaryNode * node);

		// Return 0 if two trees are equal
		static int Compare(BinaryNode * first, BinaryNode * second);
		static int Compare2(BinaryNode * first, BinaryNode * second);

		// Recursive
		static int Height(BinaryNode * node);
		virtual int Height(void) { return Height(this); }

		// Get the reference of left child pointer
		BinaryNode * & Left(void) { return (BinaryNode * &)this->Neighbor(0); }
		// Set the left child pointer
		void Left(BinaryNode * left) { this->Neighbor(0) = left; }

		// Get the reference of right child pointer
		BinaryNode * & Right(void) { return (BinaryNode * &)this->Neighbor(1); }
		// Set the right child pointer
		void Right(BinaryNode * right) { this->Neighbor(1) = right; }

		static int Size(BinaryNode * node);
		virtual int Size(void) { return Size(this); }

		static stringstream & ToString(BinaryNode * node, stringstream & output);
		static stringstream & ToString2(BinaryNode * node, stringstream & output);

		void Print(void);
		void Print2(void);

		// Recursive
		static void PreOrderWalk(BinaryNode * node, function<void(T)> f);
		void PreOrderWalk(function<void(T)> f) { PreOrderWalk(this, f); }

		// Non-recursive with stack
		static void PreOrderWalkWithStack(BinaryNode * node, function<void(T)> f);
		void PreOrderWalkWithStack(function<void(T)> f) { PreOrderWalkWithStack(this, f); }

		// Non-recursive with stack
		static void PreOrderWalkWithStack2(BinaryNode * node, function<void(T)> f);
		void PreOrderWalkWithStack2(function<void(T)> f) { PreOrderWalkWithStack2(this, f); }

		// Non-recursive with stack
		static void PreOrderWalkWithStack3(BinaryNode * node, function<void(T)> f);
		void PreOrderWalkWithStack3(function<void(T)> f) { PreOrderWalkWithStack3(this, f); }

		// Recursive
		static void InOrderWalk(BinaryNode * node, function<void(T)> f);
		void InOrderWalk(function<void(T)> f) { InOrderWalk(this, f); }
		
		// Non-recursive with stack
		static void InOrderWalkWithStack(BinaryNode * node, function<void(T)> f);
		void InOrderWalkWithStack(function<void(T)> f) { InOrderWalkWithStack(this, f); }

		// Non-recursive with stack
		static void InOrderWalkWithStack2(BinaryNode * node, function<void(T)> f);
		void InOrderWalkWithStack2(function<void(T)> f) { InOrderWalkWithStack2(this, f); }

		// Recursive
		static void PostOrderWalk(BinaryNode * node, function<void(T)> f);
		void PostOrderWalk(function<void(T)> f) { PostOrderWalk(this, f); }
				
		// Non-recursive with stack
		static void PostOrderWalkWithStack(BinaryNode * node, function<void(T)> f);
		void PostOrderWalkWithStack(function<void(T)> f) { PostOrderWalkWithStack(this, f); }

		// Non-recursive with stack
		static void PostOrderWalkWithStack2(BinaryNode * node, function<void(T)> f);
		void PostOrderWalkWithStack2(function<void(T)> f) { PostOrderWalkWithStack2(this, f); }

		// Visit level by level, left to right
		// Breadth-first search
		static void LevelOrderWalk(BinaryNode * node, function<void(T)> f);
		virtual void LevelOrderWalk(function<void(T)> f) { LevelOrderWalk(this, f); }

		// Visit level by level, left to right
		// Depth-first search
		static void LevelOrderWalk2(BinaryNode * node, function<void(T)> f);
		void LevelOrderWalk2(function<void(T)> f) { LevelOrderWalk2(this, f); }

		// Visit nodes level by level from bottom up and left to right
		static void LevelOrderWalkBottomUp(BinaryNode * node, function<void(T)> f);
		void LevelOrderWalkBottomUp(function<void(T)> f) { LevelOrderWalkBottomUp(this, f); }

		// http://leetcode.com/2010/09/printing-binary-tree-in-zig-zag-level_18.html
		// Breadth-first-search using stack
		void PrintZigZag(void);

		// Convert a binary tree to a linked list so that the list nodes
		// are linked by the right pointer and are in pre-order of original tree.
		// e.g.
		//      1
		//     / \
		//    2   5
		//   / \   \
		//  3   4   6
		// to
		//  1
		//   \
		//    2
		//     \
		//      3
		//       \
		//        4
		//         \
		//          5
		//           \
		//            6
		// This version builds a double-link list by setting node->left also.
		// If need a single-link list, just remove the statements setting node->left.
		static void ToPreOrderLinkList(BinaryNode * node);
		void ToPreOrderLinkList(void) { ToPreOrderLinkList(this); }

		// A tree is balanced if the heights of its left tree and right tree differs no more than 1.
		static bool IsBalanced(BinaryNode * node);
		bool IsBalanced(void) { return IsBalanced(this); }

		// A tree is balanced if the heights of its left tree and right tree differs no more than 1.
		// This algorithm is wrong.
		static bool IsBalanced2(BinaryNode * node);
		bool IsBalanced2(void) { return IsBalanced2(this); }

		// Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
		// For example, this binary tree is symmetric:
		//    1
		//   / \
		//  2   2
		// / \ / \
		// 3 4 4 3
		// But the following is not:
		//   1
		//  / \
		// 2   2
		//  \   \
		//   3   3
		static bool IsSymmetric(BinaryNode * node);
		bool IsSymmetric(void) { return IsSymmetric(this); }

		// Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
		// For example, this binary tree is symmetric:
		//    1
		//   / \
		//  2   2
		// / \ / \
		// 3 4 4 3
		// But the following is not:
		//   1
		//  / \
		// 2   2
		//  \   \
		//   3   3
		static bool IsSymmetric2(BinaryNode * node);
		bool IsSymmetric2(void) { return IsSymmetric2(this); }
	};

	template<class T> void BinaryNode<T>::DeleteTree(BinaryNode * node)
	{
		if (node == nullptr) return;
		if (node->Left() != nullptr) {
			DeleteTree(node->Left());
			delete node->Left();
			node->Left() = nullptr;
		}
		if (node->Right() != nullptr) {
			DeleteTree(node->Right());
			delete node->Right();
			node->Right() = nullptr;
		}
	}

	// Create a complete binary tree
	template<class T> BinaryNode<T> * BinaryNode<T>::ToCompleteTree(vector<T> values)
	{
		if (values.size() == 0) return nullptr;
		BinaryNode<T> * node = new BinaryNode<T>(values[0]);
		queue<BinaryNode<T> *> q;
		q.push(node);
		size_t i = 1;
		BinaryNode<T> * n;
		while (!q.empty() && i < values.size()) {
			n = q.front();
			q.pop();
			if (n->Left() == nullptr) {
				n->Left() = new BinaryNode<T>(values[i++]);
				if (i == values.size()) break;
			}
			q.push(n->Left());
			if (n->Right() == nullptr) {
				n->Right() = new BinaryNode<T>(values[i++]);
				if (i == values.size()) break;
			}
			q.push(n->Right());
		}
		return node;
	}

	// Fill missing nodes to make a complete tree
	template<class T> BinaryNode<T> * BinaryNode<T>::FillToComplete(BinaryNode * node, vector<T> values)
	{
		if (values.size() == 0) return node;
		size_t i = 0;
		if (node == nullptr) node = new BinaryNode<T>(values[i++]);
		queue<BinaryNode<T> *> q;
		q.push(node);
		BinaryNode<T> * n;
		while (!q.empty() && i < values.size()) {
			n = q.front();
			q.pop();
			if (n->Left() == nullptr) {
				n->Left() = new BinaryNode<T>(values[i++]);
				if (i == values.size()) break;
			}
			q.push(n->Left());
			if (n->Right() == nullptr) {
				n->Right() = new BinaryNode<T>(values[i++]);
				if (i == values.size()) break;
			}
			q.push(n->Right());
		}
		return node;
	}

	template<class T> bool BinaryNode<T>::IsCompleteTree(BinaryNode * node)
	{
		if (node == nullptr) return true;
		queue<BinaryNode<T> *> q;
		q.push(node);
		bool end = false;
		while (!q.empty()) {
			node = q.front();
			q.pop();
			if (node->Left() == nullptr) {
				if (!end) end = true;
			} else {
				if (end) return false;
				else q.push(node->Left());
			}
			if (node->Right() == nullptr) {
				if (!end) end = true;
			} else {
				if (end) return false;
				else q.push(node->Right());
			}
		}
		return true;
	}

	template<class T> int BinaryNode<T>::Compare(BinaryNode * first, BinaryNode * second)
	{
		if (first == nullptr && second == nullptr) return 0;
		if (first == nullptr && second != nullptr) return -1;
		if (first != nullptr && second == nullptr) return 1;
		if (first->Value() < second->Value()) return -1;
		if (first->Value() > second->Value()) return 1;
		int v = Compare(first->Left(), second->Left());
		if (v == 0) v = Compare(first->Right(), second->Right());
		return v;
	}

	template<class T> int BinaryNode<T>::Compare2(BinaryNode * first, BinaryNode * second)
	{
		if (first == nullptr && second == nullptr) return 0;
		if (first == nullptr && second != nullptr) return -1;
		if (first != nullptr && second == nullptr) return 1;
		if (first->Value() < second->Value()) return -1;
		if (first->Value() > second->Value()) return 1;
		deque<BinaryNode *> q;
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

	template<class T> int BinaryNode<T>::Height(BinaryNode * node)
	{
		if (node == nullptr) return 0;
		int left = Height(node->Left());
		int right = Height(node->Right());
		return 1 + std::max<int>(left, right);
	}

	template<class T> int BinaryNode<T>::Size(BinaryNode * node)
	{
		if (node == nullptr) return 0;
		int left = Size(node->Left());
		int right = Size(node->Right());
		return 1 + left + right;
	}

	template<class T> stringstream & BinaryNode<T>::ToString(BinaryNode * node, stringstream & output)
	{
		function<void(BinaryNode *, int, vector<int> &)>
		toString = [&](
			BinaryNode * n, // Current node to print
			int x,          // Current node position
			vector<int> & y // Positions of unprinted right branch starting points
			)
		{
			if (n == nullptr) return;

			static string link = "____";
			string c = String::ToString(n->Value());
			output << " " << c;
			x += (1 + c.length());

			if (n->Right() != nullptr) {
				// Record current x coordinate,
				// so it can be used to draw '|'
				y.push_back(x);
			}

			if (n->Left() != nullptr) {
				output << link;
				toString(n->Left(), x + link.length(), y);
			}

			if (n->Right() != nullptr) {
				output << endl;

				for (size_t i = 0; i < y.size(); i++) {
					int len = i == 0 ? y[i] : y[i] - y[i - 1];
					string blank(len - 1, ' ');
					output << blank << '|';
				}

				output << link;

				// The right child is ready to print
				// Remove its coordinate because it is not needed any more
				y.pop_back();

				toString(n->Right(), x + link.length(), y);
			}
		};

		vector<int> y;
		toString(node, 0, y);
		output << endl;
		return output;
	}

	template<class T> stringstream & BinaryNode<T>::ToString2(BinaryNode * node, stringstream & output)
	{
		function<void(stringstream *, int, char)>
			printChar = [&](stringstream * s, int n, char c) {
			if (n > 0) {
				string chars(n, c);
				*s << chars;
			}
		};

		function<void(BinaryNode *, unsigned int, int &, int &, vector<stringstream *> &)>
		toString = [&](
			BinaryNode * n,             // current node to print
			unsigned int y,             // current node level
			int & x,                    // x-axis position of root of last printed sub tree
			int & r,                    // x-axis position of right-most boundary of last printed sub tree
			vector<stringstream *> & ss // output streams, one per level
			)
		{
			if (n == nullptr) return;

			if (ss.size() <= y) {
				ss.push_back(new stringstream());
			}

			// print left tree, update x and r accordingly
			toString(n->Left(), y + 1, x, r, ss);

			stringstream * s = ss[y];

			int l = (int)(s->str().length());
			if (l < x) {
				printChar(s, x - l, ' ');
			}

			if (n->Left() != nullptr && r > x) {
				*s << '/';
				printChar(s, r - x - 1, '-');
			}

			string nc = String::ToString(n->Value());
			*s << nc;

			x = (r + (nc.length() >> 1));
			r = r + nc.length();

			int rx = r;
			int rr = r;
			toString(n->Right(), y + 1, rx, rr, ss);

			if (n->Right() != nullptr && rx >= r) {
				printChar(s, rx - r - 1, '-');
				*s << '\\';
			}

			// Update the right most boundary
			r = rr;
		};

		vector<stringstream *> streams;
		int x = 0;
		int r = 0;
		toString(node, 0, x, r, streams);

		for_each (streams.begin(), streams.end(), [&](stringstream * s) {
			output << s->str() << endl;
			delete s;
		});

		return output;
	}

	template<class T> void BinaryNode<T>::Print(void)
	{
		stringstream ss;
		ToString(this, ss);
		cout << ss.str();
	}

	template<class T> void BinaryNode<T>::Print2(void)
	{
		stringstream ss;
		ToString2(this, ss);
		cout << ss.str();
	}

	template<class T> void BinaryNode<T>::PreOrderWalk(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		f(node->Value());
		PreOrderWalk(node->Left(), f);
		PreOrderWalk(node->Right(), f);
	}

	template<class T> void BinaryNode<T>::PreOrderWalkWithStack(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		stack<BinaryNode *> path;
		while (!path.empty() || node != nullptr) {
			if (node != nullptr) {
				f(node->Value());
				path.push(node);
				node = node->Left();
			} else {
				node = path.top()->Right();
				path.pop();
			}
		}
	}

	template<class T> void BinaryNode<T>::PreOrderWalkWithStack2(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		stack<BinaryNode *> path;
		path.push(node);
		while (!path.empty()) {
			BinaryNode * top = path.top();
			path.pop();
			f(top->Value());
			if (top->Right() != nullptr) path.push(top->Right());
			if (top->Left() != nullptr) path.push(top->Left());
		}
	}

	template<class T> void BinaryNode<T>::PreOrderWalkWithStack3(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		stack<BinaryNode *> path;
		path.push(node);
		BinaryNode * prev = node;
		while (!path.empty()) {
			node = path.top();
			if (prev == node->Right()) {
				path.pop();
			} else if (node->Left() != nullptr && node->Left() != prev) {
				f(node->Value());
				path.push(node->Left());
			} else {
				if (node->Left() != prev) f(node->Value());
				if (node->Right() == nullptr) path.pop();
				else path.push(node->Right());
			}
			prev = node;
		}
	}

	template<class T> void BinaryNode<T>::InOrderWalk(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		InOrderWalk(node->Left(), f);
		f(node->Value());
		InOrderWalk(node->Right(), f);
	}

	template<class T> void BinaryNode<T>::InOrderWalkWithStack(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		stack<BinaryNode *> path;
		while (!path.empty() || node != nullptr) {
			if (node != nullptr) {
				path.push(node);
				node = node->Left();
			} else {
				node = path.top();
				path.pop();
				f(node->Value());
				node = node->Right();
			}
		}
	}

	template<class T> void BinaryNode<T>::InOrderWalkWithStack2(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		stack<BinaryNode *> path;
		path.push(node);
		BinaryNode * prev = nullptr;
		while (!path.empty()) {
			node = path.top();
			if (prev == node->Right()) {
				path.pop();
			} else if (node->Left() != nullptr && node->Left() != prev) {
				path.push(node->Left());
			} else {
				f(node->Value());
				if (node->Right() == nullptr) path.pop();
				else path.push(node->Right());
			}
			prev = node;
		}
	}

	template<class T> void BinaryNode<T>::PostOrderWalk(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		PostOrderWalk(node->Left(), f);
		PostOrderWalk(node->Right(), f);
		f(node->Value());
	}

	template<class T> void BinaryNode<T>::PostOrderWalkWithStack(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		stack<BinaryNode *> path;
		BinaryNode * prev = nullptr;
		while (!path.empty() || node != nullptr) {
			if (node != nullptr) {
				path.push(node);
				node = node->Left();
			} else {
				BinaryNode * top = path.top();
				if (top->Right() != nullptr && top->Right() != prev) {
					node = top->Right();
				} else {
					path.pop();
					f(top->Value());
					prev = top;
				}
			}
		}
	}

	template<class T> void BinaryNode<T>::PostOrderWalkWithStack2(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		stack<BinaryNode *> path;
		path.push(node);
		BinaryNode * prev = node;
		while (!path.empty()) {
			node = path.top();
			if (prev == node->Right()) {
				f(node->Value());
				path.pop();
			} else if (node->Left() != nullptr && node->Left() != prev) {
				path.push(node->Left());
			} else {
				if (node->Right() != nullptr) path.push(node->Right());
				else {
					f(node->Value());
					path.pop();
				}
			}
			prev = node;
		}
	}

	template<class T> void BinaryNode<T>::LevelOrderWalk(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;
		queue<BinaryNode *> q;
		q.push(node);
		while (!q.empty()) {
			node = q.front();
			q.pop();
			f(node->Value());
			if (node->Left() != nullptr) q.push(node->Left());
			if (node->Right() != nullptr) q.push(node->Right());
		}
	}

	template<class T> void BinaryNode<T>::LevelOrderWalk2(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;

		vector<vector<T> *> levels;

		function<void(BinaryNode *, unsigned int)> preOrder = [&](BinaryNode * n, unsigned int l) {
			if (n == nullptr) return;

			if (levels.size() <= l) {
				levels.push_back(new vector<T>());
			}

			vector<T> * level = levels[l];
			level->push_back(n->Value());

			preOrder(n->Left(), l + 1);
			preOrder(n->Right(), l + 1);
		};

		preOrder(node, 0);

		for_each (levels.begin(), levels.end(), [&](vector<T> * level){
			for_each (level->begin(), level->end(), [&](T c){
				f(c);
			});
			delete level;
		});
	}

	template<class T> void BinaryNode<T>::LevelOrderWalkBottomUp(BinaryNode * node, function<void(T)> f)
	{
		if (node == nullptr || f == nullptr) return;

		vector<vector<T>> levels;
		levels.push_back(vector<T> { node->Value() });

		queue<BinaryNode *> q[2];
		q[0].push(node);

		int l = 0;
		while (!q[0].empty() || !q[1].empty()) {
			queue<BinaryNode *> & current = q[l & 0x1];
			queue<BinaryNode *> & next = q[(1+l) & 0x1];
			vector<T> level;
			while (!current.empty()) {
				node = current.front();
				current.pop();
				if (node->Left() != nullptr) {
					level.push_back(node->Left()->Value());
					next.push(node->Left());
				}
				if (node->Right() != nullptr) {
					level.push_back(node->Right()->Value());
					next.push(node->Right());
				}
			}
			if (level.size() > 0) levels.insert(levels.begin(), level);
			l++;
		}

		for_each (levels.begin(), levels.end(), [&](vector<T> & level){
			for_each (level.begin(), level.end(), [&](T c){
				f(c);
			});
		});
	}

	// http://leetcode.com/2010/09/printing-binary-tree-in-zig-zag-level_18.html
	// Breadth-first-search using stack
	template<class T> void BinaryNode<T>::PrintZigZag(void)
	{
		stack<BinaryNode *> level[2];
		int l = 0;
		level[0].push(this);
		while (true) {
			stack<BinaryNode *> & current = level[l % 2];
			stack<BinaryNode *> & next = level[(l+1) % 2];
			while (!current.empty()) {
				BinaryNode * p = current.top();
				current.pop();
				cout << p->Value() << ' ';
				if (l % 2 == 0) {
					if (p->Left() != nullptr) next.push(p->Left());
					if (p->Right() != nullptr) next.push(p->Right());
				} else {
					if (p->Right() != nullptr) next.push(p->Right());
					if (p->Left() != nullptr) next.push(p->Left());
				}
			}
			cout << endl;
			if (next.empty()) break;
			l++;
		}
	}

	// Convert a binary tree to a linked list so that the list nodes
	// are linked by the right pointer and are in pre-order of original tree.
	// e.g.
	//      1
	//     / \
	//    2   5
	//   / \   \
	//  3   4   6
	// to
	//  1
	//   \
	//    2
	//     \
	//      3
	//       \
	//        4
	//         \
	//          5
	//           \
	//            6
	// This version builds a double-link list by setting node->left also.
	// If need a single-link list, just remove the statements setting node->left.
	template<class T> void BinaryNode<T>::ToPreOrderLinkList(BinaryNode * node)
	{
		if (node == nullptr) return;

		function<void(BinaryNode *, BinaryNode * &)>
		convert = [&](BinaryNode * head, BinaryNode * & tail){
			if (head == nullptr) {
				tail = nullptr;
				return;
			}

			if (head->Left() == nullptr && head->Right() == nullptr) {
				tail = head;
				return;
			}

			BinaryNode * leftTail = nullptr;
			convert(head->Left(), leftTail);

			BinaryNode * rightTail = nullptr;
			convert(head->Right(), rightTail);

			if (head->Left() != nullptr) {
				head->Left()->Left() = head;
				leftTail->Right() = head->Right();
				head->Right() = head->Left();
				head->Left() = nullptr;
				if (leftTail->Right() == nullptr) {
					tail = leftTail;
				} else {
					leftTail->Right()->Left() = leftTail;
					tail = rightTail;
				}
			} else {
				head->Right()->Left() = head;
				tail = rightTail;
			}
		};

		BinaryNode * tail;
		convert(node, tail);
	}

	template<class T> bool BinaryNode<T>::IsBalanced(BinaryNode * node)
	{
		if (node == nullptr) return true;

		function<bool(BinaryNode *, int &)>
		balanced = [&](BinaryNode * n, int & h)->bool{
			if (n == nullptr) {
				h = 0;
				return true;
			}

			if (n->Left() == nullptr && n->Right() == nullptr) {
				h = 1;
				return true;
			}

			int lh;
			bool l = balanced(n->Left(), lh);
			if (l == false) return false;

			int rh;
			bool r = balanced(n->Right(), rh);
			if (r == false) return false;

			if (lh - rh > 1 || rh - lh > 1) return false;

			h = 1 + (lh >= rh ? lh : rh);
			return true;
		};

		int height;
		bool isBalanced = balanced(node, height);
		return isBalanced;
	}

	// A tree is balanced if the heights of its left tree and right tree differs no more than 1.
	// This algorithm is wrong. A failed example is:
	//         1
	//     2       2
	//   3   3   3   3
	//  4 4 4 4 4 4
	// 5 5
	template<class T> bool BinaryNode<T>::IsBalanced2(BinaryNode * node)
	{
		if (node == nullptr) return true;

		int minDepth = INT_MAX;
		bool foundMinDepth = false;
		int depth = 0;
		queue<BinaryNode *> q[2];
		q[0].push(node);
		while (!q[0].empty() || !q[1].empty()) {
			queue<BinaryNode *> & current = q[depth & 0x1];
			queue<BinaryNode *> & next = q[(depth + 1) & 0x1];
			while (!current.empty()) {
				node = current.front();
				current.pop();
				if (node->Left() == nullptr && node->Right() == nullptr && !foundMinDepth) {
					foundMinDepth = true;
					minDepth = depth;
				}

				if (node->Left() != nullptr && node->Right() == nullptr) {
					if (node->Left()->Left() != nullptr || node->Left()->Right() != nullptr) return false;
				}

				if (node->Left() == nullptr && node->Right() != nullptr) {
					if (node->Right()->Left() != nullptr || node->Right()->Right() != nullptr) return false;
				}

				if (foundMinDepth && depth - minDepth > 1) return false;

				if (node->Left() != nullptr) next.push(node->Left());
				if (node->Right() != nullptr) next.push(node->Right());
			}

			depth++;
		}
		return true;
	}

	// Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
	// For example, this binary tree is symmetric:
	//    1
	//   / \
	//  2   2
	// / \ / \
	// 3 4 4 3
	// But the following is not:
	//   1
	//  / \
	// 2   2
	//  \   \
	//   3   3
	template<class T> bool BinaryNode<T>::IsSymmetric(BinaryNode * node)
	{
		function<bool(BinaryNode *, BinaryNode *)>
		isSymmetric = [&](BinaryNode * left, BinaryNode * right) -> bool {
			if (left == nullptr && right == nullptr) return true;
			if (left != nullptr && right == nullptr
				|| left == nullptr && right != nullptr) return false;
			if (left->Value() != right->Value()) return false;
			if (!isSymmetric(left->Left(), right->Right())) return false;
			return isSymmetric(left->Right(), right->Left());
		};

		return isSymmetric(node, node);
	}

	// Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
	// For example, this binary tree is symmetric:
	//    1
	//   / \
	//  2   2
	// / \ / \
	// 3 4 4 3
	// But the following is not:
	//   1
	//  / \
	// 2   2
	//  \   \
	//   3   3
	template<class T> bool BinaryNode<T>::IsSymmetric2(BinaryNode * node)
	{
		if (node == nullptr) return true;
		if (node->Left() == nullptr && node->Right() == nullptr) return true;
		if (node->Left() != nullptr && node->Right() == nullptr
			|| node->Left() == nullptr && node->Right() != nullptr) return false;
		if (node->Left()->Value() != node->Right()->Value()) return false;
		deque<BinaryNode *> q;
		q.push_front(node->Left());
		q.push_back(node->Right());
		while (!q.empty()) {
			BinaryNode * left = q.front();
			q.pop_front();
			BinaryNode * right = q.back();
			q.pop_back();
			if (left->Right() != nullptr && right->Left() == nullptr
				|| left->Right() == nullptr && right->Left() != nullptr) return false;
			if (left->Right() != nullptr && right->Left() != nullptr) {
				if (left->Right()->Value() != right->Left()->Value()) return false;
				q.push_front(left->Right());
				q.push_back(right->Left());
			}
			if (left->Left() != nullptr && right->Right() == nullptr
				|| left->Left() == nullptr && right->Right() != nullptr) return false;
			if (left->Left() != nullptr && right->Right() != nullptr) {
				if (left->Left()->Value() != right->Right()->Value()) return false;
				q.push_front(left->Left());
				q.push_back(right->Right());
			}
		}
		return true;
	}
}