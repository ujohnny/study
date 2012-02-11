#include <boost/test/minimal.hpp>
#include "tree.h"

int test_main(int, char* []) {
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
	BOOST_CHECK(*it == 2);
	it++;
	BOOST_CHECK(*it == 3);
	it++;
	BOOST_CHECK(*it == 4);
	it++;
	BOOST_CHECK(*it == 5);
	it++;
	BOOST_CHECK(*it == 6);
	it++;
	BOOST_CHECK(*it == 7);
	it++;
	BOOST_CHECK(*it == 8);
	return boost::exit_success;
}
