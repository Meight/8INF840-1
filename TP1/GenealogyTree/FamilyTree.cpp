/*
 * @author Matthieu Le Boucher <matt.leboucher@gmail.com>
 */

#include "stdafx.h"
#include "FamilyTree.h"
#include <stdio.h>

using namespace std;

int FamilyTree::getSize()
{
	return tree->getHeight();
}

void FamilyTree::print(TraversalMethod method)
{
	tree->print(method);
}

void FamilyTree::addMember(const Person & parent, const Person & person)
{
	TreeNode<Person>* parentNode = tree->findNode(parent);
	tree->insertNode(parentNode, new TreeNode<Person>(person));
}

void FamilyTree::addMember(const Person & person)
{
	tree->insertNode(nullptr, new TreeNode<Person>(person));
}

void FamilyTree::listDescendants(Person person, TraversalMethod method)
{
	TreeNode<Person>* associatedNode = tree->findNode(person);
	
	if (associatedNode != nullptr)
		associatedNode->print(method);
	else
		cout << Constants::ELEMENT_NOT_FOUND << endl;
}

void FamilyTree::listByEyesColor(Color color, TraversalMethod method)
{
	return tree->listByEyesColor(color, method);
}

void FamilyTree::listAncestorsWithSameEyeColor(Person person)
{
	TreeNode<Person>* associatedNode = tree->findNode(person);

	if (associatedNode != nullptr)
		static_cast<PersonNode*>(associatedNode)->listAncestorsWithSameEyeColor(associatedNode->getData().eyeColor);
	else
		cout << Constants::ELEMENT_NOT_FOUND << endl;
}

float FamilyTree::getMeanAge()
{
	return tree->getMeanAge();
}


FamilyTree::FamilyTree(Person &person)
{
	tree = new NPersonTree(person);
}


FamilyTree::~FamilyTree()
{
}
