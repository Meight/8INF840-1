#include "stdafx.h"
#include "NTree.h"
#include "Constants.h"

template<class T>
NTree<T>::NTree()
{
}

template<class T>
NTree<T>::~NTree()
{
}

template<class T>
int NTree<T>::getDepth()
{
	return (root != nullptr) ? root->getHeight() : 0;
}

template<class T>
void NTree<T>::print(TraversalMethod method)
{
	if (root != nullptr)
		root->print(method);
	else
		cout << Constants::EMPTY_TREE << endl;
}

template<class T>
void NTree<T>::insertNode(TreeNode<T> *parent, TreeNode<T> *node)
{
	if (parent != nullptr)
		parent->addChild(node);
}
