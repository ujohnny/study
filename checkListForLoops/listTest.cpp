#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE listTest
#include <boost/test/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_SUITE (listTest)

BOOST_AUTO_TEST_CASE (self_loop_test) {
	List list;
	list.add();
	list.makeLoop(0, 0);
	BOOST_CHECK(list.hasLoop() == true);
}

BOOST_AUTO_TEST_CASE (loop_test) {
	List list;
	list.add();
	list.add();
	list.add();
	list.add();
	list.makeLoop(3, 1);
	BOOST_CHECK(list.hasLoop() == true);
}

BOOST_AUTO_TEST_CASE (unaviable_loop_test) {
	List list;
	list.add();
	list.add();
	BOOST_CHECK(list.makeLoop(0, 1) == false);
}

BOOST_AUTO_TEST_CASE (no_loop_test) {
	List list;
	list.add();
	list.add();
	list.add();
	BOOST_CHECK(list.hasLoop() == false);
}

BOOST_AUTO_TEST_SUITE_END()
