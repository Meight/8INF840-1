// Main.cpp�: d�finit le point d'entr�e pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include "KdTree.h"

int main() {
	KdTree<2,int>* t = new KdTree<2,int>();


	int a[2] = { 40,45 };
	int b[2] = { 70,10 };
	int c[2] = { 69,50 };
	int d[2] = { 66,85 };
	int e[2] = { 85,90 };
	int f[2] = { 15,70 };
	int i[2] = { 8,10 };

	t->insert(a);
	t->insert(b);
	t->insert(c);
	t->insert(d);
	t->insert(e);
	t->insert(f);
	t->insert(i);

	int g[2] = { 85,90 };
	int h[2] = { 12,42 };

	std::cout << (t->search(g) ? "true\n" : "false\n");
	std::cout << (t->search(h) ? "true\n" : "false\n");


	t->remove(b);

	std::cout << *t;

	system("PAUSE");
	return 0;
}