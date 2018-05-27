// GenealogyTree.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "NTree.h"
#include "Person.h"

using namespace std;

int main(void)
{
	cout << "Hello" << endl;
	
	Person person = Person("Matt", "Le Boucher", 1994, BROWN);

	NTree<Person> tree = NTree<Person>(person);

	cout << "Created person: " << person << endl;

	cout << "Traversing tree: " << endl;

	//NTree<int> tree = NTree<int>(2);
	tree.print(PRE_ORDER);

	getchar();

    return 1;
}

