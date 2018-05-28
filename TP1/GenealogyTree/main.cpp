// GenealogyTree.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "FamilyTree.h"
#include "Person.h"

using namespace std;

int main(void)
{
	cout << "Hello" << endl;
	
	Person grandpa = Male("Grand-pere", "Tremblay", 1966, BROWN);
	Person person2 = Person("Grand-mere", "Tremblay", 1994, BROWN);
	Person dad = Male("Pere", "Tremblay", 1994, BROWN);
	Person uncle = Male("Oncle", "Tremblay", 1990, BLUE);
	Person son = Male("Fils", "Tremblay", 2007, GREEN);
	Person daughter = Female("Fille", "Tremblay", 2010, BROWN);

	FamilyTree familyTree = FamilyTree(grandpa);

	familyTree.addMember(grandpa, dad);
	familyTree.addMember(grandpa, uncle);
	familyTree.addMember(dad, son);
	familyTree.addMember(dad, daughter);

	familyTree.listDescendants(dad, PRE_ORDER);

	cout << "Mean age: " << familyTree.getMeanAge() << endl;

	familyTree.listByEyesColor(BROWN, PRE_ORDER);

	cout << "Ancestors of " << daughter << " with same eye color:" << endl;

	familyTree.listAncestorsWithSameEyeColor(daughter);

	cout << "Ancestors of " << grandpa << " with same eye color:" << endl;

	familyTree.listAncestorsWithSameEyeColor(grandpa);

	getchar();

    return 1;
}

