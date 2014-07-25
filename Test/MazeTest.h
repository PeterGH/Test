#pragma once
#include "..\Algorithm\Maze.h"
#include "..\Algorithm\TestClass.h"
class MazeTest : public Test::TestClass {
public:
	MazeTest(Test::Log & log) : Test::TestClass(log) {}
	~MazeTest(void) {}
	void Init(void);
};

