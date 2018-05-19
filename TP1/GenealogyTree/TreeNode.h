#pragma once

#include "NTree.h"

template <class T>
class TreeNode
{
private:
	T *data;
	TreeNode *nextSibling;
	TreeNode *firstChild;

public:
	TreeNode();
	~TreeNode();
    void print(TraversalMethod method);

    T *getData() const;
};

