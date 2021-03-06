
#include <iostream>
#include <stdio.h>      
#include <stdlib.h>   
#include <time.h>   
#include <cmath> 
#include "stdafx.h"
#include "Maze.h"

using namespace std;



void Maze::defineNodes() {
	int numberofnodes = this->size*this->size;
	for (int i = 0; i < numberofnodes;i++) {
		nodes[i]->x = i % size;
		nodes[i]->y = (i - i % size) / size;
	}

	this->defineNeighbors();

	int startingpoint = rand() % numberofnodes;
	int endingpoint = rand() % numberofnodes;
	
	source = nodes[startingpoint];
	goal = nodes[endingpoint];

	for (int i = 0; i < numberofnodes; i++) {
		if (goal == nodes[i]) {
			nodes[i]->distance = 0;
			nodes[i]->cost = 0;
		}
		else {
			nodes[i]->distance = abs(nodes[i]->x-goal->x)+abs(nodes[i]->y - goal->y);
			nodes[i]->cost = nodes[i]->distance;
		}
	}
	cout << "Starting point : " << source->x << " " << source->y << endl << "Ending point : " << goal->x << " " << goal->y << endl;

}


void Maze::defineNeighbors() {
	list<Node *> connectednodes;
	int numberofnodes = size * size;
	connectednodes.push_front(nodes[0]);
	for (int i = 0; i < numberofnodes; i++) {
		if (i - 1 >= 0 && i%size != 0 && !containsNode(connectednodes,nodes[i-1])) {
			nodes[i]->addNeighbor(nodes[i - 1]);
			nodes[i - 1]->addNeighbor(nodes[i]);
			connectednodes.push_front(nodes[i - 1]);
		}
		if (i + 1 < numberofnodes && (i + 1) % size != 0 && !containsNode(connectednodes, nodes[i + 1])) {
			nodes[i]->addNeighbor(nodes[i + 1]);
			nodes[i + 1]->addNeighbor(nodes[i]);
			connectednodes.push_front(nodes[i +1]);
		}
		if (i - size >= 0 && !containsNode(connectednodes, nodes[i - size])) {
			nodes[i]->addNeighbor(nodes[i - size]);
			nodes[i - size]->addNeighbor(nodes[i]);
			connectednodes.push_front(nodes[i - size]);
		}
		if (i + size < numberofnodes && !containsNode(connectednodes, nodes[i + size])) {
			nodes[i]->addNeighbor(nodes[i + size]);
			nodes[i + size]->addNeighbor(nodes[i]);
			connectednodes.push_front(nodes[i +size]);
		}
	}
}

bool Maze::containsNode(list<Node *> nodelist, Node * node) {
	if (nodelist.empty()) {
		return false;
	}
	list <Node *>::iterator current, last;
	current = nodelist.begin();
	last = nodelist.end();
	for (; current != last; ++current) {
		if ((*current)== node) {
			return true;
		}
	}
	return false;
}


void Maze::BFS() {

	bool finished = false;
	int count = -1;
	queue.push_front(source);
	Node * current;
	list <Node *>::iterator currentneighbor, lastneighbor;
	
	while (!finished) {
		current = queue.back();
		if (current == goal) {
			finished = true;
			break;
		}
		currentneighbor = current->neighbors.begin();
		lastneighbor = current->neighbors.end();
		for (; currentneighbor != lastneighbor; ++currentneighbor) {
			if ((*currentneighbor)->marked == false) {
				queue.push_front(*currentneighbor);
			}
		}
		
		current->mark();
		queue.pop_back();
		cout << "Noeud " << current->x << "  " << current->y << "  visite"<<endl;
		count++;
	}
	cout << endl << "Vous etes arrive au but en " << count << " deplacements" << endl;
}

void Maze::Astar() {
	bool finished = false;
	int totalcost = 0;
	int count = -1;
	int movecost = 1;
	int bestcost;
	queue.push_front(source);
	Node * current;
	list <Node *>::iterator currentneighbor, lastneighbor;
	deque <Node *>::iterator currentqueue, lastqueue;
	int iteratorposition,currentposition;

	while (!finished) {
		count++;
		currentqueue = queue.begin();
		lastqueue = queue.end();
		iteratorposition = 0;
		currentposition = 0;
		current = (*currentqueue);
		bestcost = (*currentqueue)->getTotalCost();
		for (; currentqueue != lastqueue; ++currentqueue) {
			if ((*currentqueue)->getTotalCost()<bestcost) {
				current = (*currentqueue);
				bestcost = (*currentqueue)->getTotalCost();
				currentposition = iteratorposition;
			}
			iteratorposition++;
		}
		if (current == goal) {
			finished = true;
			break;
		}
		current->mark();
		queue.erase(queue.begin()+currentposition);
		cout << "Noeud " << current->x << "  " << current->y << "  visite" << endl;
		

		/*currentneighbor = current->neighbors.begin();
		lastneighbor = current->neighbors.end();
		next = (*currentneighbor);
		availableneighbors = 0;
		for (; currentneighbor != lastneighbor; ++currentneighbor) {
			if ((*currentneighbor)->marked == false) {
				(*currentneighbor)->predecessor = current;
				(*currentneighbor)->cost =
				availableneighbors++;
			}
		}*/

		currentneighbor = current->neighbors.begin();
		lastneighbor = current->neighbors.end();
		for (; currentneighbor != lastneighbor; ++currentneighbor) {
			if ((*currentneighbor)->marked == false) {
				if ((*currentneighbor)->predecessor != nullptr && (*currentneighbor)->getTotalCost()<(*currentneighbor)->distance+movecost+totalcost) {
					(*currentneighbor)->predecessor = current;
					(*currentneighbor)->cost = movecost + totalcost;
				}
				else {
					queue.push_front(*currentneighbor);
					(*currentneighbor)->predecessor = current;
					(*currentneighbor)->cost = movecost + totalcost;
				}
			}
		}
	}
	cout << endl << "Vous etes arrive au but en " << count << " deplacements" << endl;
}


int abs(int x){
	if (x < 0) return -x;
	else return x;
}





