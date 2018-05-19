/*
 * @author Matthieu Le Boucher <matt.leboucher@gmail.com>
 */

#ifndef TP1_NTREE_H
#define TP1_NTREE_H

#include <iostream>
#include "TreeNode.h"

using namespace std;

enum TraversalMethod { PRE_ORDER, IN_ORDER, POST_ORDER };

template <class T>
class NTree {
private:
    TreeNode<T> *root;
public:
    NTree();
    ~NTree();

    int getDepth();
    void print(TraversalMethod method);
};


#endif //TP1_NTREE_H
