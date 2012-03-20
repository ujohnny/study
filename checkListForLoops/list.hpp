#pragma once

#include <boost/shared_ptr.hpp>

class Node;

class List {
public:
	List();
	void add();
	bool hasLoop();
	bool makeLoop(int begin, int end);

	inline int getSize() {
		return mSize;
	}
private:
	int mSize;
	boost::shared_ptr<Node> mHead;	
};
