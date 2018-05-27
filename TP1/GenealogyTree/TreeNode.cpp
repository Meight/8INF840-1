#include "stdafx.h"
#include "TreeNode.h"

template <class T>
TreeNode<T>::TreeNode(T data)
{
	this->data = data;
}

template <class T>
TreeNode<T>::~TreeNode()
{
}

template <class T>
T *TreeNode<T>::getData() const {
    return data;
}

template <class T>
void TreeNode<T>::print(TraversalMethod method) {
    switch (method) {
        case PRE_ORDER:
            if (data != nullptr) {
                cout << data << endl;
            }

            if (firstChild != nullptr) {
                firstChild->print(method);
            }

            if (nextSibling != nullptr) {
                nextSibling->print(method);
            }

            break;
        case IN_ORDER:
            if (firstChild != nullptr) {
                firstChild->print(method);
            }

            if (data != nullptr) {
                cout << data << endl;
            }

            if (nextSibling != nullptr) {
                nextSibling->print(method);
            }

            break;
        case POST_ORDER:
            if (firstChild != nullptr) {
                firstChild->print(method);
            }

            if (nextSibling != nullptr) {
                nextSibling->print(method);
            }

            if (data != nullptr) {
                cout << data << endl;
            }

            break;
    }
}

template<class T>
int TreeNode<T>::getHeight()
{
	if (firstChild == nullptr)
		return 0;

	int maximalDepth = 0;

	for (currentNode = children.begin(); currentNode != children.end(); currentNode++, i++) {
		maximalDepth = max(maximalDepth, currentNode.getHeight());
	}

	return maximalDepth + 1;
}

template <class T>
void TreeNode<T>::addSibling(TreeNode *newSibling) {
	if (parent != nullptr)
		parent->addChild(newSibling);
}

template <class T>
void TreeNode<T>::addChild(TreeNode *newChild) {
	children.push_back(newChild);
}
