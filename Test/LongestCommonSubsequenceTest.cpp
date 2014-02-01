#include "LongestCommonSubsequenceTest.h"

void LongestCommonSubsequenceTest::Init(void)
{
	Add("LCS", [&](){
		string x = "ABCBDAB";
		string y = "BDCABA";
		Test::LongestCommonSubsequence::PrintLCS(x, y);

		x = "ABCBDABJOHBFUOBLNJIPIOHUGOYO";
		y = "BDCABATIOFTYFIBLOILUIIGGOBLOBIP";
		Test::LongestCommonSubsequence::PrintLCS(x, y);
	});
}
