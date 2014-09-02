#pragma once
#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <set>
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

		// Given n distinct numbers (e.g., 1, 2, 3, ..., n)
		// Create unique binary search trees that can be built with the n numbers
		static vector<TreeNode *> CreateUniqueBinarySearchTrees(int n)
		{
			function<vector<TreeNode *>(int, int)>
			create = [&](int i, int j)->vector<TreeNode *>{
				vector<TreeNode *> trees;

				if (i > j) return trees;

				if (i == j) {
					trees.push_back(new TreeNode(i));
					return trees;
				}

				if (i + 1 == j) {
					TreeNode * n = new TreeNode(j);
					n->left = new TreeNode(i);
					trees.push_back(n);
					n = new TreeNode(i);
					n->right = new TreeNode(j);
					trees.push_back(n);
					return trees;
				}

				vector<TreeNode *> firstTrees = create(i+1, j);
				for_each (firstTrees.begin(), firstTrees.end(), [&](TreeNode * f){
					TreeNode * n = new TreeNode(i);
					n->right = f;
					trees.push_back(n);
				});

				vector<TreeNode *> lastTrees = create(i, j-1);
				for_each (lastTrees.begin(), lastTrees.end(), [&](TreeNode * l){
					TreeNode * n = new TreeNode(j);
					n->left = l;
					trees.push_back(n);
				});

				for (int k = i+1; k < j; k++) {
					vector<TreeNode *> leftTrees = create(i, k-1);
					vector<TreeNode *> rightTrees = create(k+1, j);
					for_each (leftTrees.begin(), leftTrees.end(), [&](TreeNode * l){
						for_each (rightTrees.begin(), rightTrees.end(), [&](TreeNode * r){
							TreeNode * n = new TreeNode(k);
							n->left = Clone(l);
							n->right = Clone(r);
							trees.push_back(n);
						});
					});

					for_each (leftTrees.begin(), leftTrees.end(), [&](TreeNode * l){
						DeleteTree(l);
					});
					for_each (rightTrees.begin(), rightTrees.end(), [&](TreeNode * r){
						DeleteTree(r);
					});
				}

				return trees;
			};

			return create(1, n);
		}

		// Given a string containing only digits, restore it by returning all possible valid IP address combinations.
		// Given "25525511135",
		// return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
		static vector<string> GetIpAddresses(const string & s)
		{
			vector<string> ips;
			int len = s.length();
			if (len < 4 || len > 12) return ips;

			auto check = [&](const string & octet)->bool{
				int l = octet.length();
				for (int i = 0; i < min(3, l); i++) {
					if (octet[i] < '0' || octet[i] > '9') return false;
				}
				int m = 0;
				for (int i = 0; i < min(3, l); i++) {
					m = 10 * m + octet[i] - '0';
				}
				return 0 <= m && m <= 255;
			};

			for (int i = 1;	i <= (s[0] == '0' ? 1 : min(3, len-3)); i++) {
				for (int j = i+1; j <= (s[i] == '0' ? i+1 : min(i+3, len-2)); j++) {
					for (int k = j+1; k <= (s[j] == '0' ? j+1 : min(j+3, len-1)); k++) {
						if (len - k > 3 || len - k > 1 && s[k] == '0') continue;
						if (check(s.substr(0, i)) && check(s.substr(i, j-i)) && check(s.substr(j, k-j)) && check(s.substr(k, len-k))) {
							string ip(s.substr(0, i));
							ip.append(1, '.');
							ip.append(s.substr(i, j-i));
							ip.append(1, '.');
							ip.append(s.substr(j, k-j));
							ip.append(1, '.');
							ip.append(s.substr(k, len-k));
							ips.push_back(ip);
						}
					}
				}
			}

			return ips;
		}

		struct ListNode {
			int val;
			ListNode * next;
			ListNode(int v) : val(v), next(nullptr) {}
		};

		static void Print(ListNode * node)
		{
			if (node == nullptr) return;
			while (node != nullptr) {
				cout << node->val << "->";
				node = node->next;
			}
			cout << "null" << endl;
		}

		static void DeleteList(ListNode * node)
		{
			if (node == nullptr) return;
			ListNode * p = node;
			while (p != nullptr) {
				node = p->next;
				delete p;
				p = node;
			}
		}

		static ListNode * ToList(vector<int> & numbers)
		{
			ListNode * list = nullptr;
			if (numbers.size() == 0) return list;
			list = new ListNode(numbers[0]);
			ListNode * n = list;
			for (size_t i = 1; i < numbers.size(); i++) {
				n->next = new ListNode(numbers[i]);
				n = n->next;
			}
			return list;
		}

		// Reverse a linked list from position m to n. Do it in-place and in one-pass.
		// For example:
		// Given 1->2->3->4->5->NULL, m = 2 and n = 4,
		// return 1->4->3->2->5->NULL.
		static ListNode * ReverseList(ListNode * head, int m, int n)
		{
			if (head == nullptr || m <= 0 || n <= 0 || m >= n) return head;

			ListNode * ph = nullptr;
			ListNode * pm = head;
			int i = 1;
			while (i < m && pm->next != nullptr) {
				ph = pm;
				pm = pm->next;
				i++;
			}

			if (i < m) return head;

			ListNode * r = ph;
			ListNode * s = pm;
			ListNode * t = pm->next;

			while (i <= n && t != nullptr) {
				s->next = r;
				r = s;
				s = t;
				t = t->next;
				i++;
			}

			if (i <= n && t == nullptr) {
				s->next = r;
				r = s;
				s = t;
			}

			pm->next = s;
			if (ph != nullptr) ph->next = r;
			else head = r;

			return head;
		}

		// Given a collection of integers that might contain duplicates, S, return all possible subsets.
		// Elements in a subset must be in non-descending order.
		static vector<vector<int>> Subsets(vector<int> & s)
		{
			sort(s.begin(), s.end());
			vector<vector<int>> sets = { vector<int> { } };
			for_each (s.begin(), s.end(), [&](int n){
				int size = sets.size();
				for (int i = 0; i < size; i++) {
					vector<int> ex(sets[i].begin(), sets[i].end());
					ex.push_back(n);
					sets.push_back(ex);
				}
			});
			return sets;
		}

		// Given a collection of integers that might contain duplicates, S, return all possible subsets.
		// Note:
		//   Elements in a subset must be in non-descending order.
		//   The solution set must not contain duplicate subsets.
		// For example, if S = [1,2,2], a solution is:
		// [
		//  [2],
		//  [1],
		//  [1,2,2],
		//  [2,2],
		//  [1,2],
		//  []
		// ]
		static vector<vector<int>> UniqueSubsets(vector<int> & s)
		{
			sort(s.begin(), s.end());
			vector<vector<int>> sets = { vector<int> { } };
			size_t i = 0;
			while (i < s.size()) {
				int size = sets.size();
				size_t j = i;
				while (j < s.size() - 1 && s[j+1] == s[j]) j++;
				// s[i..j] are duplicates
				for (int k = 0; k < size; k++) {
					vector<int> c;
					for (size_t l = i; l <= j; l++) {
						c.push_back(s[l]);
						vector<int> ex(sets[k].begin(), sets[k].end());
						ex.insert(ex.end(), c.begin(), c.end());
						sets.push_back(ex);
					}
				}
				i = j + 1;
			}
			return sets;
		}

		// A message containing letters from A-Z is being encoded to numbers using the following mapping:
		// 'A' -> 1
		// 'B' -> 2
		// ...
		// 'Z' -> 26
		// Given an encoded message containing digits, determine the total number of ways to decode it.
		// For example, given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).
		// The number of ways decoding "12" is 2.
		static int CountStringDecodings(const string & s)
		{
			if (s.size() == 0) return 0;
			if (s[0] < '1' || s[0] > '9') return 0;
			int c0 = 1;
			int c1 = 1;
			int c2 = c1;
			for (size_t i = 1; i < s.size(); i++) {
				if (s[i] < '0' && '9' < s[i]) return 0;
				c2 = 0;
				if ('1' <= s[i] && s[i] <= '9')	c2 = c1;
				if (s[i-1] == '1' && s[i] >= '0' && s[i] <= '9'
					|| s[i-1] == '2' && s[i] >= '0' && s[i] <= '6')
					c2 += c0;
				c0 = c1;
				c1 = c2;
			}
			return c2;
		}

		// The gray code is a binary numeral system where two successive values differ in only one bit.
		// Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code.
		// A gray code sequence must begin with 0.
		// For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:
		// 00 - 0
		// 01 - 1
		// 11 - 3
		// 10 - 2
		// Note:
		// For a given n, a gray code sequence is not uniquely defined.
		// For example, [0,2,3,1] is also a valid gray code sequence according to the above definition.
		static vector<int> GrayCode(int n)
		{
			vector<int> codes = { };
			if (n <= 0 || n > 8 * sizeof(int)) return codes;
			function<void(int &, int)> toggle = [&](int & code, int position){
				code = code ^ (0x1 << position);
				codes.push_back(code);
				if (position > 0) {
					for (int i = 0; i < position; i++) toggle(code, i);
				}
			};

			int code = 0;
			codes.push_back(code);
			for (int i = 0; i < n; i++) toggle(code, i);

			return codes;
		}

		static vector<int> GrayCode2(int n)
		{
			vector<int> codes = { };
			if (n <= 0 || n > 8 * sizeof(int)) return codes;
			codes.push_back(0);
			for (int i = 0; i < n; i++) {
				int b = 0x1 << i;
				int j = codes.size();
				for (int k = j - 1; k >= 0; k--) {
					int c = codes[k] ^ b;
					codes.push_back(c);
				}
			}
			return codes;
		}

		static void MergeSortedArrays(int A[], int m, int B[], int n) {
			if (A == nullptr || m < 0 || B == nullptr || n < 0) return;
			int i = 0;
			int j = 0;
			while (i < m && j < n) {
				if (A[i] <= B[j]) i++;
				else {
					for (int k = m; k > i; k--) {
						A[k] = A[k-1];
					}
					A[i] = B[j];
					m++;
					i++;
					j++;
				}
			}
			if (j < n) {
				for (int k = j; k < n; k++) {
					A[i] = B[k];
					i++;
				}
			}
		}

		static void MergeSortedArrays2(int A[], int m, int B[], int n) {
			if (A == nullptr || m < 0 || B == nullptr || n < 0) return;
			int i = m - 1;
			int j = n - 1;
			while (i >= 0 && j >= 0) {
				if (A[i] > B[j]) {
					A[i+j+1] = A[i];
					i--;
				} else {
					A[i+j+1] = B[j];
					j--;
				}
			}
			if (j >= 0) {
				for (int p = j; p >= 0; p--) {
					A[p] = B[p];
				}
			}
		}

		static bool Equal(const map<char, int> & m1, const map<char, int> & m2)
		{
			if (m1.size() != m2.size()) return false;
			for (map<char, int>::const_iterator it1 = m1.begin(); it1 != m1.end(); it1++) {
				map<char, int>::const_iterator it2 = m2.find(it1->first);
				if (it2 == m2.end()) return false;
				if (it2->second != it1->second) return false;
			}
			return true;
		}

		// Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.
		// Below is one possible representation of s1 = "great":
		//     great
		//    /    \
		//   gr    eat
		//  / \    /  \
		// g   r  e   at
		//            / \
		//           a   t
		// To scramble the string, we may choose any non-leaf node and swap its two children.
		// For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".
		//     rgeat
		//    /    \
		//   rg    eat
		//  / \    /  \
		// r   g  e   at
		//            / \
		//           a   t
		// We say that "rgeat" is a scrambled string of "great".
		// Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".
		//     rgtae
		//    /    \
		//   rg    tae
		//  / \    /  \
		// r   g  ta   e
		//       / \
		//      t   a
		// We say that "rgtae" is a scrambled string of "great".
		// Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.
		static bool IsScramble(const string & s1, const string & s2)
		{
			if (s1.length() != s2.length()) return false;
			if (s1.length() == 0) return true;

			int len = s1.length();

			map<char, int> m1;
			map<char, int> m2;

			for (int i = 0; i < len; i++) {
				if (m1.find(s1[i]) == m1.end()) m1[s1[i]] = 1;
				else m1[s1[i]] += 1;
				if (m2.find(s2[i]) == m2.end()) m2[s2[i]] = 1;
				else m2[s2[i]] += 1;
				if (Equal(m1, m2)) {
					// s1[0..i] and s2[0..i] may be scramble
					if (i == 0 || i == 1) {
						// s1[0] and s2[0], or s1[0..1] and s2[0..1] are scramble
						if (i == len - 1 || IsScramble(s1.substr(i + 1, len - 1 - i), s2.substr(i + 1, len - 1 - i)))
							return true;
					} else if (i < len - 1) {
						if (IsScramble(s1.substr(0, i + 1), s2.substr(0, i + 1))
							&& IsScramble(s1.substr(i + 1, len - 1 - i), s2.substr(i + 1, len - 1 - i)))
							return true;
					}
				}
			}

			m1.clear();
			m2.clear();

			for (int i = 0; i < len; i++) {
				int j = len - 1 - i;
				if (m1.find(s1[j]) == m1.end()) m1[s1[j]] = 1;
				else m1[s1[j]] += 1;
				if (m2.find(s2[i]) == m2.end()) m2[s2[i]] = 1;
				else m2[s2[i]] += 1;
				if (Equal(m1, m2)) {
					// s1[len-1-i..len-1] and s2[0..i] may be scramble
					if (i == 0 || i == 1) {
						if (i == len - 1 || IsScramble(s1.substr(0, len - 1 - i), s2.substr(i + 1, len - 1 - i)))
							return true;
					} else if (i < len - 1) {
						if (IsScramble(s1.substr(0, len - 1 - i), s2.substr(i + 1, len - 1 - i))
							&& IsScramble(s1.substr(len - 1 - i, i + 1), s2.substr(0, i + 1)))
							return true;
					}
				}
			}

			return false;
		}

		static bool IsScramble2(const string & s1, const string & s2)
		{
			if (s1.length() != s2.length()) return false;
			if (s1.length() == 0) return true;

			map<pair<int, int>, map<pair<int, int>, bool>> scramble;

			function<bool(int, int, int, int)>
			isScramble = [&](int i1, int i2, int j1, int j2)->bool{
				// check s1[i1..i2] and s2[j1..j2]
				pair<int, int> pi = make_pair(i1, i2);
				pair<int, int> pj = make_pair(j1, j2);

				if (scramble.find(pi) != scramble.end() && scramble[pi].find(pj) != scramble[pi].end())
					return scramble[pi][pj];

				if (scramble.find(pi) == scramble.end())
					scramble[pi] = map<pair<int, int>, bool> { };

				if (scramble[pi].find(pj) == scramble[pi].end())
					scramble[pi][pj] = false;

				map<char, int> m1;
				map<char, int> m2;

				for (int i = i1, j = j1; i <= i2, j <= j2; i++, j++) {
					if (m1.find(s1[i]) == m1.end()) m1[s1[i]] = 1;
					else m1[s1[i]] += 1;
					if (m2.find(s2[j]) == m2.end()) m2[s2[j]] = 1;
					else m2[s2[j]] += 1;
					if (Equal(m1, m2)) {
						// s1[i1..i] and s2[j1..j] may be scramble
						if (j - j1 <= 1) {
							if (j == j2 || isScramble(i + 1, i2, j + 1, j2)) {
								scramble[pi][pj] = true;
								return true;
							}
						} else if (j < j2) {
							if (isScramble(i1, i, j1, j) && isScramble(i + 1, i2, j + 1, j2)) {
								scramble[pi][pj] = true;
								return true;
							}
						}
					}
				}

				m1.clear();
				m2.clear();

				for (int i = i2, j = j1; i >= i1, j <= j2; i--, j++) {
					if (m1.find(s1[i]) == m1.end()) m1[s1[i]] = 1;
					else m1[s1[i]] += 1;
					if (m2.find(s2[j]) == m2.end()) m2[s2[j]] = 1;
					else m2[s2[j]] += 1;
					if (Equal(m1, m2)) {
						// s1[i..i2] and s2[j1..j] may be scramble
						if (j - j1 <= 1) {
							if (j == j2 || isScramble(i1, i - 1, j + 1, j2)) {
								scramble[pi][pj] = true;
								return true;
							}
						} else if (j < j2) {
							if (isScramble(i1, i - 1, j + 1, j2) && isScramble(i, i2, j1, j)) {
								scramble[pi][pj] = true;
								return true;
							}
						}
					}
				}

				return false;
			};

			return isScramble(0, (int)s1.length() - 1, 0, (int)s2.length() - 1);
		}

		// Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
		// You should preserve the original relative order of the nodes in each of the two partitions.
		// For example,
		// Given 1->4->3->2->5->2 and x = 3,
		// return 1->2->2->4->3->5.
		static ListNode * PartitionList(ListNode * head, int x)
		{
			if (head == nullptr) return nullptr;

			// p is the last node less than x
			ListNode * p = head;

			// q is the last node no less than x
			ListNode * q = head;

			if (head->val >= x) {
				while (q->next != nullptr && q->next->val >= x) q = q->next;
				if (q->next == nullptr) {
					// every node is equal to or greater than x
					return head;
				}

				// q->next is less than x
				ListNode * t = q->next;
				q->next = t->next;
				t->next = head;
				head = t;

				p = head;
			} else {
				while (p->next != nullptr && p->next->val < x) p = p->next;
				if (p->next == nullptr) {
					// every node is less than x
					return head;
				}

				q = p->next;
			}

			// Now check if q->next should be moved to be after p

			while (q->next != nullptr) {
				if (q->next->val < x) {
					ListNode * t = q->next;
					q->next = t->next;
					t->next = p->next;
					p->next = t;
					p = t;
				} else {
					q = q->next;
				}
			}

			return head;
		}

		// Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing all ones and return its area.
		static int MaximalRectangle(vector<vector<char>> & matrix)
		{
			if (matrix.size() == 0 || matrix[0].size() == 0) return 0;
			bool foundOne = false;
			int imin = -1;
			int imax = -1;
			int jmin = -1;
			int jmax = -1;
			for (int i = 0; i < (int)matrix.size(); i++) {
				for (int j = 0; j < (int)matrix[i].size(); j++) {
					if (matrix[i][j] == 1) {
						if (foundOne) {
							if (i < imin) imin = i;
							if (i > imax) imax = i;
							if (j < jmin) jmin = j;
							if (j > jmax) jmax = j;
						} else {
							imin = i;
							imax = i;
							jmin = j;
							jmax = j;
							foundOne = true;
						}
					}
				}
			}

			if (!foundOne) return 0;

			int area = (imax - imin + 1) * (jmax - jmin + 1);
			return area;
		}

		// Given a 2D binary matrix filled with 0's and 1's,
		// find the largest rectangle full of ones and with a give point on its top-left corner,
		// return the rectangle area.
		static int MaximalRectangleAtPoint(vector<vector<char>> & matrix, int pi, int pj)
		{
			if (matrix.size() == 0 || matrix[0].size() == 0) return 0;
			if (pi < 0 || pi >= (int)matrix.size() || pj < 0 || pj >= (int)matrix[0].size()) return 0;
			if (matrix[pi][pj] != 1) return 0;

			int i = pi;
			int j = pj;

			while (j + 1 < (int)matrix[0].size() && matrix[i][j+1] == 1) j++;

			int maxj = j;
			int maxArea = j - pj + 1;

			while (i + 1 < (int)matrix.size() && matrix[i+1][pj] == 1) {
				i++;
				j = pj;
				while (j + 1 <= maxj && matrix[i][j+1] == 1 && matrix[i-1][j+1] == 1) j++;
				int area = (i - pi + 1) * (j - pj + 1);
				if (area > maxArea) maxArea = area;
				maxj = j;
			}

			return maxArea;
		}

		// Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle full of ones,
		// return its area.
		static int MaximalRectangleFullOnes(vector<vector<char>> & matrix)
		{
			if (matrix.size() == 0 || matrix[0].size() == 0) return 0;
			int maxArea = 0;
			for (int i = 0; i < (int)matrix.size(); i++) {
				for (int j = 0; j < (int)matrix[i].size(); j++) {
					if (matrix[i][j] == 1) {
						int area = MaximalRectangleAtPoint(matrix, i, j);
						if (area > maxArea) maxArea = area;
					}
				}
			}
			return maxArea;
		}

		// Given n non-negative integers representing the histogram's bar height
		// where the width of each bar is 1, find the area of largest rectangle in the histogram.
		// One example histogram has width of each bar 1, given height = [2,1,5,6,2,3].
		// The largest rectangle has area = 10 unit, which is under the 3rd and 4th columns.
		static int LargestRectangleInHistogram(vector<int> & height)
		{
			if (height.size() == 0) return 0;

			map<int, pair<int, int>> rec = { { 0, make_pair(0, height[0]) } };
			int maxArea = height[0];

			for (int i = 1; i < (int)height.size(); i++) {
				if (height[i] == 0) {
					rec.clear();
					continue;
				}

				for (map<int, pair<int, int>>::iterator it = rec.begin(); it != rec.end(); it++) {
					if (height[i] < it->second.second)
					{
						it->second.second = height[i];
					}

					it->second.first++;

					int area = (it->second.first - it->first + 1) * it->second.second;
					if (area > maxArea) {
						maxArea = area;
					}
				}

				if (height[i] > height[i-1]) {
					rec[i] = make_pair(i, height[i]);
					if (height[i] > maxArea) {
						maxArea = height[i];
					}
				}
			}

			return maxArea;
		}

		static int LargestRectangleInHistogram2(vector<int> & height)
		{
			if (height.size() == 0) return 0;

			int maxArea = 0;
			stack<int> rec;
			for (int i = 0; i < (int)height.size(); i++) {
				while (!rec.empty() && height[rec.top()] > height[i]) {
					int t = rec.top();
					rec.pop();
					int area = height[t] * (i - 1 - (rec.empty() ? -1 : rec.top()));
					if (area > maxArea) maxArea = area;
				}
				rec.push(i);
			}

			while (!rec.empty()) {
				int t = rec.top();
				rec.pop();
				int area = height[t] * ((int)height.size() - 1 - (rec.empty() ? -1 : rec.top()));
				if (area > maxArea) maxArea = area;
			}

			return maxArea;
		}

		// Given a sorted linked list, for each node delete all its duplicates,
		// such that each node has only one copy.
		// For example,
		// Given 1->2->3->3->4->4->5, return 1->2->3->4->5.
		// Given 1->1->1->2->3, return 1->2->3.
		static ListNode * DeleteDuplicates(ListNode * head)
		{
			if (head == nullptr) return nullptr;

			ListNode * p = head;
			while (p->next != nullptr) {
				if (p->val != p->next->val) {
					p = p->next;
				} else {
					ListNode * q = p->next;
					while (q != nullptr && q->val == p->val) {
						p->next = q->next;
						delete q;
						q = p->next;
					}
					if (q == nullptr) return head;
				}
			}

			return head;
		}

		// Given a sorted linked list, delete all nodes that have duplicate numbers,
		// leaving only distinct numbers from the original list.
		// For example,
		// Given 1->2->3->3->4->4->5, return 1->2->5.
		// Given 1->1->1->2->3, return 2->3.
		static ListNode * DeleteDuplicates2(ListNode * head)
		{
			if (head == nullptr) return nullptr;

			ListNode * p;

			while (head->next != nullptr && head->val == head->next->val) {
				int dup = head->val;
				while (head != nullptr && head->val == dup) {
					p = head;
					head = p->next;
					delete p;
				}

				if (head == nullptr) return nullptr;
			}

			if (head->next == nullptr) return head;

			p = head;
			ListNode * q = p->next;

			while (q->next != nullptr) {
				if (q->val != q->next->val) {
					p = q;
					q = p->next;
				} else {
					int dup = q->val;
					while (q != nullptr && q->val == dup) {
						p->next = q->next;
						delete q;
						q = p->next;
					}
					if (q == nullptr) return head;
				}
			}

			return head;
		}

		// Suppose a sorted array is rotated at some pivot unknown to you beforehand.
		// (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
		// You are given a target value to search. If found in the array return its index, otherwise return -1.
		// You may assume no duplicate exists in the array.
		static int SearchInRotatedSortedArray(int A[], int n, int target)
		{
			if (A == nullptr || n <= 0) return -1;

			function<int(int [], int, int, int)>
			search = [&](int a[], int l, int r, int t)->int{
				while (l <= r) {
					if (a[l] == t) return l;
					if (a[r] == t) return r;

					// l < m < r, if l + 1 < r
					// l = m < r, if l + 1 = r
					// l = m = r, if l = r
					int m = (l + r) >> 1;

					if (a[m] == t) return m;

					if (m == l) return -1;

					if (a[m] > a[l] && a[m] > a[r]) {
						if (a[l] < t && t < a[m]) r = m;
						else l = m;
					} else if (a[m] < a[l] && a[m] < a[r]) {
						if (a[m] < t && t < a[r]) l = m;
						else r = m;
					} else {
						// a[l] < a[m] < a[r]
						if (t < a[m]) r = m;
						else l = m;
					}
				}
				return -1;
			};

			return search(A, 0, n-1, target);
		}

		// Suppose a sorted array is rotated at some pivot unknown to you beforehand.
		// (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
		// You are given a target value to search. If found in the array return its index, otherwise return -1.
		// Duplicates are possible in the array.
		static int SearchInRotatedSortedArray2(int A[], int n, int target)
		{
			if (A == nullptr || n <= 0) return -1;

			function<int(int [], int, int, int)>
			search = [&](int a[], int l, int r, int t)->int{
				while (l <= r) {
					if (a[l] == t) return l;
					if (a[r] == t) return r;

					// l < m < r, if l + 1 < r
					// l = m < r, if l + 1 = r
					// l = m = r, if l = r
					int m = (l + r) >> 1;

					if (a[m] == t) return m;

					if (m == l) return -1;

					if (a[l] < a[m] && a[m] > a[r]) {
						if (a[l] < t && t < a[m]) r = m;
						else l = m;
					} else if (a[l] > a[m] && a[m] < a[r]) {
						if (a[m] < t && t < a[r]) l = m;
						else r = m;
					} else if (a[l] == a[m] && a[m] > a[r]) {
						l = m;
					} else if (a[l] > a[m] && a[m] == a[r]) {
						r = m;
					} else if (a[l] == a[m] && a[m] == a[r]) {
						int i = search(a, l, m, t) ;
						if (i == -1) i = search(a, m, r, t);
						return i;
					} else {
						// a[l] < a[m] < a[r]
						if (t < a[m]) r = m;
						else l = m;
					}
				}
				return -1;
			};

			return search(A, 0, n-1, target);
		}

		// Update a sorted array so that each element can occurr only once.
		// For example,
		// Given sorted array A = [1,1,1,2,2,3],
		// Your function should return length = 3, and A is now [1,2,3].
		static int RemoveDuplicates(int A[], int n)
		{
			if (A == nullptr || n <= 1) return n;

			int i = 0;
			int j = 1;

			while (j < n) {
				while (j < n && A[j] == A[i]) j++;
				if (j == n) break;
				if (i + 1 < j) A[i+1] = A[j];
				i++;
				j++;
			}

			return i+1;
		}

		// Update a sorted array so that each element can occurr no more than two times.
		// For example,
		// Given sorted array A = [1,1,1,2,2,3],
		// Your function should return length = 5, and A is now [1,1,2,2,3].
		static int RemoveDuplicates2(int A[], int n)
		{
			if (A == nullptr || n <= 2) return n;

			int i = 0;
			int j = 1;

			while (j < n) {
				if (i + 1 < j) A[i+1] = A[j];
				i++;
				j++;
				if (A[i-1] == A[i]) {
					while (j < n && A[j] == A[i]) j++;
				}
			}

			return i+1;
		}

		// Given a 2D board and a word, find if the word exists in the grid.
		// The word can be constructed from letters of sequentially adjacent cell,
		// where "adjacent" cells are those horizontally or vertically neighboring.
		// The same letter cell may not be used more than once.
		// For example,
		// Given board =
		// [
		//  ["ABCE"],
		//  ["SFCS"],
		//  ["ADEE"]
		// ]
		// word = "ABCCED", -> returns true,
		// word = "SEE", -> returns true,
		// word = "ABCB", -> returns false.
		static bool SearchWord(vector<vector<char>> & board, const string & word)
		{
			if (board.size() == 0 || board[0].size() == 0) return false;

			function<bool(vector<vector<char>> &, int, int, const string &, set<pair<int,int>> &)>
			search = [&](vector<vector<char>> & b, int i, int j, const string & s, set<pair<int,int>> & v)->bool{
				if (s.length() == 0) return true;
				if (i < 0 || i >= (int)b.size() || j < 0 || j >= (int)b[0].size()) return false;
				pair<int, int> p = make_pair(i, j);
				if (v.find(p) != v.end()) return false;
				if (b[i][j] != s[0]) return false;
				v.insert(p);
				if (search(b, i, j+1, s.substr(1), v)) return true;
				if (search(b, i+1, j, s.substr(1), v)) return true;
				if (search(b, i, j-1, s.substr(1), v)) return true;
				if (search(b, i-1, j, s.substr(1), v)) return true;
				v.erase(p);
				return false;
			};

			for (int i = 0; i < (int)board.size(); i++) {
				for (int j = 0; j < (int)board[0].size(); j++) {
					set<pair<int,int>> visited;
					if (search(board, i, j, word, visited)) return true;
				}
			}

			return false;
		}

		// Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
		// For example,
		// If n = 4 and k = 2, a solution is:
		// [
		//  [2,4],
		//  [3,4],
		//  [2,3],
		//  [1,2],
		//  [1,3],
		//  [1,4],
		// ]
		// Let s(i, j) be the solution of choosing j numbers out of {1, 2, ..., i}
		// then we need s(n, k).
		// s(n, k) = s(n-1, k-1) + s(n-1, k)
		static vector<vector<int>> Combinations(int n, int k)
		{
			if (n < k) return vector<vector<int>> { { } };
			function<void(int, int, map<pair<int, int>, vector<vector<int>>> &)>
			combine = [&](int i, int j, map<pair<int, int>, vector<vector<int>>> & s){
				pair<int, int> p = make_pair(i, j);
				s[p] = vector<vector<int>> { };

				if (i <= 0 || j <= 0 || i < j) {
					s[p].push_back(vector<int> { });
					return;
				}

				if (i == j) {
					vector<int> v;
					for (int k = 1; k <= j; k++) {
						v.push_back(k);
					}
					s[p].push_back(v);
					return;
				}

				pair<int, int> q1 = make_pair(i-1, j-1);
				if (s.find(q1) == s.end()) combine(i-1, j-1, s);
				for_each (s[q1].begin(), s[q1].end(), [&](vector<int> & v){
					vector<int> ex(v.begin(), v.end());
					ex.push_back(i);
					s[p].push_back(ex);
				});

				pair<int, int> q2 = make_pair(i-1, j);
				if (s.find(q2) == s.end()) combine(i-1, j, s);
				for_each (s[q2].begin(), s[q2].end(), [&](vector<int> & v){
					s[p].push_back(v);
				});
			};

			map<pair<int, int>, vector<vector<int>>> sets;
			combine(n, k, sets);
			pair<int, int> p = make_pair(n, k);
			return sets[p];
		}

		// Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
		// For example,
		// If n = 4 and k = 2, a solution is:
		// [
		//  [2,4],
		//  [3,4],
		//  [2,3],
		//  [1,2],
		//  [1,3],
		//  [1,4],
		// ]
		// Let s(i, j) be the solution of choosing j numbers out of {1, 2, ..., i}
		// then we need s(n, k).
		// s(n, k) = s(n-1, k-1) + s(n-1, k)
		//
		// s(1,1)
		// s(2,1)     s(2,2)
		// s(3,1)     s(3,2)     s(3,3)
		// s(4,1)     s(4,2)     s(4,3)     s(4,4)
		// ......     ......     ......     ......
		// ......     ......     ......     ......  ......
		// ......     ......     ......     ......  ...... ......
		// ......     ......     ......     ......  ...... s(k,k-1)   s(k,k)
		// ......     ......     ......     ......  ...... s(k+1,k-1) s(k+1,k)
		// ......     ......     ......     ......  ...... ......     ......
		// ......     ......     ......     ......  ...... ......     ......
		// s(n-k+1,1) s(n-k+1,2) ......     ......  ...... ......     ......
		//            s(n-k+2,2) ......     ......  ...... ......     ......
		//                       s(n-k+2,3) ......  ...... ......     ......
		//                                  ......  ...... ......     ......
		//                                          ...... ......     ......
		//                                                 s(n-1,k-1) s(n-1,k)
		//                                                            s(n,k)
		static vector<vector<int>> Combinations2(int n, int k)
		{
			if (n <= 0 || k <= 0 || n < k) return vector<vector<int>> { { } };

			vector<vector<vector<int>>> s(n-k+1, vector<vector<int>> { { } });

			for (int j = 1; j <= k; j++) {
				s[0][0].push_back(j);
				for (int i = 1; i <= n-k; i++) {
					for_each (s[i].begin(), s[i].end(), [&](vector<int> & v){
						v.push_back(i+j);
					});
					for_each (s[i-1].begin(), s[i-1].end(), [&](vector<int> & v){
						s[i].push_back(v);
					});
				}
			}

			return s[n-k];
		}

		// Minimum Window Substring
		// Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).
		// For example,
		// S = "ADOBECODEBANC"
		// T = "ABC"
		// Minimum window is "BANC".
		// Note:
		// If there is no such window in S that covers all characters in T, return the emtpy string "".
		// If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.
		static string MinWindow(const string & s, const string & t)
		{
			if (s.length() == 0 || t.length() == 0 || s.length() < t.length()) return "";

			map<char, int> countT;
			for (size_t i = 0; i < t.length(); i++) {
				if (countT.find(t[i]) == countT.end()) countT[t[i]] = 1;
				else countT[t[i]] += 1;
			}

			// c1 count should be no less than c2 count
			auto compare = [&](map<char, int> & c1, map<char, int> & c2)->bool{
				if (c1.size() != c2.size()) return false;
				for (map<char, int>::iterator it = c1.begin(); it != c1.end(); it++) {
					if (c2.find(it->first) == c2.end()) return false;
					if (c2[it->first] > it->second) return false;
				}
				return true;
			};

			map<char, int> countS;
			queue<pair<char, int>> indices;
			int begin = -1;
			int end = (int)s.length();
			for (int i = 0; i < (int)s.length(); i++) {
				if (countT.find(s[i]) != countT.end()) {
					if (countS.find(s[i]) == countS.end()) countS[s[i]] = 1;
					else countS[s[i]] += 1;

					indices.push(make_pair(s[i], i));

					while (countS[indices.front().first] > countT[indices.front().first]) {
						countS[indices.front().first] -= 1;
						indices.pop();
					}

					if (compare(countS, countT)) {
						if (i - indices.front().second < end - begin) {
							begin = indices.front().second;
							end = i;
						}
					}
				}
			}

			if (begin == -1) return "";
			else return s.substr(begin, end - begin + 1);
		}

		static string MinWindow2(const string & s, const string & t)
		{
			if (s.length() == 0 || t.length() == 0 || s.length() < t.length()) return "";

			map<char, int> countT;
			for (size_t i = 0; i < t.length(); i++) {
				if (countT.find(t[i]) == countT.end()) countT[t[i]] = 1;
				else countT[t[i]] += 1;
			}

			map<char, int> countS;
			int total = 0;
			queue<pair<char, int>> indices;
			int begin = -1;
			int end = (int)s.length();
			for (int i = 0; i < (int)s.length(); i++) {
				if (countT.find(s[i]) != countT.end()) {
					if (countS.find(s[i]) == countS.end()) countS[s[i]] = 1;
					else countS[s[i]] += 1;

					if (countS[s[i]] <= countT[s[i]]) total++;

					indices.push(make_pair(s[i], i));

					while (countS[indices.front().first] > countT[indices.front().first]) {
						countS[indices.front().first] -= 1;
						indices.pop();
					}

					if (total == (int)t.length()) {
						if (i - indices.front().second < end - begin) {
							begin = indices.front().second;
							end = i;
						}
					}
				}
			}

			if (begin == -1) return "";
			else return s.substr(begin, end - begin + 1);
		}

		// An array contains integers 0, 1, 2. Sort it.
		static void SortColors(int A[], int n)
		{
			if (A == nullptr || n <= 1) return;

			int i = 0;
			int j = 0;
			int k = n - 1;
			int t;
			while (i < k) {
				while (A[i] == 0) i++;
				while (A[k] == 2) k--;
				if (i >= k) return;
				if (A[i] > A[k]) {
					t = A[i];
					A[i] = A[k];
					A[k] = t;
				} else {
					// A[i] == A[k] == 1
					if (j <= i) j = i+1;
					while (A[j] == 1) j++;
					if (j >= k) return;
					if (A[j] == 0) {
						t = A[i];
						A[i] = A[j];
						A[j] = t;
					} else {
						t = A[k];
						A[k] = A[j];
						A[j] = t;
					}
				}
			}
		}

		// Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
		//   Integers in each row are sorted from left to right.
		//   The first integer of each row is greater than the last integer of the previous row.
		// For example,
		// Consider the following matrix:
		// [
		//  [1,   3,  5,  7],
		//  [10, 11, 16, 20],
		//  [23, 30, 34, 50]
		// ]
		// Given target = 3, return true.
		static bool SearchMatrix(vector<vector<int>> & matrix, int target)
		{
			if (matrix.size() == 0 || matrix[0].size() == 0) return false;

			int l = 0;
			int h = matrix.size() - 1;
			int m;
			while (l <= h) {
				m = l + ((h - l) >> 1);
				if (target == matrix[m][0]) return true;
				if (target < matrix[m][0]) {
					if (l == m) return false;
					h = m - 1;
				} else {
					if (l == m) {
						if (target >= matrix[h][0]) m = h;
						break;
					}

					l = m;
				}
			}

			l = 0;
			h = matrix[m].size() - 1;
			int n;
			while (l <= h) {
				n = l + ((h - l) >> 1);
				if (target == matrix[m][n]) return true;
				if (target < matrix[m][n]) {
					if (l == n) break;
					h = n - 1;
				} else {
					if (n == h) break;
					l = n + 1;
				}
			}

			return false;
		}

		// Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.
		static void SetMatrixZeroes(vector<vector<int> > & matrix)
		{
			if (matrix.size() == 0 || matrix[0].size() == 0) return;

			bool firstRowHasZero = false;
			for (int j = 0; j < (int)matrix[0].size(); j++) {
				if (matrix[0][j] == 0) {
					firstRowHasZero = true;
					break;
				}
			}

			bool firstColumnHasZero = false;
			for (int i = 0; i < (int)matrix.size(); i++) {
				if (matrix[i][0] == 0) {
					firstColumnHasZero = true;
					break;
				}
			}

			for (int i = 1; i < (int)matrix.size(); i++) {
				for (int j = 1; j < (int)matrix[i].size(); j++) {
					if (matrix[i][j] == 0) {
						matrix[i][0] = 0;
						matrix[0][j] = 0;
					}
				}
			}

			for (int i = 1; i < (int)matrix.size(); i++) {
				if (matrix[i][0] == 0) {
					for (int j = 1; j < (int)matrix[i].size(); j++) {
						matrix[i][j] = 0;
					}
				}
			}

			for (int j = 1; j < (int)matrix[0].size(); j++) {
				if (matrix[0][j] == 0) {
					for (int i = 1; i < (int)matrix.size(); i++) {
						matrix[i][j] = 0;
					}
				}
			}

			if (firstRowHasZero) {
				for (int j = 0; j < (int)matrix[0].size(); j++) {
					matrix[0][j] = 0;
				}
			}

			if (firstColumnHasZero) {
				for (int i = 0; i < (int)matrix.size(); i++) {
					matrix[i][0] = 0;
				}
			}
		}

		// Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2.
		// (each operation is counted as 1 step.)
		// You have the following 3 operations permitted on a word:
		//  a) Insert a character
		//  b) Delete a character
		//  c) Replace a character
		static int MinDistance(const string & word1, const string & word2)
		{
			function<int(const string &, int, const string &, int, map<pair<int,int>, int> &)>
			distance = [&](const string & w1, int i, const string & w2, int j, map<pair<int,int>, int> & d) -> int {
				pair<int, int> p = make_pair(i, j);
				if (d.find(p) == d.end()) {
					if (i == (int)w1.length()) {
						d[p] = (int)w2.length() - j;
					} else if (j == (int)w2.length()) {
						d[p] = (int)w1.length() - i;
					} else if (w1[i] == w2[j]) {
						d[p] = distance(w1, i+1, w2, j+1, d);
					} else {
						int ins = distance(w1, i, w2, j+1, d);
						int rep = distance(w1, i+1, w2, j+1, d);
						int del = distance(w1, i+1, w2, j, d);
						int min = ins;
						if (rep < min) min = rep;
						if (del < min) min = del;
						d[p] = 1 + min;
					}
				}
				return d[p];
			};

			map<pair<int,int>, int> d;
			return distance(word1, 0, word2, 0, d);
		}

		// Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2.
		// (each operation is counted as 1 step.)
		// You have the following 3 operations permitted on a word:
		//  a) Insert a character
		//  b) Delete a character
		//  c) Replace a character
		// d[i,j]
		//     j 0 1 2 3 ...... n-1
		// i 0
		//   1
		//   2
		//   .
		//   m-1
		//
		// d[m-1][n-1] = 0,                                             if w1[m-1] == w2[n-1]
		//               1,                                             if w1[m-1] != w2[n-1]
		// d[m-1][j]   = n - 1 - j,                                     if w1[m-1] == w2[j]
		//               1 + min { n - 1 - j, d[m-1][j+1] },            if w1[m-1] != w2[j]
		// d[i][n-1]   = m - 1 - i,                                     if w1[i] == w2[n-1]
		//               1 + min { m - 1 - i, d[i+1][n-1] },            if w1[i] != w2[n-1]
		// d[i][j]     = d[i+1][j+1],                                   if w1[i] == w2[j]
		//               1 + min { d[i][j+1], d[i+1][j+1], d[i+1][j] }, if w1[i] != w2[j]
		static int MinDistance2(const string & word1, const string & word2)
		{
			int m = word1.length();
			int n = word2.length();

			if (m == 0) return n;
			if (n == 0) return m;

			vector<vector<int>> d(m, vector<int>(n, 0));

			d[m-1][n-1] = word1[m-1] == word2[n-1] ? 0 : 1;

			for (int j = n-2; j >= 0; j--) {
				if (word1[m-1] == word2[j]) {
					d[m-1][j] = n - 1 - j;
				} else {
					d[m-1][j] = n - 1 - j;
					if (d[m-1][j+1] < d[m-1][j]) d[m-1][j] = d[m-1][j+1];
					d[m-1][j] += 1;
				}
			}

			for (int i = m-2; i >= 0; i--) {
				if (word1[i] == word2[n-1]) {
					d[i][n-1] =  m - 1 - i;
				} else {
					d[i][n-1] = m - 1 - i;
					if (d[i+1][n-1] < d[i][n-1]) d[i][n-1] = d[i+1][n-1];
					d[i][n-1] += 1;
				}
			}

			for (int i = m - 2; i >= 0; i--) {
				for (int j = n - 2; j >= 0; j--) {
					if (word1[i] == word2[j]) {
						d[i][j] = d[i+1][j+1];
					} else {
						d[i][j] = d[i][j+1];
						if (d[i+1][j+1] < d[i][j]) d[i][j] = d[i+1][j+1];
						if (d[i+1][j] < d[i][j]) d[i][j] = d[i+1][j];
						d[i][j] += 1;
					}
				}
			}

			return d[0][0];
		}

		// Given an absolute path for a file (Unix-style), simplify it.
		// For example,
		// path = "/home/", => "/home"
		// path = "/a/./b/../../c/", => "/c"
		static string SimplifyPath(string path)
		{
			int len = path.length();
			if (len == 0) return "";
			vector<string> tokens;
			int i = 0;
			while (i < len) {
				while (i < len && path[i] == '/') i++;
				if (i == len) break;
				if (path[i] == '.') {
					if (i + 1 == len) break;
					if (path[i+1] == '/') {
						i += 2;
						continue;
					} else if (path[i+1] == '.') {
						if (i + 2 == len ||	path[i+2] == '/') {
							if (!tokens.empty()) {
								tokens.pop_back();
							}
							i += 3;
							continue;
						}
					}
				}
				string token;
				int j = i;
				while (j < len && path[j] != '/') {
					token.append(1, path[j]);
					j++;
				}
				tokens.push_back(token);
				i = j;
			}
			string output;
			if (tokens.size() == 0) {
				output.append(1, '/');
			} else {
				for_each (tokens.begin(), tokens.end(), [&](string & t){
					output.append(1, '/');
					output.append(t.begin(), t.end());
				});
			}
			return output;
		}

		// Compute and return the square root of x.
		static int Sqrt(int x)
		{
			if (x < 0) throw invalid_argument("x cannot be negative");
			if (x < 2) return x;
			long long l = 1;
			long long h = (x >> 1) + 1;
			while (l <= h) {
				long long m = l + ((h - l) >> 1);
				long long s = m * m;
				if (x == s) return (int)m;
				else if (x < s) {
					if (l == m) break;
					h = m;
				} else {
					if (l == m) {
						s = h * h;
						if (x == s) return (int)h;
						return (int)m;
					} else {
						l = m;
					}
				}
			}
			throw runtime_error("sqrt(x) cannot be found");
		}

		// Given an array of words and a length L, format the text such that each line has exactly L characters
		// and is fully (left and right) justified.
		// You should pack your words in a greedy approach; that is, pack as many words as you can in each line.
		// Pad extra spaces ' ' when necessary so that each line has exactly L characters.
		// Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not
		// divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.
		// For the last line of text, it should be left justified and no extra space is inserted between words.
		// For example,
		// words: ["This", "is", "an", "example", "of", "text", "justification."]
		// L: 16.
		// Return the formatted lines as:
		// [
		//   "This    is    an",
		//   "example  of text",
		//   "justification.  "
		// ]
		// Note: Each word is guaranteed not to exceed L in length.
		// Corner Cases:
		// A line other than the last line might contain only one word. What should you do in this case?
		// In this case, that line should be left-justified.
		static vector<string> TextJustification(vector<string> & words, int L)
		{
			if (words.size() == 0) return vector<string> { };
			vector<string> output;
			int i = 0;
			int j = 0;
			int count = (int)words.size();
			int len = 0;
			while (i < count && j < count) {
				while (j < count && len + (int)words[j].length() + j - i <= L) {
					len += words[j].length();
					j++;
				}
				if (j == count) {
					// last line with words[i..j-1]
					string line;
					for (int k = i; k < j; k++) {
						if (k != i) line.append(1, ' ');
						line.append(words[k]);
					}
					int extra = L - len - (j - 1 - i);
					if (extra > 0) line.append(extra, ' ');
					output.push_back(line);
					break;
				} else {
					// one line with words[i..j-1]
					string line(words[i]);
					int totalSpaces = L - len;
					int intervals = j - 1 - i;
					if (intervals == 0) {
						line.append(totalSpaces, ' ');
					} else {
						int spaces = totalSpaces / intervals;
						int extra = totalSpaces % intervals;
						for (int k = i + 1; k <= i + extra; k++) {
							line.append(spaces + 1, ' ');
							line.append(words[k]);
						}
						for (int k = i + extra + 1; k < j; k++) {
							line.append(spaces, ' ');
							line.append(words[k]);
						}
					}
					output.push_back(line);
					i = j;
					len = 0;
				}
			}
			return output;
		}

		// Given a non-negative number represented as an array of digits, plus one to the number.
		// The digits are stored such that the most significant digit is at the head of the list.
		static vector<int> PlusOne(vector<int> & digits)
		{
			vector<int> output = { };
			int len = digits.size();
			if (len == 0) return output;
			int carry = 0;
			int d = (digits[len-1] + 1) % 10;
			if (d == 0) carry = 1;
			output.insert(output.begin(), d);
			for (int i = digits.size() - 2; i >= 0; i--) {
				d = digits[i];
				if (carry == 1) {
					d = (d + 1) % 10;
					if (d == 0) carry = 1;
					else carry = 0;
				}
				output.insert(output.begin(), d);
			}
			if (carry == 1) output.insert(output.begin(), 1);
			return output;
		}

		// Validate if a given string is numeric. Some examples:
		// "0" => true
		// " 0.1 " => true
		// "abc" => false
		// "1 a" => false
		// "2e10" => true
		static bool IsNumber(const char * s)
		{
			if (s == nullptr || *s == '\0') return false;
			while (*s == ' ') s++;
			if (*s == '\0') return false;
			if (*s != '+' && *s != '-' && *s != '.' && (*s < '0' || *s > '9')) return false;
			if ((*s == '+' || *s == '-') && *(s+1) == '.' && (*(s+2) == '\0' || *(s+2) == ' ')) return false;
			bool foundDot = *s == '.';
			if (foundDot && (*(s+1) < '0' || *(s+1) > '9')) return false;
			bool foundE = false;
			s++;
			while (*s != '\0' && *s != ' ') {
				switch (*s) {
				case '+':
				case '-':
					if (*(s-1) != 'e' && *(s-1) != 'E') return false;
					if (*(s+1) < '0' || *(s+1) > '9') return false;
					break;
				case '.':
					if (foundE || foundDot) return false;
					foundDot = true;
					if (*(s+1) != '\0' && *(s+1) != ' ' && *(s+1) != 'e'  && *(s+1) != 'E' && (*(s+1) < '0' || *(s+1) > '9')) return false;
					break;
				case 'e':
				case 'E':
					if (foundE) return false;
					foundE = true;
					if (*(s-1) != '.' && (*(s-1) < '0' || *(s-1) > '9')) return false;
					if (*(s+1) != '+' && *(s+1) != '-' && (*(s+1) < '0' || *(s+1) > '9')) return false;
					break;
				default:
					if (*s < '0' || *s > '9') return false;
					break;
				}
				s++;
			}
			while (*s == ' ') s++;
			if (*s == '\0') return true;
			else return false;
		}

		// Given two binary strings, return their sum (also a binary string). For example,
		// a = "11"
		// b = "1"
		// Return "100".
		static string AddBinaryString(const string & a, const string & b)
		{
			if (a.length() == 0) return b;
			if (b.length() == 0) return a;
			int i = a.length() - 1;
			int j = b.length() - 1;
			int carry = 0;
			string c;
			while (i >= 0 && j >= 0) {
				if (a[i] == '0' && b[j] == '0') {
					if (carry == 0) {
						c.insert(0, 1, '0');
					} else {
						c.insert(0, 1, '1');
						carry = 0;
					}
				} else if (a[i] == '0' && b[j] == '1' || a[i] == '1' && b[j] == '0') {
					c.insert(0, 1, carry == 0 ? '1' : '0');
				} else if (a[i] == '1' && b[j] == '1') {
					if (carry == 0) {
						c.insert(0, 1, '0');
						carry = 1;
					} else {
						c.insert(0, 1, '1');
					}
				}
				i--;
				j--;
			}
			while (i >= 0) {
				if (carry == 0) {
					c.insert(0, a, 0, i+1);
					break;
				} else {
					if (a[i] == '0') {
						c.insert(0, 1, '1');
						carry = 0;
					} else {
						c.insert(0, 1, '0');
					}
					i--;
				}
			}
			while (j >= 0) {
				if (carry == 0) {
					c.insert(0, b, 0, j+1);
					break;
				} else {
					if (b[j] == '0') {
						c.insert(0, 1, '1');
						carry = 0;
					} else {
						c.insert(0, 1, '0');
					}
					j--;
				}
			}

			if (carry == 1) c.insert(0, 1, '1');
			return c;
		}

		static ListNode * MergeSortedLists(ListNode * l1, ListNode * l2)
		{
			if (l1 == nullptr) return l2;
			if (l2 == nullptr) return l1;

			ListNode * head = l1;
			if (l1->val > l2->val) {
				head = l2;
				l2 = l2->next;
			} else {
				l1 = l1->next;
			}

			ListNode * p = head;

			while (l1 != nullptr && l2 != nullptr) {
				if (l1->val <= l2->val) {
					if (p->next != l1) p->next = l1;
					p = l1;
					l1 = p->next;
				} else {
					if (p->next != l2) p->next = l2;
					p = l2;
					l2 = p->next;
				}
			}

			ListNode * q = l1 == nullptr ? l2 : l1;
			if (q != nullptr && p->next != q) p->next = q;

			return head;
		}

		// Given a m x n grid filled with non-negative numbers, find a path from top left to
		// bottom right which minimizes the sum of all numbers along its path.
		// Note: You can only move either down or right at any point in time.
		static int MinPathSum(vector<vector<int>> & grid)
		{
			if (grid.size() == 0 && grid[0].size() == 0) return 0;
			vector<vector<int>> sum(grid.size(), vector<int>(grid[0].size(), 0));
			sum[0][0] = grid[0][0];
			int i = 0;
			int j = 0;
			for (j = 1; j < (int)grid[0].size(); j++) {
				sum[0][j] = sum[0][j-1] + grid[0][j];
			}
			for (i = 1; i < (int)grid.size(); i++) {
				sum[i][0] = sum[i-1][0] + grid[i][0];
			}
			for (i = 1; i < (int)grid.size(); i++) {
				for (j = 1; j < (int)grid[i].size(); j++) {
					sum[i][j] = grid[i][j] + min(sum[i][j-1], sum[i-1][j]);
				}
			}
			return sum[i-1][j-1];
		}

		// Given a m x n grid filled with non-negative numbers, find a path from top left to
		// bottom right which minimizes the sum of all numbers along its path.
		// Note: You can only move either down or right at any point in time.
		static int MinPathSum2(vector<vector<int>> & grid)
		{
			if (grid.size() == 0 && grid[0].size() == 0) return 0;
			vector<int> sum(grid[0].size(), 0);
			sum[0] = grid[0][0];
			int i = 0;
			int j = 0;
			for (j = 1; j < (int)grid[0].size(); j++) {
				sum[j] = sum[j-1] + grid[0][j];
			}
			for (i = 1; i < (int)grid.size(); i++) {
				sum[0] = sum[0] + grid[i][0];
				for (j = 1; j < (int)grid[i].size(); j++) {
					sum[j] = grid[i][j] + min(sum[j-1], sum[j]);
				}
			}
			return sum[j-1];
		}

		// A robot is located at the top-left corner of a m x n grid.
		// The robot can only move either down or right at any point in time. The robot is trying to
		// reach the bottom-right corner of the grid.
		// How many possible unique paths are there?
		static int UniquePaths(int m, int n)
		{
			if (m <= 0 || n <= 0) return 0;
			vector<int> sum(n, 1);
			for (int i = m - 2; i >= 0; i--) {
				for (int j = n - 2; j >= 0; j--) {
					sum[j] += sum[j+1];
				}
			}
			return sum[0];
		}

		// A robot is located at the top-left corner of a m x n grid.
		// The robot can only move either down or right at any point in time. The robot is trying to
		// reach the bottom-right corner of the grid.
		// Some obstacles are added to the grids.
		// An obstacle and empty space is marked as 1 and 0 respectively in the grid.
		// How many possible unique paths are there?
		static int UniquePathsWithObstacles(vector<vector<int> > & obstacleGrid)
		{
			int m = obstacleGrid.size();
			if (m == 0) return 0;
			int n = obstacleGrid[0].size();
			if (n == 0) return 0;
			if (obstacleGrid[m-1][n-1] == 1) return 0;
			vector<int> sum(n, 0);
			sum[n-1] = 1;
			for (int j = n-2; j >= 0; j--) {
				sum[j] = obstacleGrid[m-1][j] == 1 ? 0 : sum[j+1];
			}
			for (int i = m - 2; i >= 0; i--) {
				sum[n-1] = obstacleGrid[i][n-1] == 1 ? 0 : sum[n-1];
				for (int j = n - 2; j >= 0; j--) {
					sum[j] = obstacleGrid[i][j] == 1 ? 0 : (sum[j] + sum[j+1]);
				}
			}
			return sum[0];
		}

		// Given a list, rotate the list to the right by k places, where k is non-negative. For example:
		// Given 1->2->3->4->5->NULL and k = 2,
		// return 4->5->1->2->3->NULL.
		static ListNode * RotateRight(ListNode * head, int k)
		{
			if (head == nullptr || k <= 0) return head;
			ListNode * p = head;
			ListNode * q = head;
			int i = 0;
			while (i < k && q->next != nullptr) {
				q = q->next;
				i++;
			}
			if (q->next == nullptr) {
				int l = i + 1;
				k = k % l;
				if (k == 0) return head;
				i = 0;
				q = head;
				while (i < k && q->next != nullptr) {
					q = q->next;
					i++;
				}
			}
			while (q->next != nullptr) {
				q = q->next;
				p = p->next;
			}
			q->next = head;
			head = p->next;
			p->next = nullptr;
			return head;
		}

		// The set [1,2,3,��,n] contains a total of n! unique permutations.
		// By listing and labeling all of the permutations in order,
		// We get the following sequence (ie, for n = 3):
		// 1."123"
		// 2."132"
		// 3."213"
		// 4."231"
		// 5."312"
		// 6."321"
		// Given n and k, return the k-th permutation sequence.
		// Note: Given n will be between 1 and 9 inclusive.
		static string GetPermutation(int n, int k)
		{
			if (n <= 0 || k <= 0) return string();
			int i = 1; // Count number of digits
			int m = 1; // Count number of permutations of i digits, i.e. i!
			while (m < k && i < n) {
				i++;
				m *= i;
			}
			if (m < k) return string(); // k > n!
			// 1 2 3 ...... n-i n-i+1 n-i+2 ...... n-1 n
			// ~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~~~~~~~
			//     not permute         permute
			string output;
			for (int j = 1; j <= n - i; j++) {
				output.append(1, '0' + j);
			}

			vector<int> permute;
			for (int j = n-i+1; j <= n; j++) {
				permute.push_back(j);
			}

			while (i > 0) {
				if (i == 1) {
					// k = 1 since k <= m = i! = 1
					output.append(1, '0' + permute[permute.size()-1]);
					break;
				} else if (i == 2) {
					if (k == 1) {
						output.append(1, '0' + permute[permute.size()-2]);
						output.append(1, '0' + permute[permute.size()-1]);
					} else { // k = 2
						output.append(1, '0' + permute[permute.size()-1]);
						output.append(1, '0' + permute[permute.size()-2]);
					}
					break;
				}
				// Permute 1 2 3 4 5 ...... i-1 i, will get i ranges determined by the first digit
				//   1 ......
				//   1 ......
				//   2 ......
				//   2 ......
				//   ......
				//   ......
				//   i-1 ......
				//   i-1 ......
				//   i ......
				//   i ......
				m = m / i; // Count permutations per range
				int j = (k - 1) / m + 1; // Get the range index which k falls into
				// 1 2 3 4 5 ... j-1 j j+1 ... i-1 i
				// j 1 2 3 4 5 ... j-1 j+1 ... i-1 i
				int t = permute[j-1];
				permute.erase(permute.begin() + j - 1);
				output.append(1, '0' + t);
				i--; // Get the i-th range
				k = ((k - 1) % m) + 1; // Get the index in the i-th range
			}

			return output;
		}

		// Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.
		// For example,
		// Given the following matrix:
		// [
		//  [ 1, 2, 3 ],
		//  [ 4, 5, 6 ],
		//  [ 7, 8, 9 ]
		// ]
		// You should return [1,2,3,6,9,8,7,4,5].
		static vector<int> SpiralOrder(vector<vector<int>> & matrix)
		{
			vector<int> o;
			int v = matrix.size();
			if (v == 0) return o;
			int h = matrix[0].size();
			if (h == 0) return o;
			int i = 0;
			int j = -1;
			int d = 0;
			while (h > 0 && v > 0) {
				d = d % 4;
				if (d == 0) {
					for (int k = 1; k <= h; k++) {
						j++;
						o.push_back(matrix[i][j]);
					}
					v--;
					d++;
				} else if (d == 1) {
					for (int k = 1; k <= v; k++) {
						i++;
						o.push_back(matrix[i][j]);
					}
					h--;
					d++;
				} else if (d == 2) {
					for (int k = 1; k <= h; k++) {
						j--;
						o.push_back(matrix[i][j]);
					}
					v--;
					d++;
				} else {
					for (int k = 1; k <= v; k++) {
						i--;
						o.push_back(matrix[i][j]);
					}
					h--;
					d++;
				}
			}
			return o;
		}

		// Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.
		// For example,
		// Given n = 3,
		// You should return the following matrix:
		// [
		//  [ 1, 2, 3 ],
		//  [ 8, 9, 4 ],
		//  [ 7, 6, 5 ]
		// ]
		static vector<vector<int>> SpiralOrderMatrix(int n)
		{
			if (n == 0) return vector<vector<int>>();
			if (n < 0) n = -n;
			vector<vector<int>> o(n, vector<int>(n, 0));
			int h = n;
			int v = n;
			int i = 0;
			int j = -1;
			int t = 1;
			int d = 0;
			while (h > 0 && v > 0) {
				d = d % 4;
				switch (d) {
				case 0:
					for (int k = 1; k <= h; k++) {
						j++;
						o[i][j] = t++;
					}
					v--;
					d++;
					break;
				case 1:
					for (int k = 1; k <= v; k++) {
						i++;
						o[i][j] = t++;
					}
					h--;
					d++;
					break;
				case 2:
					for (int k = 1; k <= h; k++) {
						j--;
						o[i][j] = t++;
					}
					v--;
					d++;
					break;
				default:
					for (int k = 1; k <= v; k++) {
						i--;
						o[i][j] = t++;
					}
					h--;
					d++;
					break;
				}
			}
			return o;
		}

		// Given a string s consists of upper/lower-case alphabets and empty space characters ' ',
		// return the length of last word in the string.
		// If the last word does not exist, return 0.
		// Note: A word is defined as a character sequence consists of non-space characters only.
		// For example,
		// Given s = "Hello World",
		// return 5.
		static int LengthOfLastWord(const char * s)
		{
			if (*s == '\0') return 0;
			while (*s == ' ') s++;
			int i = 0;
			while (*s != '\0') {
				while (*s != '\0' && *s != ' ') {
					i++;
					s++;
				}
				while (*s == ' ') s++;
				if (*s != '\0') i = 0;
			}
			return i;
		}

		struct Interval {
			int start;
			int end;
			Interval() : start(0), end(0) {}
			Interval(int s, int e) : start(s), end(e) {}
		};

		// It will produce Runtime Error simply because you provide the sort() with a wrong comparator.
		// 1.A correct comparator should have determined behavior, i.e. return the same result on same input.
		// 2.The result should be transitive, i.e., if you return true for a<b and b<c, you should return true for a<c
		// 3.The result should not contain conflicts, e.g., if you return true for a<b, you should return false for b<a
		// 4.return false for both a<b and b<a will means that a == b.
		// Violating the above rules and trying to pass an invalid comparator to sort() will result in undefined behavior, usually crash.
		static bool IntervalLess(const Interval & i1, const Interval & i2)
		{
			if (i1.start < i2.start) return true;
			if (i1.start == i2.start) {
				// cannot use <=, otherwise violates 3.
				return i1.end < i2.end;
			}
			return false;
		}

		// Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
		// Example 1:
		// Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
		// Example 2:
		// Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].
		// This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
		static vector<Interval> InsertMergeInterval(vector<Interval> & intervals, Interval newInterval)
		{
			vector<Interval> output;
			for_each (intervals.begin(), intervals.end(), [&](Interval i){
				if (i.end < newInterval.start || newInterval.end < i.start) {
					output.push_back(i);
				} else {
					newInterval.start = min(newInterval.start, i.start);
					newInterval.end = max(newInterval.end, i.end);
				}
			});
			output.push_back(newInterval);
			return output;
		}

		// Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
		// You may assume that the intervals were initially sorted according to their start times.
		// Example 1:
		// Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
		// Example 2:
		// Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].
		// This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
		static vector<Interval> InsertMergeSortedInterval(vector<Interval> & intervals, Interval newInterval)
		{
			vector<Interval> output;
			int len = intervals.size();
			int i = 0;
			while (i < len && intervals[i].end < newInterval.start) output.push_back(intervals[i++]);
			output.push_back(newInterval);
			int j = i;
			while (j < len && output[i].end >= intervals[j].start) {
				output[i].start = min(output[i].start, intervals[j].start);
				output[i].end = max(output[i].end, intervals[j].end);
				j++;
			}
			while (j < len) output.push_back(intervals[j++]);
			return output;
		}

		// Given a collection of intervals, merge all overlapping intervals. For example,
		// Given [1,3],[2,6],[8,10],[15,18],
		// return [1,6],[8,10],[15,18].
		static vector<Interval> MergeIntervals(vector<Interval> & intervals)
		{
			vector<Interval> output;
			int len = intervals.size();
			if (len == 0) return output;
			sort(intervals.begin(), intervals.end(), IntervalLess);
			output.push_back(intervals[0]);
			int i = 0;
			for (int j = 1; j < len; j++) {
				if (output[i].end < intervals[j].start) {
					output.push_back(intervals[j]);
					i++;
				} else {
					output[i].start = min(output[i].start, intervals[j].start);
					output[i].end = max(output[i].end, intervals[j].end);
				}
			}
			return output;
		}

		// Jump Game
		// Given an array of non-negative integers, you are initially positioned at the first index of the array.
		// Each element in the array represents your maximum jump length at that position.
		// Determine if you are able to reach the last index.
		// For example:
		// A = [2,3,1,1,4], return true.
		// A = [3,2,1,0,4], return false.
		static bool CanJump(int A[], int n)
		{
			if (A == nullptr || n <= 0) return false;
			if (n == 1) return true;
			unique_ptr<bool[]> jump(new bool[n]);
			jump[n-1] = true;
			for (int i = n - 2; i >= 0; i--) {
				jump[i] = false;
				int j = i + A[i];
				if (j >= n - 1) jump[i] = true;
				else {
					for (int k = i + 1; k <= j; k++) {
						if (jump[k] == true) {
							jump[i] = true;
							break;
						}
					}
				}
			}
			return jump[0];
		}

		// Jump Game
		// Given an array of non-negative integers, you are initially positioned at the first index of the array.
		// Each element in the array represents your maximum jump length at that position.
		// Determine if you are able to reach the last index.
		// For example:
		// A = [2,3,1,1,4], return true.
		// A = [3,2,1,0,4], return false.
		static bool CanJump2(int A[], int n)
		{
			if (A == nullptr || n <= 0) return false;
			int lastTrue = n-1;
			for (int i = n - 2; i >= 0; i--) {
				int j = i + A[i];
				if (j >= n - 1 || j >= lastTrue) {
					lastTrue = i;
				}
			}
			return lastTrue == 0;
		}
	};
}