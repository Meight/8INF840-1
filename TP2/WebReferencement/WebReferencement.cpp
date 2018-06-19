// WebReferencement.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include "Hypergraphe.h"
#include <vector>


using namespace std;

int main()
{
	Hypergraphe hypergraph = Hypergraphe(BY_HOST);

	vector<string> urls = { string("http://www.test.com"), string("http://www.test.com/autre_page.html"), string("http://www.autre-domaine.com") };

	for (int i = 0; i < urls.size(); i++)
		hypergraph.addPage(urls[i]);

	system("Pause");

    return 0;
}

