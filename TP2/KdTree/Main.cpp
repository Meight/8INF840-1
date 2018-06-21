// Main.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "KdTree.h"
#include <iostream>

int main() {
	KdTree<2,int>* t = new KdTree<2,int>();

	int a[2] = { 40,45 };
	int b[2] = { 70,10 };
	int c[2] = { 69,50 };
	int d[2] = { 66,85 };
	int e[2] = { 85,90 };
	int f[2] = { 15,70 };

	t->insert(a);
	t->insert(b);
	t->insert(c);
	t->insert(d);
	t->insert(e);
	t->insert(f);

	t->printTree();

	std::cout << "\n";

	int g[2] = { 85,90 };
	int h[2] = { 70,80 };

	std::cout << "recherche de (" << g[0] << "," << g[1] << "): " << (t->search(g) ? "true\n" : "false\n");
	std::cout << "recherche de (" << h[0] << "," << h[1] << "): " << (t->search(h) ? "true\n" : "false\n");

	std::cout << "\n";

	int i[2] = { 10,10 };
	
	int* x = t->nearestNeighbor(h);
	std::cout << "plus proche voisin de (" << h[0] << "," << h[1] << "): (" << x[0] << "," << x[1] << ")\n";
	delete[] x;
	x = t->nearestNeighbor(i);
	std::cout << "plus proche voisin de (" << i[0] << "," << i[1] << "): (" << x[0] << "," << x[1] << ")\n";

	std::cout << "\n";

	t->remove(a);
	std::cout << "suppression de (" << a[0] << "," << a[1] << ")\nnouvel arbre:\n";
	t->printTree();

	system("PAUSE");
	return 0;
}