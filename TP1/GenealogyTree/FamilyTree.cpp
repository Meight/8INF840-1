/*
 * @author Matthieu Le Boucher <matt.leboucher@gmail.com>
 */

#include "stdafx.h"
#include "FamilyTree.h"


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
}

void FamilyTree::listByEyesColor(Color color)
{
}

float FamilyTree::getMeanAge()
{
	return 0.0f;
}


FamilyTree::FamilyTree(const Person &person)
{
	tree = new NTree<Person>(person);
}


FamilyTree::~FamilyTree()
{
}
