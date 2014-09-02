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

	Add("SearchWord", [&](){
		auto print = [&](vector<vector<char>> & board) {
			Logger().WriteInformation("Board:\n");
			for_each (board.begin(), board.end(), [&](vector<char> & row){
				for_each (row.begin(), row.end(), [&](char c){
					Logger().WriteInformation(" %c", c);
				});
				Logger().WriteInformation("\n");
			});
		};
		auto check = [&](vector<vector<char>> & board, const string & word, bool expect) {
			bool actual = Test::LeetCode::SearchWord(board, word);
			Logger().WriteInformation("  %s is %sfound\n", word.c_str(), actual ? "" : "not ");
			ASSERT1(actual == expect);
		};
		{
			vector<vector<char>> b = {
					{ 'A' }
			};
			print(b);
			check(b, "A", true);
			check(b, "B", false);
			check(b, "AA", false);
			check(b, "AB", false);
		}
		{
			vector<vector<char>> b = {
					{ 'A', 'B' },
					{ 'B', 'A' }
			};
			print(b);
			check(b, "A", true);
			check(b, "B", true);
			check(b, "AA", false);
			check(b, "AB", true);
			check(b, "ABA", true);
			check(b, "BAB", true);
			check(b, "ABAB", true);
			check(b, "ABBA", false);
			check(b, "BAAB", false);
			check(b, "BABA", true);
		}
		{
			vector<vector<char>> b = {
					{ 'A', 'A' },
					{ 'A', 'A' }
			};
			print(b);
			check(b, "A", true);
			check(b, "B", false);
			check(b, "AA", true);
			check(b, "AAA", true);
			check(b, "AAAA", true);
			check(b, "AAAAA", false);
		}
		{
			vector<vector<char>> b = {
					{ 'A', 'B', 'C', 'E' },
					{ 'S', 'F', 'C', 'S' },
					{ 'A', 'D', 'E', 'E' }
			};
			print(b);
			check(b, "ABCCED", true);
			check(b, "SEE", true);
			check(b, "ABCB", false);
		}
		{
			vector<vector<char>> b = {
					{ 'A', 'B', 'C', 'E' },
					{ 'S', 'F', 'E', 'S' },
					{ 'A', 'D', 'E', 'E' }
			};
			print(b);
			check(b, "ABCEFSADEESE", true);
		}
	});

	Add("Combinations", [&](){
		auto print = [&](vector<vector<int>> & sets) {
			for_each (sets.begin(), sets.end(), [&](vector<int> & v){
				Logger().WriteInformation("  {");
				for (size_t i = 0; i < v.size(); i++) {
					if (i != 0) Logger().WriteInformation(", ");
					Logger().WriteInformation("%d", v[i]);
				}
				Logger().WriteInformation("}\n");
			});
		};
		auto check = [&](int n, int k){
			vector<vector<int>> sets = Test::LeetCode::Combinations(n, k);
			vector<vector<int>> sets2 = Test::LeetCode::Combinations2(n, k);
			Logger().WriteInformation("Choose(%d, %d):\n", n, k);
			print(sets);
			Logger().WriteInformation("Choose(%d, %d):\n", n, k);
			print(sets2);
			ASSERT1(sets.size() == sets2.size());
		};

		check(1, 1);
		check(2, 1);
		check(2, 2);
		check(3, 1);
		check(3, 2);
		check(3, 3);
		check(4, 1);
		check(4, 2);
		check(4, 3);
		check(4, 4);
		check(5, 1);
		check(5, 2);
		check(5, 3);
		check(5, 4);
		check(5, 5);
	});

	Add("MinWindow", [&](){
		auto check = [&](const string & s, const string & t, const string & e){
			Logger().WriteInformation("Source: %s\n", s.c_str());
			Logger().WriteInformation("Target: %s\n", t.c_str());
			string u = Test::LeetCode::MinWindow(s, t);
			string v = Test::LeetCode::MinWindow2(s, t);
			Logger().WriteInformation("Substring: %s %s %s\n", u.c_str(), u == v ? "==" : "!=", v.c_str());
			ASSERT1(u == e);
			ASSERT1(v == e);
		};
		check("", "", "");
		check("", "A", "");
		check("A", "", "");
		check("AA", "A", "A");
		check("AA", "AA", "AA");
		check("AB", "A", "A");
		check("AB", "B", "B");
		check("AB", "BA", "AB");
		check("AB", "AB", "AB");
		check("ACCCCCBCCCACCACB", "ABA", "ACCACB");
		check("ACCCCCBCCCACCACB", "ABD", "");
		check("ADOBECODEBANC", "ABC", "BANC");
	});

	Add("SortColors", [&](){
		auto print = [&](int a[], int n){
			Logger().WriteInformation("[");
				for (int i = 0; i < n; i++) {
					if (i != 0) Logger().WriteInformation(" ");
					Logger().WriteInformation("%d", a[i]);
				}
				Logger().WriteInformation("]\n");
		};
		auto check = [&](int a[], int n){
			Logger().WriteInformation("Input:  ");
			print(a, n);
			Test::LeetCode::SortColors(a, n);
			Logger().WriteInformation("Output: ");
			print(a, n);
			for (int i = 1; i < n; i++) {
				ASSERT1(a[i] >= a[i-1]);
			}
		};
		{
			int a[] = { 1 };
			check(a, 1);
		}
		{
			int a[] = { 0, 0 };
			check(a, 2);
		}
		{
			int a[] = { 0, 1 };
			check(a, 2);
		}
		{
			int a[] = { 0, 2 };
			check(a, 2);
		}
		{
			int a[] = { 1, 0 };
			check(a, 2);
		}
		{
			int a[] = { 1, 1 };
			check(a, 2);
		}
		{
			int a[] = { 1, 2 };
			check(a, 2);
		}
		{
			int a[] = { 2, 0 };
			check(a, 2);
		}
		{
			int a[] = { 2, 1 };
			check(a, 2);
		}
		{
			int a[] = { 2, 2 };
			check(a, 2);
		}
		{
			int a[] = { 0, 0, 0 };
			check(a, 3);
		}
		{
			int a[] = { 0, 0, 1 };
			check(a, 3);
		}
		{
			int a[] = { 0, 0, 2 };
			check(a, 3);
		}
		{
			int a[] = { 0, 1, 0 };
			check(a, 3);
		}
		{
			int a[] = { 0, 1, 1 };
			check(a, 3);
		}
		{
			int a[] = { 0, 1, 2 };
			check(a, 3);
		}
		{
			int a[] = { 0, 2, 0 };
			check(a, 3);
		}
		{
			int a[] = { 0, 2, 1 };
			check(a, 3);
		}
		{
			int a[] = { 0, 2, 2 };
			check(a, 3);
		}
		{
			int a[] = { 1, 0, 0 };
			check(a, 3);
		}
		{
			int a[] = { 1, 0, 1 };
			check(a, 3);
		}
		{
			int a[] = { 1, 0, 2 };
			check(a, 3);
		}
		{
			int a[] = { 1, 1, 0 };
			check(a, 3);
		}
		{
			int a[] = { 1, 1, 1 };
			check(a, 3);
		}
		{
			int a[] = { 1, 1, 2 };
			check(a, 3);
		}
		{
			int a[] = { 1, 2, 0 };
			check(a, 3);
		}
		{
			int a[] = { 1, 2, 1 };
			check(a, 3);
		}
		{
			int a[] = { 1, 2, 2 };
			check(a, 3);
		}
		{
			int a[] = { 2, 0, 0 };
			check(a, 3);
		}
		{
			int a[] = { 2, 0, 1 };
			check(a, 3);
		}
		{
			int a[] = { 2, 0, 2 };
			check(a, 3);
		}
		{
			int a[] = { 2, 1, 0 };
			check(a, 3);
		}
		{
			int a[] = { 2, 1, 1 };
			check(a, 3);
		}
		{
			int a[] = { 2, 1, 2 };
			check(a, 3);
		}
		{
			int a[] = { 2, 2, 0 };
			check(a, 3);
		}
		{
			int a[] = { 2, 2, 1 };
			check(a, 3);
		}
		{
			int a[] = { 2, 2, 2 };
			check(a, 3);
		}
		{
			for (int i = 0; i < 100; i++) {
				int len = 1 + Test::Random::Next(50);
				unique_ptr<int[]> a(new int[len]);
				for (int j = 0; j < len; j++) {
					int v = Test::Random::Next();
					v = v % 3;
					a[j] = v;
				}
				check(a.get(), len);
			}
		}
	});

	Add("SearchMatrix", [&](){
		auto print = [&](vector<vector<int>> & m) {
			Logger().WriteInformation("Matrix:\n");
			for_each (m.begin(), m.end(), [&](vector<int> & v){
				Logger().WriteInformation("  ");
				for (size_t i = 0; i < v.size(); i++) {
					if (i != 0) Logger().WriteInformation(" ");
					Logger().WriteInformation("%d", v[i]);
				}
				Logger().WriteInformation("\n");
			});
		};
		auto check = [&](vector<vector<int>> & m, int t, bool e){
			bool a = Test::LeetCode::SearchMatrix(m, t);
			Logger().WriteInformation("%d is %sfound\n", t, a ? "" : "not ");
			ASSERT1(a == e);
		};
		{
			vector<vector<int>> m = {
					{1,   3,  5,  7},
					{10, 11, 16, 20},
					{23, 30, 34, 50}
			};
			print(m);
			check(m, 1, true);
			check(m, 2, false);
			check(m, 3, true);
			check(m, 4, false);
			check(m, 5, true);
			check(m, 6, false);
			check(m, 7, true);
			check(m, 8, false);
			check(m, 10, true);
			check(m, 11, true);
			check(m, 12, false);
			check(m, 16, true);
			check(m, 18, false);
			check(m, 20, true);
			check(m, 21, false);
			check(m, 23, true);
			check(m, 25, false);
			check(m, 30, true);
			check(m, 32, false);
			check(m, 34, true);
			check(m, 40, false);
			check(m, 50, true);
			check(m, 60, false);
		}
	});

	Add("MinDistance1", [&](){
		auto check = [&](const string & w1, const string & w2, int e){
			Logger().WriteInformation("Source:   %s\n", w1.c_str());
			Logger().WriteInformation("Target:   %s\n", w2.c_str());
			int a = Test::LeetCode::MinDistance(w1, w2);
			int b = Test::LeetCode::MinDistance2(w1, w2);
			Logger().WriteInformation("Distance: %d, %d\n", a, b);
			ASSERT1(a == e);
			ASSERT1(b == e);
		};
		check("", "", 0);
		check("a", "", 1);
		check("ab", "", 2);
		check("", "b", 1);
		check("", "bc", 2);
		check("a", "a", 0);
		check("a", "b", 1);
		check("aa", "a", 1);
		check("aa", "b", 2);
		check("a", "bb", 2);
		check("b", "bb", 1);
		check("aa", "bb", 2);
		check("aa", "ab", 1);
		check("aa", "ba", 1);
		check("ab", "bb", 1);
		check("ba", "bb", 1);
		check("bb", "bb", 0);
		check("aaa", "a", 2);
		check("aaa", "b", 3);
		check("aaa", "aa", 1);
		check("aaa", "ab", 2);
		check("aaa", "ba", 2);
		check("aaa", "bc", 3);
		check("aaa", "abc", 2);
		check("aaa", "bac", 2);
		check("aaa", "bca", 2);
		check("aaa", "aab", 1);
		check("aaa", "aba", 1);
		check("aaa", "baa", 1);
		check("aaa", "bcd", 3);
		check("aaa", "aaa", 0);
		check("a", "aaa", 2);
		check("b", "aaa", 3);
		check("aa", "aaa", 1);
		check("ab", "aaa", 2);
		check("ba", "aaa", 2);
		check("bc", "aaa", 3);
		check("abc", "aaa", 2);
		check("bac", "aaa", 2);
		check("bca", "aaa", 2);
		check("aab", "aaa", 1);
		check("aba", "aaa", 1);
		check("baa", "aaa", 1);
		check("bcd", "aaa", 3);
		check("aaa", "aaa", 0);
		check("e", "dhwjmfxritzebjkoqvtm", 19);
	});

	Add("MinDistance2", [&](){
		for (int i = 0; i < 100; i++) {
			int len1 = 1 + Test::Random::Next(100);
			string w1;
			for (int j = 0; j < len1; j++) {
				char c = 'a' + (Test::Random::Next(100) % 26);
				w1.append(1, c);
			}
			int len2 = 1 + Test::Random::Next(100);
			string w2;
			for (int j = 0; j < len2; j++) {
				char c = 'a' + (Test::Random::Next(100) % 26);
				w2.append(1, c);
			}
			Logger().WriteInformation("Source:   %s\n", w1.c_str());
			Logger().WriteInformation("Target:   %s\n", w2.c_str());
			int d1 = Test::LeetCode::MinDistance(w1, w2);
			int d2 = Test::LeetCode::MinDistance2(w1, w2);
			Logger().WriteInformation("Distance: %d %s %d\n", d1, d1 == d2 ? "==" : "!=", d2);
			ASSERT1(d1 == d2);
		}
	});

	Add("SimplifyPath", [&](){
		auto check = [&](const string & p, const string e) {
			Logger().WriteInformation("Input:  %s\n", p.c_str());
			string a = Test::LeetCode::SimplifyPath(p);
			Logger().WriteInformation("Output: %s\n", a.c_str());
			ASSERT1(a == e);
		};

		check("", "");

		check("/", "/");
		check(".", "/");
		check("a", "/a");

		check("//", "/");
		check("..", "/");
		check("ab", "/ab");

		check("/.", "/");
		check("./", "/");

		check("/a", "/a");
		check("a/", "/a");

		check(".a", "/.a");
		check("a.", "/a.");

		check("///", "/");
		check("...", "/...");
		check("abc", "/abc");

		check("/..", "/");
		check("../", "/");
		check("./.", "/");

		check(".//", "/");
		check("/./", "/");
		check("//.", "/");

		check("/ab", "/ab");
		check("a/b", "/a/b");
		check("ab/", "/ab");

		check("a//", "/a");
		check("/a/", "/a");
		check("//a", "/a");

		check("/a.", "/a.");
		check("/.a", "/.a");
		check("./a", "/a");
		check(".a/", "/.a");
		check("a/.", "/a");
		check("a./", "/a.");

		check(".ab", "/.ab");
		check("a.b", "/a.b");
		check("ab.", "/ab.");

		check("a..", "/a..");
		check(".a.", "/.a.");
		check("..a", "/..a");

		check("////", "/");
		check("....", "/....");
		check("abcd", "/abcd");

		check(".///", "/");
		check("/.//", "/");
		check("//./", "/");
		check("///.", "/");

		check("..//", "/");
		check("././", "/");
		check(".//.", "/");
		check("/../", "/");
		check("/./.", "/");
		check("//..", "/");

		check("/...", "/...");
		check("./..", "/");
		check("../.", "/");
		check(".../", "/...");

		check("./a/", "/a");
		check(".//a", "/a");
		check(".a//", "/.a");
		check("/.a/", "/.a");
		check("/./a", "/a");
		check("/a./", "/a.");
		check("/a/.", "/a");
		check("//.a", "/.a");
		check("//a.", "/a.");
		check("a.//", "/a.");
		check("a/./", "/a");
		check("a//.", "/a");

		check("../a", "/a");
		check("..a/", "/..a");
		check("./.a", "/.a");
		check("./a.", "/a.");
		check(".a/.", "/.a");
		check(".a./", "/.a.");
		check("/a..", "/a..");
		check("/.a.", "/.a.");
		check("/..a", "/..a");
		check("a/..", "/");
		check("a./.", "/a.");
		check("a../", "/a..");

		check("//ab", "/ab");
		check("/a/b", "/a/b");
		check("/ab/", "/ab");

		check("./ab", "/ab");
		check(".a/b", "/.a/b");
		check(".ab/", "/.ab");
		check("/.ab", "/.ab");
		check("/a.b", "/a.b");
		check("/ab.", "/ab.");
		check("a./b", "/a./b");
		check("a.b/", "/a.b");
		check("a/.b", "/a/.b");
		check("a/b.", "/a/b.");
		check("ab./", "/ab.");
		check("ab/.", "/ab");

		check("..ab", "/..ab");
		check(".a.b", "/.a.b");
		check(".ab.", "/.ab.");
		check("a..b", "/a..b");
		check("a.b.", "/a.b.");
		check("ab..", "/ab..");

		check(".abc", "/.abc");
		check("a.bc", "/a.bc");
		check("ab.c", "/ab.c");
		check("abc.", "/abc.");

		check("/abc", "/abc");
		check("a/bc", "/a/bc");
		check("ab/c", "/ab/c");
		check("abc/", "/abc");

		check("/....", "/....");
		check("./...", "/...");
		check("../..", "/");
		check(".../.", "/...");
		check("..../", "/....");

		check("//...", "/...");
		check("/./..", "/");
		check("/../.", "/");
		check("/.../", "/...");

		check("/a/b/c", "/a/b/c");
		check("//ab/c", "/ab/c");
		check("///abc", "/abc");
		check("/a/./..", "/");
		check("/a/b/..", "/a");
		check("/a/../b", "/b");
		check("/../a/./b", "/a/b");
	});

	Add("Sqrt", [&](){
		auto check = [&](int x){
			Logger().WriteInformation("sqrt(%d) = ", x);
			int a = Test::LeetCode::Sqrt(x);
			int b = (int)sqrt(x);
			Logger().WriteInformation("%d, %d\n", a, b);
			ASSERT1(a == b);
		};
		check(0);
		check(1);
		check(2);
		check(3);
		check(4);
		check(5);
		check(6);
		check(7);
		check(8);
		check(9);
		check(10);
		check(INT_MAX - 9);
		check(INT_MAX - 8);
		check(INT_MAX - 7);
		check(INT_MAX - 6);
		check(INT_MAX - 5);
		check(INT_MAX - 4);
		check(INT_MAX - 3);
		check(INT_MAX - 2);
		check(INT_MAX - 1);
		check(INT_MAX);
		for (int i = 0; i < 100; i++) {
			int v = Test::Random::Next();
			check(v);
		}
	});

	Add("TextJustification", [&](){
		auto print = [&](vector<string> words){
			Logger().WriteInformation("Words:");
			for_each (words.begin(), words.end(), [&](string & w){
				Logger().WriteInformation(" %s", w.c_str());
			});
			Logger().WriteInformation("\n");
		};
		auto check = [&](vector<string> words, int l){
			vector<string> text = Test::LeetCode::TextJustification(words, l);
			Logger().WriteInformation("Format with width %d:\n", l);
			for_each (text.begin(), text.end(), [&](string & w){
				Logger().WriteInformation("  \"%s\"\n", w.c_str());
			});
			Logger().WriteInformation("\n");
		};
		{
			vector<string> w = { "This" };
			print(w);
			check(w, 4);
			check(w, 5);
			check(w, 6);
		}
		{
			vector<string> w = { "This", "is" };
			print(w);
			for (int i = 4; i < 10; i++) {
				check(w, i);
			}
		}
		{
			vector<string> w = { "This", "is", "an" };
			print(w);
			for (int i = 4; i < 12; i++) {
				check(w, i);
			}
		}
		{
			vector<string> w = { "This", "is", "an", "example", "of", "text", "justification." };
			print(w);
			for (int i = 14; i < 60; i++) {
				check(w, i);
			}
		}
	});

	Add("PlusOne", [&](){
		auto number = [&](vector<int> & digits)->int{
			int s = 0;
			for_each (digits.begin(), digits.end(), [&](int n){
				s = 10 * s + n;
			});
			return s;
		};
		auto check = [&](vector<int> & digits){
			int a = number(digits);
			Logger().WriteInformation("%d + 1 = ", a);
			vector<int> output = Test::LeetCode::PlusOne(digits);
			int b = number(output);
			Logger().WriteInformation("%d\n", b);
			ASSERT1(a + 1 == b);
		};
		check(vector<int> { 0 });
		check(vector<int> { 9 });
		check(vector<int> { 1, 0 });
		check(vector<int> { 1, 9 });
		check(vector<int> { 9, 9 });
		check(vector<int> { 1, 0, 0 });
		check(vector<int> { 1, 0, 9 });
		check(vector<int> { 1, 9, 0 });
		check(vector<int> { 1, 9, 9 });
		check(vector<int> { 9, 9, 9 });
	});

	Add("IsNumber", [&](){
		auto check = [&](const char * s, bool e) {
			Logger().WriteInformation("%s", s);
			bool a = Test::LeetCode::IsNumber(s);
			Logger().WriteInformation(" is %sa number\n", a ? "" : "not ");
			ASSERT1(a == e);
		};
		check("  00  ", true);
		cout << "\t00 = " << 00 << endl;
		check("  +00  ", true);
		cout << "\t+00 = " << +00 << endl;
		check("  01  ", true);
		cout << "\t01 = " << 01 << endl;
		check("  -01  ", true);
		cout << "\t-01 = " << -01 << endl;
		check("  00.0  ", true);
		cout << "\t00.0 = " << 00.0 << endl;
		check("  +00.0  ", true);
		cout << "\t+00.0 = " << +00.0 << endl;
		check("  00.  ", true);
		cout << "\t00. = " << 00. << endl;
		check("  -00.  ", true);
		cout << "\t-00. = " << -00. << endl;
		check("  1.  ", true);
		cout << "\t1. = " << 1. << endl;
		check("  +1.  ", true);
		cout << "\t+1. = " << +1. << endl;
		check("  .1  ", true);
		cout << "\t.1 = " << .1 << endl;
		check("  -.1  ", true);
		cout << "\t-.1 = " << -.1 << endl;
		check("  .1e010  ", true);
		cout << "\t.1e010 = " << .1e010 << endl;
		check("  +.1e010  ", true);
		cout << "\t+.1e010 = " << +.1e010 << endl;
		check("  .1e-010  ", true);
		cout << "\t.1e-010 = " << .1e-010 << endl;
		check("  -.1e-010  ", true);
		cout << "\t-.1e-010 = " << -.1e-010 << endl;
		check("  .1e+02  ", true);
		cout << "\t.1e+02 = " << .1e+02 << endl;
		check("  +.1e+02  ", true);
		cout << "\t+.1e+02 = " << +.1e+02 << endl;
		check("  .1e-02  ", true);
		cout << "\t.1e-02 = " << .1e-02 << endl;
		check("  -.1e-02  ", true);
		cout << "\t-.1e-02 = " << -.1e-02 << endl;
		check("2e0", true);
		cout << "\t2e0 = " << 2e0 << endl;
		check("2.e01", true);
		cout << "\t2.e01 = " << 2.e01 << endl;
		check(".", false);
		check("-.", false);
		check("0e", false);
		check("e+02", false);
		check(".e+02", false);
		check("+e+02", false);
		check(".1e.1", false);
		check(".1e0.1", false);
	});

	Add("AddBinaryString", [&](){
		auto check = [&](const string & a, const string & b, const string & e){
			int width = 1 + max(a.length(), b.length());
			Logger().WriteInformation("\n   %s%s\n", string(width - a.length(), ' ').c_str(), a.c_str());
			Logger().WriteInformation(" + %s%s\n", string(width - b.length(), ' ').c_str(), b.c_str());
			string c = Test::LeetCode::AddBinaryString(a, b);
			Logger().WriteInformation(" = %s%s\n", string(width - c.length(), ' ').c_str(), c.c_str());
			ASSERT1(c == e);
		};
		check("0", "0", "0");
		check("0", "1", "1");
		check("1", "0", "1");
		check("1", "1", "10");
		check("00", "00", "00");
		check("01", "01", "10");
		check("01", "10", "11");
		check("00", "11", "11");
		check("11", "01", "100");
		check("11", "10", "101");
		check("11", "11", "110");
		check("11", "1", "100");
		check("1110", "10", "10000");
		check("101", "11101", "100010");
	});

	Add("MergeSortedLists", [&](){
		auto check = [&](vector<int> & v1, vector<int> & v2){
			Logger().WriteInformation("Merge:\n");
			Test::LeetCode::ListNode * l1 = Test::LeetCode::ToList(v1);
			Test::LeetCode::ListNode * l2 = Test::LeetCode::ToList(v2);
			Test::LeetCode::Print(l1);
			Test::LeetCode::Print(l2);
			Test::LeetCode::ListNode * l3 = Test::LeetCode::MergeSortedLists(l1, l2);
			Test::LeetCode::Print(l3);
			Test::LeetCode::ListNode * p = l3;
			Test::LeetCode::ListNode * q = p->next;
			bool sorted = true;
			while (q != nullptr) {
				if (p->val > q->val) sorted = false;
				p = q;
				q = p->next;
			}
			Test::LeetCode::DeleteList(l3);
			ASSERT1(sorted == true);
		};
		{
			vector<int> v1 { 0 };
			vector<int> v2 { 0 };
			check(v1, v2);
		}
		{
			vector<int> v1 { 0 };
			vector<int> v2 { 1 };
			check(v1, v2);
		}
		{
			vector<int> v1 { 1 };
			vector<int> v2 { 0 };
			check(v1, v2);
		}
		{
			vector<int> v1 { 0 };
			vector<int> v2 { 0, 1 };
			check(v1, v2);
		}
		{
			vector<int> v1 { 0, 1 };
			vector<int> v2 { 0 };
			check(v1, v2);
		}
		{
			vector<int> v1 { 0 };
			vector<int> v2 { 1, 2 };
			check(v1, v2);
		}
		{
			vector<int> v1 { 1, 2 };
			vector<int> v2 { 0 };
			check(v1, v2);
		}
		{
			vector<int> v1 { 1 };
			vector<int> v2 { 0, 1 };
			check(v1, v2);
		}
		{
			vector<int> v1 { 0, 1 };
			vector<int> v2 { 1 };
			check(v1, v2);
		}
		{
			vector<int> v1 { 2 };
			vector<int> v2 { 0, 1 };
			check(v1, v2);
		}
		{
			vector<int> v1 { 0, 1 };
			vector<int> v2 { 2 };
			check(v1, v2);
		}
		{
			vector<int> v1 { 1 };
			vector<int> v2 { 0, 2 };
			check(v1, v2);
		}
		{
			vector<int> v1 { 0, 2 };
			vector<int> v2 { 1 };
			check(v1, v2);
		}
		{
			for (int i = 0; i < 100; i++) {
				int len1 = 1 + Test::Random::Next(100);
				vector<int> v1;
				for (int i = 0; i < len1; i++) {
					int v = Test::Random::Next();
					v1.push_back(v);
				}
				sort(v1.begin(), v1.end());
				int len2 = 1 + Test::Random::Next(100);
				vector<int> v2;
				for (int i = 0; i < len2; i++) {
					int v = Test::Random::Next();
					v2.push_back(v);
				}
				sort(v2.begin(), v2.end());
				check(v1, v2);
			}
		}
	});

	Add("RotateRight", [&](){
		auto check = [&](vector<int> & v, int k){
			Logger().WriteInformation("Right rotate list by %d\n", k);
			Test::LeetCode::ListNode * l = Test::LeetCode::ToList(v);
			Test::LeetCode::Print(l);
			l = Test::LeetCode::RotateRight(l, k);
			Test::LeetCode::Print(l);
			Test::LeetCode::DeleteList(l);
		};
		{
			vector<int> v = { 0 };
			check(v, 0);
			check(v, 1);
			check(v, 2);
		}
		{
			vector<int> v = { 0, 1 };
			check(v, 0);
			check(v, 1);
			check(v, 2);
			check(v, 3);
			check(v, 4);
			check(v, 5);
		}
		{
			vector<int> v = { 0, 1, 2 };
			check(v, 0);
			check(v, 1);
			check(v, 2);
			check(v, 3);
			check(v, 4);
			check(v, 5);
			check(v, 6);
			check(v, 7);
			check(v, 8);
		}
	});

	Add("GetPermutation", [&](){
		auto fact = [&](int n)-> int {
			int m = 1;
			for ( int i = 1; i <= n; i++) {
				m *= i;
			}
			return m;
		};
		auto print = [&](int n){
			for (int i = 1; i <= n; i++) {
				Logger().WriteInformation("%c", '0' + i);
			}
			Logger().WriteInformation("\n");
		};
		auto check = [&](int n){
			print(n);
			int m = fact(n);
			for (int i = 1; i <= m; i++) {
				string p = Test::LeetCode::GetPermutation(n, i);
				Logger().WriteInformation("  %d  %s\n", i, p.c_str());
			}
		};
		check(1);
		check(2);
		check(3);
		check(4);
		check(5);
		check(6);
		check(7);
		check(8);
		check(9);
	});

	Add("SpiralOrder1", [&](){
		auto print = [&](vector<vector<int>> & m) {
			Logger().WriteInformation("Matrix:\n");
			for_each (m.begin(), m.end(), [&](vector<int> & v){
				Logger().WriteInformation("  ");
				for (size_t i = 0; i < v.size(); i++) {
					if (i != 0) Logger().WriteInformation(" ");
					Logger().WriteInformation("%d", v[i]);
				}
				Logger().WriteInformation("\n");
			});
		};
		auto check = [&](vector<vector<int>> m){
			print(m);
			vector<int> o = Test::LeetCode::SpiralOrder(m);
			Logger().WriteInformation("  ");
			for (size_t i = 0; i < o.size(); i++) {
				if (i != 0) Logger().WriteInformation(" ");
				Logger().WriteInformation("%d", o[i]);
			}
			Logger().WriteInformation("\n");
			for (size_t i = 0; i < o.size(); i++) {
				ASSERT1(o[i] == i);
			}
		};
		{
			vector<vector<int>> m = {
					{ 0 }
			};
			check(m);
		}
		{
			vector<vector<int>> m = {
					{ 0, 1 }
			};
			check(m);
		}
		{
			vector<vector<int>> m = {
					{ 0, 1, 2 }
			};
			check(m);
		}
		{
			vector<vector<int>> m = {
					{ 0 },
					{ 1 }
			};
			check(m);
		}
		{
			vector<vector<int>> m = {
					{ 0 },
					{ 1 },
					{ 2 }
			};
			check(m);
		}
		{
			vector<vector<int>> m = {
					{ 0, 1 },
					{ 3, 2 }
			};
			check(m);
		}
		{
			vector<vector<int>> m = {
					{ 0, 1, 2 },
					{ 5, 4, 3 }
			};
			check(m);
		}
		{
			vector<vector<int>> m = {
					{ 0, 1 },
					{ 5, 2 },
					{ 4, 3 }
			};
			check(m);
		}
		{
			vector<vector<int>> m = {
					{ 0, 1, 2 },
					{ 7, 8, 3 },
					{ 6, 5, 4 }
			};
			check(m);
		}
		{
			vector<vector<int>> m = {
					{ 0, 1,  2,  3 },
					{ 9, 10, 11, 4 },
					{ 8, 7,  6,  5 }
			};
			check(m);
		}
		{
			vector<vector<int>> m = {
					{ 0, 1,  2 },
					{ 9, 10, 3 },
					{ 8, 11, 4 },
					{ 7, 6,  5 }
			};
			check(m);
		}
		{
			vector<vector<int>> m = {
					{ 0,  1,  2,  3 },
					{ 11, 12, 13, 4 },
					{ 10, 15, 14, 5 },
					{ 9,  8,  7,  6 }
			};
			check(m);
		}
	});

	Add("SpiralOrder2", [&](){
		auto print = [&](vector<vector<int>> & m) {
			for_each (m.begin(), m.end(), [&](vector<int> & v){
				Logger().WriteInformation("  ");
				for (size_t i = 0; i < v.size(); i++) {
					if (i != 0) Logger().WriteInformation(" ");
					Logger().WriteInformation("%d", v[i]);
				}
				Logger().WriteInformation("\n");
			});
		};
		auto check = [&](int n){
			Logger().WriteInformation("%dX%d matrix:\n", n, n);
			vector<vector<int>> m = Test::LeetCode::SpiralOrderMatrix(n);
			print(m);
			vector<int> o = Test::LeetCode::SpiralOrder(m);
			Logger().WriteInformation("  ");
			for (size_t i = 0; i < o.size(); i++) {
				if (i != 0) Logger().WriteInformation(" ");
				Logger().WriteInformation("%d", o[i]);
			}
			Logger().WriteInformation("\n");
			for (size_t i = 0; i < o.size(); i++) {
				ASSERT1(o[i] == i + 1);
			}
		};
		check(1);
		check(2);
		check(3);
		check(4);
		check(5);
		check(6);
		check(7);
		check(8);
		check(9);
		check(10);
	});

	Add("MergeIntervals", [&](){
		auto print = [&](vector<Test::LeetCode::Interval> it){
			for_each(it.begin(), it.end(), [&](Test::LeetCode::Interval i){
				Logger().WriteInformation(" [%d,%d]", i.start, i.end);
			});
			Logger().WriteInformation("\n");
		};
		auto check = [&](vector<Test::LeetCode::Interval> it){
			Logger().WriteInformation("Input: ");
			print(it);
			vector<Test::LeetCode::Interval> o = Test::LeetCode::MergeIntervals(it);
			Logger().WriteInformation("Output:");
			print(o);
		};
		{
			vector<Test::LeetCode::Interval> it = {
				Test::LeetCode::Interval(74,78),
				Test::LeetCode::Interval(61,63),
				Test::LeetCode::Interval(46,50),
				Test::LeetCode::Interval(51,54),
				Test::LeetCode::Interval(50,50),
				Test::LeetCode::Interval(60,64),
				Test::LeetCode::Interval(39,42),
				Test::LeetCode::Interval(25,27),
				Test::LeetCode::Interval(91,95)
			};
			check(it);
		}
	});

	Add("JumpGame", [&](){
		auto check = [&](int a[], int n){
			for (int i = 0; i < n; i++) {
				Logger().WriteInformation(" %d", a[i]);
			}
			Logger().WriteInformation("\n");
			bool j = Test::LeetCode::CanJump(a, n);
			bool k = Test::LeetCode::CanJump2(a, n);
			Logger().WriteInformation("Can %sjump\n", j ? "" : "not ");
			Logger().WriteInformation("Can %sjump\n", k ? "" : "not ");
			ASSERT1(j == k);
		};
		{
			int a[] = { 0, 1 };
			check(a, 2);
		}
		{
			int a[] = { 2, 3, 1, 1, 4 };
			check(a, 5);
		}
		{
			int a[] = { 3, 2, 1, 0, 4 };
			check(a, 5);
		}
	});
}