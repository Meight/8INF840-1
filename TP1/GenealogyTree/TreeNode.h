#pragma once

#include <vector>

using namespace std;

enum TraversalMethod { PRE_ORDER, IN_ORDER, POST_ORDER };
template <class T>
class TreeNode
{
private:
	T data;
	TreeNode<T>* parent;
	vector<TreeNode<T>*> children;

public:
	TreeNode(T data);
	~TreeNode();
    void addSibling(TreeNode<T> *newSibling);
    void addChild(TreeNode<T> *newChild);
    void print(TraversalMethod method);
	int getHeight();

    T getData() const;
};

template <class T>
TreeNode<T>::TreeNode(T nodeData) : data(nodeData), parent(NULL), children(NULL) {
}

template <class T>
TreeNode<T>::~TreeNode()
{
}

template <class T>
T TreeNode<T>::getData() const {
	return data;
}

template <class T>
void TreeNode<T>::print(TraversalMethod method) {
	switch (method) {
	case PRE_ORDER:
		cout << "Pre order traversal." << endl;
		cout << data << endl;

		break;
	case IN_ORDER:
		cout << "In order traversal." << endl;

		break;
	case POST_ORDER:
		cout << "Post order traversal." << endl;

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
void TreeNode<T>::addSibling(TreeNode<T> *newSibling) {
	if (parent != nullptr)
		parent->addChild(newSibling);
}

template <class T>
void TreeNode<T>::addChild(TreeNode<T> *newChild) {
	children.push_back(newChild);
}
