#pragma once

#include "TreeNode.h"
#include <stdio.h>
#include "Constants.h"

using namespace std;

template <class T>
class NTree
{
private:
	TreeNode<T> *root;
public:
	NTree(T data);
	~NTree();

	int getHeight();
	void print(TraversalMethod method);
	void insertNode(TreeNode<T> *parent, TreeNode<T> *node);
	void insertNodeAfterRoot(TreeNode<T> *node);
	TreeNode<T>* findNode(T data);
};

template<class T>
NTree<T>::NTree(T data)
{
	root = new TreeNode<T>(data);
}


template<class T>
NTree<T>::~NTree()
{
}

template<class T>
int NTree<T>::getHeight()
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
	else
		root->addChild(node);
}

template<class T>
inline void NTree<T>::insertNodeAfterRoot(TreeNode<T>* node)
{
	root->addChild(node);
}

template<class T>
inline TreeNode<T>* NTree<T>::findNode(T data)
{
	return root->findNode(data);
}
