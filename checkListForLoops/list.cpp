#include "list.hpp"
#include "node.hpp"

List::List()
{
}

void List::add() {
	mSize++;
	if (!mHead) {
		mHead = boost::shared_ptr<Node>(new Node());
		return;
	}
	boost::shared_ptr<Node> tmp = mHead;
	while (tmp->getNext()) {
		tmp = tmp->getNext();
	}
	boost::shared_ptr<Node> inserted(new Node);
	tmp->setNext(inserted);
}

bool List::hasLoop() {
	boost::shared_ptr<Node> current = mHead;
	int j = 0;
	while (current->getNext()) {
		boost::shared_ptr<Node> tmp = mHead;
		int i = 0;
		bool isFirstCheck = true;
		do {
			if (!isFirstCheck) {
				tmp = tmp->getNext();
			} else {
				isFirstCheck = false;
			}

			if (current->getNext() == tmp) {
				return true;
			}
		} while (tmp != current);
		current = current->getNext();
	} 
	return false;
}

bool List::makeLoop(int beginPos, int endPos) {
	if (beginPos < endPos || beginPos > mSize) {
		return false;
	}

	boost::shared_ptr<Node> begin = mHead;
	boost::shared_ptr<Node> end = mHead;
	for (int i = 0; i < beginPos; i++) {
		if (i < endPos)
			end = end->getNext();
		begin = begin->getNext();
	}

	begin->setNext(end);
}
