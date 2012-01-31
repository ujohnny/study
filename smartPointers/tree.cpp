#include "tree.h"

Tree::Tree()
{
}

void Tree::insert(int value) {
	boost::shared_ptr<TreeElement> elementToInsert(new TreeElement(value));

	if (!mRoot) {
		mRoot = elementToInsert;
		return;
	}

	boost::shared_ptr<TreeElement> tmp = mRoot;
	while (1) {
		if (value < tmp.get()->getValue()) {
			if (tmp.get()->getLeftChild()) {
				tmp = tmp.get()->getLeftChild();
			} else {
				tmp.get()->setLeftChild(elementToInsert);
				return;
			}
		} else {
			if (tmp.get()->getRightChild()) {
				tmp = tmp.get()->getRightChild();
			} else {
				tmp.get()->setRightChild(elementToInsert);
				return;
			}
		}

	}
}

void Tree::remove(int value) {

}

const bool Tree::contains(int value) const {

}

TreeIterator Tree::iterator() const {
	return TreeIterator(mRoot);
}
