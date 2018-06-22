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
	int cost;  //cout de deplacement pour se rendre à ce noeud
	bool marked; // a été visité ou non
	bool goal; // est un noeud objectif ou non
	int x; //"coordonnée en largeur"
	int y;//"coordonnée en hauteur
	list <Node *> neighbors; //liste des voisins du noeud
	Node * predecessor; //prédecesseur du noeud

	void addNeighbor(Node * n) { neighbors.push_back(n); }
	bool mark();
	int getTotalCost();


};
