#pragma once

template <class T>
class TreeNode
{
private:
	T *data;
	TreeNode *nextSibling;
	TreeNode *firstChild;

public:
	TreeNode(T data);
	~TreeNode();
    void addSibling(TreeNode *newSibling);
    void addChild(TreeNode *newChild);
    void print(TraversalMethod method);

    T *getData() const;
};

