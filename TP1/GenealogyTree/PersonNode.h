#pragma once
#include "TreeNode.h"
#include "Person.h"

class PersonNode : public TreeNode<Person>
{
public:
	PersonNode(Person &data);
	~PersonNode();

	void accumulateAges(float &currentSum, int &numberOfNodes);
};

