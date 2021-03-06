// WebReferencement.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include "Hypergraphe.h"
#include <vector>
#include <set>
#include <algorithm>
#include <functional>


using namespace std;

int main()
{
	Hypergraphe hg = Hypergraphe(BY_PAGE);
	hg.load("nodesTest.txt", "edgesTest.txt");
	cout << "Done loading" << endl;

	hg.print();

	// Declaring the type of Predicate that accepts 2 pairs and return a bool
	typedef std::function<bool(std::pair<int, float>, std::pair<int, float>)> Comparator;

	// Defining a lambda function to compare two pairs. It will compare two pairs using second field
	Comparator compFunctor =
		[](std::pair<int, float> elem1, std::pair<int, float> elem2)
	{
		return elem1.second > elem2.second;
	};

	cout << endl << "-----------------------------------------------" << endl;
	cout << "INDEGREE:" << endl << endl;

	map<int, float> inDegreeScores = hg.inDegree();
	for (auto& element : inDegreeScores) {
		cout << "Page " << element.first << " with score " << element.second << endl;
	}

	cout << endl << "-----------------------------------------------" << endl;
	cout << "PAGERANK:" << endl << endl;
	int amountOfPagesToPrint = 10;

	map<int, float> scores = hg.pageRank(0.15, 0.005);

	// Declaring a set that will store the pairs using above comparision logic
	std::set<std::pair<int, float>, Comparator> sortedScores(
		scores.begin(), scores.end(), compFunctor);

	for (std::pair<int, float> element : sortedScores)
		if (amountOfPagesToPrint > 0) {
			cout << "Page " << element.first << " with score " << element.second << endl;
			amountOfPagesToPrint--;
		}
		else
			break;

	system("Pause");

    return 0;
}

