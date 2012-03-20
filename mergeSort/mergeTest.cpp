#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE mergeSortTest
#include <boost/test/unit_test.hpp>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "merge.cpp"

BOOST_AUTO_TEST_SUITE (mergeSortTest)

BOOST_AUTO_TEST_CASE (random) {
	srand(time(0));
	std::vector<int> v1;
	std::vector<int> v2;
	for (int i = 0; i < 99; i++) {
		int tmp = rand() % 300;
		v1.push_back(tmp);
		v2.push_back(tmp);
	}
	msort(v1, v1.begin(), v1.size());
	sort(v2.begin(), v2.end());
	for (int i = 0; i < v1.size(); i++) {
		BOOST_CHECK_EQUAL(v1[i], v2[i]);
	}
}
	
BOOST_AUTO_TEST_CASE (reverse) {
	std::vector<int> v1;
	std::vector<int> v2;
	for (int i = 11; i > 0; i--) {
		v1.push_back(i);
		v2.push_back(i);
	}
	msort(v1, v1.begin(), v1.size());
	sort(v2.begin(), v2.end());
	for (int i = 0; i < v1.size(); i++) {
		BOOST_CHECK_EQUAL(v1[i], v2[i]);
	}
}
BOOST_AUTO_TEST_SUITE_END()

