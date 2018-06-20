// WebReferencement.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include "Hypergraphe.h"
#include <vector>


using namespace std;

int main()
{
	
	Hypergraphe hg = Hypergraphe(BY_HOST);
	hg.load("nodesTest.txt", "edgesTest.txt");
	hg.print();

	system("Pause");

    return 0;
}

