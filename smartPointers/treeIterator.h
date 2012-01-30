#pragma once

#include <boost/shared_ptr.hpp>
#include <stack>

class TreeElement;

class TreeIterator
{
public:
	TreeIterator(boost::shared_ptr<TreeElement> root);
	const bool hasNext();
	boost::shared_ptr<TreeElement> next();

private:
	TreeIterator();

	inline void setCurrentElement(boost::shared_ptr<TreeElement> element) {
		mCurrentElement = element;
	}

	void goDown();

	boost::shared_ptr<TreeElement> mCurrentElement;
	std::stack<boost::shared_ptr<TreeElement> > mHistoryStack;

	bool mIsGoingDownLeft;
	bool mIsGoingDownRight;
};

