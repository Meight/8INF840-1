// WebReferencement.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include "Hypergraphe.h"


using namespace std;

int main()
{
	Hypergraphe hypergraph = Hypergraphe(BY_HOST);

	string url = string("http://www.test.com");

	hypergraph.addPage(url);

	system("Pause");

    return 0;
}

