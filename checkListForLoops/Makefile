CXX = g++
SOURCES = node.hpp list.hpp list.cpp

liblist.so : list.o
	$(CXX) list.o -fprofile-arcs -shared -o liblist.so

list.o : $(SOURCES)
	$(CXX) -c -fpic -ftest-coverage -fprofile-arcs list.cpp -o list.o

test : listTest.cpp
	$(CXX) -L$(PWD) -llist -lboost_unit_test_framework -fprofile-arcs -ftest-coverage listTest.cpp -o test

clean : 
	rm -f liblist.so list.o test *.gcda *.gcno