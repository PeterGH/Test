#include "LeetCodeTest.h"

void LeetCodeTest::Init(void)
{
	Add("RecoverTree", [&](){
		auto check = [&](Test::LeetCode::TreeNode * node) {
			Logger().WriteInformation("Recover tree\n");
			Test::LeetCode::Print(node);
			Test::LeetCode::TreeNode * copy = Test::LeetCode::Clone(node);
			Logger().WriteInformation("to\n");
			Test::LeetCode::RecoverTree(node);
			Test::LeetCode::RecoverTree2(copy);
			Test::LeetCode::Print(node);
			Test::LeetCode::Print(copy);
			bool equal = Test::LeetCode::Equal(node, copy);
			Test::LeetCode::DeleteTree(node);
			Test::LeetCode::DeleteTree(copy);
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
}