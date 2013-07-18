STD = c++11

.PHONY:
	all clean

all: main.cpp serializer.cpp algorithm.cpp
	$(CXX) -std=$(STD) $^ -o puddles
clean:
	rm -rf puddles
