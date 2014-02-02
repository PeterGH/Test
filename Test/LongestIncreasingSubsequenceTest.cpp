#include "LongestIncreasingSubsequenceTest.h"

void LongestIncreasingSubsequenceTest::Init(void)
{
	Add("1", [&](){
		int I[] = { 1 };
		Test::LongestIncreasingSubsequence::PrintSolution(I, 1);
	});

	Add("2", [&](){
		int I1[] = { 1, 2};
		Test::LongestIncreasingSubsequence::PrintSolution(I1, 2);

		int I2[] = { 2, 1};
		Test::LongestIncreasingSubsequence::PrintSolution(I2, 2);
	});

	Add("3", [&](){
		int I1[] = { 1, 2, 3 };
		Test::LongestIncreasingSubsequence::PrintSolution(I1, 3);

		int I2[] = { 1, 3, 2 };
		Test::LongestIncreasingSubsequence::PrintSolution(I2, 3);

		int I3[] = { 2, 1, 3 };
		Test::LongestIncreasingSubsequence::PrintSolution(I3, 3);

		int I4[] = { 2, 3, 1 };
		Test::LongestIncreasingSubsequence::PrintSolution(I4, 3);

		int I5[] = { 3, 1, 2 };
		Test::LongestIncreasingSubsequence::PrintSolution(I5, 3);

		int I6[] = { 3, 2, 1 };
		Test::LongestIncreasingSubsequence::PrintSolution(I6, 3);
	});

	Add("4", [&](){
		int I1[] = { 1, 2, 3, 4 };
		Test::LongestIncreasingSubsequence::PrintSolution(I1, 4);

		int I2[] = { 1, 2, 4, 3 };
		Test::LongestIncreasingSubsequence::PrintSolution(I2, 4);

		int I3[] = { 1, 3, 2, 4 };
		Test::LongestIncreasingSubsequence::PrintSolution(I3, 4);

		int I4[] = { 1, 3, 4, 2 };
		Test::LongestIncreasingSubsequence::PrintSolution(I4, 4);

		int I5[] = { 1, 4, 2, 3 };
		Test::LongestIncreasingSubsequence::PrintSolution(I5, 4);

		int I6[] = { 1, 4, 3, 2 };
		Test::LongestIncreasingSubsequence::PrintSolution(I6, 4);

		int I7[] = { 2, 1, 3, 4 };
		Test::LongestIncreasingSubsequence::PrintSolution(I7, 4);

		int I8[] = { 2, 1, 4, 3 };
		Test::LongestIncreasingSubsequence::PrintSolution(I8, 4);

		int I9[] = { 2, 3, 1, 4 };
		Test::LongestIncreasingSubsequence::PrintSolution(I9, 4);

		int I10[] = { 2, 3, 4, 1 };
		Test::LongestIncreasingSubsequence::PrintSolution(I10, 4);

		int I11[] = { 2, 4, 1, 3 };
		Test::LongestIncreasingSubsequence::PrintSolution(I11, 4);

		int I12[] = { 2, 4, 3, 1 };
		Test::LongestIncreasingSubsequence::PrintSolution(I12, 4);

		int I13[] = { 3, 1, 2, 4 };
		Test::LongestIncreasingSubsequence::PrintSolution(I13, 4);

		int I14[] = { 3, 1, 4, 2 };
		Test::LongestIncreasingSubsequence::PrintSolution(I14, 4);

		int I15[] = { 3, 2, 1, 4 };
		Test::LongestIncreasingSubsequence::PrintSolution(I15, 4);

		int I16[] = { 3, 2, 4, 1 };
		Test::LongestIncreasingSubsequence::PrintSolution(I16, 4);

		int I17[] = { 3, 4, 1, 2 };
		Test::LongestIncreasingSubsequence::PrintSolution(I17, 4);

		int I18[] = { 3, 4, 2, 1 };
		Test::LongestIncreasingSubsequence::PrintSolution(I18, 4);

		int I19[] = { 4, 1, 2, 3 };
		Test::LongestIncreasingSubsequence::PrintSolution(I19, 4);

		int I20[] = { 4, 1, 3, 2 };
		Test::LongestIncreasingSubsequence::PrintSolution(I20, 4);

		int I21[] = { 4, 2, 1, 3 };
		Test::LongestIncreasingSubsequence::PrintSolution(I21, 4);

		int I22[] = { 4, 2, 3, 1 };
		Test::LongestIncreasingSubsequence::PrintSolution(I22, 4);

		int I23[] = { 4, 3, 1, 2 };
		Test::LongestIncreasingSubsequence::PrintSolution(I23, 4);

		int I24[] = { 4, 3, 2, 1 };
		Test::LongestIncreasingSubsequence::PrintSolution(I24, 4);
	});
}