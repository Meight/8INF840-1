#pragma once
#include "NTree.h"
#include "Person.h"
#include "PersonNode.h"

class NPersonTree : public NTree<Person>
{
public:
	NPersonTree(Person &person);
	~NPersonTree();
	float getMeanAge();
};

