#pragma once

#include <boost/shared_ptr.hpp>
#include "treeIterator.h"

class TreeElement;

class Tree
{
public:
	Tree();
	void insert(int value);
	void remove(int value);
	const bool contains(int value) const;

	TreeIterator begin();
	TreeIterator end();
	
	typedef TreeIterator iterator;

	inline boost::shared_ptr<TreeElement> getRoot() {
		return mRoot;
	}

private:
	boost::shared_ptr<TreeElement> mRoot;
};

