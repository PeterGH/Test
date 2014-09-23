#pragma once
#include "..\Algorithm\Maze.h"
#include "..\Algorithm\TestClass.h"
using namespace Test;
class MazeTest : public TestClass {
public:
	MazeTest(Log & log) : TestClass(log) {}
	~MazeTest(void) {}
	void Init(void);
};

