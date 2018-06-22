#include <string>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include "stdafx.h"
#include "Node.h"

bool Node::mark() {//deque<Node *>
	//&queue

	if (this == nullptr || this->marked == true) {
		return false;
	}

	this->marked = true;
	if (this->goal) {
		return true;
	}
	/*
	list <Node *>::iterator currentnode, lastnode;
	currentnode = neighbors.begin();
	lastnode = neighbors.end();
	for (; currentnode != lastnode; ++currentnode) {
		if ((*currentnode)->marked == false){
			queue.push_back (*currentnode);
		}
	}*/
	return false;
}

int Node::getTotalCost() {
	return cost + distance;
}