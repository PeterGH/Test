#pragma once

#include "..\Algorithm\Partition.h"
#include "..\Algorithm\TestClass.h"

class PartitionTest : public Test::TestClass {
public:
	PartitionTest(Test::Log & log) : Test::TestClass(log) {}
	~PartitionTest(void) {}
	void Init(void);
};

