#pragma once
#include <algorithm>
#include "..\Algorithm\Random.h"
#include "..\Algorithm\SeamCarving.h"
#include "..\Algorithm\TestClass.h"
using namespace std;
class SeamCarvingTest : public Test::TestClass {
public:
	SeamCarvingTest(Test::Log & log) : Test::TestClass(log) {}
	~SeamCarvingTest(void) {}
	void Init(void);
};

