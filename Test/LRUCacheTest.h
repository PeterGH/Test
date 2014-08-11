#pragma once
#include "..\Algorithm\LRUCache.h"
#include "..\Algorithm\TestClass.h"
class LRUCacheTest : public Test::TestClass {
public:
	LRUCacheTest(Test::Log & log) : Test::TestClass(log) {}
	~LRUCacheTest(void) {}
	void Init(void);
};

