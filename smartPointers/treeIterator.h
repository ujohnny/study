#pragma once

#include <boost/shared_ptr.hpp>

class TreeElement;

class TreeIterator
{
public:
	TreeIterator(boost::shared_ptr<TreeElement> element, bool isBegin);

private:
	int operator*();
	TreeIterator& operator++();
	TreeIterator& operator--();

	boost::shared_ptr<TreeElement> mCurrentElement;
	//std::stack<boost::shared_ptr<TreeElement> > mHistoryStack;

};

