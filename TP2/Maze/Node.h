#pragma once
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <deque>
using namespace std;


class Node {

public:
	int size;

	Node() : marked(false), goal(false), predecessor(nullptr), cost(0){

	}

	int distance; //distance de Manhattan par rapport au noeud cible
	int cost;  //cout de deplacement pour se rendre � ce noeud
	bool marked; // a �t� visit� ou non
	bool goal; // est un noeud objectif ou non
	int x; //"coordonn�e en largeur"
	int y;//"coordonn�e en hauteur
	list <Node *> neighbors; //liste des voisins du noeud
	Node * predecessor; //pr�decesseur du noeud

	void addNeighbor(Node * n) { neighbors.push_back(n); }
	bool mark();
	int getTotalCost();


};
