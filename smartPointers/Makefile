CXX = g++
FLAGS = -fpic -c
OBJECTS = tree.o treeIterator.o
INCLUDES = -I/usr/include

libtree.so : $(OBJECTS)
	$(CXX) -shared $(OBJECTS) -o libtree.so

tree.o : tree.h tree.cpp treeElement.h treeIterator.h
	$(CXX) $(FLAGS) $(INCLUDES) tree.cpp -o tree.o

treeIterator.o : treeIterator.h treeIterator.cpp treeElement.h
	$(CXX) $(FLAGS) $(INCLUDES) treeIterator.cpp -o treeIterator.o

clean: 
	rm libtree.so $(OBJECTS)