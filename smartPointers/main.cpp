
#include <cppunit/TestResult.h>
#include <iostream>
#include "tree.h"
#include "treeIteratorTest.h"

int main(int argc, char *argv[])
{
	TreeIteratorTest test("equality");
	test.runTest();
}
