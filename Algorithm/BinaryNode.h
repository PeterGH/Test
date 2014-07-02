#pragma once
#include <functional>
#if DEBUG
#include <iostream>
#endif
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
			if (this->left != nullptr)
			{
				delete this->left;
				this->left = nullptr;
			}

			if (this->right != nullptr)
			{
				delete this->right;
				this->right = nullptr;
			}

#if DEBUG
			cout << "Deleting " << this->content << endl;
#endif
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

		// Recursive
		static int Height(BinaryNode * node)
		{
			if (node == nullptr) return 0;
			int left = Height(node->left);
			int right = Height(node->right);
			return 1 + std::max<int>(left, right);
		}

		virtual int Height(void) { return Height(this); }

		static BinaryNode * LowestCommonAncestor(BinaryNode * node, BinaryNode * first, BinaryNode * second)
		{
			if (node == nullptr || first == nullptr || second == nullptr) return nullptr;
			if (node == first || node == second) return node;

			auto hits = [=](BinaryNode * n, BinaryNode * f, BinaryNode * s) -> int {
				if (n == nullptr) return 0;
				int h = hits(n->left, f, s) + hits(n->right, f, s);
				if (n == f || n == s) return 1 + h;
				else return h;
			};

			int h = hits(node->left, first, second);
			if (h == 1) return node;
			else if (h == 2) return LowestCommonAncestor(node->left, first, second);
			else return LowestCommonAncestor(node->right, first, second);
		}

		static BinaryNode * LowestCommonAncestor2(BinaryNode * node, BinaryNode * first, BinaryNode * second)
		{
			if (node == nullptr || first == nullptr || second == nullptr) return nullptr;
			if (node == first || node == second) return node;
			BinaryNode * left = LowestCommonAncestor2(node->left, first, second);
			BinaryNode * right = LowestCommonAncestor2(node->right, first, second);
			if (left != nullptr && right != nullptr) return node;
			if (left != nullptr) return left;
			else return right;
		}

		static stringstream & ToString(stringstream & ss, BinaryNode * node, int x, vector<int> & y)
		{
			if (node == nullptr) return ss;

			static string link = "____";
			string c = String::Format(" %d ", node->content);
			ss << c;
			x += c.length();
			
			if (node->right != nullptr) {
				// Record current x coordinate,
				// so it can be used to draw '|'
				y.push_back(x);
			}
			
			if (node->left != nullptr) {
				ss << link;
				ToString(ss, node->left, x + link.length(), y);
			}
			
			if (node->right != nullptr) {
				ss << endl;
				
				for (size_t i = 0; i < y.size(); i++) {
					int len = i == 0 ? y[i] : y[i] - y[i - 1];
					string blank(len - 1, ' ');
					ss << blank << '|';
				}
				
				ss << link;
				
				// The right child is ready to print
				// Remove its coordinate because it is not needed any more
				y.pop_back();
				
				ToString(ss, node->right, x + link.length(), y);
			}
			
			return ss;
		}
		
		void Print(void)
		{
			stringstream ss;
			vector<int> y;
			ToString(ss, this, 0, y);
			ss << endl;
			cout << ss.str();
		}
	};
}