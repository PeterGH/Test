#pragma once

#include <queue>
#include "..\Algorithm\Queue.h"
#include "..\Algorithm\TestClass.h"

using namespace std;

class QueueTest : public Test::TestClass {
public:
	QueueTest(Test::Log & log) : Test::TestClass(log) {}
	~QueueTest(void) {}
	void Init(void);
};

