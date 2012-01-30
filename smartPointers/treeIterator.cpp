#include "treeElement.h"
#include "treeIterator.h"

TreeIterator::TreeIterator(boost::shared_ptr<TreeElement> root)
	: mCurrentElement(root)
	, mIsGoingDownLeft(true)
	, mIsGoingDownRight(false)
{
}

const bool TreeIterator::hasNext() {
	//may be it'll good if use memento here

	bool tempLeft = mIsGoingDownLeft;
	bool tempRight = mIsGoingDownRight;
	boost::shared_ptr<TreeElement> tempCurrent = mCurrentElement;
	std::stack<boost::shared_ptr<TreeElement> > tempStack = mHistoryStack;

	bool hasNext = static_cast<bool>(next());

	mIsGoingDownLeft = tempLeft;
	mIsGoingDownRight = tempRight;
	mCurrentElement = tempCurrent;
	mHistoryStack = tempStack;

	return hasNext;
}

boost::shared_ptr<TreeElement> TreeIterator::next() {

	if (mIsGoingDownLeft || mIsGoingDownRight) {
		goDown();
		mHistoryStack.push(mCurrentElement);
		return mCurrentElement;
	} else {
		boost::shared_ptr<TreeElement> previous;
		boost::shared_ptr<TreeElement> current;
		do {
			previous = mHistoryStack.top();
			mHistoryStack.pop();

			if (mHistoryStack.empty())
				return boost::shared_ptr<TreeElement>();

			current = mHistoryStack.top();

			mCurrentElement = current;
			if (current.get()->getLeftChild() == previous) {
				if (mCurrentElement.get()->hasRightChild())
					mIsGoingDownRight = true;
				return mCurrentElement;
			}
		} while (!current.get()->hasRightChild() ||
				 current.get()->getRightChild() == previous); //bug check current->right and prev

		mHistoryStack.push(mCurrentElement);

		mIsGoingDownRight = true;
		goDown();
		return mCurrentElement;
	}

}

void TreeIterator::goDown() {
	if (mIsGoingDownRight) {
		mCurrentElement = mCurrentElement.get()->getRightChild();
		if (mCurrentElement.get()->hasLeftChild()) {
			mIsGoingDownLeft = true;
			mIsGoingDownRight = false;
		}
	}

	if (mIsGoingDownLeft)
		while (mCurrentElement.get()->hasLeftChild()) {
			mHistoryStack.push(mCurrentElement);
			mCurrentElement = mCurrentElement.get()->getLeftChild();
		}

	if (mCurrentElement.get()->getRightChild()) {
		mIsGoingDownRight = true;
		mIsGoingDownLeft = false;
	}

	if (!mCurrentElement.get()->getLeftChild() && !mCurrentElement.get()->getRightChild()) {
		mIsGoingDownLeft = false;
		mIsGoingDownRight = false;
	}
}
