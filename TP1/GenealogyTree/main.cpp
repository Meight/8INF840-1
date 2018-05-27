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
	
	Person person = Person("Grand-père", "Papy", 1994, BROWN);
	Person person2 = Person("Grand-mère", "Mamie", 1994, BROWN);
	Person person3 = Person("Père", "Papa", 1994, BROWN);
	Person person4 = Person("Oncle", "Tonton", 1994, BROWN);
	Person person5 = Person("Fils", "Fils 1", 1994, BROWN);
	Person person6 = Person("Fils", "Fils 2", 1994, BROWN);

	FamilyTree familyTree = FamilyTree(person);

	familyTree.addMember(person, person3);
	familyTree.addMember(person, person4);
	familyTree.addMember(person3, person5);
	familyTree.addMember(person3, person6);

	familyTree.print(PRE_ORDER);

	getchar();

    return 1;
}

