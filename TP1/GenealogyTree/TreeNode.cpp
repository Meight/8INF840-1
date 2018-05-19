#include "stdafx.h"
#include "TreeNode.h"

template <class T>
TreeNode::TreeNode()
{
}

template <class T>
TreeNode::~TreeNode()
{
}

T *TreeNode::getData() const {
    return data;
}

void TreeNode::print(TraversalMethod method) {
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