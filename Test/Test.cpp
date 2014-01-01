// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Algorithm\Argument.h"
#include "..\Algorithm\TestSuite.h"
#include "ArrayTest.h"
#include "BinarySearchTest.h"
#include "BitSetTest.h"
#include "CircularSingleLinkListTest.h"
#include "ColumnSortTest.h"
#include "HeapTest.h"
#include "InsertionSortTest.h"
#include "MergeSortTest.h"
#include "PartitionTest.h"
#include "QuickSortTest.h"
#include "RandomTest.h"
#include "SingleLinkListTest.h"
#include "SortedCircularSingleLinkListTest.h"
#include "SortedSingleLinkListTest.h"
#include "StringTest.h"
#include "TestClassTest.h"

int main(int argc, char * argv[])
{
	if (argc < 2) {
		cout << "Test.exe -l" << endl;
		cout << "\tList all tests." << endl;
		cout << "Test.exe Test -l" << endl;
		cout << "\tList all test methods of a test. The test name can be a partial name." << endl;
		cout << "Test.exe *" << endl;
		cout << "\tRun all tests." << endl;
		cout << "Test.exe Test" << endl;
		cout << "\tRun a specified test. The test name can be a partial name." << endl;
		cout << "Test.exe Test Method" << endl;
		cout << "\tRun a specified test method of a specific test. Both the test name and method name can be partial names." << endl;
		return 0;
	}

	// Note argc >= 1, argv[0] == "Test.exe"
	Test::Argument<char> arg(argc, argv);

	Test::LogLevel level = arg.Has("v") ? Test::LogLevel::Verbose : Test::LogLevel::Error;
	Test::Log log(cout, level);
	Test::TestSuite suite(log);

	suite.Add(new ArrayTest(log));
	suite.Add(new BinarySearchTest(log));
	suite.Add(new BitSetTest(log));
	suite.Add(new CircularSingleLinkListTest(log));
	suite.Add(new ColumnSortTest(log));
	suite.Add(new HeapTest(log));
	suite.Add(new InsertionSortTest(log));
	suite.Add(new MergeSortTest(log));
	suite.Add(new PartitionTest(log));
	suite.Add(new QuickSortTest(log));
	suite.Add(new RandomTest(log));
	suite.Add(new SingleLinkListTest(log));
	suite.Add(new SortedCircularSingleLinkListTest(log));
	suite.Add(new SortedSingleLinkListTest(log));
	suite.Add(new StringTest(log));
	suite.Add(new TestClassTest(log));
	
	if (arg.Has("l")) {
		if (arg.CountIndexedArgs() == 1) {
			cout << "Available tests are:" << endl;
			suite.List();
			return 0;
		} else if (arg.CountIndexedArgs() > 1) {
			suite.List(arg[1]);
			return 0;
		}
	} else if (arg.CountIndexedArgs() > 1) {
		if (arg[1] == "*") {
			suite.Run();
		} else if (arg.CountIndexedArgs() == 2) {
			suite.Run(arg[1]);
		} else {
			suite.Run(arg[1], arg[2]);
		}
	}

	suite.Report();
	return 0;
}

