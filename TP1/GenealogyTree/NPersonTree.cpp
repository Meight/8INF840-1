#include "stdafx.h"
#include "NPersonTree.h"


NPersonTree::NPersonTree(Person & person) : NTree<Person>(person)
{
	root = new PersonNode(person);
}

NPersonTree::~NPersonTree()
{
}

float NPersonTree::getMeanAge()
{
	float sum = 0;
	int numberOfNodes = 0;
	static_cast<PersonNode*>(root)->accumulateAges(sum, numberOfNodes);

	return sum / numberOfNodes;
}
