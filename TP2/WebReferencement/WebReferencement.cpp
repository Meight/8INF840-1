// WebReferencement.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "Hypergraphe.h"

int main()
{
	Hypergraphe hypergraph = Hypergraphe(BY_PAGE);

	string url = string("http://test.com");

	hypergraph.addPage(url);

	system("Pause");

    return 0;
}

