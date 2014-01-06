#pragma once

#include "..\Algorithm\Array.h"
#include "..\Algorithm\Random.h"
#include "..\Algorithm\YoungTableau.h"
#include "..\Algorithm\TestClass.h"

class YoungTableauTest : public Test::TestClass {
public:
	YoungTableauTest(Test::Log & log) : Test::TestClass(log) {}
	~YoungTableauTest(void) {}
	void Init(void);
};

