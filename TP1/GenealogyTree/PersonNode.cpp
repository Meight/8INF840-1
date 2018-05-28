#include "stdafx.h"
#include "PersonNode.h"
#include "stdio.h"

using namespace std;

PersonNode::PersonNode(Person &personData) : TreeNode<Person>(personData) { }

PersonNode::~PersonNode()
{
}

void PersonNode::accumulateAges(float &currentSum, int &numberOfNodes)
{
	cout << "Accumulating age of " << data.getFirstName() << " which is " << data.getAge() << endl;
	currentSum += data.getAge();
	numberOfNodes++;

	for (const auto& currentNode : children)
		static_cast<PersonNode*>(currentNode)->accumulateAges(currentSum, numberOfNodes);
}

void PersonNode::listByEyesColor(Color color, TraversalMethod method)
{
	switch (method) {
	case PRE_ORDER:
		if (data.getEyeColor() == color)
			cout << data << endl;

		for (const auto& currentNode : children)
			static_cast<PersonNode*>(currentNode)->listByEyesColor(color, method);

		break;
	case IN_ORDER:
		cout << "In order traversal." << endl;

		break;
	case POST_ORDER:
		for (const auto& currentNode : children)
			static_cast<PersonNode*>(currentNode)->listByEyesColor(color, method);

		if (data.getEyeColor() == color)
			cout << data << endl;

		break;
	}
}
