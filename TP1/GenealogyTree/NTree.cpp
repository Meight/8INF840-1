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
	return 0;
}

template<class T>
void NTree<T>::print(TraversalMethod method)
{
	if (root != nullptr)
		root->print(method);
	else
		cout << Constants::EMPTY_TREE << endl;
}
