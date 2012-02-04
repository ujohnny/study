#pragma once

#include <boost/shared_ptr.hpp>

class TreeElement;

class TreeIterator
{
public:
	TreeIterator();
	TreeIterator(boost::shared_ptr<TreeElement> element, bool isBegin);
	
	int& operator*();
	TreeIterator& operator++();
	TreeIterator& operator--();
	TreeIterator operator++(int);
	TreeIterator operator--(int);
	const bool operator==(TreeIterator i) const;
	const bool operator!=(TreeIterator i) const;
	
	inline boost::shared_ptr<TreeElement> getCurrentElement() {
		return mCurrentElement;
	}

private:
	boost::shared_ptr<TreeElement> mEnd;
	boost::shared_ptr<TreeElement> mCurrentElement;
	//std::stack<boost::shared_ptr<TreeElement> > mHistoryStack;

};

