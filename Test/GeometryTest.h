#pragma once
#include "..\Algorithm\Geometry.h"
#include "..\Algorithm\Random.h"
#include "..\Algorithm\TestClass.h"
class GeometryTest : public Test::TestClass {
public:
	GeometryTest(Test::Log & log) : Test::TestClass(log) {}
	~GeometryTest(void) {}
	void Init(void);
};

