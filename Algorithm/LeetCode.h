#pragma once
#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <stack>
#include <sstream>
#include <unordered_map>
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

		// Verify if a tree is a binary search tree.
		// Assume no duplicate elements.
		static bool IsBinarySearchTree(TreeNode * root)
		{
			if (root == nullptr) return true;
			stack<TreeNode *> path;
			path.push(root);
			TreeNode * node = root;
			TreeNode * prev = nullptr;
			TreeNode * lastVisited = nullptr;
			while (!path.empty()) {
				node = path.top();
				if (node->right != nullptr && node->right == lastVisited) {
					lastVisited = node;
					path.pop();
				} else if (node->left != nullptr && node->left != lastVisited) {
					lastVisited = node;
					path.push(node->left);
				} else {
					if (prev != nullptr && prev->val >= node->val) return false;
					prev = node;
					lastVisited = node;
					if (node->right != nullptr) path.push(node->right);
					else path.pop();
				}
			}
			return true;
		}

		static bool IsBinarySearchTree2(TreeNode * root)
		{
			function<bool(TreeNode *, int &, int &)>
			verify = [&](TreeNode * node, int & min, int & max)->bool{
				if (node == nullptr) return true;
				if (node->left == nullptr && node->right == nullptr) {
					min = node->val;
					max = node->val;
					return true;
				}

				if (node->left == nullptr) {
					min = node->val;
				} else {
					int leftMin;
					int leftMax;
					if (!verify(node->left, leftMin, leftMax)) return false;
					if (leftMax >= node->val) return false;
					min = leftMin;
				}

				if (node->right == nullptr) {
					max = node->val;
				} else {
					int rightMin;
					int rightMax;
					if (!verify(node->right, rightMin, rightMax)) return false;
					if (rightMin <= node->val) return false;
					max = rightMax;
				}

				return true;
			};

			int min;
			int max;
			return verify(root, min, max);
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

		// Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
		// For example,
		// s1 = "aabcc",
		// s2 = "dbbca",
		// When s3 = "aadbbcbcac", return true.
		// When s3 = "aadbbbaccc", return false.
		//   j 0 1 2
		// i 0
		//   1
		//   2
		// Let M[i][j] indicates whether s3[0..i+j-] is interleave of s1[0..i-1] and s2[0..j-1]
		// M[i][j] =   s1[i-1] == s3[i+j-1] && M[i-1][j]
		//          || s2[j-1] == s3[i+j-1] && M[i][j-1]
		static bool IsInterLeave(const string & s1, const string & s2, const string & s3)
		{
			if (s3.length() != s1.length() + s2.length()) return false;
			if (s3.length() == 0) return true;

			vector<bool> match(1 + s2.size(), true);
			for (size_t j = 1; j <= s2.size(); j++) {
				match[j] = match[j-1] && s2[j-1] == s3[j-1];
			}

			for (size_t i = 1; i <= s1.size(); i++) {
				match[0] = match[0] && s1[i-1] == s3[i-1];
				for (size_t j = 1; j <= s2.size(); j++) {
					match[j] = match[j] && s1[i-1] == s3[i+j-1] || match[j-1] && s2[j-1] == s3[i+j-1];
				}
			}

			return match[s2.size()];
		}

		// Given n distinct numbers (e.g., 1, 2, 3, ..., n)
		// count unique binary search trees that can be built with the n numbers
		// Let C[i,j] be the count of unique binary search trees using numbers i to j
		// Then chose a k between i and j and solve sub problems
		// C[i,j] = C[i+1, j]
		//        + C[i, j-1]
		//        + C[i, k-1] * C[k+1, j]
		static int UniqueBinarySearchTrees(int n)
		{
			if (n <= 0) return 0;

			vector<vector<int>> count(n, vector<int>(n, 0));

			for (int i = 0; i < n; i++) {
				count[i][i] = 1;
			}

			for (int l = 1; l < n; l++) {
				for (int i = 0; i < n - l; i++) {
					int j = i + l;
					count[i][j] = count[i+1][j] + count[i][j-1];
					for (int k = i+1; k < j; k++) {
						count[i][j] += count[i][k-1] * count[k+1][j];
					}
				}
			}

			return count[0][n-1];
		}
	};
}