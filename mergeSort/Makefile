libsort.so : merge.cpp
	g++ -c -fpic -ftest-coverage -fprofile-arcs merge.cpp -shared -o libsort.so

test : mergeTest.cpp
	g++ -L$(PWD) -lsort -lboost_unit_test_framework -fprofile-arcs -ftest-coverage mergeTest.cpp -o test

clean :
	rm -f libsort.so *.gcno *.gcda test