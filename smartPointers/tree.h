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

private:
	boost::shared_ptr<TreeElement> mRoot;

};

