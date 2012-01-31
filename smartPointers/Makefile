CXX = g++
FLAGS = -fpic -c
OBJECTS = tree.o treeIterator.o
INCLUDES = -I/usr/include

libTreeIterator.so : $(OBJECTS)
	$(CXX) -shared $(OBJECTS) -o libTreeIterator.so

tree.o : tree.h tree.cpp treeElement.h treeIterator.h
	$(CXX) $(FLAGS) $(INCLUDES) tree.cpp -o tree.o

treeIterator.o : treeIterator.h treeIterator.cpp treeElement.h
	$(CXX) $(FLAGS) $(INCLUDES) treeIterator.cpp -o treeIterator.o

clean: 
	rm libTreeIterator.so $(OBJECTS)