#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE IteratorTest
#include <boost/test/unit_test.hpp>
#include "tree.h"

BOOST_AUTO_TEST_SUITE (IteratorTest)

BOOST_AUTO_TEST_CASE (test_insert) {
	Tree t;
	t.insert(5);
	t.insert(2);
	t.insert(3);
	t.insert(4);
	t.insert(2);
	t.insert(6);
	t.insert(7);
	t.insert(8);
}

BOOST_AUTO_TEST_CASE (operators_test) {
	
	Tree t;
	t.insert(5);
	t.insert(2);
	t.insert(3);
	t.insert(4);
	t.insert(2);
	t.insert(6);
	t.insert(7);
	t.insert(8);
	Tree::iterator it = t.begin();

	BOOST_CHECK(*it == 2);
	it++;

	for (int i = 2; i < 8; i++, it++) {
		BOOST_CHECK(*it == i);
	}

	for (int i = 7; i > 2; i--) {
		--it;
		BOOST_CHECK(*it == i);
	}
	it--;
	BOOST_CHECK(*it == 2);
}

BOOST_AUTO_TEST_CASE (test_equals) {
	Tree t;
	t.insert(5);
	t.insert(6);
	Tree::iterator it1 = t.begin();
	Tree::iterator it2 = t.end();
	BOOST_CHECK(it1 != it2 == true);
	it1++;
	BOOST_CHECK(it1 == it2 == true);
}

BOOST_AUTO_TEST_SUITE_END()
