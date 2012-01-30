#pragma once

#include <boost/shared_ptr.hpp>

class TreeElement
{
public:
	TreeElement(int value)
		: mValue(value)
	{
	}

	inline void setLeftChild(boost::shared_ptr<TreeElement> element) {
		mLeftChild = element;
	}

	inline void setRightChild(boost::shared_ptr<TreeElement> element) {
		mRightChild = element;
	}

	inline const bool hasLeftChild() const {
		return mLeftChild;
	}

	inline const bool hasRightChild() const {
		return mRightChild;
	}

	inline boost::shared_ptr<TreeElement> getLeftChild() const {
		return mLeftChild;
	}

	inline boost::shared_ptr<TreeElement> getRightChild() const {
		return mRightChild;
	}

	inline int getValue() const {
		return mValue;
	}
private:
	TreeElement();

	int mValue;
	boost::shared_ptr<TreeElement> mLeftChild;
	boost::shared_ptr<TreeElement> mRightChild;
};

