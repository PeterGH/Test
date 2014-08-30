#pragma once
#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <map>
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
	};
}