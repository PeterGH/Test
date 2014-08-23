#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <stack>
#include <sstream>
#include <vector>
using namespace std;
namespace Test {
	class __declspec(dllexport) LeetCode {
	public:
		struct TreeNode {
			int val;
			TreeNode * left;
			TreeNode * right;
			TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
		};

		static void Print(TreeNode * node)
		{
			function<void(stringstream *, int, char)>
			printChar = [&](stringstream * s, int n, char c) {
				if (n > 0) {
					string chars(n, c);
					*s << chars;
				}
			};

			function<void(TreeNode *, unsigned int, int &, int &, vector<stringstream *> &)>
			toString = [&](
				TreeNode * n,             // current node to print
				unsigned int y,           // current node level
				int & x,                  // x-axis position of root of last printed sub tree
				int & r,                  // x-axis position of right-most boundary of last printed sub tree
				vector<stringstream *> & ss // output streams, one per level
				)
			{
				if (n == nullptr) return;

				if (ss.size() <= y) ss.push_back(new stringstream());

				// print left tree, update x and r accordingly
				toString(n->left, y + 1, x, r, ss);

				stringstream * s = ss[y];

				int l = (int)(s->str().length());
				if (l < x) printChar(s, x - l, ' ');

				if (n->left != nullptr && r > x) {
					*s << '/';
					printChar(s, r - x - 1, '-');
				}

				string nc = to_string(n->val);
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
				cout << s->str() << endl;
				delete s;
			});
		}

		static void DeleteTree(TreeNode * root)
		{
			if (root == nullptr) return;
			if (root->left != nullptr) DeleteTree(root->left);
			if (root->right != nullptr) DeleteTree(root->right);
			delete root;
		}

		static TreeNode * Clone(TreeNode * root)
		{
			if (root == nullptr) return nullptr;
			TreeNode * clone = new TreeNode(root->val);
			clone->left = Clone(root->left);
			clone->right = Clone(root->right);
			return clone;
		}

		static bool Equal(TreeNode * first, TreeNode * second)
		{
			if (first == nullptr && second == nullptr) return true;
			if (first == nullptr || second == nullptr) return false;
			if (first->val != second->val) return false;
			if (!Equal(first->left, second->left)) return false;
			return Equal(first->right, second->right);
		}

		// Two elements of a binary search tree are swapped by mistake.
		// Recover the tree without changing its structure.
		// If we traverse a binary search tree in-order, we will get an increasing
		// sequence, e.g.,
		//    1, 2, 3, 4, 5, 6, 7, .......
		// If two neighboring elements are swapped, we will have one inversion, e.g.,
		//    1, 2, 4, 3, 5, 6, 7, .......
		// If two non-neighboring elements are swapped, we will have two inversions, e.g.,
		//    1, 2, 3, 6, 5, 4, 7, ....... , or
		//    1, 2, 6, 4, 5, 3, 7, .......
		static void RecoverTree(TreeNode * root)
		{
			if (root == nullptr) return;
			if (root->left == nullptr && root->right == nullptr) return;

			// Track the first inversion
			TreeNode * n1 = nullptr;
			TreeNode * n2 = nullptr;
			// Track the second inversion
			TreeNode * n3 = nullptr;
			TreeNode * n4 = nullptr;

			stack<TreeNode *> path;
			path.push(root);

			// Track the in-order previous and current nodes
			TreeNode * prev = nullptr;
			TreeNode * node = root;

			// Track the last visited node
			TreeNode * lastVisited = nullptr;

			while (!path.empty()) {
				node = path.top();
				if (node->right != nullptr && node->right == lastVisited) {
					path.pop();
					lastVisited = node;
				} else if (node->left != nullptr && node->left != lastVisited) {
					lastVisited = node;
					path.push(node->left);
				} else {
					if (prev == nullptr) {
						prev = node;
					} else {
						if (prev->val > node->val) {
							if (n1 == nullptr && n2 == nullptr) {
								n1 = prev;
								n2 = node;
							} else {
								n3 = prev;
								n4 = node;
								break;
							}
						}
						prev = node;
					}
					lastVisited = node;
					if (node->right != nullptr) {
						path.push(node->right);
					} else {
						path.pop();
					}
				}
			}

			if (n3 == nullptr && n4 == nullptr
				&& n1 != nullptr && n2 != nullptr) {
				int t = n1->val;
				n1->val = n2->val;
				n2->val = t;
			} else if (n3 != nullptr && n4 != nullptr
				&& n1 != nullptr && n2 != nullptr) {
				int t = n1->val;
				n1->val = n4->val;
				n4->val = t;
			}
		}

		static void RecoverTree2(TreeNode * root)
		{
			if (root == nullptr) return;
			if (root->left == nullptr && root->right == nullptr) return;

			function<void(TreeNode *, TreeNode * &, TreeNode * &, TreeNode * &, TreeNode * &, TreeNode * &)>
			search = [&](
				TreeNode * node,
				TreeNode * & prev,
				TreeNode * & n1,
				TreeNode * & n2,
				TreeNode * & n3,
				TreeNode * & n4)
			{
				if (node == nullptr) return;

				if (node->left != nullptr)
					search(node->left, prev, n1, n2, n3, n4);

				if (prev != nullptr) {
					if (prev->val > node->val) {
						if (n1 == nullptr && n2 == nullptr) {
							n1 = prev;
							n2 = node;
						} else {
							n3 = prev;
							n4 = node;
						}
					}
				}

				prev = node;

				if (node->right != nullptr)
					search(node->right, prev, n1, n2, n3, n4);
			};

			TreeNode * prev = nullptr;
			TreeNode * n1 = nullptr;
			TreeNode * n2 = nullptr;
			TreeNode * n3 = nullptr;
			TreeNode * n4 = nullptr;
			search(root, prev, n1, n2, n3, n4);

			if (n3 == nullptr && n4 == nullptr
				&& n1 != nullptr && n2 != nullptr) {
				int t = n1->val;
				n1->val = n2->val;
				n2->val = t;
			} else if (n3 != nullptr && n4 != nullptr
				&& n1 != nullptr && n2 != nullptr) {
				int t = n1->val;
				n1->val = n4->val;
				n4->val = t;
			}
		}
	};
}