#include "LeetCodeTest.h"

void LeetCodeTest::Init(void)
{
	Add("RecoverTree", [&](){
		auto check = [&](Test::LeetCode::TreeNode * node) {
			Logger().WriteInformation("Recover tree\n");
			Test::LeetCode::Print(node);
			bool valid = Test::LeetCode::IsBinarySearchTree(node);
			bool valid2 = Test::LeetCode::IsBinarySearchTree2(node);
			Test::LeetCode::TreeNode * copy = Test::LeetCode::Clone(node);
			Logger().WriteInformation("to\n");
			Test::LeetCode::RecoverTree(node);
			Test::LeetCode::RecoverTree2(copy);
			Test::LeetCode::Print(node);
			bool valid3 = Test::LeetCode::IsBinarySearchTree(node);
			bool valid4 = Test::LeetCode::IsBinarySearchTree2(node);
			bool equal = Test::LeetCode::Equal(node, copy);
			Test::LeetCode::DeleteTree(node);
			Test::LeetCode::DeleteTree(copy);
			ASSERT1(valid == valid2);
			ASSERT1(valid3 == true);
			ASSERT1(valid4 == true);
			ASSERT1(equal == true);
		};
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(1);
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(2);
			n1->left = n2;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(1);
			n1->right = n2;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(3);
			n1->left = n2;
			n1->right = n3;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(2);
			n1->left = n2;
			n1->right = n3;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(1);
			n1->left = n2;
			n1->right = n3;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(2);
			n1->left = n2;
			n2->left = n3;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(1);
			n1->left = n2;
			n2->left = n3;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(3);
			n1->right = n2;
			n2->right = n3;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(2);
			n1->right = n2;
			n2->right = n3;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(4);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(6);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(5);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(7);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(4);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(6);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(5);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(7);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(4);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(6);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(5);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(7);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(4);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(6);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(5);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(7);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(6);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(4);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(5);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(7);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(6);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(4);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(5);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(7);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(4);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(5);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(6);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(7);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(4);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(7);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(5);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(6);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(4);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(6);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(7);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(5);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(6);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(4);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(5);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(7);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(5);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(6);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(4);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(7);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(7);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(6);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(5);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(4);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(4);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(6);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(5);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(7);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(4);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(6);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(7);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(5);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(3);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(4);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(6);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(7);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(5);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(1);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(4);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(6);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(5);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(7);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(4);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(6);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(5);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(7);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(4);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(6);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(5);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(7);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(4);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(6);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(5);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(7);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(4);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(5);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(6);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(2);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(7);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
		{
			Test::LeetCode::TreeNode * n1 = new Test::LeetCode::TreeNode(4);
			Test::LeetCode::TreeNode * n2 = new Test::LeetCode::TreeNode(7);
			Test::LeetCode::TreeNode * n3 = new Test::LeetCode::TreeNode(6);
			Test::LeetCode::TreeNode * n4 = new Test::LeetCode::TreeNode(1);
			Test::LeetCode::TreeNode * n5 = new Test::LeetCode::TreeNode(3);
			Test::LeetCode::TreeNode * n6 = new Test::LeetCode::TreeNode(5);
			Test::LeetCode::TreeNode * n7 = new Test::LeetCode::TreeNode(2);
			n1->left = n2;
			n1->right = n3;
			n2->left = n4;
			n2->right = n5;
			n3->left = n6;
			n3->right = n7;
			check(n1);
		}
	});

	Add("IsInterLeave", [&](){
		auto check = [&](const string & s1, const string & s2, const string &  s3, bool expect){
			Logger().WriteInformation("s1: %s\n", s1.c_str());
			Logger().WriteInformation("s2: %s\n", s2.c_str());
			Logger().WriteInformation("s3: %s\n", s3.c_str());
			bool r = Test::LeetCode::IsInterLeave(s1, s2, s3);
			Logger().WriteInformation("  is %sinterleave\n", r ? "" : "not ");
			ASSERT1(r == expect);
		};

		check("", "", "", true);
		check("a", "", "a", true);
		check("a", "", "b", false);
		check("", "a", "a", true);
		check("", "a", "b", false);
		check("a", "a", "aa", true);
		check("a", "a", "ab", false);
		check("a", "a", "ba", false);
		check("a", "b", "ab", true);
		check("a", "b", "ba", true);
		check("ab", "ac", "abac", true);
		check("ab", "ac", "acab", true);
		check("ab", "ac", "aabc", true);
		check("ab", "ac", "aacb", true);
		check("ab", "ac", "acba", false);
		check("ab", "ac", "caab", false);
		check("ab", "ac", "bcaa", false);
		check("aabcc", "dbbca", "aadbbcbcac", true);
		check("aabcc", "dbbca", "aadbbbaccc", false);
	});

	Add("UniqueBinarySearchTrees", [&](){
		auto check = [&](int n, int c){
			int m = Test::LeetCode::UniqueBinarySearchTrees(n);
			Logger().WriteInformation("%d distinct numbers can build %d unique binary search trees.\n", n, m);
			vector<Test::LeetCode::TreeNode *> trees = Test::LeetCode::CreateUniqueBinarySearchTrees(n);
			for_each (trees.begin(), trees.end(), [&](Test::LeetCode::TreeNode * t){
				bool valid1 = Test::LeetCode::IsBinarySearchTree(t);
				bool valid2 = Test::LeetCode::IsBinarySearchTree2(t);
				Test::LeetCode::Print(t);
				Test::LeetCode::DeleteTree(t);
				ASSERT1(valid1 == true);
				ASSERT1(valid2 == true);
			});
			ASSERT1(m == c);
			ASSERT1((int)trees.size() == c);
		};

		check(1, 1);
		check(2, 2);
		check(3, 5);
		check(4, 14);
	});

	Add("IpAddresses", [&](){
		auto check = [&](const string & s){
			Logger().WriteInformation("%s\n", s.c_str());
			vector<string> ips = Test::LeetCode::GetIpAddresses(s);
			for_each (ips.begin(), ips.end(), [&](string & i){
				Logger().WriteInformation("\t%s\n", i.c_str());
			});
		};

		check("0000");
		check("1234");
		check("255255255255");
		check("25525511135");
		check("010010");
	});

	Add("ReverseList", [&](){
		auto check = [&](vector<int> nums, int m, int n){
			Logger().WriteInformation("Reverse between %d and %d\n", m, n);
			Test::LeetCode::ListNode * list = Test::LeetCode::ToList(nums);
			Test::LeetCode::Print(list);
			list = Test::LeetCode::ReverseList(list, m, n);
			Test::LeetCode::Print(list);
			Logger().WriteInformation("\n");
			Test::LeetCode::DeleteList(list);
		};

		check(vector<int> { 1 }, 1, 1);
		check(vector<int> { 1 }, 1, 2);
		check(vector<int> { 1, 2 }, 1, 1);
		check(vector<int> { 1, 2 }, 2, 2);
		check(vector<int> { 1, 2 }, 2, 3);
		check(vector<int> { 1, 2 }, 1, 2);
		check(vector<int> { 1, 2 }, 1, 3);
		check(vector<int> { 1, 2, 3, 4, 5 }, 1, 2);
		check(vector<int> { 1, 2, 3, 4, 5 }, 1, 3);
		check(vector<int> { 1, 2, 3, 4, 5 }, 1, 4);
		check(vector<int> { 1, 2, 3, 4, 5 }, 1, 5);
		check(vector<int> { 1, 2, 3, 4, 5 }, 2, 3);
		check(vector<int> { 1, 2, 3, 4, 5 }, 2, 4);
		check(vector<int> { 1, 2, 3, 4, 5 }, 2, 5);
		check(vector<int> { 1, 2, 3, 4, 5 }, 3, 4);
		check(vector<int> { 1, 2, 3, 4, 5 }, 3, 5);
		check(vector<int> { 1, 2, 3, 4, 5 }, 4, 5);
	});

	Add("Subsets", [&](){
		auto print = [&](vector<int> & s){
			Logger().WriteInformation("\t[");
			for (size_t i = 0; i < s.size(); i++) {
				if (i != 0) Logger().WriteInformation(" ");
				Logger().WriteInformation("%d", s[i]);
			}
			Logger().WriteInformation("]\n");
		};
		auto check = [&](vector<int> & s){
			Logger().WriteInformation("%d elements\n", s.size());
			print(s);
			int expectSize = 1 << s.size();
			vector<vector<int>> sets = Test::LeetCode::Subsets(s);
			int actualSize = sets.size();
			Logger().WriteInformation("%d subsets\n", actualSize);
			for_each (sets.begin(), sets.end(), [&](vector<int> & ss){
				print(ss);
				bool sorted = is_sorted(ss.begin(), ss.end());
				ASSERT1(sorted);
			});
			ASSERT1(actualSize == expectSize);
			vector<vector<int>> uniquesets = Test::LeetCode::UniqueSubsets(s);
			int actualUniqueSize = uniquesets.size();
			Logger().WriteInformation("%d unique subsets\n", actualUniqueSize);
			for_each (uniquesets.begin(), uniquesets.end(), [&](vector<int> & ss){
				print(ss);
				bool sorted = is_sorted(ss.begin(), ss.end());
				ASSERT1(sorted);
			});
			ASSERT1(actualUniqueSize <= expectSize);
			Logger().WriteInformation("\n");
		};

		check(vector<int> { 1, 2, 2 });
	});

	Add("DecodeString", [&](){
		auto check = [&](const string & s){
			int c = Test::LeetCode::CountStringDecodings(s);
			Logger().WriteInformation("There are %d ways to decode %s\n", c, s.c_str());
		};
		check("#");
		check("0");
		check("1");
		check("12");
		check("1@2");
		check("12#");
		check("123");
		check("1234");
	});

	Add("GrayCode", [&](){
		auto check = [&](int n){
			vector<int> codes = Test::LeetCode::GrayCode(n);
			vector<int> codes2 = Test::LeetCode::GrayCode2(n);
			Logger().WriteInformation("%d-bit gray codes:\n", n);
			ASSERT1(codes.size() == codes2.size());
			for (size_t i = 0; i < codes.size(); i++){
				Logger().WriteInformation("  ");
				for (int j = n - 1; j >= 0; j--) {
					Logger().WriteInformation("%d", (codes[i] >> j) & 0x1);
				}
				Logger().WriteInformation(" %s %d\n", codes[i] == codes2[i] ? "==" : "!=", codes2[i]);
				ASSERT1(codes[i] == codes2[i]);
			}
		};

		check(1);
		check(2);
		check(3);
		check(4);
		check(5);
		check(6);
	});

	Add("Merge", [&](){
		auto print = [&](int a[], int n){
			Logger().WriteInformation("\t[");
			for (int i = 0; i < n; i++) {
				if (i != 0) Logger().WriteInformation(" ");
				Logger().WriteInformation("%d", a[i]);
			}
			Logger().WriteInformation("]\n");
		};

		auto check = [&](int A1[], int A2[], int m, int B1[], int B2[], int n) {
			Logger().WriteInformation("Merge:\n");
			print(A1, m);
			print(B1, n);
			Test::LeetCode::MergeSortedArrays(A1, m, B1, n);
			Test::LeetCode::MergeSortedArrays(A2, m, B2, n);
			Logger().WriteInformation("  to:\n");
			print(A1, m + n);
			for (int i = 1; i < m + n; i++) {
				ASSERT1(A1[i-1] <= A1[i]);
			}
			for (int i = 1; i < m + n; i++) {
				ASSERT1(A2[i-1] <= A2[i]);
			}
			for (int i = 0; i < m + n; i++) {
				ASSERT1(A1[i] == A2[i]);
			}
		};

		{
			int A1[1] = { };
			int B1[] = { 1 };
			int A2[1] = { };
			int B2[] = { 1 };
			check(A1, A2, 0, B1, B2, 1);
		}
		{
			int A1[1] = { 1 };
			int B1[1] = { };
			int A2[1] = { 1 };
			int B2[1] = { };
			check(A1, A2, 1, B1, B2, 0);
		}
		{
			int A1[2] = { 1 };
			int B1[1] = { 2 };
			int A2[2] = { 1 };
			int B2[1] = { 2 };
			check(A1, A2, 1, B1, B2, 1);
		}
		{
			int A1[2] = { 1 };
			int B1[1] = { 0 };
			int A2[2] = { 1 };
			int B2[1] = { 0 };
			check(A1, A2, 1, B1, B2, 1);
		}
		{
			int A1[3] = { 1, 1 };
			int B1[1] = { 2 };
			int A2[3] = { 1, 1 };
			int B2[1] = { 2 };
			check(A1, A2, 2, B1, B2, 1);
		}
		{
			int A1[3] = { 1, 2 };
			int B1[1] = { 2 };
			int A2[3] = { 1, 2 };
			int B2[1] = { 2 };
			check(A1, A2, 2, B1, B2, 1);
		}
		{
			int A1[3] = { 1, 3 };
			int B1[1] = { 2 };
			int A2[3] = { 1, 3 };
			int B2[1] = { 2 };
			check(A1, A2, 2, B1, B2, 1);
		}
		{
			int A1[3] = { 1, 1 };
			int B1[1] = { 0 };
			int A2[3] = { 1, 1 };
			int B2[1] = { 0 };
			check(A1, A2, 2, B1, B2, 1);
		}
	});

	Add("ScrambleString", [&](){
		auto check = [&](const string & s1, const string & s2){
			bool isScramble = Test::LeetCode::IsScramble(s1, s2);
			bool isScramble2 = Test::LeetCode::IsScramble2(s1, s2);
			Logger().WriteInformation("%s is %sscramble of %s\n", s2.c_str(), isScramble ? "" : "not ", s1.c_str());
			ASSERT1(isScramble == isScramble2);
		};
		check("", "");
		check("a", "b");
		check("a", "a");
		check("ab", "ab");
		check("ab", "ba");
		check("ab", "ac");
		check("ab", "ca");
		check("aaa", "aaa");
		check("abcd", "acbd");
		check("abcd", "adbc");
		check("abcd", "badc");
		check("abcd", "bdac");
		check(
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

		for (int i = 0; i < 100; i++) {
			int len = 1 + Test::Random::Next(10);
			string s1;
			for (int j = 0; j < len; j++) {
				char c = 'a' + Test::Random::Next(25);
				s1.append(1, c);
			}

			for (int j = 0; j < 10; j++) {
				string s2(s1);
				random_shuffle(s2.begin(), s2.end());
				check(s1, s2);
			}
		}
	});

	Add("PartitionList", [&](){
		auto check = [&](Test::LeetCode::ListNode * list, int x){
			Logger().WriteInformation("Partition by %d:\n", x);
			Test::LeetCode::Print(list);
			list = Test::LeetCode::PartitionList(list, x);
			Test::LeetCode::Print(list);
			Test::LeetCode::DeleteList(list);
		};
		{
			vector<int> nums = { 1 };
			Test::LeetCode::ListNode * list = Test::LeetCode::ToList(nums);
			check(list, 3);
		}
		{
			vector<int> nums = { 5 };
			Test::LeetCode::ListNode * list = Test::LeetCode::ToList(nums);
			check(list, 3);
		}
		{
			vector<int> nums = { 2, 1 };
			Test::LeetCode::ListNode * list = Test::LeetCode::ToList(nums);
			check(list, 3);
		}
		{
			vector<int> nums = { 5, 3 };
			Test::LeetCode::ListNode * list = Test::LeetCode::ToList(nums);
			check(list, 3);
		}
		{
			vector<int> nums = { 2, 4 };
			Test::LeetCode::ListNode * list = Test::LeetCode::ToList(nums);
			check(list, 3);
		}
		{
			vector<int> nums = { 5, 1 };
			Test::LeetCode::ListNode * list = Test::LeetCode::ToList(nums);
			check(list, 3);
		}
		{
			vector<int> nums = { 1, 4, 3, 2, 5, 2 };
			Test::LeetCode::ListNode * list = Test::LeetCode::ToList(nums);
			check(list, 3);
		}
	});

	Add("MaximalRectangle", [&](){
		auto check = [&](vector<vector<char>> & matrix, int expect){
			Logger().WriteInformation("Matrix:\n");
			for (int i = 0; i < (int)matrix.size(); i++) {
				for (int j = 0; j < (int)matrix[i].size(); j++) {
					Logger().WriteInformation(" %d", matrix[i][j]);
				}
				Logger().WriteInformation("\n");
			}
			int area = Test::LeetCode::MaximalRectangle(matrix);
			Logger().WriteInformation("Area: %d\n", area);
			ASSERT1(area == expect);
		};
		{
			vector<vector<char>> m = { { 0 } };
			check(m, 0);
		}
		{
			vector<vector<char>> m = { { 1 } };
			check(m, 1);
		}
		{
			vector<vector<char>> m = { { 0 }, { 0 } };
			check(m, 0);
		}
		{
			vector<vector<char>> m = { { 0 }, { 1 } };
			check(m, 1);
		}
		{
			vector<vector<char>> m = { { 1 }, { 0 } };
			check(m, 1);
		}
		{
			vector<vector<char>> m = { { 1 }, { 1 } };
			check(m, 2);
		}
		{
			vector<vector<char>> m = { { 0, 0 } };
			check(m, 0);
		}
		{
			vector<vector<char>> m = { { 0, 1 } };
			check(m, 1);
		}
		{
			vector<vector<char>> m = { { 1, 0 } };
			check(m, 1);
		}
		{
			vector<vector<char>> m = { { 1, 1 } };
			check(m, 2);
		}
		{
			vector<vector<char>> m = { { 0, 0 }, { 0, 0 } };
			check(m, 0);
		}
		{
			vector<vector<char>> m = { { 1, 0 }, { 0, 0 } };
			check(m, 1);
		}
		{
			vector<vector<char>> m = { { 0, 1 }, { 0, 0 } };
			check(m, 1);
		}
		{
			vector<vector<char>> m = { { 0, 0 }, { 1, 0 } };
			check(m, 1);
		}
		{
			vector<vector<char>> m = { { 0, 0 }, { 0, 1 } };
			check(m, 1);
		}
		{
			vector<vector<char>> m = { { 1, 1 }, { 0, 0 } };
			check(m, 2);
		}
		{
			vector<vector<char>> m = { { 1, 0 }, { 1, 0 } };
			check(m, 2);
		}
		{
			vector<vector<char>> m = { { 1, 0 }, { 0, 1 } };
			check(m, 4);
		}
		{
			vector<vector<char>> m = { { 0, 1 }, { 1, 0 } };
			check(m, 4);
		}
		{
			vector<vector<char>> m = { { 0, 1 }, { 0, 1 } };
			check(m, 2);
		}
		{
			vector<vector<char>> m = { { 0, 0 }, { 1, 1 } };
			check(m, 2);
		}
	});

	Add("MaximalRectangleAtPoint", [&](){
		auto print = [&](vector<vector<char>> & matrix){
			Logger().WriteInformation("Matrix:\n");
			for (int i = 0; i < (int)matrix.size(); i++) {
				for (int j = 0; j < (int)matrix[i].size(); j++) {
					Logger().WriteInformation(" %d", matrix[i][j]);
				}
				Logger().WriteInformation("\n");
			}
		};

		auto check = [&](vector<vector<char>> & matrix, int pi, int pj, int expect){
			int area = Test::LeetCode::MaximalRectangleAtPoint(matrix, pi, pj);
			Logger().WriteInformation(" Area at (%d, %d): %d\n", pi, pj, area);
			ASSERT1(area == expect);
		};
		{
			vector<vector<char>> m = { { 0 } };
			print(m);
			check(m, 0, 0, 0);
		}
		{
			vector<vector<char>> m = { { 1 } };
			print(m);
			check(m, 0, 0, 1);
		}
		{
			vector<vector<char>> m = { { 0, 0 } };
			print(m);
			check(m, 0, 0, 0);
			check(m, 0, 1, 0);
		}
		{
			vector<vector<char>> m = { { 0, 1 } };
			print(m);
			check(m, 0, 0, 0);
			check(m, 0, 1, 1);
		}
		{
			vector<vector<char>> m = { { 1, 0 } };
			print(m);
			check(m, 0, 0, 1);
			check(m, 0, 1, 0);
		}
		{
			vector<vector<char>> m = { { 1, 1 } };
			print(m);
			check(m, 0, 0, 2);
			check(m, 0, 1, 1);
		}
		{
			vector<vector<char>> m = { { 0 }, { 0 } };
			print(m);
			check(m, 0, 0, 0);
			check(m, 1, 0, 0);
		}
		{
			vector<vector<char>> m = { { 1 }, { 0 } };
			print(m);
			check(m, 0, 0, 1);
			check(m, 1, 0, 0);
		}
		{
			vector<vector<char>> m = { { 0 }, { 1 } };
			print(m);
			check(m, 0, 0, 0);
			check(m, 1, 0, 1);
		}
		{
			vector<vector<char>> m = { { 1 }, { 1 } };
			print(m);
			check(m, 0, 0, 2);
			check(m, 1, 0, 1);
		}
		{
			vector<vector<char>> m = {
					{ 0, 0 },
					{ 0, 0 }
			};
			print(m);
			check(m, 0, 0, 0);
			check(m, 0, 1, 0);
			check(m, 1, 0, 0);
			check(m, 1, 1, 0);
		}
		{
			vector<vector<char>> m = {
					{ 1, 0 },
					{ 0, 0 }
			};
			print(m);
			check(m, 0, 0, 1);
			check(m, 0, 1, 0);
			check(m, 1, 0, 0);
			check(m, 1, 1, 0);
		}
		{
			vector<vector<char>> m = {
					{ 0, 1 },
					{ 0, 0 }
			};
			print(m);
			check(m, 0, 0, 0);
			check(m, 0, 1, 1);
			check(m, 1, 0, 0);
			check(m, 1, 1, 0);
		}
		{
			vector<vector<char>> m = {
					{ 0, 0 },
					{ 1, 0 }
			};
			print(m);
			check(m, 0, 0, 0);
			check(m, 0, 1, 0);
			check(m, 1, 0, 1);
			check(m, 1, 1, 0);
		}
		{
			vector<vector<char>> m = {
					{ 0, 0 },
					{ 0, 1 }
			};
			print(m);
			check(m, 0, 0, 0);
			check(m, 0, 1, 0);
			check(m, 1, 0, 0);
			check(m, 1, 1, 1);
		}
		{
			vector<vector<char>> m = {
					{ 1, 1 },
					{ 0, 0 }
			};
			print(m);
			check(m, 0, 0, 2);
			check(m, 0, 1, 1);
			check(m, 1, 0, 0);
			check(m, 1, 1, 0);
		}
		{
			vector<vector<char>> m = {
					{ 1, 0 },
					{ 1, 0 }
			};
			print(m);
			check(m, 0, 0, 2);
			check(m, 0, 1, 0);
			check(m, 1, 0, 1);
			check(m, 1, 1, 0);
		}
		{
			vector<vector<char>> m = {
					{ 1, 0 },
					{ 0, 1 }
			};
			print(m);
			check(m, 0, 0, 1);
			check(m, 0, 1, 0);
			check(m, 1, 0, 0);
			check(m, 1, 1, 1);
		}
		{
			vector<vector<char>> m = {
					{ 0, 1 },
					{ 1, 0 }
			};
			print(m);
			check(m, 0, 0, 0);
			check(m, 0, 1, 1);
			check(m, 1, 0, 1);
			check(m, 1, 1, 0);
		}
		{
			vector<vector<char>> m = {
					{ 0, 1 },
					{ 0, 1 }
			};
			print(m);
			check(m, 0, 0, 0);
			check(m, 0, 1, 2);
			check(m, 1, 0, 0);
			check(m, 1, 1, 1);
		}
		{
			vector<vector<char>> m = {
					{ 0, 0 },
					{ 1, 1 }
			};
			print(m);
			check(m, 0, 0, 0);
			check(m, 0, 1, 0);
			check(m, 1, 0, 2);
			check(m, 1, 1, 1);
		}
		{
			vector<vector<char>> m = {
					{ 1, 1 },
					{ 1, 0 }
			};
			print(m);
			check(m, 0, 0, 2);
			check(m, 0, 1, 1);
			check(m, 1, 0, 1);
			check(m, 1, 1, 0);
		}
		{
			vector<vector<char>> m = {
					{ 1, 1 },
					{ 0, 1 }
			};
			print(m);
			check(m, 0, 0, 2);
			check(m, 0, 1, 2);
			check(m, 1, 0, 0);
			check(m, 1, 1, 1);
		}
		{
			vector<vector<char>> m = {
					{ 1, 0 },
					{ 1, 1 }
			};
			print(m);
			check(m, 0, 0, 2);
			check(m, 0, 1, 0);
			check(m, 1, 0, 2);
			check(m, 1, 1, 1);
		}
		{
			vector<vector<char>> m = {
					{ 0, 1 },
					{ 1, 1 }
			};
			print(m);
			check(m, 0, 0, 0);
			check(m, 0, 1, 2);
			check(m, 1, 0, 2);
			check(m, 1, 1, 1);
		}
		{
			vector<vector<char>> m = {
					{ 1, 1 },
					{ 1, 1 }
			};
			print(m);
			check(m, 0, 0, 4);
			check(m, 0, 1, 2);
			check(m, 1, 0, 2);
			check(m, 1, 1, 1);
		}
		{
			vector<vector<char>> m = {
					{ 1, 1, 1 },
					{ 1, 0, 0 }
			};
			print(m);
			check(m, 0, 0, 3);
			check(m, 0, 1, 2);
			check(m, 0, 2, 1);
			check(m, 1, 0, 1);
			check(m, 1, 1, 0);
			check(m, 1, 2, 0);
		}
		{
			vector<vector<char>> m = {
					{ 1, 1, 1 },
					{ 1, 1, 0 }
			};
			print(m);
			check(m, 0, 0, 4);
			check(m, 0, 1, 2);
			check(m, 0, 2, 1);
			check(m, 1, 0, 2);
			check(m, 1, 1, 1);
			check(m, 1, 2, 0);
		}
		{
			vector<vector<char>> m = {
					{ 1, 1, 1 },
					{ 1, 1, 1 }
			};
			print(m);
			check(m, 0, 0, 6);
			check(m, 0, 1, 4);
			check(m, 0, 2, 2);
			check(m, 1, 0, 3);
			check(m, 1, 1, 2);
			check(m, 1, 2, 1);
		}
	});

	Add("MaximalRectangleFullOnes", [&](){
		auto print = [&](vector<vector<char>> & matrix){
			Logger().WriteInformation("Matrix:\n");
			for (int i = 0; i < (int)matrix.size(); i++) {
				for (int j = 0; j < (int)matrix[i].size(); j++) {
					Logger().WriteInformation(" %d", matrix[i][j]);
				}
				Logger().WriteInformation("\n");
			}
		};

		auto check = [&](vector<vector<char>> & matrix, int expect){
			print(matrix);
			int area = Test::LeetCode::MaximalRectangleFullOnes(matrix);
			Logger().WriteInformation(" Area: %d\n", area);
			ASSERT1(area == expect);
		};
		{
			vector<vector<char>> m = { { 0 } };
			check(m, 0);
		}
		{
			vector<vector<char>> m = { { 1 } };
			check(m, 1);
		}
		{
			vector<vector<char>> m = { { 0, 0 } };
			check(m, 0);
		}
		{
			vector<vector<char>> m = { { 0, 1 } };
			check(m, 1);
		}
		{
			vector<vector<char>> m = { { 1, 0 } };
			check(m, 1);
		}
		{
			vector<vector<char>> m = { { 1, 1 } };
			check(m, 2);
		}
		{
			vector<vector<char>> m = { { 0 }, { 0 } };
			check(m, 0);
		}
		{
			vector<vector<char>> m = { { 1 }, { 0 } };
			check(m, 1);
		}
		{
			vector<vector<char>> m = { { 0 }, { 1 } };
			check(m, 1);
		}
		{
			vector<vector<char>> m = { { 1 }, { 1 } };
			check(m, 2);
		}
		{
			vector<vector<char>> m = {
					{ 0, 0 },
					{ 0, 0 }
			};
			check(m, 0);
		}
		{
			vector<vector<char>> m = {
					{ 1, 0 },
					{ 0, 0 }
			};
			check(m, 1);
		}
		{
			vector<vector<char>> m = {
					{ 0, 1 },
					{ 0, 0 }
			};
			check(m, 1);
		}
		{
			vector<vector<char>> m = {
					{ 0, 0 },
					{ 1, 0 }
			};
			check(m, 1);
		}
		{
			vector<vector<char>> m = {
					{ 0, 0 },
					{ 0, 1 }
			};
			check(m, 1);
		}
		{
			vector<vector<char>> m = {
					{ 1, 1 },
					{ 0, 0 }
			};
			check(m, 2);
		}
		{
			vector<vector<char>> m = {
					{ 1, 0 },
					{ 1, 0 }
			};
			check(m, 2);
		}
		{
			vector<vector<char>> m = {
					{ 1, 0 },
					{ 0, 1 }
			};
			check(m, 1);
		}
		{
			vector<vector<char>> m = {
					{ 0, 1 },
					{ 1, 0 }
			};
			check(m, 1);
		}
		{
			vector<vector<char>> m = {
					{ 0, 1 },
					{ 0, 1 }
			};
			check(m, 2);
		}
		{
			vector<vector<char>> m = {
					{ 0, 0 },
					{ 1, 1 }
			};
			check(m, 2);
		}
		{
			vector<vector<char>> m = {
					{ 1, 1 },
					{ 1, 0 }
			};
			check(m, 2);
		}
		{
			vector<vector<char>> m = {
					{ 1, 1 },
					{ 0, 1 }
			};
			check(m, 2);
		}
		{
			vector<vector<char>> m = {
					{ 1, 0 },
					{ 1, 1 }
			};
			check(m, 2);
		}
		{
			vector<vector<char>> m = {
					{ 0, 1 },
					{ 1, 1 }
			};
			check(m, 2);
		}
		{
			vector<vector<char>> m = {
					{ 1, 1 },
					{ 1, 1 }
			};
			check(m, 4);
		}
		{
			vector<vector<char>> m = {
					{ 1, 1, 1 },
					{ 1, 0, 0 }
			};
			check(m, 3);
		}
		{
			vector<vector<char>> m = {
					{ 1, 1, 1 },
					{ 1, 1, 0 }
			};
			check(m, 4);
		}
		{
			vector<vector<char>> m = {
					{ 1, 1, 1 },
					{ 1, 1, 1 }
			};
			check(m, 6);
		}
		{
			vector<vector<char>> m = {
					{ 0, 0, 1, 0 },
					{ 1, 1, 1, 1 },
					{ 1, 1, 1, 1 },
					{ 1, 1, 1, 0 },
					{ 1, 1, 0, 0 },
					{ 1, 1, 1, 1 },
					{ 1, 1, 1, 0 },
			};
			check(m, 12);
		}
	});

	Add("LargestRectangleInHistogram", [&](){
		auto check = [&](vector<int> & h, int e){
			Logger().WriteInformation("Histogram:");
			for (int i = 0; i < (int)h.size(); i++) {
				Logger().WriteInformation(" %d", h[i]);
			}
			Logger().WriteInformation("\n");
			int a = Test::LeetCode::LargestRectangleInHistogram(h);
			int b = Test::LeetCode::LargestRectangleInHistogram2(h);
			Logger().WriteInformation(" max area: %d, %d\n", a, b);
			if (e >= 0) {
				ASSERT1(a == e);
				ASSERT1(b == e);
			} else {
				ASSERT1(a == b);
			}
		};

		check(vector<int> { 1 }, 1);
		check(vector<int> { 2 }, 2);
		check(vector<int> { 1, 1 }, 2);
		check(vector<int> { 1, 2 }, 2);
		check(vector<int> { 1, 3 }, 3);
		check(vector<int> { 2, 3 }, 4);
		check(vector<int> { 0, 1 }, 1);
		check(vector<int> { 0, 2 }, 2);
		check(vector<int> { 0, 0 }, 0);
		check(vector<int> { 1, 0 }, 1);
		check(vector<int> { 2, 0 }, 2);
		check(vector<int> { 2, 1 }, 2);
		check(vector<int> { 3, 1 }, 3);
		check(vector<int> { 3, 2 }, 4);
		check(vector<int> { 0, 0, 0 }, 0);
		check(vector<int> { 1, 0, 0 }, 1);
		check(vector<int> { 0, 1, 0 }, 1);
		check(vector<int> { 0, 0, 1 }, 1);
		check(vector<int> { 1, 1, 0 }, 2);
		check(vector<int> { 1, 0, 1 }, 1);
		check(vector<int> { 0, 1, 1 }, 2);
		check(vector<int> { 1, 1, 1 }, 3);
		check(vector<int> { 2, 1, 1 }, 3);
		check(vector<int> { 1, 2, 1 }, 3);
		check(vector<int> { 1, 1, 2 }, 3);
		check(vector<int> { 3, 1, 1 }, 3);
		check(vector<int> { 1, 3, 1 }, 3);
		check(vector<int> { 1, 1, 3 }, 3);
		check(vector<int> { 4, 1, 1 }, 4);
		check(vector<int> { 1, 4, 1 }, 4);
		check(vector<int> { 1, 1, 4 }, 4);
		check(vector<int> { 1, 2, 2 }, 4);
		check(vector<int> { 2, 1, 2 }, 3);
		check(vector<int> { 2, 2, 1 }, 4);
		check(vector<int> { 1, 2, 3 }, 4);
		check(vector<int> { 1, 3, 2 }, 4);
		check(vector<int> { 2, 1, 3 }, 3);
		check(vector<int> { 2, 3, 1 }, 4);
		check(vector<int> { 3, 1, 2 }, 3);
		check(vector<int> { 3, 2, 1 }, 4);
		check(vector<int> { 1, 2, 5 }, 5);
		check(vector<int> { 1, 5, 2 }, 5);
		check(vector<int> { 5, 2, 1 }, 5);
		check(vector<int> { 5, 1, 2 }, 5);
		check(vector<int> { 1, 3, 4 }, 6);
		check(vector<int> { 3, 1, 4 }, 4);
		check(vector<int> { 1, 2, 3, 4 }, 6);
		check(vector<int> { 2, 1, 3, 4 }, 6);
		check(vector<int> { 2, 3, 1, 4 }, 4);
		check(vector<int> { 4, 2, 1, 3 }, 4);
		check(vector<int> { 4, 2, 3, 1 }, 6);
		check(vector<int> { 1, 2, 3, 4, 5 }, 9);
		check(vector<int> { 5, 4, 3, 2, 1 }, 9);
		check(vector<int> { 2, 1, 5, 6, 2, 3 }, 10);
		for (int i = 0; i < 100; i++) {
			int len = 1 + Test::Random::Next(100);
			vector<int> hist;
			for (int j = 0; j < len; j++) {
				int v = Test::Random::Next(100);
				hist.push_back(v);
			}
			check(hist, -1);
		}
	});

	Add("DeleteDuplicates1", [&](){
		auto check = [&](vector<int> & nums){
			Test::LeetCode::ListNode * list = Test::LeetCode::ToList(nums);
			Logger().WriteInformation("List:  ");
			Test::LeetCode::Print(list);
			list = Test::LeetCode::DeleteDuplicates(list);
			Logger().WriteInformation("Dedup: ");
			if (list == nullptr) Logger().WriteInformation("\n");
			else {
				Test::LeetCode::Print(list);
				int v = list->val;
				Test::LeetCode::ListNode * p = list->next;
				bool foundDup = false;
				while (p != nullptr) {
					if (p->val == v) foundDup = true;
					v = p->val;
					p = p->next;
				}
				Test::LeetCode::DeleteList(list);
				ASSERT1(foundDup == false);
			}
		};
		check(vector<int> { 1 });
		check(vector<int> { 1, 1 });
		check(vector<int> { 1, 2 });
		check(vector<int> { 1, 1, 2 });
		check(vector<int> { 1, 2, 2 });
		check(vector<int> { 1, 1, 1 });
		check(vector<int> { 1, 2, 3 });
		check(vector<int> { 1, 1, 2, 2 });
		check(vector<int> { 1, 1, 1, 2 });
		check(vector<int> { 1, 2, 2, 2 });
		check(vector<int> { 1, 1, 1, 1 });
		check(vector<int> { 1, 2, 2, 3 });
		check(vector<int> { 1, 2, 3, 4 });
	});

	Add("DeleteDuplicates2", [&](){
		auto check = [&](vector<int> & nums){
			Test::LeetCode::ListNode * list = Test::LeetCode::ToList(nums);
			Logger().WriteInformation("List:  ");
			Test::LeetCode::Print(list);
			list = Test::LeetCode::DeleteDuplicates2(list);
			Logger().WriteInformation("Dedup: ");
			if (list == nullptr) Logger().WriteInformation("\n");
			else {
				Test::LeetCode::Print(list);
				int v = list->val;
				Test::LeetCode::ListNode * p = list->next;
				bool foundDup = false;
				while (p != nullptr) {
					if (p->val == v) foundDup = true;
					v = p->val;
					p = p->next;
				}
				Test::LeetCode::DeleteList(list);
				ASSERT1(foundDup == false);
			}
		};
		check(vector<int> { 1 });
		check(vector<int> { 1, 1 });
		check(vector<int> { 1, 2 });
		check(vector<int> { 1, 1, 2 });
		check(vector<int> { 1, 2, 2 });
		check(vector<int> { 1, 1, 1 });
		check(vector<int> { 1, 2, 3 });
		check(vector<int> { 1, 1, 2, 2 });
		check(vector<int> { 1, 1, 1, 2 });
		check(vector<int> { 1, 2, 2, 2 });
		check(vector<int> { 1, 1, 1, 1 });
		check(vector<int> { 1, 2, 2, 3 });
		check(vector<int> { 1, 2, 3, 4 });
	});

	Add("SearchInRotatedSortedArray1", [&](){
		auto print = [&](int a[], int n){
			Logger().WriteInformation("Array:");
			for (int i = 0; i < n; i++) {
				Logger().WriteInformation(" %d", a[i]);
			}
			Logger().WriteInformation("\n");
		};
		auto check = [&](int a[], int n, int t, int e) {
			int b = Test::LeetCode::SearchInRotatedSortedArray(a, n, t);
			int c = Test::LeetCode::SearchInRotatedSortedArray2(a, n, t);
			Logger().WriteInformation("  %d is at index %d, %d\n", t, b, c);
			ASSERT1(b == e);
			ASSERT1(c == e);
		};
		{
			int a[] = { 1 };
			print(a, 1);
			check(a, 1, 1, 0);
			check(a, 1, 0, -1);
			check(a, 1, 2, -1);
		}
		{
			int a[] = { 1, 2 };
			print(a, 2);
			check(a, 2, 0, -1);
			check(a, 2, 1, 0);
			check(a, 2, 2, 1);
			check(a, 2, 3, -1);
		}
		{
			int a[] = { 2, 1 };
			print(a, 2);
			check(a, 2, 0, -1);
			check(a, 2, 1, 1);
			check(a, 2, 2, 0);
			check(a, 2, 3, -1);
		}
		{
			int a[] = { 1, 2, 3 };
			print(a, 3);
			check(a, 3, 0, -1);
			check(a, 3, 1, 0);
			check(a, 3, 2, 1);
			check(a, 3, 3, 2);
			check(a, 3, 4, -1);
		}
		{
			int a[] = { 3, 1, 2 };
			print(a, 3);
			check(a, 3, 0, -1);
			check(a, 3, 1, 1);
			check(a, 3, 2, 2);
			check(a, 3, 3, 0);
			check(a, 3, 4, -1);
		}
		{
			int a[] = { 2, 3, 1 };
			print(a, 3);
			check(a, 3, 0, -1);
			check(a, 3, 1, 2);
			check(a, 3, 2, 0);
			check(a, 3, 3, 1);
			check(a, 3, 4, -1);
		}
		{
			int a[] = { 1, 2, 3, 4 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 0);
			check(a, 4, 2, 1);
			check(a, 4, 3, 2);
			check(a, 4, 4, 3);
			check(a, 4, 5, -1);
		}
		{
			int a[] = { 4, 1, 2, 3 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 1);
			check(a, 4, 2, 2);
			check(a, 4, 3, 3);
			check(a, 4, 4, 0);
			check(a, 4, 5, -1);
		}
		{
			int a[] = { 3, 4, 1, 2 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 2);
			check(a, 4, 2, 3);
			check(a, 4, 3, 0);
			check(a, 4, 4, 1);
			check(a, 4, 5, -1);
		}
		{
			int a[] = { 2, 3, 4, 1 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 3);
			check(a, 4, 2, 0);
			check(a, 4, 3, 1);
			check(a, 4, 4, 2);
			check(a, 4, 5, -1);
		}
	});

	Add("SearchInRotatedSortedArray2", [&](){
		auto print = [&](int a[], int n){
			Logger().WriteInformation("Array:");
			for (int i = 0; i < n; i++) {
				Logger().WriteInformation(" %d", a[i]);
			}
			Logger().WriteInformation("\n");
		};
		auto check = [&](int a[], int n, int t, int e) {
			int b = Test::LeetCode::SearchInRotatedSortedArray2(a, n, t);
			Logger().WriteInformation("  %d is at index %d\n", t, b);
			if (e == -1) ASSERT1(b == -1);
			else ASSERT1(a[b] == a[e]);
		};
		{
			int a[] = { 2, 2 };
			print(a, 2);
			check(a, 2, 0, -1);
			check(a, 2, 2, 1);
			check(a, 2, 3, -1);
		}
		{
			int a[] = { 1, 2, 2 };
			print(a, 3);
			check(a, 3, 0, -1);
			check(a, 3, 1, 0);
			check(a, 3, 2, 1);
			check(a, 3, 3, -1);
		}
		{
			int a[] = { 2, 1, 2 };
			print(a, 3);
			check(a, 3, 0, -1);
			check(a, 3, 1, 1);
			check(a, 3, 2, 2);
			check(a, 3, 3, -1);
		}
		{
			int a[] = { 2, 2, 1 };
			print(a, 3);
			check(a, 3, 0, -1);
			check(a, 3, 1, 2);
			check(a, 3, 2, 1);
			check(a, 3, 3, -1);
		}
		{
			int a[] = { 1, 1, 2 };
			print(a, 3);
			check(a, 3, 0, -1);
			check(a, 3, 1, 1);
			check(a, 3, 2, 2);
			check(a, 3, 3, -1);
		}
		{
			int a[] = { 2, 1, 1 };
			print(a, 3);
			check(a, 3, 0, -1);
			check(a, 3, 1, 1);
			check(a, 3, 2, 0);
			check(a, 3, 3, -1);
		}
		{
			int a[] = { 1, 2, 1 };
			print(a, 3);
			check(a, 3, 0, -1);
			check(a, 3, 1, 2);
			check(a, 3, 2, 1);
			check(a, 3, 3, -1);
		}
		{
			int a[] = { 2, 2, 2 };
			print(a, 3);
			check(a, 3, 1, -1);
			check(a, 3, 2, 2);
			check(a, 3, 3, -1);
		}
		{
			int a[] = { 1, 1, 3, 4 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 0);
			check(a, 4, 2, -1);
			check(a, 4, 3, 2);
			check(a, 4, 4, 3);
			check(a, 4, 5, -1);
		}
		{
			int a[] = { 4, 1, 1, 3 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 1);
			check(a, 4, 2, -1);
			check(a, 4, 3, 3);
			check(a, 4, 4, 0);
			check(a, 4, 5, -1);
		}
		{
			int a[] = { 3, 4, 1, 1 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 2);
			check(a, 4, 2, -1);
			check(a, 4, 3, 0);
			check(a, 4, 4, 1);
			check(a, 4, 5, -1);
		}
		{
			int a[] = { 1, 3, 4, 1 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 0);
			check(a, 4, 2, -1);
			check(a, 4, 3, 1);
			check(a, 4, 4, 2);
			check(a, 4, 5, -1);
		}
		{
			int a[] = { 1, 1, 1, 4 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 0);
			check(a, 4, 2, -1);
			check(a, 4, 4, 3);
			check(a, 4, 5, -1);
		}
		{
			int a[] = { 4, 1, 1, 1 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 1);
			check(a, 4, 2, -1);
			check(a, 4, 4, 0);
			check(a, 4, 5, -1);
		}
		{
			int a[] = { 1, 4, 1, 1 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 0);
			check(a, 4, 2, -1);
			check(a, 4, 4, 1);
			check(a, 4, 5, -1);
		}
		{
			int a[] = { 1, 1, 4, 1 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 0);
			check(a, 4, 2, -1);
			check(a, 4, 4, 2);
			check(a, 4, 5, -1);
		}
		{
			int a[] = { 1, 1, 1, 1 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 0);
			check(a, 4, 2, -1);
			check(a, 4, 4, -1);
		}
		{
			int a[] = { 1, 2, 2, 4 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 0);
			check(a, 4, 2, 1);
			check(a, 4, 3, -1);
			check(a, 4, 4, 3);
			check(a, 4, 5, -1);
		}
		{
			int a[] = { 4, 1, 2, 2 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 1);
			check(a, 4, 2, 2);
			check(a, 4, 3, -1);
			check(a, 4, 4, 0);
			check(a, 4, 5, -1);
		}
		{
			int a[] = { 2, 4, 1, 2 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 2);
			check(a, 4, 2, 0);
			check(a, 4, 3, -1);
			check(a, 4, 4, 1);
			check(a, 4, 5, -1);
		}
		{
			int a[] = { 2, 2, 4, 1 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 3);
			check(a, 4, 2, 0);
			check(a, 4, 3, -1);
			check(a, 4, 4, 2);
			check(a, 4, 5, -1);
		}
		{
			int a[] = { 1, 2, 2, 2 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 0);
			check(a, 4, 2, 1);
			check(a, 4, 3, -1);
			check(a, 4, 4, -1);
		}
		{
			int a[] = { 2, 1, 2, 2 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 1);
			check(a, 4, 2, 0);
			check(a, 4, 3, -1);
			check(a, 4, 4, -1);
		}
		{
			int a[] = { 2, 2, 1, 2 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 2);
			check(a, 4, 2, 0);
			check(a, 4, 3, -1);
			check(a, 4, 4, -1);
		}
		{
			int a[] = { 2, 2, 2, 1 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 3);
			check(a, 4, 2, 0);
			check(a, 4, 3, -1);
			check(a, 4, 4, -1);
		}
		{
			int a[] = { 1, 2, 4, 4 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 0);
			check(a, 4, 2, 1);
			check(a, 4, 3, -1);
			check(a, 4, 4, 2);
		}
		{
			int a[] = { 4, 1, 2, 4 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 1);
			check(a, 4, 2, 2);
			check(a, 4, 3, -1);
			check(a, 4, 4, 0);
		}
		{
			int a[] = { 4, 4, 1, 2 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 2);
			check(a, 4, 2, 3);
			check(a, 4, 3, -1);
			check(a, 4, 4, 0);
		}
		{
			int a[] = { 2, 4, 4, 1 };
			print(a, 4);
			check(a, 4, 0, -1);
			check(a, 4, 1, 3);
			check(a, 4, 2, 0);
			check(a, 4, 3, -1);
			check(a, 4, 4, 1);
		}
		{
			int a[] = { 1 };
			print(a, 1);
			check(a, 1, 0, -1);
			check(a, 1, 1, 0);
		}
	});

	Add("RemoveDuplicates1", [&]() {
		auto print = [&](int a[], int n){
			for (int i = 0; i < n; i++) {
				Logger().WriteInformation(" %d", a[i]);
			}
			Logger().WriteInformation("\n");
		};

		auto check = [&](int a[], int n, int e){
			Logger().WriteInformation("Input: ");
			print(a, n);
			n = Test::LeetCode::RemoveDuplicates(a, n);
			Logger().WriteInformation("Output:");
			print(a, n);
			ASSERT1(n == e);
		};

		{
			int a[] = { 1 };
			check(a, 1, 1);
		}
		{
			int a[] = { 1, 1 };
			check(a, 2, 1);
		}
		{
			int a[] = { 1, 2 };
			check(a, 2, 2);
		}
		{
			int a[] = { 1, 1, 2 };
			check(a, 3, 2);
		}
		{
			int a[] = { 1, 1, 1 };
			check(a, 3, 1);
		}
		{
			int a[] = { 1, 2, 2 };
			check(a, 3, 2);
		}
		{
			int a[] = { 1, 2, 3 };
			check(a, 3, 3);
		}
		{
			int a[] = { 1, 2, 3, 4 };
			check(a, 4, 4);
		}
		{
			int a[] = { 1, 1, 3, 4 };
			check(a, 4, 3);
		}
		{
			int a[] = { 1, 1, 1, 4 };
			check(a, 4, 2);
		}
		{
			int a[] = { 1, 1, 1, 1 };
			check(a, 4, 1);
		}
		{
			int a[] = { 1, 2, 2, 4 };
			check(a, 4, 3);
		}
		{
			int a[] = { 1, 2, 2, 2 };
			check(a, 4, 2);
		}
		{
			int a[] = { 1, 2, 3, 3 };
			check(a, 4, 3);
		}
		{
			int a[] = { 1, 1, 3, 3 };
			check(a, 4, 2);
		}
		{
			int a[] = { 1, 2, 3, 4, 5 };
			check(a, 5, 5);
		}
		{
			int a[] = { 1, 1, 2, 2, 5 };
			check(a, 5, 3);
		}
		{
			int a[] = { 1, 1, 3, 4, 5 };
			check(a, 5, 4);
		}
		{
			int a[] = { 1, 1, 1, 4, 4 };
			check(a, 5, 2);
		}
		{
			int a[] = { 1, 1, 1, 1, 5 };
			check(a, 5, 2);
		}
		{
			int a[] = { 1, 1, 1, 1, 1 };
			check(a, 5, 1);
		}
		{
			int a[] = { 1, 1, 3, 3, 3 };
			check(a, 5, 2);
		}
		{
			int a[] = { 1, 3, 3, 3, 3 };
			check(a, 5, 2);
		}
		{
			int a[] = { 1, 3, 3, 3, 4 };
			check(a, 5, 3);
		}
	});

	Add("RemoveDuplicates2", [&]() {
		auto print = [&](int a[], int n){
			for (int i = 0; i < n; i++) {
				Logger().WriteInformation(" %d", a[i]);
			}
			Logger().WriteInformation("\n");
		};

		auto check = [&](int a[], int n, int e){
			Logger().WriteInformation("Input: ");
			print(a, n);
			n = Test::LeetCode::RemoveDuplicates2(a, n);
			Logger().WriteInformation("Output:");
			print(a, n);
			ASSERT1(n == e);
		};

		{
			int a[] = { 1 };
			check(a, 1, 1);
		}
		{
			int a[] = { 1, 1 };
			check(a, 2, 2);
		}
		{
			int a[] = { 1, 2 };
			check(a, 2, 2);
		}
		{
			int a[] = { 1, 1, 2 };
			check(a, 3, 3);
		}
		{
			int a[] = { 1, 1, 1 };
			check(a, 3, 2);
		}
		{
			int a[] = { 1, 2, 2 };
			check(a, 3, 3);
		}
		{
			int a[] = { 1, 2, 3 };
			check(a, 3, 3);
		}
		{
			int a[] = { 1, 2, 3, 4 };
			check(a, 4, 4);
		}
		{
			int a[] = { 1, 1, 3, 4 };
			check(a, 4, 4);
		}
		{
			int a[] = { 1, 1, 1, 4 };
			check(a, 4, 3);
		}
		{
			int a[] = { 1, 1, 1, 1 };
			check(a, 4, 2);
		}
		{
			int a[] = { 1, 2, 2, 4 };
			check(a, 4, 4);
		}
		{
			int a[] = { 1, 2, 2, 2 };
			check(a, 4, 3);
		}
		{
			int a[] = { 1, 2, 3, 3 };
			check(a, 4, 4);
		}
		{
			int a[] = { 1, 1, 3, 3 };
			check(a, 4, 4);
		}
		{
			int a[] = { 1, 2, 3, 4, 5 };
			check(a, 5, 5);
		}
		{
			int a[] = { 1, 1, 2, 2, 5 };
			check(a, 5, 5);
		}
		{
			int a[] = { 1, 1, 3, 4, 5 };
			check(a, 5, 5);
		}
		{
			int a[] = { 1, 1, 1, 4, 4 };
			check(a, 5, 4);
		}
		{
			int a[] = { 1, 1, 1, 1, 5 };
			check(a, 5, 3);
		}
		{
			int a[] = { 1, 1, 1, 1, 1 };
			check(a, 5, 2);
		}
		{
			int a[] = { 1, 1, 3, 3, 3 };
			check(a, 5, 4);
		}
		{
			int a[] = { 1, 3, 3, 3, 3 };
			check(a, 5, 3);
		}
		{
			int a[] = { 1, 3, 3, 3, 4 };
			check(a, 5, 4);
		}
	});
}