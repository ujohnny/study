#include "treeElement.h"
#include "treeIterator.h"

TreeIterator::TreeIterator() 
{
}

TreeIterator::TreeIterator(boost::shared_ptr<TreeElement> element
	, bool const isBegin)
{
	//i dont like this constructor
	if (isBegin) {
		while (element->getLeftChild()) {
			element = element->getLeftChild();
		}
	} else {
		while (element->getRightChild()) {
			element = element->getRightChild();
		}
	}
	mCurrentElement = element;
}

int TreeIterator::operator*() {
	return mCurrentElement->getValue();
}

TreeIterator& TreeIterator::operator++() {
	if (mCurrentElement->getRightChild()) {
		mCurrentElement = mCurrentElement->getRightChild();
		while (mCurrentElement->getLeftChild()) {
			mCurrentElement = mCurrentElement->getLeftChild();
		}
	} else {
		if (mCurrentElement->getParent()) {
			boost::shared_ptr<TreeElement> parent = mCurrentElement->getParent();
			while (parent->getRightChild() == mCurrentElement) {
				mCurrentElement = parent;
				parent = parent->getParent();
			}
			mCurrentElement = parent;
		}
	}
	return *this;
}

TreeIterator& TreeIterator::operator--() {
	if (mCurrentElement->getLeftChild()) {
		mCurrentElement = mCurrentElement->getLeftChild();
		while (mCurrentElement->getRightChild()) {
			mCurrentElement = mCurrentElement->getRightChild();
		}
	} else {
		if (mCurrentElement->getParent()) {
			boost::shared_ptr<TreeElement> parent = mCurrentElement->getParent();
			while (parent->getLeftChild() == mCurrentElement) {
				mCurrentElement = parent;
				parent = parent->getParent();
			}
			mCurrentElement = parent;
		}
	}
	return *this;
}

TreeIterator TreeIterator::operator++(int) {
	TreeIterator result = (*this);
	++(*this);
	return result;
}

TreeIterator TreeIterator::operator--(int) {
	TreeIterator result = (*this);
	--(*this);
	return result;
}

const bool TreeIterator::operator==(TreeIterator i) const {
	return (i.getCurrentElement() == mCurrentElement) ? true : false;
}

const bool TreeIterator::operator!=(TreeIterator i) const {
	return (i.getCurrentElement() == mCurrentElement) ? false : true;
}
