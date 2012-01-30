#pragma once

#include "treeElement.h"
#include "treeIterator.h"

class Tree
{
public:
    Tree();
	void insert(int value);
	void remove(int value);
	const bool contains(int value) const;
	TreeIterator iterator() const;
	inline boost::shared_ptr<TreeElement> getRoot() {
		return mRoot;
	}

private:
	boost::shared_ptr<TreeElement> mRoot;

};

