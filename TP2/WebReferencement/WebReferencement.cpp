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


	cout << endl << "-----------------------------------------------" << endl;
	cout << "PAGERANK:" << endl << endl;

	map<int, float> scores = hg.pageRank(0.15, 0.005);

	for (auto& s : scores) {
		cout << "Score page with id \"" << s.first << "\": " << s.second << endl;
	}



	system("Pause");

    return 0;
}

