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
}