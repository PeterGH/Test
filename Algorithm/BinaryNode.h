#pragma once
#include <functional>
#if DEBUG
#include <iostream>
#endif
#include <queue>
#include <stack>
#include <vector>
using namespace std;

namespace Test {
	template<class T> class BinaryNode {
	public:
		T content;
		BinaryNode * left;
		BinaryNode * right;

		BinaryNode(const T & content)
		{
			this->content = content;
			this->left = nullptr;
			this->right = nullptr;
		}

		virtual ~BinaryNode(void)
		{
			this->left = nullptr;
			this->right = nullptr;
#if DEBUG
			cout << "Deleting " << this->content << endl;
#endif
		}

		// Delete a rooted binary tree
		static void DeleteTree(BinaryNode * node)
		{
			if (node == nullptr) return;
			if (node->left != nullptr) {
				DeleteTree(node->left);
				delete node->left;
				node->left = nullptr;
			}
			if (node->right != nullptr) {
				DeleteTree(node->right);
				delete node->right;
				node->right = nullptr;
			}
		}

		void DeleteTree(void)
		{
			DeleteTree(this);
		}

		// Recursive
		static void PreOrderWalk(BinaryNode * node, function<void(T)> f)
		{
			if (node == nullptr || f == nullptr) return;
			f(node->content);
			PreOrderWalk(node->left, f);
			PreOrderWalk(node->right, f);
		}

		void PreOrderWalk(function<void(T)> f) { PreOrderWalk(this, f); }

		// Non-recursive with stack
		static void PreOrderWalkWithStack(BinaryNode * node, function<void(T)> f)
		{
			if (node == nullptr || f == nullptr) return;
			stack<BinaryNode *> path;
			while (!path.empty() || node != nullptr) {
				if (node != nullptr) {
					f(node->content);
					path.push(node);
					node = node->left;
				} else {
					node = path.top()->right;
					path.pop();
				}
			}
		}

		void PreOrderWalkWithStack(function<void(T)> f) { PreOrderWalkWithStack(this, f); }

		// Non-recursive with stack
		static void PreOrderWalkWithStack2(BinaryNode * node, function<void(T)> f)
		{
			if (node == nullptr || f == nullptr) return;
			stack<BinaryNode *> path;
			path.push(node);
			while (!path.empty()) {
				BinaryNode * top = path.top();
				path.pop();
				f(top->content);
				if (top->right != nullptr) path.push(top->right);
				if (top->left != nullptr) path.push(top->left);
			}
		}

		void PreOrderWalkWithStack2(function<void(T)> f) { PreOrderWalkWithStack2(this, f); }

		// Non-recursive with stack
		static void PreOrderWalkWithStack3(BinaryNode * node, function<void(T)> f)
		{
			if (node == nullptr || f == nullptr) return;
			stack<BinaryNode *> path;
			path.push(node);
			BinaryNode * prev = node;
			while (!path.empty()) {
				node = path.top();
				if (prev == node->right) {
					path.pop();
					prev = node;
				} else if (node->left != nullptr && node->left != prev) {
					f(node->content);
					path.push(node->left);
					prev = node;
				} else {
					if (node->left != prev) {
						f(node->content);
					}

					if (node->right == nullptr) {
						path.pop();
					} else {
						path.push(node->right);
					}
					prev = node;
				}
			}
		}

		void PreOrderWalkWithStack3(function<void(T)> f) { PreOrderWalkWithStack3(this, f); }

		// Recursive
		static void InOrderWalk(BinaryNode * node, function<void(T)> f)
		{
			if (node == nullptr || f == nullptr) return;
			InOrderWalk(node->left, f);
			f(node->content);
			InOrderWalk(node->right, f);
		}
		
		void InOrderWalk(function<void(T)> f) { InOrderWalk(this, f); }
		
		// Non-recursive with stack
		static void InOrderWalkWithStack(BinaryNode * node, function<void(T)> f)
		{
			if (node == nullptr || f == nullptr) return;
			stack<BinaryNode *> path;
			while (!path.empty() || node != nullptr) {
				if (node != nullptr) {
					path.push(node);
					node = node->left;
				} else {
					node = path.top();
					path.pop();
					f(node->content);
					node = node->right;
				}
			}
		}

		void InOrderWalkWithStack(function<void(T)> f) { InOrderWalkWithStack(this, f); }

		// Non-recursive with stack
		static void InOrderWalkWithStack2(BinaryNode * node, function<void(T)> f)
		{
			if (node == nullptr || f == nullptr) return;
			stack<BinaryNode *> path;
			path.push(node);
			BinaryNode * prev = nullptr;
			while (!path.empty()) {
				BinaryNode * top = path.top();
				if (prev == top->right) {
					prev = top;
					path.pop();
				} else if (top->left != nullptr && prev != top->left) {
					prev = top;
					path.push(top->left);
				} else {
					f(top->content);
					prev = top;
					if (top->right != nullptr) path.push(top->right);
					else path.pop();
				}
			}
		}

		void InOrderWalkWithStack2(function<void(T)> f) { InOrderWalkWithStack2(this, f); }

		// Recursive
		static void PostOrderWalk(BinaryNode * node, function<void(T)> f)
		{
			if (node == nullptr || f == nullptr) return;
			PostOrderWalk(node->left, f);
			PostOrderWalk(node->right, f);
			f(node->content);
		}
		
		void PostOrderWalk(function<void(T)> f) { PostOrderWalk(this, f); }
				
		// Non-recursive with stack
		static void PostOrderWalkWithStack(BinaryNode * node, function<void(T)> f)
		{
			if (node == nullptr || f == nullptr) return;
			stack<BinaryNode *> path;
			BinaryNode * prev = nullptr;
			while (!path.empty() || node != nullptr) {
				if (node != nullptr) {
					path.push(node);
					node = node->left;
				} else {
					BinaryNode * top = path.top();
					if (top->right != nullptr && top->right != prev) {
						node = top->right;
					} else {
						path.pop();
						f(top->content);
						prev = top;
					}
				}
			}
		}

		void PostOrderWalkWithStack(function<void(T)> f) { PostOrderWalkWithStack(this, f); }

		// Non-recursive with stack
		static void PostOrderWalkWithStack2(BinaryNode * node, function<void(T)> f)
		{
			if (node == nullptr || f == nullptr) return;
			stack<BinaryNode *> path;
			path.push(node);
			BinaryNode * prev = node;
			while (!path.empty()) {
				BinaryNode * top = path.top();
				if (prev == top->right) {
					f(top->content);
					prev = top;
					path.pop();
				} else if (top->left != nullptr && prev != top->left) {
					prev = top;
					path.push(top->left);
				} else {
					prev = top;
					if (top->right != nullptr) path.push(top->right);
					else {
						f(top->content);
						path.pop();
					}
				}
			}
		}

		void PostOrderWalkWithStack2(function<void(T)> f) { PostOrderWalkWithStack2(this, f); }

		// Visit level by level, left to right
		// Breadth-first search
		static void LevelOrderWalk(BinaryNode * node, function<void(T)> f)
		{
			if (node == nullptr || f == nullptr) return;
			queue<BinaryNode *> q;
			q.push(node);
			while (!q.empty()) {
				BinaryNode * p = q.front();
				q.pop();
				f(p->content);
				if (p->left != nullptr) q.push(p->left);
				if (p->right != nullptr) q.push(p->right);
			}
		}

		virtual void LevelOrderWalk(function<void(T)> f) { LevelOrderWalk(this, f); }

		// Visit level by level, left to right
		// Depth-first search
		static void LevelOrderWalk2(BinaryNode * node, function<void(T)> f)
		{
			if (node == nullptr || f == nullptr) return;
			vector<vector<T> *> levels;

			function<void(BinaryNode *, unsigned int)> preOrder = [&](BinaryNode * n, unsigned int l) {
				if (n == nullptr) return;

				if (levels.size() <= l) {
					levels.push_back(new vector<T>());
				}

				vector<T> * level = levels[l];

				level->push_back(n->content);

				preOrder(n->left, l + 1);
				preOrder(n->right, l + 1);
			};

			preOrder(node, 0);

			for_each (levels.begin(), levels.end(), [&](vector<T> * level){
				for_each (level->begin(), level->end(), [&](T c){
					f(c);
				});
				delete level;
			});
		}

		void LevelOrderWalk2(function<void(T)> f) { LevelOrderWalk2(this, f); }

		// Recursive
		static int Height(BinaryNode * node)
		{
			if (node == nullptr) return 0;
			int left = Height(node->left);
			int right = Height(node->right);
			return 1 + std::max<int>(left, right);
		}

		virtual int Height(void) { return Height(this); }

		static int Size(BinaryNode * node)
		{
			if (node == nullptr) return 0;
			return 1 + Size(node->left) + Size(node->right);
		}

		virtual int Size(void) { return Size(this); }

		static stringstream & ToString(BinaryNode * node, stringstream & output)
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
				string c = String::Format(" %d ", n->content);
				output << c;
				x += c.length();
			
				if (n->right != nullptr) {
					// Record current x coordinate,
					// so it can be used to draw '|'
					y.push_back(x);
				}
			
				if (n->left != nullptr) {
					output << link;
					toString(n->left, x + link.length(), y);
				}
			
				if (n->right != nullptr) {
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
				
					toString(n->right, x + link.length(), y);
				}
			};

