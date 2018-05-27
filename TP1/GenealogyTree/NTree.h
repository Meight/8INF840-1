#pragma once

#include "TreeNode.h"
#include <stdio.h>

using namespace std;

template <class T>
class NTree
{
private:
	TreeNode<T> *root;
public:
	NTree();
	~NTree();

	int getDepth();
	void print(TraversalMethod method);
	void insertNode(TreeNode<T> *parent, TreeNode<T> *node);
};

