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
	Person grandpa = Male("Grand-pere", "Tremblay", 1966, BROWN);
	Person person2 = Person("Grand-mere", "Tremblay", 1994, BROWN);
	Person dad = Male("Pere", "Tremblay", 1994, BROWN);
	Person uncle = Male("Oncle", "Tremblay", 1990, BLUE);
	Person cousin = Male("Cousin", "Tremblay", 2016, GREEN);
	Person son = Male("Fils", "Tremblay", 2007, GREEN);
	Person daughter = Female("Fille", "Tremblay", 2010, BROWN);

	FamilyTree familyTree = FamilyTree(grandpa);

	familyTree.addMember(grandpa, dad);
	familyTree.addMember(grandpa, uncle);
	familyTree.addMember(uncle, cousin);
	familyTree.addMember(dad, son);
	familyTree.addMember(dad, daughter);

	cout << "--- Height of the family tree:" << endl;

	cout << familyTree.getSize() << endl;

	cout << endl << "--- Printing family tree in pre order:" << endl;

	familyTree.print(PRE_ORDER);

	cout << endl << "--- Printing family tree in post order:" << endl;

	familyTree.print(POST_ORDER);

	cout << endl << "--- List of descendants of " << dad << ":" << endl;

	familyTree.listDescendants(dad, PRE_ORDER);

	cout << endl << "--- List of descendants of " << uncle << ":" << endl;

	familyTree.listDescendants(uncle, PRE_ORDER);

	cout << endl << "--- Mean age of the family tree:" << endl;

	cout << familyTree.getMeanAge() << endl;

	cout << endl << "--- List of all people with eye color BROWN:" << endl;

	familyTree.listByEyesColor(BROWN, PRE_ORDER);

	cout << endl << "--- List of all people with eye color GREEN:" << endl;

	familyTree.listByEyesColor(GREEN, PRE_ORDER);

	cout << endl << "--- Ancestors of " << son << " with same eye color:" << endl;

	familyTree.listAncestorsWithSameEyeColor(son);

	cout << endl << "--- Ancestors of " << daughter << " with same eye color:" << endl;

	familyTree.listAncestorsWithSameEyeColor(daughter);

	cout << endl << "--- Ancestors of " << grandpa << " with same eye color:" << endl;

	familyTree.listAncestorsWithSameEyeColor(grandpa);

	getchar();

    return 1;
}

