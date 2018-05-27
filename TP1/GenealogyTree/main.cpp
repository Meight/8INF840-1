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
	
	Person grandpa = Person("Grand-père", "Papy", 1994, BROWN);
	Person person2 = Person("Grand-mère", "Mamie", 1994, BROWN);
	Person dad = Person("Père", "Papa", 1994, BROWN);
	Person uncle = Person("Oncle", "Tonton", 1994, BROWN);
	Person son1 = Person("Fils", "Fils 1", 1994, BROWN);
	Person son2 = Person("Fils", "Fils 2", 1994, BROWN);

	FamilyTree familyTree = FamilyTree(grandpa);

	familyTree.addMember(grandpa, dad);
	familyTree.addMember(grandpa, uncle);
	familyTree.addMember(dad, son1);
	familyTree.addMember(dad, son2);

	familyTree.listDescendants(dad, PRE_ORDER);

	getchar();

    return 1;
}

