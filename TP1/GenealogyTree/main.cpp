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
	
	Person grandpa = Male("Grand-père", "Papy", 1994, BROWN);
	Person person2 = Person("Grand-mère", "Mamie", 1994, BROWN);
	Person dad = Male("Père", "Papa", 1994, BROWN);
	Person uncle = Male("Oncle", "Tonton", 1994, BROWN);
	Person son1 = Male("Fils", "Fils 1", 1994, BROWN);
	Person son2 = Female("Fille", "Fille 1", 1994, BROWN);

	FamilyTree familyTree = FamilyTree(grandpa);

	familyTree.addMember(grandpa, dad);
	familyTree.addMember(grandpa, uncle);
	familyTree.addMember(dad, son1);
	familyTree.addMember(dad, son2);

	familyTree.listDescendants(dad, PRE_ORDER);

	getchar();

    return 1;
}

