#pragma once

#include <cppunit/TestCase.h>
#include <string>
#include "tree.h"

class TreeIteratorTest : public CppUnit::TestCase
{
public:
	TreeIteratorTest(std::string name) : CppUnit::TestCase(name) {}

	void runTest();
private:
	Tree mTree;
};
