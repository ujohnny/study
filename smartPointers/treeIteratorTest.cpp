#include "treeIteratorTest.h"

void TreeIteratorTest::runTest() {
	mTree.insert(0);
	mTree.insert(10);
	mTree.insert(4);
	mTree.insert(3);
	mTree.insert(2);
	mTree.insert(1);
	mTree.insert(9);
	mTree.insert(8);
	mTree.insert(7);
	mTree.insert(5);
	mTree.insert(6);
	TreeIterator i = mTree.iterator();
	int current = 0;
	while (i.hasNext()) {
		CPPUNIT_ASSERT_EQUAL(i.next().get()->getValue(), current);
		current++;
	}
}