			vector<int> y;
			toString(node, 0, y);
			output << endl;
			return output;
		}

		static stringstream & ToString2(BinaryNode * node, stringstream & output)
		{
			function<void(stringstream *, int, char)>
			printChar = [&](stringstream * s, int n, char c) {
				if (n > 0) {
					string chars(n, c);
					*s << chars;
				}
			};

			function<void(BinaryNode *, unsigned int, int &, int&, vector<stringstream *> &)>
			toString = [&](
				BinaryNode * n,             // current node to print
				unsigned int y,             // current node level
				int & x,                    // x-axis position of root of last printed sub tree
				int & r,                    // x-axis position of right-most boundary of last printed sub tree
				vector<stringstream *> & ss // output streams, one per level
				)
			{
				if (n == nullptr) {
					return;
				}

				if (ss.size() <= y) {
					ss.push_back(new stringstream());
				}

				// print left tree, update x and r accordingly
				toString(n->left, y + 1, x, r, ss);

				stringstream * s = ss[y];

				int l = (int)(s->str().length());
				if (l < x) {
					printChar(s, x - l, ' ');
				}

				if (n->left != nullptr && r > x) {
					*s << '/';
					printChar(s, r - x - 1, '-');
				}

				string nc = to_string(n->content);
				*s << nc;

				x = (r + (nc.length() >> 1));
				r = r + nc.length();

				int rx = r;
				int rr = r;
				toString(n->right, y + 1, rx, rr, ss);

				if (n->right != nullptr && rx >= r) {
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

		void Print(void)
		{
			stringstream ss;
			ToString(this, ss);
			cout << ss.str();
		}

		void Print2(void)
		{
			stringstream output;
			ToString2(this, output);
			cout << output.str();
		}

		// http://leetcode.com/2010/09/printing-binary-tree-in-zig-zag-level_18.html
		// Breadth-first-search using stack
		void PrintZigZag(void)
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
					cout << p->content << ' ';
					if (l % 2 == 0) {
						if (p->left != nullptr) {
							next.push(p->left);
						}
						if (p->right != nullptr) {
							next.push(p->right);
						}
					} else {
						if (p->right != nullptr) {
							next.push(p->right);
						}
						if (p->left != nullptr) {
							next.push(p->left);
						}
					}
				}
				cout << endl;
				if (next.empty()) break;
				l++;
			}
		}
	};
}