#pragma once
#include<iostream>
#include <string>
#include <vector>
#include <deque>
#include "Node.h"
using namespace std;
 

class Maze {

public:
	int size;
	Node * source;
	Node * goal;
	deque<Node *> queue;
	deque<Node *> nodes;


	Maze(int size) :size(size) {

		for (int i = 0; i < size*size; i++) {
			nodes.push_back(new Node());
		}

		this->defineNodes();

	}

	void defineNodes();
	void BFS();
	void Astar();


};
