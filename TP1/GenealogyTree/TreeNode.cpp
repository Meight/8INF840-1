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

template <class T>
void TreeNode<T>::addSibling(TreeNode *newSibling) {
    if (nextSibling != nullptr)
        nextSibling->addSibling(newSibling);
    else
        nextSibling = newSibling;
}

template <class T>
void TreeNode<T>::addChild(TreeNode *newChild) {
    if (firstChild != nullptr)
        firstChild->addSibling(newChild);
    else
        firstChild = newChild;
}
