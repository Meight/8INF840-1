#pragma once
#include<iostream>
#include <string>
#include <vector>
#include <deque>
#include "Node.h"
using namespace std;
 

class Maze {

public:
	int size; //le labyrinthe sera de cette taille en largeur et en longueur
	Node * source; //noeud source
	Node * goal; //noeud objectif
	deque<Node *> queue;  //file dans laquelle les noeuds à visiter seront placés
	deque<Node *> nodes; //ensemble des noeuds


	Maze(int size) :size(size) {

		for (int i = 0; i < size*size; i++) {
			nodes.push_back(new Node());
		}

		this->defineNodes();

	}
	bool containsNode(list<Node *> nodelist, Node * node);
	void defineNeighbors();
	void defineNodes();
	void BFS();
	void Astar();


};
