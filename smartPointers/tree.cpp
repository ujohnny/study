#include "tree.h"
#include "treeElement.h"

Tree::Tree()
{
}

TreeIterator Tree::begin() {
	return TreeIterator(mRoot, true);
}

TreeIterator Tree::end() {
	return TreeIterator(mRoot, false);
}

void Tree::insert(int value) {
	boost::shared_ptr<TreeElement> elementToInsert(new TreeElement(value));

	if (!mRoot) {
		mRoot = elementToInsert;
		return;
	}

	boost::shared_ptr<TreeElement> tmp = mRoot;
	while (1) {
		if (value < tmp->getValue()) {
			if (tmp->getLeftChild()) {
				tmp = tmp->getLeftChild();
			} else {
				tmp->setLeftChild(elementToInsert);
				elementToInsert->setParent(tmp);
				return;
			}
		} else {
			if (tmp->getRightChild()) {
				tmp = tmp->getRightChild();
			} else {
				tmp->setRightChild(elementToInsert);
				elementToInsert->setParent(tmp);
				return;
			}
		}

	}
}

void Tree::remove(int value) {

}

const bool Tree::contains(int value) const {

}
