 #pragma once

#include <vector>
#include <algorithm>

using namespace std;

enum TraversalMethod { PRE_ORDER, IN_ORDER, POST_ORDER };
template <class T>
class TreeNode
{
protected:
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

	TreeNode<T>* findNode(T data);

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
		cout << data << endl;

		for (const auto& currentNode : children)
			currentNode->print(method);

		break;
	case IN_ORDER:
		cout << "In order traversal." << endl;

		break;
	case POST_ORDER:
		for (const auto& currentNode : children)
			currentNode->print(method);

		cout << data << endl;

		break;
	}
}

template<class T>
int TreeNode<T>::getHeight()
{
	if (children.empty())
		return 0;

	int maximalDepth = 0;

	for (const auto& currentNode : children) {
		maximalDepth = std::max(maximalDepth, currentNode->getHeight());
	}

	return maximalDepth + 1;
}

template<class T>
inline TreeNode<T>* TreeNode<T>::findNode(T dataToFind)
{
	if (data == dataToFind)
		return this;
	else {
		for (const auto& currentNode : children) {
			TreeNode<T>* foundNode = currentNode->findNode(dataToFind);

			if (foundNode != nullptr)
				return foundNode;
		}
	}

	return nullptr;
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