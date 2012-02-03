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

	inline void setParent(boost::shared_ptr<TreeElement> element) {
		mParent = element;
	}

	inline boost::shared_ptr<TreeElement> getLeftChild() const {
		return mLeftChild;
	}

	inline boost::shared_ptr<TreeElement> getRightChild() const {
		return mRightChild;
	}

	inline boost::shared_ptr<TreeElement> getParent() const {
		return mParent;
	}

	inline int getValue() const {
		return mValue;
	}
private:
	TreeElement();

	int mValue;
	boost::shared_ptr<TreeElement> mParent;
	boost::shared_ptr<TreeElement> mLeftChild;
	boost::shared_ptr<TreeElement> mRightChild;
};

