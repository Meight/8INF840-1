#pragma once

#include <vector>

using namespace std;

enum TraversalMethod { PRE_ORDER, IN_ORDER, POST_ORDER };
template <class T>
class TreeNode
{
private:
	T *data;
	TreeNode* parent;
	vector<TreeNode*> children;

public:
	TreeNode(T data);
	~TreeNode();
    void addSibling(TreeNode *newSibling);
    void addChild(TreeNode *newChild);
    void print(TraversalMethod method);
	int getHeight();

    T *getData() const;
};

