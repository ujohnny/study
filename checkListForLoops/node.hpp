#pragma once

#include <boost/shared_ptr.hpp>

class Node {
public:
	boost::shared_ptr<Node> getNext() {
		return mNext;
	}
	void setNext(boost::shared_ptr<Node> node) {
		mNext = node;
	}
private:
	boost::shared_ptr<Node> mNext;
};
